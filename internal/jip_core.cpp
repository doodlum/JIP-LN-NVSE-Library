#include "internal/jip_core.h"

ExpressionEvaluatorUtils s_expEvalUtils;

_WriteRecord WriteRecord;
_WriteRecordData WriteRecordData;
_GetNextRecordInfo GetNextRecordInfo;
_ReadRecordData ReadRecordData;
_ResolveRefID ResolveRefID;
_WriteRecord8 WriteRecord8;
_WriteRecord16 WriteRecord16;
_WriteRecord32 WriteRecord32;
_WriteRecord64 WriteRecord64;
_ReadRecord8 ReadRecord8;
_ReadRecord16 ReadRecord16;
_ReadRecord32 ReadRecord32;
_ReadRecord64 ReadRecord64;
_GetCmdByOpcode GetCmdByOpcode;
_GetPluginInfoByName GetPluginInfoByName;
_GetStringVar GetStringVar;
_AssignString AssignString;
_CreateArray CreateArray;
_CreateStringMap CreateStringMap;
_AssignCommandResult AssignCommandResult;
_SetElement SetElement;
_AppendElement AppendElement;
_GetArraySize GetArraySize;
_LookupArrayByID LookupArrayByID;
_GetElement GetElement;
_GetElements GetElements;
_GetContainerType GetContainerType;
_ArrayHasKey ArrayHasKey;
_ExtractArgsEx ExtractArgsEx;
_ExtractFormatStringArgs ExtractFormatStringArgs;
_CallFunction CallFunction;
//_GetFunctionParams GetFunctionParams;
_CaptureLambdaVars CaptureLambdaVars;
_UncaptureLambdaVars UncaptureLambdaVars;
_InventoryRefCreate InventoryRefCreate;
_InventoryRefGetForID InventoryRefGetForID;

DIHookControl *g_DIHookCtrl;
UInt8 *g_numPreloadMods;

_UIOInjectComponent UIOInjectComponent = nullptr;

ModelLoader *g_modelLoader;
DataHandler *g_dataHandler;
LoadedReferenceCollection *g_loadedReferences;
InterfaceManager *g_interfaceManager;
OSGlobals *g_OSGlobals;
TES *g_TES;
PlayerCharacter *g_thePlayer;
NiCamera *g_mainCamera;
void *g_scrapHeapQueue;
FontManager *g_fontManager;
OSInputGlobals *g_inputGlobals;
TileMenu **g_tileMenuArray;
HUDMainMenu *g_HUDMainMenu;
ConsoleManager *g_consoleManager;
NiNode *s_pc1stPersonNode = nullptr, *g_cursorNode;
ShadowSceneNode *g_shadowSceneNode;
TESObjectREFR *s_tempPosMarker;
float g_screenResConvert, g_screenWidth, g_screenHeight;
const char *g_terminalModelDefault;
TESObjectWEAP *g_fistsWeapon;
TESObjectACTI *g_ashPileACTI, *g_gooPileACTI;
TESGlobal *g_gameYear, *g_gameMonth, *g_gameDay, *g_gameHour, *g_timeScale;
TESObjectMISC *g_capsItem;
TESImageSpaceModifier *g_getHitIMOD, *g_explosionInFaceIMOD;
UInt32 s_mainThreadID, s_initialTickCount;

const bool kInventoryType[] =
{
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0
};

alignas(16) const UInt8 kMaterialConvert[] =
{
	kMaterial_Stone,
	kMaterial_Cloth,
	kMaterial_Dirt,
	kMaterial_Glass,
	kMaterial_Grass,
	kMaterial_Metal,
	kMaterial_Organic,
	kMaterial_Organic,
	kMaterial_Water,
	kMaterial_Wood,
	kMaterial_Stone,
	kMaterial_Metal,
	kMaterial_Wood,
	kMaterial_Metal,
	kMaterial_Metal,
	kMaterial_Metal,
	kMaterial_HollowMetal,
	kMaterial_HollowMetal,
	kMaterial_Dirt,
	kMaterial_Stone,
	kMaterial_Metal,
	kMaterial_Metal,
	kMaterial_HollowMetal,
	kMaterial_HollowMetal,
	kMaterial_Glass,
	kMaterial_HollowMetal,
	kMaterial_Metal,
	kMaterial_Metal,
	kMaterial_HollowMetal,
	kMaterial_HollowMetal,
	kMaterial_Wood,
	kMaterial_Wood
};

const char kDaysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

const char kMenuIDJumpTable[] =
{
	0, 1, 2, 3, -1, -1, 4, 5, 6, -1, -1, 7, 8, 9, -1, 10, -1, -1, -1, -1, -1, -1, 11, -1, -1, 12, 13, -1, -1, -1, 
	-1, -1, -1, -1, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 16, -1, -1, 17, -1, 18, 19, 20, 21, 22, 
	23, 24, 25, 26, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 27, 28, 29, 30, -1, -1, 31, 32, 33, 34, 35
};

UInt32 s_serializedFlags = 0;

__declspec(naked) void __vectorcall ResultVars::Set(__m128 values)
{
	__asm
	{
		andps	xmm0, PS_XYZ0Mask
		cvtps2pd	xmm1, xmm0
		shufps	xmm0, xmm0, 0xFE
		cvtps2pd	xmm0, xmm0
		mov		eax, [ecx]
		movq	qword ptr [eax+8], xmm1
		mov		eax, [ecx+4]
		movhpd	qword ptr [eax+8], xmm1
		mov		eax, [ecx+8]
		movq	qword ptr [eax+8], xmm0
		retn
	}
}

__declspec(naked) void __vectorcall ResultVars::Set(__m128 values, const __m128 modifier)
{
	__asm
	{
		mulps	xmm0, xmm1
		cvtps2pd	xmm1, xmm0
		shufps	xmm0, xmm0, 0xFE
		cvtps2pd	xmm0, xmm0
		mov		eax, [ecx]
		movq	qword ptr [eax+8], xmm1
		mov		eax, [ecx+4]
		movhpd	qword ptr [eax+8], xmm1
		mov		eax, [ecx+8]
		movq	qword ptr [eax+8], xmm0
		retn
	}
}

__declspec(noinline) TempFormList *GetTempFormList()
{
	thread_local TempObject<TempFormList> s_tempFormList(0x40);
	s_tempFormList().Clear();
	return *s_tempFormList;
}

__declspec(noinline) TempElements *GetTempElements()
{
	thread_local TempObject<TempElements> s_tempElements(0x100);
	s_tempElements().Clear();
	return *s_tempElements;
}

TempObject<UnorderedMap<const char*, UInt32>> s_strRefs;

UInt32 __fastcall StringToRef(char *refStr)
{
	UInt32 *findStr;
	if (!s_strRefs().Insert(refStr, &findStr)) return *findStr;
	*findStr = 0;
	char *colon = FindChr(refStr, ':');
	if (colon)
	{
		UInt8 modIdx;
		if (colon != refStr)
		{
			*colon = 0;
			modIdx = g_dataHandler->GetModIndex(refStr);
			*colon = ':';
			if (modIdx == 0xFF) return 0;
		}
		else modIdx = 0xFF;
		*findStr = (modIdx << 24) | HexToUInt(colon + 1);
		return *findStr;
	}
	return ResolveRefID(HexToUInt(refStr), findStr) ? *findStr : 0;
}

__declspec(noinline) InventoryItemsMap *GetInventoryItemsMap()
{
	thread_local TempObject<InventoryItemsMap> s_inventoryItemsMap(0x40);
	s_inventoryItemsMap().Clear();
	return *s_inventoryItemsMap;
}

bool GetInventoryItems(TESObjectREFR *refr, UInt8 typeID, InventoryItemsMap *invItemsMap)
{
	TESContainer *container = refr->baseForm->GetContainer();
	if (!container) return false;
	ExtraContainerChanges::EntryDataList *entryList = refr->GetContainerChangesList();
	if (!entryList) return false;

	TESContainer::FormCount *formCount;
	TESForm *item;
	SInt32 contCount, countDelta;
	ContChangesEntry *entry;

	auto contIter = container->formCountList.Head();
	do
	{
		if (!(formCount = contIter->data)) continue;
		item = formCount->form;
		if ((typeID && (item->typeID != typeID)) || (item->typeID == kFormType_TESLevItem) || invItemsMap->HasKey(item))
			continue;
		contCount = container->GetCountForForm(item);
		if (entry = entryList->FindForItem(item))
		{
			countDelta = entry->countDelta;
			if (entry->HasExtraLeveledItem())
				contCount = countDelta;
			else contCount += countDelta;
		}
		if (contCount > 0)
			invItemsMap->Emplace(item, contCount, entry);
	}
	while (contIter = contIter->next);

	auto xtraIter = entryList->Head();
	do
	{
		if (!(entry = xtraIter->data)) continue;
		item = entry->type;
		if ((typeID && (item->typeID != typeID)) || invItemsMap->HasKey(item))
			continue;
		countDelta = entry->countDelta;
		if (countDelta > 0)
			invItemsMap->Emplace(item, countDelta, entry);
	}
	while (xtraIter = xtraIter->next);

	return !invItemsMap->Empty();
}

__declspec(naked) void __fastcall ShowItemMessage(TESForm *item, const char *msgStr)
{
	__asm
	{
		push	ebp
		mov		ebp, esp
		push	edx
		call	TESForm::GetTheName
		cmp		[eax], 0
		jz		done
		sub		esp, 0x70
		mov		edx, eax
		lea		ecx, [ebp-0x74]
		call	StrCopy
		mov		[eax], ' '
		mov		edx, [ebp-4]
		lea		ecx, [eax+1]
		call	StrCopy
		mov		word ptr [eax], '.'
		push	0
		push	0x40000000
		push	0
		push	0x10208E0
		push	0
		lea		eax, [ebp-0x74]
		push	eax
		CALL_EAX(0x7052F0)
	done:
		leave
		retn
	}
}

struct alignas(16) RayCastData
{
	AlignedVector4	pos0;		// 00	
	AlignedVector4	pos1;		// 10
	UInt8			byte20;		// 20
	UInt8			pad21[3];	// 21
	UInt8			layerType;	// 24
	UInt8			filterFlags;// 25
	UInt8			pad26[2];	// 26
	UInt32			unk28[6];	// 28
	float			flt40;		// 40
	UInt32			unk44[19];	// 44
	AlignedVector4	vector90;	// 90
	UInt32			unkA0[3];	// A0
	UInt8			byteAC;		// AC
	UInt8			padAD[3];	// AD
};
static_assert(sizeof(RayCastData) == 0xB0);

__declspec(naked) NiAVObject* __fastcall _GetRayCastObject(RayCastData *rcData)
{
	__asm
	{
		push	ebx
		mov		ebx, ecx
		mov		eax, [ebp+0xC]
		mov		ecx, [ebp+8]
		movups	xmm0, [eax]
		shufps	xmm0, xmm0, 0xC
		movss	xmm1, [eax+0x18]
		unpcklpd	xmm0, xmm1
		movss	xmm1, [ebp+0x10]
		shufps	xmm1, xmm1, 0x40
		mulps	xmm0, xmm1
		movups	xmm1, [ecx]
		movaps	xmm2, kUnitConv
		mulps	xmm1, xmm2
		movaps	[ebx], xmm1
		mulps	xmm0, xmm2
		addps	xmm0, xmm1
		movaps	[ebx+0x10], xmm0
		mov		dword ptr [ebx+0x40], 0x3F800000
		mov		eax, 0xFFFFFFFF
		mov		[ebx+0x44], eax
		mov		[ebx+0x50], eax
		xor		eax, eax
		mov		[ebx+0x20], al
		lea		ecx, [ebx+0x70]
		mov		[ecx], eax
		mov		[ecx+0x10], eax
		xorps	xmm0, xmm0
		movaps	[ecx+0x20], xmm0
		movaps	[ecx+0x30], xmm0
		mov		eax, g_thePlayer
		mov		ecx, [eax+0x68]
		mov		eax, [ecx+0x138]
		mov		ecx, [eax+0x594]
		mov		eax, [ecx+8]
		mov		ecx, [eax+0x2C]
		mov		eax, [ebp+0x14]
		mov		edx, 6
		test	eax, eax
		cmovs	eax, edx
		and		eax, 0x3F
		mov		cx, ax
		mov		[ebx+0x24], ecx
		push	1
		push	ebx
		mov		ecx, g_TES
		CALL_EAX(0x458440)
		pop		ebx
		retn
		ALIGN 16
	kUnitConv:
		EMIT_PS_3(3E, 12, 4D, D2)
	}
}

__declspec(naked) NiAVObject* __stdcall GetRayCastObject(const NiVector3 &posVector, float *rotMatRow, float maxRange, UInt32 filter)
{
	__asm
	{
		push	ebp
		mov		ebp, esp
		and		esp, 0xFFFFFFF0
		sub		esp, 0xC0
		mov		ecx, esp
		call	_GetRayCastObject
		leave
		retn	0x10
	}
}

__declspec(naked) bool NiVector4::RayCastCoords(const NiVector3 &posVector, float *rotMatRow, float maxRange, UInt32 filter)
{
	__asm
	{
		push	ebp
		mov		ebp, esp
		and		esp, 0xFFFFFFF0
		sub		esp, 0xC0
		push	ecx
		lea		ecx, [esp+4]
		call	_GetRayCastObject
		pop		ecx
		movss	xmm0, [esp+0x40]
		shufps	xmm0, xmm0, 0x40
		movaps	xmm1, PS_V3_One
		subps	xmm1, xmm0
		mulps	xmm0, [esp+0x10]
		mulps	xmm1, [esp]
		addps	xmm0, xmm1
		mulps	xmm0, PS_HKUnitCnvrt
		movups	[ecx], xmm0
		test	eax, eax
		jnz		done
		mov		eax, g_TES
		cmp		dword ptr [eax+0x34], 0
		jnz		done
		mov		ecx, [eax+0x88]
		call	TESWorldSpace::GetCellAtPos
		test	eax, eax
	done:
		setnz	al
		leave
		retn	0x10
	}
}

__declspec(naked) int __stdcall GetRayCastMaterial(const NiVector3 &posVector, float *rotMatRow, float maxRange, UInt32 filter)
{
	__asm
	{
		push	ebp
		mov		ebp, esp
		and		esp, 0xFFFFFFF0
		sub		esp, 0xD0
		lea		ecx, [esp+0x10]
		call	_GetRayCastObject
		test	eax, eax
		jz		invalid
		mov		[esp+0xC], eax
		mov		ecx, eax
		call	NiAVObject::GetParentRef
		test	eax, eax
		jz		isTerrain
		mov		ecx, eax
		mov		eax, [ecx]
		cmp		dword ptr [eax+0x100], ADDR_ReturnTrue
		jnz		notActor
		mov		eax, [ecx]
		call	dword ptr [eax+0x218]
		mov		ecx, [ecx+0x20]
		test	al, al
		jz		notNPC
		mov		eax, [ecx+0x1E4]
		leave
		retn	0x14
	notNPC:
		mov		eax, [ecx+0x148]
		leave
		retn	0x14
	notActor:
		mov		ecx, [esp+0xC]
		mov		ecx, [ecx+0x1C]
		test	ecx, ecx
		jz		invalid
		mov		ecx, [ecx+0x10]
		test	ecx, ecx
		jz		invalid
		mov		ecx, [ecx+8]
		mov		ecx, [ecx+0x10]
		test	ecx, ecx
		jz		invalid
		mov		ecx, [ecx+8]
		test	ecx, ecx
		jz		invalid
		mov		eax, [ecx+0x10]
		jmp		convert
	isTerrain:
		movss	xmm0, [esp+0x50]
		shufps	xmm0, xmm0, 0x40
		movaps	xmm1, PS_V3_One
		subps	xmm1, xmm0
		mulps	xmm0, [esp+0x20]
		mulps	xmm1, [esp+0x10]
		addps	xmm0, xmm1
		mulps	xmm0, PS_HKUnitCnvrt
		movaps	[esp], xmm0
		push	esp
		mov		ecx, g_TES
		CALL_EAX(0x457720)
		test	eax, eax
		jz		invalid
		movzx	eax, byte ptr [eax+0x1C]
	convert:
		cmp		eax, 0x1F
		ja		invalid
		mov		edx, eax
		movzx	eax, kMaterialConvert[edx]
		leave
		retn	0x14
	invalid:
		mov		eax, 0xFFFFFFFF
		leave
		retn	0x10
	}
}

TempObject<UnorderedMap<TESNPC*, AppearanceUndo*>> s_appearanceUndoMap;

TempObject<UnorderedSet<TESGlobal*>> s_resolvedGlobals;

__declspec(naked) UInt32 TESGlobal::ResolveRefValue()
{
	__asm
	{
		mov		word ptr [ecx+6], 1
		push	esi
		lea		esi, [ecx+0x24]
		cmp		byte ptr [esi], 0xFF
		jz		doLookup
		push	esi
		push	dword ptr [esi]
		call	ResolveRefID
		add		esp, 8
		movzx	eax, al
		test	eax, eax
		jz		invalid
	doLookup:
		push	dword ptr [esi]
		call	LookupFormByRefID
		test	eax, eax
		jz		invalid
		mov		eax, [esi]
		pop		esi
		retn
	invalid:
		mov		[esi], eax
		pop		esi
		retn
	}
}

hkpWorld *GethkpWorld()
{
	bhkWorld *hkWorld = nullptr;
	TESObjectCELL *cell = g_thePlayer->parentCell;
	if (cell)
	{
		if (cell->cellFlags & 1)
		{
			ExtraHavok *xHavok = GetExtraType(&cell->extraDataList, Havok);
			if (xHavok) hkWorld = xHavok->world;
		}
		else hkWorld = bhkWorldM::GetSingleton();
	}
	return hkWorld ? (hkpWorld*)hkWorld->refObject : nullptr;
}

void *TESRecipe::ComponentList::GetComponents(Script *scriptObj)
{
	TempElements *tmpElements = GetTempElements();
	Node *iter = Head();
	RecipeComponent *component;
	do
	{
		if (component = iter->data)
			tmpElements->Append(component->item);
	}
	while (iter = iter->next);
	NVSEArrayVar *outArray = CreateArray(tmpElements->Data(), tmpElements->Size(), scriptObj);
	return outArray;
}

bool LeveledListHasFormDeep(TESLeveledList *pLvlList, TESForm *form, TempFormList *tmpFormLst)
{
	auto iter = pLvlList->list.Head();
	TESLeveledList::ListData *data;
	TESLeveledList *lvlList;
	do
	{
		if (!(data = iter->data)) continue;
		if (data->form == form)
			return true;
		lvlList = data->form->GetLvlList();
		if (lvlList && tmpFormLst->Insert(data->form) && LeveledListHasFormDeep(lvlList, form, tmpFormLst))
			return true;
	}
	while (iter = iter->next);
	return false;
}

float GetDaysPassed(int bgnYear, int bgnMonth, int bgnDay)
{
	int totalDays = 0, iter;
	int iYear = g_gameYear->data, iMonth = g_gameMonth->data, iDay = g_gameDay->data;
	iYear -= bgnYear;
	if (iYear > 0)
	{
		totalDays = kDaysPerMonth[bgnMonth] - bgnDay;
		for (iter = bgnMonth + 1; iter < 12; iter++)
			totalDays += kDaysPerMonth[iter];
		iYear--;
		if (iYear) totalDays += (365 * iYear);
		for (iter = 0; iter < iMonth; iter++)
			totalDays += kDaysPerMonth[iter];
		totalDays += iDay - 1;
	}
	else if (bgnMonth < iMonth)
	{
		totalDays = kDaysPerMonth[bgnMonth] - bgnDay;
		for (iter = bgnMonth + 1; iter < iMonth; iter++)
			totalDays += kDaysPerMonth[iter];
		totalDays += iDay - 1;
	}
	else totalDays = iDay - bgnDay;
	return (float)totalDays + g_gameHour->data * (1 / 24.0F);
}

TempObject<UnorderedMap<UInt32, ScriptVariablesMap>> s_scriptVariablesBuffer;
TempObject<UnorderedMap<UInt32, VariableNames>> s_addedVariables;

bool __fastcall GetVariableAdded(UInt32 ownerID, char *varName)
{
	VariableNames *findOwner = s_addedVariables().GetPtr(ownerID);
	if (!findOwner) return false;
	return findOwner->HasKey(varName);
}

ScriptVar *Script::AddVariable(char *varName, ScriptEventList *eventList, UInt32 ownerID, UInt8 modIdx)
{
	VariableInfo *varInfo = GetVariableByName(varName);
	if (!varInfo)
	{
		varInfo = (VariableInfo*)GameHeapAlloc(sizeof(VariableInfo));
		ZeroMemory(varInfo, sizeof(VariableInfo));
		varInfo->idx = ++info.varCount;
		varInfo->name.Set(varName);
		varList.Append(varInfo);
		s_addedVariables()[refID].Insert(varName);
	}
	else if (!GetVariableAdded(refID, varName)) return NULL;

	ScriptVar *var = eventList->GetVariable(varInfo->idx);
	if (!var)
	{
		var = (ScriptVar*)GameHeapAlloc(sizeof(ScriptVar));
		var->id = varInfo->idx;
		var->next = NULL;
		var->data.num = 0;
		eventList->m_vars->Append(var);
	}

	if (varName[0] != '*')
		s_scriptVariablesBuffer()[ownerID][varName].Set(var, modIdx);
	return var;
}

__declspec(naked) TESIdleForm *AnimData::GetPlayedIdle()
{
	__asm
	{
		mov		eax, [ecx+0x128]
		test	eax, eax
		jz		noQueued
		mov		eax, [eax+0x2C]
		test	eax, eax
		jnz		done
	noQueued:
		mov		eax, [ecx+0x124]
		test	eax, eax
		jz		done
		mov		eax, [eax+0x2C]
		test	eax, eax
		jz		done
		push	eax
		CALL_EAX(0x4985F0)
		pop		edx
		movzx	eax, al
		dec		eax
		and		eax, edx
	done:
		retn
	}
}

TempObject<UnorderedMap<UInt32, LinkedRefEntry>> s_linkedRefModified;
TempObject<UnorderedMap<UInt32, UInt32>> s_linkedRefDefault, s_linkedRefsTemp;

bool TESObjectREFR::SetLinkedRef(TESObjectREFR *linkObj = NULL, UInt8 modIdx)
{
	ExtraLinkedRef *xLinkedRef = GetExtraType(&extraDataList, LinkedRef);
	if (!linkObj)
	{
		auto findDefID = s_linkedRefDefault().Find(refID);
		if (findDefID)
		{
			if (xLinkedRef)
			{
				if (*findDefID)
				{
					TESForm *form = LookupFormByRefID(*findDefID);
					if (form && IS_REFERENCE(form)) xLinkedRef->linkedRef = (TESObjectREFR*)form;
				}
				else extraDataList.RemoveExtra(xLinkedRef, true);
			}
			findDefID.Remove();
		}
		s_linkedRefModified().Erase(refID);
		return true;
	}
	if (!xLinkedRef)
	{
		extraDataList.AddExtra(ExtraLinkedRef::Create(linkObj));
		s_linkedRefDefault()[refID] = 0;
	}
	else
	{
		if (!xLinkedRef->linkedRef) return false;
		s_linkedRefDefault()[refID] = xLinkedRef->linkedRef->refID;
		xLinkedRef->linkedRef = linkObj;
	}
	s_linkedRefModified()[refID].Set(linkObj->refID, modIdx);
	return true;
}

bool SetLinkedRefID(UInt32 thisID, UInt32 linkID, UInt8 modIdx)
{
	TESObjectREFR *thisObj = (TESObjectREFR*)LookupFormByRefID(thisID);
	if (!thisObj || NOT_REFERENCE(thisObj)) return false;
	if (!linkID) return thisObj->SetLinkedRef();
	TESObjectREFR *linkObj = (TESObjectREFR*)LookupFormByRefID(linkID);
	return linkObj && IS_REFERENCE(linkObj) && thisObj->SetLinkedRef(linkObj, modIdx);
}

TempObject<AuxVarModsMap> s_auxVariablesPerm, s_auxVariablesTemp;

TempObject<RefMapModsMap> s_refMapArraysPerm, s_refMapArraysTemp;

UInt32 __fastcall GetSubjectID(TESForm *form, TESObjectREFR *thisObj)
{
	if (form) return IS_REFERENCE(form) ? ((TESObjectREFR*)form)->baseForm->refID : form->refID;
	if (thisObj) return thisObj->refID;
	return 0;
}

UInt8 s_dataChangedFlags = 0;

void EventCallbackScripts::InvokeEvents(UInt32 arg)
{
	for (auto script = BeginCp(); script; ++script)
		CallFunction(*script, NULL, 1, arg);
}

void EventCallbackScripts::InvokeEvents2(UInt32 arg1, UInt32 arg2)
{
	for (auto script = BeginCp(); script; ++script)
		CallFunction(*script, NULL, 2, arg1, arg2);
}

void EventCallbackScripts::InvokeEventsThis(TESObjectREFR *thisObj)
{
	for (auto script = BeginCp(); script; ++script)
		CallFunction(*script, thisObj, 0);
}

void EventCallbackScripts::InvokeEventsThis1(TESObjectREFR *thisObj, UInt32 arg)
{
	for (auto script = BeginCp(); script; ++script)
		CallFunction(*script, thisObj, 1, arg);
}

void EventCallbackScripts::InvokeEventsThis2(TESObjectREFR *thisObj, UInt32 arg1, UInt32 arg2)
{
	for (auto script = BeginCp(); script; ++script)
		CallFunction(*script, thisObj, 2, arg1, arg2);
}

TempObject<CriticalHitEventCallbacks> s_criticalHitEvents;

TempObject<UnorderedMap<Script*, DisabledScriptBlocks>> s_disabledScriptBlocksMap;

ExtraDataList *InventoryRef::CreateExtraData()
{
	ContChangesEntry *pEntry = containerRef->GetContainerChangesEntry(type);
	if (!pEntry) return NULL;
	xData = ExtraDataList::Create();
	if (pEntry->extendData)
		pEntry->extendData->Prepend(xData);
	else
	{
		pEntry->extendData = (ExtraContainerChanges::ExtendDataList*)GameHeapAlloc(8);
		pEntry->extendData->Init(xData);
	}
	containerRef->MarkAsModified(0x20);
	return xData;
}

TESObjectREFR* __fastcall CreateRefForStack(TESObjectREFR *container, ContChangesEntry *menuEntry)
{
	return (container && menuEntry) ? InventoryRefCreate(container, menuEntry->type, menuEntry->countDelta, menuEntry->extendData ? menuEntry->extendData->GetFirstItem() : NULL) : NULL;
}

ExtraDataList* __fastcall SplitFromStack(ContChangesEntry *entry, ExtraDataList *xDataIn)
{
	ExtraCount *xCount = GetExtraType(xDataIn, Count);
	if (!xCount) return xDataIn;
	ExtraDataList *xDataOut = xDataIn->CreateCopy();
	xDataOut->RemoveByType(kExtraData_Worn);
	xDataOut->RemoveByType(kExtraData_Count);
	xDataOut->RemoveByType(kExtraData_Hotkey);
	if (--xCount->count < 2)
	{
		xDataIn->RemoveExtra(xCount, true);
		if (!xDataIn->m_data)
		{
			entry->extendData->Remove(xDataIn);
			GameHeapFree(xDataIn);
		}
	}
	entry->extendData->Prepend(xDataOut);
	return xDataOut;
}

TESObjectREFR* __fastcall GetEquippedItemRef(Actor *actor, UInt32 slotIndex)
{
	ExtraContainerChanges::EntryDataList *entryList = actor->GetContainerChangesList();
	if (!entryList) return NULL;
	UInt32 partMask = 1 << slotIndex;
	TESForm *item;
	ContChangesEntry *entry;
	ExtraDataList *xData;
	if (actor->GetRefNiNode())
	{
		if (slotIndex == 5)
		{
			entry = actor->GetWeaponInfo();
			if (entry && entry->extendData)
				return InventoryRefCreate(actor, entry->type, entry->countDelta, entry->extendData->GetFirstItem());
		}
		else
		{
			ValidBip01Names *equipment = actor->GetValidBip01Names();
			if (equipment)
			{
				ValidBip01Names::Data *slotData = equipment->slotData;
				for (UInt8 count = 20; count; count--, slotData++)
				{
					item = slotData->item;
					if (!item || NOT_TYPE(item, TESObjectARMO) || !(((TESObjectARMO*)item)->bipedModel.partMask & partMask))
						continue;
					if (!(entry = entryList->FindForItem(item)) || !(xData = entry->GetEquippedExtra()))
						break;
					return InventoryRefCreate(actor, item, entry->countDelta, xData);
				}
			}
		}
	}
	else
	{
		auto listIter = entryList->Head();
		do
		{
			entry = listIter->data;
			if (!entry || !entry->extendData)
				continue;
			item = entry->type;
			if (slotIndex == 5)
			{
				if NOT_ID(item, TESObjectWEAP)
					continue;
			}
			else if (NOT_TYPE(item, TESObjectARMO) || !(((TESObjectARMO*)item)->bipedModel.partMask & partMask))
				continue;
			if (xData = entry->GetEquippedExtra())
				return InventoryRefCreate(actor, item, entry->countDelta, xData);
		}
		while (listIter = listIter->next);
	}
	return NULL;
}

ContChangesEntry* __fastcall GetHotkeyItemEntry(UInt8 index, ExtraDataList **outXData)
{
	ExtraContainerChanges::EntryDataList *entryList = g_thePlayer->GetContainerChangesList();
	if (!entryList) return NULL;
	auto entryIter = entryList->Head();
	ContChangesEntry *entry;
	UInt8 type;
	ListNode<ExtraDataList> *xdlIter;
	ExtraDataList *xData;
	ExtraHotkey *xHotkey;
	do
	{
		if (!(entry = entryIter->data) || !entry->extendData)
			continue;
		type = entry->type->typeID;
		if ((type != kFormType_TESObjectARMO) && (type != kFormType_TESObjectWEAP) && (type != kFormType_AlchemyItem))
			continue;
		xdlIter = entry->extendData->Head();
		do
		{
			if (!(xData = xdlIter->data)) continue;
			xHotkey = GetExtraType(xData, Hotkey);
			if (!xHotkey || (xHotkey->index != index))
				continue;
			*outXData = xData;
			return entry;
		}
		while (xdlIter = xdlIter->next);
	}
	while (entryIter = entryIter->next);
	return NULL;
}

bool __fastcall ClearHotkey(UInt8 index)
{
	ExtraDataList *xData;
	ContChangesEntry *entry = GetHotkeyItemEntry(index, &xData);
	if (entry)
	{
		xData->RemoveByType(kExtraData_Hotkey);
		if (!xData->m_data)
		{
			entry->extendData->Remove(xData);
			GameHeapFree(xData);
		}
		return true;
	}
	return false;
}

float __fastcall GetModBonuses(TESObjectREFR *wpnRef, UInt32 effectID)
{
	TESObjectWEAP *weapon = (TESObjectWEAP*)wpnRef->baseForm;
	if NOT_ID(weapon, TESObjectWEAP) return 0;
	ExtraWeaponModFlags *xModFlags = GetExtraType(&wpnRef->extraDataList, WeaponModFlags);
	if (!xModFlags) return 0;
	float result = 0;
	for (UInt32 idx = 0; idx < 3; idx++)
		if ((xModFlags->flags & (1 << idx)) && (weapon->effectMods[idx] == effectID))
			result += weapon->value1Mod[idx];
	return result;
}

__declspec(naked) float __vectorcall GetLightAmountAtPoint(const NiVector3 &pos)
{
	__asm
	{
		push	ebx
		push	esi
		push	edi
		push	ecx
		mov		esi, g_shadowSceneNode
		mov		edi, [esi+0xE0]
		xorps	xmm6, xmm6
		test	edi, edi
		jz		done
		mov		ebx, 0xB9BC50
		movups	xmm7, [ecx]
		andps	xmm7, PS_XYZ0Mask
		mov		eax, g_TES
		cmp		dword ptr [eax+0x34], 0
		jnz		isInterior
		mov		ecx, [eax+0x88]
		test	ecx, ecx
		jz		done
		movaps	xmm0, xmm7
		call	TESWorldSpace::GetCellAtPos
		test	eax, eax
		jz		done
		sub		esp, 0x10
		movups	[esp], xmm7
		mov		ecx, edi
		call	ebx
		fstp	dword ptr [esp]
		movss	xmm6, [esp]
		jmp		doneCell
		ALIGN 16
	isInterior:
		mov		eax, [edi+0xF8]
		add		eax, 0xC8
		movss	xmm0, [eax]
		maxss	xmm0, [eax+4]
		maxss	xmm0, [eax+8]
		movss	xmm6, [eax+0xC]
		maxss	xmm6, [eax+0x10]
		maxss	xmm6, [eax+0x14]
		addss	xmm6, xmm0
	doneCell:
		mov		ecx, 0x11F9EA0
		call	LightCS::Enter
		mov		esi, [esi+0xB4]
		ALIGN 16
	iterHead:
		test	esi, esi
		jz		doClamp
		mov		ecx, [esi+8]
		mov		esi, [esi]
		test	ecx, ecx
		jz		iterHead
		mov		eax, [ecx+0xF8]
		test	eax, eax
		jz		iterHead
		test	byte ptr [eax+0x30], 1
		jnz		iterHead
		sub		esp, 0x10
		movups	[esp], xmm7
		call	ebx
		fstp	dword ptr [esp]
		addss	xmm6, [esp]
		jmp		iterHead
	doClamp:
		xorps	xmm0, xmm0
		maxss	xmm6, xmm0
		movss	xmm0, SS_100
		mulss	xmm6, xmm0
		minss	xmm6, xmm0
		mov		ecx, 0x11F9EA0
		dec		dword ptr [ecx+4]
		jnz		done
		mov		dword ptr [ecx], 0
	done:
		movaps	xmm0, xmm6
		pop		ecx
		pop		edi
		pop		esi
		pop		ebx
		retn
	}
}

const AnimGroupClassify kAnimGroupClassify[] =
{
	{1, 1, 0, 0}, {1, 1, 0, 0}, {1, 1, 0, 0}, {2, 1, 0, 0}, {2, 2, 0, 0}, {2, 3, 0, 0}, {2, 4, 0, 0}, {2, 1, 1, 0}, {2, 2, 1, 0}, 
	{2, 3, 1, 0}, {2, 4, 1, 0}, {2, 1, 2, 0}, {2, 2, 2, 0}, {2, 3, 2, 0}, {2, 4, 2, 0}, {2, 3, 4, 0}, {2, 4, 4, 0}, {3, 0, 0, 0}, 
	{3, 0, 1, 0}, {3, 0, 2, 0}, {3, 0, 4, 0}, {3, 0, 5, 0}, {3, 0, 6, 0}, {1, 2, 0, 0}, {1, 2, 0, 0}, {1, 2, 0, 0}, {3, 1, 0, 0}, 
	{3, 1, 1, 0}, {3, 1, 2, 0}, {3, 1, 4, 0}, {3, 1, 5, 0}, {3, 1, 6, 0}, {3, 2, 0, 0}, {3, 2, 1, 0}, {3, 2, 2, 0}, {3, 2, 4, 0}, 
	{3, 2, 5, 0}, {3, 2, 6, 0}, {3, 3, 0, 0}, {3, 3, 1, 0}, {3, 3, 2, 0}, {3, 3, 4, 0}, {3, 3, 5, 0}, {3, 3, 6, 0}, {3, 4, 0, 0}, 
	{3, 4, 1, 0}, {3, 4, 2, 0}, {3, 4, 4, 0}, {3, 4, 5, 0}, {3, 4, 6, 0}, {3, 5, 0, 0}, {3, 5, 1, 0}, {3, 5, 2, 0}, {3, 5, 4, 0}, 
	{3, 5, 5, 0}, {3, 5, 6, 0}, {3, 6, 0, 0}, {3, 6, 1, 0}, {3, 6, 2, 0}, {3, 6, 4, 0}, {3, 6, 5, 0}, {3, 6, 6, 0}, {3, 7, 0, 0}, 
	{3, 7, 1, 0}, {3, 7, 2, 0}, {3, 7, 4, 0}, {3, 7, 5, 0}, {3, 7, 6, 0}, {3, 8, 0, 0}, {3, 8, 1, 0}, {3, 8, 2, 0}, {3, 8, 4, 0}, 
	{3, 8, 5, 0}, {3, 8, 6, 0}, {3, 10, 0, 0}, {3, 10, 1, 0}, {3, 10, 2, 0}, {3, 10, 4, 0}, {3, 10, 5, 0}, {3, 10, 6, 0}, {3, 11, 0, 0}, 
	{3, 11, 1, 0}, {3, 11, 2, 0}, {3, 11, 4, 0}, {3, 11, 5, 0}, {3, 11, 6, 0}, {3, 12, 0, 0}, {3, 12, 1, 0}, {3, 12, 2, 0}, {3, 12, 4, 0}, 
	{3, 12, 5, 0}, {3, 12, 6, 0}, {3, 23, 0, 0}, {3, 23, 0, 0}, {3, 23, 0, 0}, {3, 23, 0, 0}, {3, 23, 0, 0}, {3, 23, 0, 0}, {3, 23, 0, 0}, 
	{3, 23, 0, 0}, {3, 23, 0, 0}, {3, 23, 0, 0}, {3, 21, 0, 0}, {3, 21, 1, 0}, {3, 21, 2, 0}, {3, 21, 4, 0}, {3, 21, 5, 0}, {3, 21, 6, 0}, 
	{3, 22, 0, 0}, {3, 22, 1, 0}, {3, 22, 2, 0}, {3, 22, 4, 0}, {3, 22, 5, 0}, {3, 22, 6, 0}, {3, 13, 0, 0}, {3, 13, 1, 0}, {3, 13, 2, 0}, 
	{3, 13, 4, 0}, {3, 13, 5, 0}, {3, 13, 6, 0}, {3, 14, 0, 0}, {3, 14, 1, 0}, {3, 14, 2, 0}, {3, 14, 4, 0}, {3, 14, 5, 0}, {3, 14, 6, 0}, 
	{3, 15, 0, 0}, {3, 15, 1, 0}, {3, 15, 2, 0}, {3, 15, 4, 0}, {3, 15, 5, 0}, {3, 15, 6, 0}, {3, 16, 0, 0}, {3, 16, 1, 0}, {3, 16, 2, 0}, 
	{3, 16, 4, 0}, {3, 16, 5, 0}, {3, 16, 6, 0}, {3, 17, 0, 0}, {3, 17, 1, 0}, {3, 17, 2, 0}, {3, 17, 4, 0}, {3, 17, 5, 0}, {3, 17, 6, 0}, 
	{3, 9, 0, 0}, {3, 9, 1, 0}, {3, 9, 2, 0}, {3, 9, 4, 0}, {3, 9, 5, 0}, {3, 9, 6, 0}, {3, 18, 0, 0}, {3, 18, 1, 0}, {3, 18, 2, 0}, 
	{3, 18, 4, 0}, {3, 18, 5, 0}, {3, 18, 6, 0}, {3, 19, 0, 0}, {3, 19, 1, 0}, {3, 19, 2, 0}, {3, 19, 4, 0}, {3, 19, 5, 0}, {3, 19, 6, 0}, 
	{3, 20, 0, 0}, {3, 20, 1, 0}, {3, 20, 2, 0}, {3, 20, 4, 0}, {3, 20, 5, 0}, {3, 20, 6, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 3, 0, 0}, 
	{1, 3, 0, 0}, {1, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, 
	{4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, 
	{4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {4, 0, 0, 0}, {5, 0, 0, 0}, 
	{5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, 
	{5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, {5, 0, 0, 0}, 
	{5, 0, 0, 0}, {5, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {2, 5, 0, 0}, {2, 5, 0, 0}, {2, 5, 0, 0}, {1, 4, 0, 0}, 
	{1, 4, 0, 0}, {1, 4, 0, 0}, {1, 4, 0, 0}, {1, 4, 0, 0}, {1, 4, 0, 0}, {2, 5, 0, 0}, {2, 5, 0, 0}, {2, 5, 0, 0}, {2, 5, 0, 0}, {1, 0, 0, 0}, 
	{2, 5, 0, 0}, {2, 5, 0, 0}, {2, 5, 0, 0}, {2, 5, 0, 0}
};

TempObject<UnorderedMap<char*, Script*>> s_cachedScripts;

namespace JIPScriptRunner
{
	void Init()
	{
		char *fileName, scriptsPath[0x50] = "Data\\NVSE\\plugins\\scripts\\*.txt", *buffer = GetStrArgBuffer();
		for (DirectoryIterator iter(scriptsPath); iter; ++iter)
		{
			if (!iter.IsFile()) continue;
			fileName = const_cast<char*>(*iter);
			if (fileName[2] != '_') continue;
			StrCopy(scriptsPath + 26, fileName);
			if (!FileToBuffer(scriptsPath, buffer))
				continue;
			switch (*(UInt16*)fileName |= 0x2020)
			{
				case kRunOn_RestartGame:
					PrintLog("Run Script : %s >> %s", fileName, RunScriptSource(buffer) ? "SUCCESS" : "FAILED");
					break;
				case kRunOn_LoadGame:
				case kRunOn_ExitToMainMenu:
				case kRunOn_NewGame:
				case kRunOn_SaveGame:
				case kRunOn_ExitGame:
					s_cachedScripts()[fileName] = Script::Create(buffer);
					break;
				default:
					break;
			}
		}
	}

	void RunScripts(UInt16 type)
	{
		for (auto iter = s_cachedScripts().Begin(); iter; ++iter)
		{
			if (*(UInt16*)iter.Key() != type) continue;
			if (iter->info.dataLength)
			{
				SuppressConsoleOutput();
				iter->Execute(nullptr, nullptr, nullptr, true);
			}
			PrintLog("Run Script : %s >> %s", iter.Key(), iter->info.dataLength ? "SUCCESS" : "FAILED");
		}
	}

	bool __fastcall RunScript(Script *script, int EDX, TESObjectREFR *callingRef)
	{
		bool result = script->info.dataLength != 0;
		if (result)
		{
			ExtraScript *xScript = GetExtraType(&callingRef->extraDataList, Script);
			ScriptEventList *eventList = xScript ? xScript->eventList : nullptr;
			if (eventList) xScript->eventList = nullptr;
			SuppressConsoleOutput();
			script->Execute(callingRef, nullptr, nullptr, true);
			if (eventList) xScript->eventList = eventList;
		}
		if (EDX != 1)
		{
			script->Destructor();
			GameHeapFree(script);
		}
		return result;
	}

	bool __fastcall RunScriptSource(char *scrSource)
	{
		UInt8 tempScrBuf[sizeof(Script)];
		Script *tempScript = (Script*)tempScrBuf;
		tempScript->Init(scrSource);
		bool result = tempScript->info.dataLength != 0;
		if (result)
		{
			SuppressConsoleOutput();
			tempScript->Execute(nullptr, nullptr, nullptr, true);
		}
		tempScript->Destructor();
		return result;
	}
};

TempObject<UnorderedMap<const char*, NiCamera*>> s_extraCamerasMap;

bool s_HUDCursorMode = false;

bool GetMenuMode()
{
	return (g_interfaceManager->currentMode > 1) || s_HUDCursorMode;
}

__declspec(naked) bool IsConsoleOpen()
{
	__asm
	{
		mov		al, byte ptr ds:[0x11DEA2E]
		test	al, al
		jz		done
		mov		eax, fs:[0x2C]
		mov		edx, ds:[0x126FD98]
		mov		eax, [eax+edx*4]
		mov		al, [eax+0x268]
	done:
		retn
	}
}

__declspec(naked) void SuppressConsoleOutput()
{
	__asm
	{
		mov		eax, fs:[0x2C]
		mov		edx, ds:[0x126FD98]
		mov		eax, [eax+edx*4]
		mov		[eax+0x268], 0
		retn
	}
}

__declspec(naked) void __fastcall DoConsolePrint(double *result)
{
	__asm
	{
		call	IsConsoleOpen
		test	al, al
		jz		done
		cmp		dword ptr [ebp+4], 0x5E234B
		jnz		done
		mov		edx, [ebp]
		mov		edx, [edx-0x30]
		mov		edx, [edx]
		movq	xmm0, qword ptr [ecx]
		push	ebp
		mov		ebp, esp
		sub		esp, 0x50
		lea		ecx, [ebp-0x50]
		call	StrCopy
		mov		ecx, eax
		mov		dword ptr [ecx], ' >> '
		add		ecx, 4
		call	FltToStr
		lea		eax, [ebp-0x50]
		push	eax
		push	eax
		mov		ecx, g_consoleManager
		CALL_EAX(0x71D0A0)
		leave
	done:
		retn
	}
}

__declspec(naked) void __fastcall DoConsolePrint(TESForm *result)
{
	__asm
	{
		call	IsConsoleOpen
		test	al, al
		jz		done
		cmp		dword ptr [ebp+4], 0x5E234B
		jnz		done
		mov		edx, [ebp]
		mov		edx, [edx-0x30]
		mov		edx, [edx]
		push	ebp
		mov		ebp, esp
		sub		esp, 0x60
		push	esi
		mov		esi, ecx
		lea		ecx, [ebp-0x60]
		call	StrCopy
		mov		ecx, eax
		mov		dword ptr [ecx], ' >> '
		add		ecx, 4
		test	esi, esi
		jnz		haveID
		mov		word ptr [ecx], '0'
		jmp		noEDID
	haveID:
		mov		edx, [esi+0xC]
		call	UIntToHex
		mov		ecx, esi
		mov		esi, eax
		mov		eax, [ecx]
		call	dword ptr [eax+0x130]
		test	eax, eax
		jz		noEDID
		cmp		[eax], 0
		jz		noEDID
		mov		ecx, esi
		mov		word ptr [ecx], '\" '
		add		ecx, 2
		mov		edx, eax
		call	StrCopy
		mov		word ptr [eax], '\"'
	noEDID:
		pop		esi
		lea		eax, [ebp-0x60]
		push	eax
		push	eax
		mov		ecx, g_consoleManager
		CALL_EAX(0x71D0A0)
		leave
	done:
		retn
	}
}

bool IsInMainThread()
{
	return GetCurrentThreadId() == s_mainThreadID;
}

__declspec(naked) TLSData *GetTLSData()
{
	__asm
	{
		mov		eax, fs:[0x2C]
		mov		edx, ds:[0x126FD98]
		mov		eax, [eax+edx*4]
		retn
	}
}

TempObject<UnorderedMap<const char*, UInt32>> s_fileExtToType(std::initializer_list<MappedPair<const char*, UInt32>>({{"nif", 1}, {"egm", 1},
	{"egt", 1}, {"kf", 1}, {"psa", 1}, {"tri", 1}, {"dds", 2}, {"fnt", 2}, {"psd", 2}, {"tai", 2}, {"tex", 2}, {"wav", 8}, {"lip", 0x10},
	{"ogg", 0x10}, {"spt", 0x40}, {"ctl", 0x100}, {"dat", 0x100}, {"dlodsettings", 0x100}, {"xml", 0x100}}));

__declspec(naked) bool __fastcall GetFileArchived(const char *filePath)
{
	__asm
	{
		push	ebp
		mov		ebp, esp
		sub		esp, 0x1C
		push	esi
		push	edi
		mov		esi, ecx
		call	StrLen
		push	'.'
		mov		edx, eax
		call	FindChrR
		test	eax, eax
		jz		retnFalse
		inc		eax
		push	eax
		mov		ecx, offset s_fileExtToType
		call	UnorderedMap<const char*, UInt32>::Get
		test	eax, eax
		jz		retnFalse
		mov		[ebp-4], ax
		mov		edx, 0x10A4828
		mov		ecx, esi
		call	StrBeginsCI
		test	al, al
		jz		noSubDir
		add		esi, 5
	noSubDir:
		lea		eax, [ebp-0x14]
		push	eax
		lea		eax, [ebp-0xC]
		push	eax
		push	esi
		CALL_EAX(0xAFD270)
		add		esp, 0xC
		mov		edi, ds:[0x11F8160]
		ALIGN 16
	iterHead:
		test	edi, edi
		jz		retnFalse
		mov		ecx, [edi]
		mov		edi, [edi+4]
		test	ecx, ecx
		jz		iterHead
		mov		ax, word ptr [ecx+0x180]
		and		ax, word ptr [ebp-4]
		jz		iterHead
		push	esi
		lea		eax, [ebp-0x1C]
		push	eax
		lea		eax, [ebp-0x18]
		push	eax
		lea		eax, [ebp-0x14]
		push	eax
		lea		eax, [ebp-0xC]
		push	eax
		CALL_EAX(0xAF9BF0)
		test	al, al
		jz		iterHead
		jmp		done
	retnFalse:
		xor		al, al
	done:
		pop		edi
		pop		esi
		leave
		retn
	}
}

__declspec(naked) int __stdcall FileExistsEx(char *filePath, bool isFolder)
{
	__asm
	{
		push	'\\'
		mov		dl, '/'
		mov		ecx, [esp+8]
		call	ReplaceChr
		push	dword ptr [esp+4]
		call	GetFileAttributesA
		test	eax, eax
		js		notFound
		test	al, 0x10
		setnz	dl
		xor		eax, eax
		cmp		dl, [esp+8]
		setz	al
		retn	8
		ALIGN 16
	notFound:
		xor		eax, eax
		cmp		[esp+8], 0
		jnz		done
		mov		ecx, [esp+4]
		call	GetFileArchived
		shl		al, 1
		movzx	eax, al
	done:
		retn	8
	}
}

int GetIsLAA()
{
	static int isLAA = -1;
	if (isLAA == -1)
	{
		HMODULE gameHandle = GetModuleHandle(NULL);
		UInt8 *dataPtr = (UInt8*)gameHandle + *(UInt32*)((UInt8*)gameHandle + 0x3C) + 0x16;
		isLAA = (*dataPtr & 0x20) ? 1 : 0;
		if (isLAA)
		{
			void *blockPtrs[20], *block;
			MemZero(blockPtrs, 0x50);
			int idx = 0;
			do
			{
				blockPtrs[idx++] = block = malloc(0x6400000);
				if (!block) break;
				if ((UInt32)block >= 0x80000000)
				{
					isLAA = 2;
					break;
				}
			}
			while (idx < 20);
			do
			{
				free(blockPtrs[--idx]);
			}
			while (idx);
		}
	}
	return isLAA;
}

double s_nvseVersion = 0;

bool Cmd_EmptyCommand_Execute(COMMAND_ARGS)
{
	*result = 0;
	return true;
}

#if 0
#include <psapi.h>
#pragma comment(lib, "psapi.lib")

char s_memUseUI[] = "<text name=\"MemUseDisplay\"><font>3</font><string></string><justify>1</justify><x>40</x><y>40</y><systemcolor>2</systemcolor></text>";
TileText *s_memUsageTile = nullptr;

void UpdateMemUsageDisplay()
{
	Tile::Value *tileStr = s_memUsageTile->GetValue(kTileValue_string);
	if (tileStr)
	{
		PROCESS_MEMORY_COUNTERS_EX pmc;
		GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
		size_t physMemUsed = pmc.WorkingSetSize >> 0xA;
		size_t virtMemUsed = pmc.PrivateUsage >> 0xA;
		char dataStr[0x80];
		sprintf_s(dataStr, 0x80, "RAM:   %d\nVRAM:  %d", physMemUsed, virtMemUsed);
		tileStr->SetString(dataStr);
	}
}

Tile* __stdcall InjectUIComponent(Tile *parentTile, char *dataStr);
bool MainLoopHasCallback(void *cmdPtr, void *thisObj);
void MainLoopAddCallbackEx(void *cmdPtr, void *thisObj, UInt32 callCount, UInt32 callDelay);

void InitMemUsageDisplay(UInt32 callDelay)
{
	if (!s_memUsageTile)
		s_memUsageTile = (TileText*)InjectUIComponent(g_HUDMainMenu->tile, s_memUseUI);
	if (s_memUsageTile && !MainLoopHasCallback(UpdateMemUsageDisplay, nullptr))
		MainLoopAddCallbackEx(UpdateMemUsageDisplay, nullptr, 0xFFFFFFF0, callDelay);
}
#endif

#if LOG_HOOKS
Map<UInt32, UInt8*> s_hookOriginalData(0x200);

void __stdcall StoreOriginalData(UInt32 addr, UInt8 size)
{
	UInt8 **dataPtr;
	if (s_hookOriginalData.Insert(addr, &dataPtr))
	{
		UInt8 *data = (UInt8*)malloc(0x10);
		*dataPtr = data;
		*data++ = size;
		memcpy(data, (void*)addr, size);
	}
}
#endif