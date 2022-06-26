#pragma once

DEFINE_COMMAND_PLUGIN(SetPersistent, 1, 1, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(GetObjectDimensions, 0, 2, kParams_OneAxis_OneOptionalForm);
DEFINE_COMMAND_PLUGIN(GetIsItem, 0, 1, kParams_OneOptionalObjectID);
DEFINE_COMMAND_ALT_PLUGIN(SetLinkedReference, SetLinkedRef, 1, 1, kParams_OneOptionalObjectRef);
DEFINE_COMMAND_PLUGIN(GetEnableChildren, 1, 0, NULL);
DEFINE_COMMAND_PLUGIN(GetLinkedChildren, 1, 0, NULL);
DEFINE_COMMAND_PLUGIN(HasPrimitive, 1, 0, NULL);
DEFINE_COMMAND_PLUGIN(GetPrimitiveBound, 1, 1, kParams_OneAxis);
DEFINE_COMMAND_PLUGIN(SetPrimitiveBound, 1, 2, kParams_OneAxis_OneFloat);
DEFINE_COMMAND_PLUGIN(AddPrimitive, 1, 4, kParams_OneInt_ThreeFloats);
DEFINE_COMMAND_PLUGIN(GetTeammates, 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(MoveToCell, 1, 4, kParams_OneForm_ThreeFloats);
DEFINE_COMMAND_PLUGIN(MoveToEditorPosition, 1, 1, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(GetCenterPos, 1, 1, kParams_OneAxis);
DEFINE_COMMAND_PLUGIN(GetRefType, 0, 1, kParams_OneOptionalObjectRef);
DEFINE_COMMAND_PLUGIN(ToggleObjectCollision, 1, 1, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(GetMaterialPropertyValue, 1, 2, kParams_OneString_OneInt);
DEFINE_COMMAND_PLUGIN(SetMaterialPropertyValue, 1, 3, kParams_OneString_OneInt_OneFloat);
DEFINE_COMMAND_PLUGIN(GetHasContact, 1, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(GetHasContactBase, 1, 1, kParams_OneForm);
DEFINE_CMD_COND_PLUGIN(GetHasContactType, 1, 1, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(GetContactRefs, 1, 0, NULL);
DEFINE_COMMAND_PLUGIN(GetHasPhantom, 1, 0, NULL);
DEFINE_COMMAND_PLUGIN(GetInteractionDisabled, 0, 1, kParams_OneOptionalObject);
DEFINE_COMMAND_PLUGIN(SetInteractionDisabled, 0, 2, kParams_OneInt_OneOptionalObject);
DEFINE_COMMAND_PLUGIN(GetInteractionDisabledType, 0, 1, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(SetInteractionDisabledType, 0, 2, kParams_TwoInts);
DEFINE_COMMAND_PLUGIN(AddRefMapMarker, 1, 0, NULL);
DEFINE_COMMAND_PLUGIN(RemoveRefMapMarker, 1, 0, NULL);
DEFINE_COMMAND_PLUGIN(RefHasMapMarker, 1, 0, NULL);
DEFINE_COMMAND_PLUGIN(SetPosEx, 1, 4, kParams_ThreeFloats_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(MoveToReticle, 1, 5, kParams_FourOptionalFloats_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(SetRefName, 1, 1, kParams_OneOptionalString);
DEFINE_COMMAND_PLUGIN(SetAngleEx, 1, 4, kParams_ThreeFloats_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(GetTeleportDoor, 1, 0, NULL);
DEFINE_COMMAND_PLUGIN(SetOnCriticalHitEventHandler, 0, 5, kParams_OneForm_OneInt_ThreeOptionalForms);
DEFINE_COMMAND_PLUGIN(MoveToFadeDelay, 1, 2, kParams_OneObjectRef_OneFloat);
DEFINE_COMMAND_PLUGIN(GetCrosshairWater, 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(IsAnimPlayingEx, 1, 3, kParams_OneInt_TwoOptionalInts);
DEFINE_COMMAND_PLUGIN(GetRigidBodyMass, 1, 0, NULL);
DEFINE_COMMAND_PLUGIN(PushObject, 1, 5, kParams_FourFloats_OneOptionalObjectRef);
DEFINE_COMMAND_PLUGIN(MoveToContainer, 1, 2, kParams_OneObjectRef_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(GetNifBlockTranslation, 1, 3, kParams_OneString_TwoOptionalInts);
DEFINE_COMMAND_PLUGIN(SetNifBlockTranslation, 1, 6, kParams_OneString_ThreeFloats_TwoOptionalInts);
DEFINE_COMMAND_PLUGIN(GetNifBlockRotation, 1, 3, kParams_OneString_TwoOptionalInts);
DEFINE_COMMAND_PLUGIN(SetNifBlockRotation, 1, 6, kParams_OneString_ThreeFloats_TwoOptionalInts);
DEFINE_COMMAND_PLUGIN(GetNifBlockScale, 1, 2, kParams_OneString_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(SetNifBlockScale, 1, 3, kParams_OneString_OneFloat_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(GetNifBlockFlag, 1, 3, kParams_OneString_OneInt_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(SetNifBlockFlag, 1, 4, kParams_OneString_TwoInts_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(GetObjectVelocity, 1, 1, kParams_OneOptionalAxis);
DEFINE_COMMAND_PLUGIN(GetAngularVelocity, 1, 2, kParams_OneString_OneOptionalAxis);
DEFINE_COMMAND_PLUGIN(SetAngularVelocity, 1, 3, kParams_OneString_OneAxis_OneFloat);
DEFINE_COMMAND_PLUGIN(PlaceAtCell, 0, 6, kParams_OneForm_OneInt_OneForm_ThreeFloats);
DEFINE_COMMAND_PLUGIN(GetRayCastPos, 1, 7, kParams_ThreeGlobals_OneOptFloat_OneOptInt_OneOptString_OneOptFloat);
DEFINE_COMMAND_PLUGIN(GetAnimSequenceFrequency, 1, 1, kParams_OneString);
DEFINE_COMMAND_PLUGIN(SetAnimSequenceFrequency, 1, 2, kParams_OneString_OneFloat);
DEFINE_COMMAND_PLUGIN(MoveToNode, 1, 5, kParams_OneObjectRef_OneString_ThreeOptionalFloats);
DEFINE_COMMAND_PLUGIN(GetPlayerPerks, 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(GetNifBlockParentNodes, 1, 2, kParams_OneString_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(GetCrosshairRefEx, 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(IsMobile, 1, 0, NULL);
DEFINE_COMMAND_PLUGIN(IsGrabbable, 1, 0, NULL);
DEFINE_COMMAND_PLUGIN(AttachLight, 1, 5, kParams_OneString_OneForm_ThreeOptionalFloats);
DEFINE_COMMAND_PLUGIN(RemoveLight, 1, 1, kParams_OneString);
DEFINE_COMMAND_PLUGIN(GetExtraFloat, 1, 0, NULL);
DEFINE_COMMAND_PLUGIN(SetExtraFloat, 1, 1, kParams_OneFloat);
DEFINE_COMMAND_PLUGIN(SetLinearVelocity, 1, 5, kParams_OneString_ThreeFloats_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(InsertNode, 0, 23, kParams_OneForm_OneInt_OneFormatString);
DEFINE_COMMAND_PLUGIN(AttachModel, 0, 23, kParams_OneForm_OneInt_OneFormatString);
DEFINE_COMMAND_ALT_PLUGIN(SynchronizePosition, SyncPos, 0, 4, kParams_OneOptionalObjectRef_OneOptionalInt_OneOptionalFloat_OneOptionalString);
DEFINE_COMMAND_PLUGIN(ModelHasBlock, 0, 22, kParams_OneForm_OneFormatString);
DEFINE_COMMAND_PLUGIN(GetRayCastRef, 1, 2, kParams_OneOptionalInt_OneOptionalString);
DEFINE_COMMAND_PLUGIN(GetRayCastMaterial, 1, 2, kParams_OneOptionalInt_OneOptionalString);
DEFINE_COMMAND_PLUGIN(GetCollisionNodes, 1, 0, NULL);
DEFINE_COMMAND_PLUGIN(GetChildBlocks, 1, 2, kParams_OneOptionalString_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(GetBlockTextureSet, 1, 1, kParams_OneString);
DEFINE_COMMAND_PLUGIN(GetPosEx, 1, 3, kParams_ThreeScriptVars);
DEFINE_COMMAND_PLUGIN(GetAngleEx, 1, 4, kParams_ThreeScriptVars_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(SetTextureTransformKey, 1, 4, kParams_OneString_TwoInts_OneFloat);
DEFINE_COMMAND_PLUGIN(AttachExtraCamera, 1, 3, kParams_OneString_OneInt_OneOptionalString);
DEFINE_COMMAND_PLUGIN(ProjectExtraCamera, 0, 4, kParams_TwoStrings_OneFloat_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(RenameNifBlock, 1, 3, kParams_TwoStrings_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(RemoveNifBlock, 1, 2, kParams_OneString_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(PlayAnimSequence, 1, 2, kParams_OneString_OneOptionalString);
DEFINE_COMMAND_PLUGIN(GetTranslatedPos, 1, 6, kParams_ThreeFloats_ThreeScriptVars);
DEFINE_COMMAND_PLUGIN(GetNifBlockTranslationAlt, 1, 6, kParams_OneString_ThreeScriptVars_TwoOptionalInts);
DEFINE_COMMAND_PLUGIN(GetNifBlockRotationAlt, 1, 6, kParams_OneString_ThreeScriptVars_TwoOptionalInts);
DEFINE_COMMAND_PLUGIN(GetLinearVelocityAlt, 1, 5, kParams_OneString_ThreeScriptVars_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(GetAngularVelocityAlt, 1, 5, kParams_OneString_ThreeScriptVars_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(SetAngularVelocityEx, 1, 5, kParams_OneString_ThreeFloats_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(GetCollisionObjProperty, 1, 2, kParams_OneString_OneInt);
DEFINE_COMMAND_PLUGIN(SetCollisionObjProperty, 1, 3, kParams_OneString_OneInt_OneFloat);
DEFINE_COMMAND_PLUGIN(GetCollisionObjLayerType, 1, 1, kParams_OneString);
DEFINE_COMMAND_PLUGIN(SetCollisionObjLayerType, 1, 2, kParams_OneString_OneInt);
DEFINE_COMMAND_PLUGIN(SetRefrModelPath, 1, 1, kParams_OneOptionalString);
DEFINE_COMMAND_PLUGIN(AttachLine, 1, 7, kParams_TwoStrings_FiveFloats);
DEFINE_COMMAND_PLUGIN(ToggleNoZPosReset, 1, 1, kParams_OneInt);

bool Cmd_SetPersistent_Execute(COMMAND_ARGS)
{
	UInt32 doSet;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &doSet) && (!doSet != !(thisObj->flags & TESObjectREFR::kFlags_Persistent)))
		ThisCall(0x565480, thisObj, doSet != 0);
	return true;
}

bool Cmd_GetObjectDimensions_Execute(COMMAND_ARGS)
{
	*result = 0;
	char axis;
	TESForm *form = NULL;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &axis, &form)) return true;
	axis -= 'X';
	float scale = 1.0F;
	if (!form)
	{
		if (!thisObj) return true;
		scale = thisObj->GetScale();
		BSBound *bounds = thisObj->GetBoundingBox();
		if (bounds)
		{
			*result = (bounds->centre[axis] + bounds->dimensions[axis]) * scale;
			return true;
		}
		form = thisObj->baseForm;
	}
	TESBoundObject *object = (TESBoundObject*)form;
	if (object->IsBoundObject())
		*result = abs(object->bounds[axis + 3] - object->bounds[axis]) * scale;
	return true;
}

bool Cmd_GetIsItem_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm *form = NULL;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &form)) return true;
	if (!form)
	{
		if (!thisObj) return true;
		form = thisObj->baseForm;
	}
	*result = kInventoryType[form->typeID];
	return true;
}

bool Cmd_SetLinkedReference_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESObjectREFR *linkRef = NULL;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &linkRef) && thisObj->SetLinkedRef(linkRef, scriptObj->GetOverridingModIdx()))
	{
		*result = 1;
		s_dataChangedFlags |= kChangedFlag_LinkedRefs;
	}
	return true;
}

bool Cmd_GetEnableChildren_Execute(COMMAND_ARGS)
{
	*result = 0;
	ExtraEnableStateChildren *xEnableChildren = GetExtraType(&thisObj->extraDataList, EnableStateChildren);
	if (!xEnableChildren) return true;
	TempElements *tmpElements = GetTempElements();
	auto iter = xEnableChildren->children.Head();
	do
	{
		if (iter->data) tmpElements->Append(iter->data);
	}
	while (iter = iter->next);
	if (!tmpElements->Empty())
		AssignCommandResult(CreateArray(tmpElements->Data(), tmpElements->Size(), scriptObj), result);
	return true;
}

bool Cmd_GetLinkedChildren_Execute(COMMAND_ARGS)
{
	*result = 0;
	ExtraLinkedRefChildren *xLinkedChildren = GetExtraType(&thisObj->extraDataList, LinkedRefChildren);
	if (!xLinkedChildren) return true;
	TempElements *tmpElements = GetTempElements();
	auto iter = xLinkedChildren->children.Head();
	do
	{
		if (iter->data) tmpElements->Append(iter->data);
	}
	while (iter = iter->next);
	if (!tmpElements->Empty())
		AssignCommandResult(CreateArray(tmpElements->Data(), tmpElements->Size(), scriptObj), result);
	return true;
}

bool Cmd_HasPrimitive_Execute(COMMAND_ARGS)
{
	ExtraPrimitive *xPrimitive = GetExtraType(&thisObj->extraDataList, Primitive);
	*result = (xPrimitive && xPrimitive->primitive) ? 1 : 0;
	return true;
}

bool Cmd_GetPrimitiveBound_Execute(COMMAND_ARGS)
{
	*result = -1;
	char axis;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &axis))
	{
		ExtraPrimitive *xPrimitive = GetExtraType(&thisObj->extraDataList, Primitive);
		if (xPrimitive && xPrimitive->primitive)
			*result = xPrimitive->primitive->bounds[axis - 'X'] * 2.0;
	}
	return true;
}

bool Cmd_SetPrimitiveBound_Execute(COMMAND_ARGS)
{
	*result = -1;
	char axis;
	float val;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &axis, &val))
		return true;
	ExtraPrimitive *xPrimitive = GetExtraType(&thisObj->extraDataList, Primitive);
	if (!xPrimitive || !xPrimitive->primitive) return true;
	BGSPrimitive *primitive = xPrimitive->primitive;
	axis -= 'X';
	val *= 0.5F;
	*result = primitive->bounds[axis] * 2.0;
	if (primitive->type == 2)
		primitive->bounds = {val, val, val};
	else primitive->bounds[axis] = val;
	thisObj->Update3D();
	return true;
}

bool Cmd_AddPrimitive_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 type;
	NiVector3 bounds;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &type, &bounds.x, &bounds.y, &bounds.z) && (type >= 1) && (type <= 3) &&
		((thisObj->baseForm->refID == 0x21) || (IS_ID(thisObj->baseForm, TESObjectACTI) && (type != 3))) &&
		!thisObj->extraDataList.HasType(kExtraData_Primitive))
	{
		ExtraPrimitive *xPrimitive = ExtraPrimitive::Create();
		thisObj->extraDataList.AddExtra(xPrimitive);
		UInt32 size = (type == 1) ? 0x4C : 0x34;
		BGSPrimitive *primitive = (BGSPrimitive*)GameHeapAlloc(size);
		MemZero(primitive, size);
		*(UInt32*)primitive = (type == 1) ? kVtbl_BGSPrimitiveBox : ((type == 2) ? kVtbl_BGSPrimitiveSphere : kVtbl_BGSPrimitivePlane);
		primitive->type = type;
		bounds *= 0.5F;
		primitive->bounds.x = bounds.x;
		if (type == 2)
		{
			primitive->bounds.y = bounds.x;
			primitive->bounds.z = bounds.x;
		}
		else
		{
			primitive->bounds.y = (type == 1) ? bounds.y : 1.0F;
			primitive->bounds.z = bounds.z;
		}
		xPrimitive->primitive = primitive;
		thisObj->Update3D();
		*result = 1;
	}
	return true;
}

bool Cmd_GetTeammates_Execute(COMMAND_ARGS)
{
	*result = 0;
	TempElements *tmpElements = GetTempElements();
	auto iter = g_thePlayer->teammates.Head();
	do
	{
		if (iter->data) tmpElements->Append(iter->data);
	}
	while (iter = iter->next);
	if (!tmpElements->Empty())
		AssignCommandResult(CreateArray(tmpElements->Data(), tmpElements->Size(), scriptObj), result);
	return true;
}

bool Cmd_MoveToCell_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESObjectCELL *cell;
	NiVector3 posVector;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &cell, &posVector.x, &posVector.y, &posVector.z))
	{
		if NOT_ID(cell, TESObjectCELL)
		{
			if NOT_ID(cell, TESWorldSpace)
				return true;
			cell = ((TESWorldSpace*)cell)->cell;
		}
		thisObj->MoveToCell(cell, posVector);
		*result = 1;
	}
	return true;
}

bool Cmd_MoveToEditorPosition_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 resetRot = 0;
	if (NUM_ARGS_EX)
		ExtractArgsEx(EXTRACT_ARGS_EX, &resetRot);
	TESObjectCELL *cell;
	NiVector3 *posVector;
	NiVector4 rotVector(_mm_setzero_ps());
	if (IS_ACTOR(thisObj))
	{
		Actor *actor = (Actor*)thisObj;
		cell = (TESObjectCELL*)actor->startingWorldOrCell;
		posVector = &actor->startingPos;
		if (resetRot)
			rotVector.z = actor->startingZRot * Flt180dPI;
	}
	else
	{
		ExtraStartingPosition *xStartingPos = GetExtraType(&thisObj->extraDataList, StartingPosition);
		if (!xStartingPos) return true;
		ExtraStartingWorldOrCell *xStartingCell = GetExtraType(&thisObj->extraDataList, StartingWorldOrCell);
		cell = xStartingCell ? (TESObjectCELL*)xStartingCell->worldOrCell : thisObj->GetParentCell();
		posVector = &xStartingPos->posVector;
		if (resetRot)
		{
			rotVector = xStartingPos->rotVector;
			rotVector *= Flt180dPI;
		}
	}
	if (!cell) return true;
	if NOT_ID(cell, TESObjectCELL)
	{
		if NOT_ID(cell, TESWorldSpace)
			return true;
		cell = ((TESWorldSpace*)cell)->cell;
	}
	thisObj->MoveToCell(cell, *posVector);
	if (resetRot)
		thisObj->SetAngle(rotVector.PS(), false);
	*result = 1;
	return true;
}

bool Cmd_GetCenterPos_Execute(COMMAND_ARGS)
{
	char axis;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &axis))
	{
		axis -= 'X';
		float cntPos = 0;
		BSBound *bounds = thisObj->GetBoundingBox();
		if (bounds)
			cntPos = bounds->centre[axis];
		else
		{
			TESBoundObject *object = (TESBoundObject*)thisObj->baseForm;
			if (object->IsBoundObject())
				cntPos = (object->bounds[axis] + object->bounds[axis + 3]) * 0.5F;
		}
		*result = thisObj->position[axis] + (cntPos * thisObj->GetScale());
	}
	else *result = 0;
	return true;
}

bool Cmd_GetRefType_Execute(COMMAND_ARGS)
{
	TESObjectREFR *objRefr = NULL;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &objRefr) && (objRefr || (objRefr = thisObj)))
	{
		*result = objRefr->typeID;
		DoConsolePrint(result);
	}
	else *result = 0;
	return true;
}

bool Cmd_ToggleObjectCollision_Execute(COMMAND_ARGS)
{
	UInt32 enable;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &enable) && NOT_ACTOR(thisObj) && (!enable == !(thisObj->JIPRefFlags() & kHookRefFlag5F_DisableCollision)))
	{
		thisObj->JIPRefFlags() ^= kHookRefFlag5F_DisableCollision;
		thisObj->Update3D();
	}
	return true;
}

bool Cmd_GetMaterialPropertyValue_Execute(COMMAND_ARGS)
{
	*result = 0;
	char blockName[0x40];
	UInt32 traitID;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &traitID) || (traitID > 8)) return true;
	NiAVObject *block = thisObj->GetNiBlock(blockName);
	if (!block) return true;
	NiMaterialProperty *matProp = (NiMaterialProperty*)block->GetProperty(2);
	if (!matProp) return true;
	switch (traitID)
	{
		case 0:
		case 1:
		case 2:
			*result = matProp->specularRGB[traitID];
			break;
		case 3:
		case 4:
		case 5:
			*result = matProp->emissiveRGB[traitID - 3];
			break;
		case 6:
			*result = matProp->glossiness;
			break;
		case 7:
			*result = matProp->alpha;
			break;
		default:
			*result = matProp->emitMult;
	}
	return true;
}

bool Cmd_SetMaterialPropertyValue_Execute(COMMAND_ARGS)
{
	char blockName[0x40];
	UInt32 traitID;
	float value;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &traitID, &value) && (traitID <= 8) && (value >= 0))
	{
		NiNode *niNode = thisObj->GetNiNode();
		if (niNode)
		{
			if (*(UInt16*)blockName == '*')
				niNode->BulkSetMaterialPropertyTraitValue(traitID, value);
			else
			{
				NiAVObject *block = niNode->GetBlock(blockName);
				if (block)
				{
					NiMaterialProperty *matProp = (NiMaterialProperty*)block->GetProperty(2);
					if (matProp) matProp->SetTraitValue(traitID, value);
				}
			}
		}
	}
	return true;
}

void __fastcall PopulateFormSet(TESForm *form, TempFormList *tmpFormLst)
{
	if IS_ID(form, BGSListForm)
	{
		auto traverse = ((BGSListForm*)form)->list.Head();
		do
		{
			tmpFormLst->Insert(traverse->data);
		}
		while (traverse = traverse->next);
	}
	else tmpFormLst->Insert(form);
}

bool __fastcall GetHasContact(TESObjectREFR *thisObj, TESForm *form)
{
	TempFormList *tmpFormLst = GetTempFormList();
	PopulateFormSet(form, tmpFormLst);
	hkpWorldObject **bodies;
	UInt32 count;
	TESObjectREFR *refr;
	if (IS_ACTOR(thisObj))
	{
		HighProcess *hiProc = (HighProcess*)((Actor*)thisObj)->baseProcess;
		if (!hiProc || hiProc->processLevel) return false;
		bhkCharacterController *charCtrl = hiProc->charCtrl;
		if (!charCtrl) return false;
		if (!charCtrl->byte608 && charCtrl->bodyUnderFeet)
		{
			refr = charCtrl->bodyUnderFeet->GetParentRef();
			if (refr && tmpFormLst->HasKey(refr))
				return true;
		}
		bodies = charCtrl->pointCollector.contactBodies.data;
		count = charCtrl->pointCollector.contactBodies.size;
	}
	else
	{
		NiNode *niNode = thisObj->GetRefNiNode();
		if (!niNode) return false;
		ContactObjects contactObjs;
		niNode->GetContactObjects(contactObjs);
		bodies = contactObjs.Data();
		count = contactObjs.Size();
	}
	for (; count; count--, bodies++)
	{
		refr = (*bodies)->GetParentRef();
		if (refr && tmpFormLst->HasKey(refr))
			return true;
	}
	return false;
}

bool Cmd_GetHasContact_Execute(COMMAND_ARGS)
{
	TESForm *form;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &form))
		*result = GetHasContact(thisObj, form);
	else *result = 0;
	return true;
}

bool __fastcall GetHasContactBase(TESObjectREFR *thisObj, TESForm *form)
{
	TempFormList *tmpFormLst = GetTempFormList();
	PopulateFormSet(form, tmpFormLst);
	hkpWorldObject **bodies;
	UInt32 count;
	TESObjectREFR *refr;
	if (IS_ACTOR(thisObj))
	{
		HighProcess *hiProc = (HighProcess*)((Actor*)thisObj)->baseProcess;
		if (!hiProc || hiProc->processLevel) return false;
		bhkCharacterController *charCtrl = hiProc->charCtrl;
		if (!charCtrl) return false;
		if (!charCtrl->byte608 && charCtrl->bodyUnderFeet)
		{
			refr = charCtrl->bodyUnderFeet->GetParentRef();
			if (refr && tmpFormLst->HasKey(refr->baseForm))
				return true;
		}
		bodies = charCtrl->pointCollector.contactBodies.data;
		count = charCtrl->pointCollector.contactBodies.size;
	}
	else
	{
		NiNode *niNode = thisObj->GetRefNiNode();
		if (!niNode) return false;
		ContactObjects contactObjs;
		niNode->GetContactObjects(contactObjs);
		bodies = contactObjs.Data();
		count = contactObjs.Size();
	}
	for (; count; count--, bodies++)
	{
		refr = (*bodies)->GetParentRef();
		if (refr && tmpFormLst->HasKey(refr->baseForm))
			return true;
	}
	return false;
}

bool Cmd_GetHasContactBase_Execute(COMMAND_ARGS)
{
	TESForm *form;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &form))
		*result = GetHasContactBase(thisObj, form);
	else *result = 0;
	return true;
}

bool __fastcall GetHasContactType(TESObjectREFR *thisObj, UInt32 typeID)
{
	hkpWorldObject **bodies;
	UInt32 count;
	TESObjectREFR *refr;
	if (IS_ACTOR(thisObj))
	{
		HighProcess *hiProc = (HighProcess*)((Actor*)thisObj)->baseProcess;
		if (!hiProc || hiProc->processLevel) return false;
		bhkCharacterController *charCtrl = hiProc->charCtrl;
		if (!charCtrl) return false;
		if (!charCtrl->byte608 && charCtrl->bodyUnderFeet)
		{
			refr = charCtrl->bodyUnderFeet->GetParentRef();
			if (refr && (refr->baseForm->typeID == typeID))
				return true;
		}
		bodies = charCtrl->pointCollector.contactBodies.data;
		count = charCtrl->pointCollector.contactBodies.size;
	}
	else
	{
		NiNode *niNode = thisObj->GetRefNiNode();
		if (!niNode) return false;
		ContactObjects contactObjs;
		niNode->GetContactObjects(contactObjs);
		bodies = contactObjs.Data();
		count = contactObjs.Size();
	}
	for (; count; count--, bodies++)
	{
		refr = (*bodies)->GetParentRef();
		if (refr && (refr->baseForm->typeID == typeID))
			return true;
	}
	return false;
}

bool Cmd_GetHasContactType_Execute(COMMAND_ARGS)
{
	UInt32 typeID;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &typeID))
		*result = GetHasContactType(thisObj, typeID);
	else *result = 0;
	return true;
}

bool Cmd_GetHasContactType_Eval(COMMAND_ARGS_EVAL)
{
	*result = GetHasContactType(thisObj, (UInt32)arg1);
	return true;
}

bool Cmd_GetContactRefs_Execute(COMMAND_ARGS)
{
	*result = 0;
	TempElements *tmpElements = GetTempElements();
	hkpWorldObject **bodies;
	UInt32 count;
	TESObjectREFR *refr;
	if (IS_ACTOR(thisObj))
	{
		HighProcess *hiProc = (HighProcess*)((Actor*)thisObj)->baseProcess;
		if (!hiProc || hiProc->processLevel) return true;
		bhkCharacterController *charCtrl = hiProc->charCtrl;
		if (!charCtrl) return true;
		if (!charCtrl->byte608 && charCtrl->bodyUnderFeet)
		{
			refr = charCtrl->bodyUnderFeet->GetParentRef();
			if (refr) tmpElements->Append(refr);
		}
		bodies = charCtrl->pointCollector.contactBodies.data;
		count = charCtrl->pointCollector.contactBodies.size;
	}
	else
	{
		NiNode *niNode = thisObj->GetRefNiNode();
		if (!niNode) return true;
		ContactObjects contactObjs;
		niNode->GetContactObjects(contactObjs);
		bodies = contactObjs.Data();
		count = contactObjs.Size();
	}
	for (; count; count--, bodies++)
	{
		refr = (*bodies)->GetParentRef();
		if (refr) tmpElements->InsertUnique(refr);
	}
	if (!tmpElements->Empty())
		AssignCommandResult(CreateArray(tmpElements->Data(), tmpElements->Size(), scriptObj), result);
	return true;
}

bool Cmd_GetHasPhantom_Execute(COMMAND_ARGS)
{
	if (IS_ACTOR(thisObj))
	{
		*result = 1;
		return true;
	}
	NiNode *niNode = thisObj->GetRefNiNode();
	*result = (niNode && niNode->HasPhantom()) ? 1 : 0;
	return true;
}

bool Cmd_GetInteractionDisabled_Execute(COMMAND_ARGS)
{
	TESForm *form = NULL;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &form) && (form || (form = thisObj)))
		*result = (form->jipFormFlags6 & kHookFormFlag6_NoPCActivation) ? 1 : 0;
	else *result = 0;
	return true;
}

bool Cmd_SetInteractionDisabled_Execute(COMMAND_ARGS)
{
	UInt32 disable;
	TESForm *form = NULL;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &disable, &form)) return true;
	if (!form)
	{
		if (!thisObj) return true;
		form = thisObj;
	}
	bool add = (disable != 0);
	if (add == !(form->jipFormFlags6 & kHookFormFlag6_NoPCActivation))
	{
		form->SetJIPFlag(kHookFormFlag6_NoPCActivation, add);
		HOOK_MOD(PCActivateRef, add);
		HOOK_MOD(SetRolloverText, add);
	}
	return true;
}

bool Cmd_GetInteractionDisabledType_Execute(COMMAND_ARGS)
{
	UInt32 typeID;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &typeID) && (typeID < kFormType_Max) && kValidFilterForm[typeID])
		*result = s_activationDisabledTypes[typeID] ? 1 : 0;
	else *result = 0;
	return true;
}

bool Cmd_SetInteractionDisabledType_Execute(COMMAND_ARGS)
{
	UInt32 disable, typeID;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &disable, &typeID) && (typeID < kFormType_Max) && kValidFilterForm[typeID] && (!disable == s_activationDisabledTypes[typeID]))
	{
		bool add = (disable != 0);
		s_activationDisabledTypes[typeID] = add;
		HOOK_MOD(PCActivateRef, add);
		HOOK_MOD(SetRolloverText, add);
	}
	return true;
}

bool Cmd_AddRefMapMarker_Execute(COMMAND_ARGS)
{
	if (!thisObj->ValidForHooks()) return true;
	if (!s_refMapMarkersCount)
		s_refMapMarkersList.Head()->next = g_thePlayer->teammates.Head();
	else if (s_refMapMarkersList.IsInList(thisObj)) return true;
	s_refMapMarkersList.Prepend(thisObj);
	s_refMapMarkersCount++;
	HOOK_MOD(CreateMapMarkers, true);
	return true;
}

bool Cmd_RemoveRefMapMarker_Execute(COMMAND_ARGS)
{
	SInt32 idx = s_refMapMarkersList.GetIndexOf(thisObj);
	if ((idx == -1) || (idx >= s_refMapMarkersCount)) return true;
	if (--s_refMapMarkersCount) s_refMapMarkersList.RemoveNth(idx);
	else s_refMapMarkersList.Init();
	HOOK_MOD(CreateMapMarkers, false);
	return true;
}

bool Cmd_RefHasMapMarker_Execute(COMMAND_ARGS)
{
	if (s_refMapMarkersCount)
	{
		SInt32 idx = s_refMapMarkersList.GetIndexOf(thisObj);
		if ((idx >= 0) && (idx < s_refMapMarkersCount))
		{
			*result = 1;
			return true;
		}
	}
	*result = 0;
	return true;
}

bool Cmd_SetPosEx_Execute(COMMAND_ARGS)
{
	NiVector4 posVector;
	UInt32 transform = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &posVector.x, &posVector.y, &posVector.z, &transform))
	{
		if (!transform)
			thisObj->SetPos(posVector);
		else if (transform == 1)
			thisObj->SetPos(thisObj->GetTranslatedPos(posVector));
		else if (transform == 2)
			thisObj->SetPos(posVector += thisObj->position);
	}
	return true;
}

bool Cmd_MoveToReticle_Execute(COMMAND_ARGS)
{
	*result = 0;
	float maxRange = 50000.0F;
	NiVector4 posMods(_mm_setzero_ps());
	UInt32 translate = 0;
	UInt8 numArgs = NUM_ARGS;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &maxRange, &posMods.x, &posMods.y, &posMods.z, &translate))
	{
		TESObjectCELL *cell = g_thePlayer->parentCell;
		NiVector4 coords;
		if (cell && (coords.RayCastCoords(g_mainCamera->WorldTranslate(), g_mainCamera->WorldRotate(), maxRange, 6) || translate))
		{
			if (numArgs > 1)
				coords += posMods;
			if (cell->worldSpace && !(cell = cell->worldSpace->GetCellAtPos(coords.PS())))
				return true;
			thisObj->MoveToCell(cell, coords);
			*result = 1;
		}
	}
	return true;
}

bool Cmd_SetRefName_Execute(COMMAND_ARGS)
{
	char name[0x80];
	name[0] = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &name))
	{
		if (name[0])
		{
			char **namePtr;
			if (s_refNamesMap().Insert(thisObj, &namePtr))
				HOOK_MOD(GetRefName, true);
			else free(*namePtr);
			*namePtr = CopyString(name);
			thisObj->JIPRefFlags() |= kHookRefFlag5F_AltRefName;
		}
		else
		{
			if (s_refNamesMap().EraseFree(thisObj))
				HOOK_MOD(GetRefName, false);
			thisObj->JIPRefFlags() &= ~kHookRefFlag5F_AltRefName;
		}
	}
	return true;
}

bool Cmd_SetAngleEx_Execute(COMMAND_ARGS)
{
	NiVector4 rotVector;
	UInt32 transform = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &rotVector.x, &rotVector.y, &rotVector.z, &transform))
	{
		if (transform <= 1)
			thisObj->SetAngle(rotVector.PS(), transform);
		else thisObj->Rotate(rotVector.PS());
	}
	return true;
}

bool Cmd_GetTeleportDoor_Execute(COMMAND_ARGS)
{
	*result = 0;
	if (thisObj->baseForm && IS_ID(thisObj->baseForm, TESObjectDOOR))
	{
		ExtraTeleport *xTeleport = GetExtraType(&thisObj->extraDataList, Teleport);
		if (xTeleport && xTeleport->data && xTeleport->data->linkedDoor)
			REFR_RES = xTeleport->data->linkedDoor->refID;
	}
	return true;
}

bool Cmd_SetOnCriticalHitEventHandler_Execute(COMMAND_ARGS)
{
	Script *script;
	UInt32 addEvnt;
	Actor *target = NULL;
	TESObjectREFR *source = NULL;
	TESObjectWEAP *weapon = NULL;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &script, &addEvnt, &target, &source, &weapon) || NOT_ID(script, Script)) return true;
	if (target)
	{
		if (NOT_ACTOR(target))
		{
			if (!source) return true;
			target = NULL;
		}
		if (source)
		{
			if NOT_REFERENCE(source)
			{
				if (!weapon) return true;
				source = NULL;
			}
			if (weapon && NOT_ID(weapon, TESObjectWEAP))
				return true;
		}
	}
	CriticalHitEventData evntData(target, source, weapon, script);
	if (addEvnt && s_criticalHitEvents().Find(CriticalHitEventFind(evntData)))
		return true;
	s_criticalHitEvents().Remove(CriticalHitEventRemove(evntData));
	if (addEvnt)
		*s_criticalHitEvents().Append() = evntData;
	return true;
}

bool Cmd_MoveToFadeDelay_Execute(COMMAND_ARGS)
{
	TESObjectREFR *destRef;
	float delayTime;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &destRef, &delayTime))
	{
		if IS_ACTOR(thisObj)
		{
			HighProcess *hiProcess = (HighProcess*)((Actor*)thisObj)->baseProcess;
			if (hiProcess && !hiProcess->processLevel)
			{
				hiProcess->delayTime = delayTime;
				ThisCall(0x8FE9E0, hiProcess, thisObj, destRef, 0, 0, 0);
				return true;
			}
		}
		CdeclCall(ADDR_MoveToMarker, thisObj, destRef, 0, 0, 0);
	}
	return true;
}

bool Cmd_GetCrosshairWater_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESWaterForm *water = NULL;
	TESObjectREFR *refr = g_interfaceManager->crosshairRef;
	if (refr && IS_ID(refr->baseForm, BGSPlaceableWater))
		water = ((BGSPlaceableWater*)refr->baseForm)->water;
	if (water) REFR_RES = water->refID;
	DoConsolePrint(water);
	return true;
}

bool Cmd_IsAnimPlayingEx_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 category, subType = 0, flags = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &category, &subType, &flags))
	{
		AnimData *animData = thisObj->GetAnimData();
		if (animData)
		{
			UInt32 animID;
			const AnimGroupClassify *classify;
			for (UInt16 groupID : animData->animGroupIDs)
			{
				animID = groupID & 0xFF;
				if (animID >= 245) continue;
				classify = &kAnimGroupClassify[animID];
				if ((classify->category == category) && ((category >= 4) || ((!subType || (classify->subType == subType)) && (!flags || (classify->flags & flags)))))
				{
					*result = 1;
					break;
				}
			}
		}
	}
	return true;
}

bool Cmd_GetRigidBodyMass_Execute(COMMAND_ARGS)
{
	*result = 0;
	if (NOT_ACTOR(thisObj))
	{
		NiNode *niNode = thisObj->GetRefNiNode();
		if (niNode) *result = niNode->GetBodyMass(0);
	}
	return true;
}

bool Cmd_PushObject_Execute(COMMAND_ARGS)
{
	NiVector4 forceVector;
	TESObjectREFR *refr = NULL;
	if (NOT_ACTOR(thisObj) && ExtractArgsEx(EXTRACT_ARGS_EX, &forceVector.x, &forceVector.y, &forceVector.z, &forceVector.w, &refr))
	{
		NiNode *niNode = thisObj->GetRefNiNode();
		if (niNode)
		{
			if (!refr) refr = thisObj;
			forceVector += refr->position;
			niNode->ApplyForce(forceVector);
		}
	}
	return true;
}

bool Cmd_MoveToContainer_Execute(COMMAND_ARGS)
{
	TESObjectREFR *target;
	UInt32 clrOwner = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &target, &clrOwner) && kInventoryType[thisObj->baseForm->typeID] && target->baseForm->GetContainer())
	{
		if (thisObj == g_HUDMainMenu->crosshairRef)
			CdeclCall(0x775A00, 0, 0, 0);
		ExtraCount *xCount = GetExtraType(&thisObj->extraDataList, Count);
		SInt32 quantity = xCount ? xCount->count : 1;
		if (clrOwner) thisObj->extraDataList.RemoveByType(kExtraData_Ownership);
		if (target->refID == 0x14)
			ThisCall(0x953FF0, target, thisObj, quantity, 0);
		else
		{
			ThisCall(0x572230, thisObj);
			ThisCall(0x574B30, target, thisObj, quantity, 0, 0);
			if (!(thisObj->flags & 1) && !ThisCall<ModInfo*>(0x484E60, thisObj, 0xFFFFFFFF))
				thisObj->Destroy(true);
		}
	}
	return true;
}

__declspec(naked) NiAVObject* __fastcall GetNifBlock(TESObjectREFR *thisObj, UInt32 pcNode, char *blockName)
{
	__asm
	{
		test	dl, dl
		jz		notPlayer
		cmp		dword ptr [ecx+0xC], 0x14
		jnz		notPlayer
		test	dl, 1
		jz		get1stP
		mov		eax, [ecx+0x64]
		test	eax, eax
		jz		done
		mov		eax, [eax+0x14]
		jmp		gotRoot
	get1stP:
		mov		eax, [ecx+0x694]
		jmp		gotRoot
	notPlayer:
		call	TESObjectREFR::GetNiNode
	gotRoot:
		test	eax, eax
		jz		done
		mov		edx, [esp+4]
		cmp		[edx], 0
		jz		done
		mov		ecx, eax
		call	NiNode::GetBlock
	done:
		retn	4
	}
}

bool Cmd_GetNifBlockTranslation_Execute(COMMAND_ARGS)
{
	*result = 0;
	char blockName[0x40];
	UInt32 getWorld = 0, pcNode = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &getWorld, &pcNode))
	{
		NiAVObject *niBlock = GetNifBlock(thisObj, pcNode, blockName);
		if (niBlock)
		{
			NiVector3 &transltn = getWorld ? niBlock->WorldTranslate() : niBlock->LocalTranslate();
			ArrayElementL elements[3] = {transltn.x, transltn.y, transltn.z};
			AssignCommandResult(CreateArray(elements, 3, scriptObj), result);
		}
	}
	return true;
}

bool Cmd_SetNifBlockTranslation_Execute(COMMAND_ARGS)
{
	char blockName[0x40];
	NiVector3 transltn;
	UInt32 pcNode = 0, transform = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &transltn.x, &transltn.y, &transltn.z, &pcNode, &transform))
	{
		if (blockName[0])
		{
			NiAVObject *niBlock = GetNifBlock(thisObj, pcNode, blockName);
			if (niBlock)
			{
				if (transform)
					niBlock->LocalTranslate() += transltn;
				else niBlock->LocalTranslate() = transltn;
				if IS_NODE(niBlock)
				{
					if NOT_ACTOR(thisObj)
						((NiNode*)niBlock)->ResetCollision();
				}
				else if IS_TYPE(niBlock, NiPointLight)
				{
					NiPointLight *ptLight = (NiPointLight*)niBlock;
					if (ptLight->extraFlags & 1)
						ptLight->vector100 = transltn;
				}
				niBlock->UpdateDownwardPass(kUpdateParams, 0);
			}
		}
		else
		{
			if (transform)
				transltn += thisObj->position;
			thisObj->SetPos(transltn);
		}
	}
	return true;
}

bool Cmd_GetNifBlockRotation_Execute(COMMAND_ARGS)
{
	*result = 0;
	char blockName[0x40];
	UInt32 getMode = 0, pcNode = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &getMode, &pcNode))
	{
		NiAVObject *niBlock = GetNifBlock(thisObj, pcNode, blockName);
		if (niBlock)
		{
			NiVector4 rot;
			__asm
			{
				mov		ecx, niBlock
				lea		eax, [ecx+0x68]
				add		ecx, 0x34
				test	getMode, 1
				cmovnz	ecx, eax
				mov		eax, NiMatrix33::ToEulerPRY
				mov		edx, NiMatrix33::ToEulerPRYInv
				test	getMode, 2
				cmovnz	eax, edx
				call	eax
				mulps	xmm0, PS_V3_180dPI
				movups	rot, xmm0
			}
			ArrayElementL elements[3] = {rot.x, rot.y, rot.z};
			AssignCommandResult(CreateArray(elements, 3, scriptObj), result);
		}
	}
	return true;
}

bool Cmd_SetNifBlockRotation_Execute(COMMAND_ARGS)
{
	char blockName[0x40];
	NiVector4 rot;
	UInt32 transform = 0, pcNode = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &rot.x, &rot.y, &rot.z, &transform, &pcNode))
	{
		if (blockName[0])
		{
			NiAVObject *niBlock = GetNifBlock(thisObj, pcNode, blockName);
			if (niBlock)
			{
				if (!transform)
					niBlock->LocalRotate().FromEulerPRY(rot * GET_PS(8));
				else if (transform == 1)
					niBlock->LocalRotate().Rotate(rot * GET_PS(8));
				else
					niBlock->LocalRotate().FromEulerPRYInv(rot * GET_PS(8));
				if (IS_NODE(niBlock) && NOT_ACTOR(thisObj))
					((NiNode*)niBlock)->ResetCollision();
				niBlock->UpdateDownwardPass(kUpdateParams, 0);
			}
		}
		else if (transform != 1)
			thisObj->SetAngle(rot.PS(), transform);
		else thisObj->Rotate(rot.PS());
	}
	return true;
}

bool Cmd_GetNifBlockScale_Execute(COMMAND_ARGS)
{
	*result = 0;
	char blockName[0x40];
	UInt32 pcNode = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &pcNode))
	{
		NiAVObject *niBlock = GetNifBlock(thisObj, pcNode, blockName);
		if (niBlock) *result = niBlock->m_transformLocal.scale;
	}
	return true;
}

bool Cmd_SetNifBlockScale_Execute(COMMAND_ARGS)
{
	char blockName[0x40];
	float newScale;
	UInt32 pcNode = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &newScale, &pcNode))
	{
		if (blockName[0])
		{
			NiAVObject *niBlock = GetNifBlock(thisObj, pcNode, blockName);
			if (niBlock)
			{
				niBlock->m_transformLocal.scale = newScale;
				if (IS_NODE(niBlock) && NOT_ACTOR(thisObj))
					((NiNode*)niBlock)->ResetCollision();
				niBlock->UpdateDownwardPass(kUpdateParams, 0);
			}
		}
		else ThisCall(0x567490, thisObj, newScale);
	}
	return true;
}

bool Cmd_GetNifBlockFlag_Execute(COMMAND_ARGS)
{
	*result = 0;
	char blockName[0x40];
	UInt32 flagID, pcNode = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &flagID, &pcNode) && (flagID <= 31))
	{
		NiAVObject *niBlock = GetNifBlock(thisObj, pcNode, blockName);
		if (niBlock) *result = (niBlock->m_flags & (1 << flagID)) != 0;
	}
	return true;
}

bool Cmd_SetNifBlockFlag_Execute(COMMAND_ARGS)
{
	char blockName[0x40];
	UInt32 flagID, doSet, pcNode = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &flagID, &doSet, &pcNode) && (flagID <= 26))
	{
		NiAVObject *niBlock = GetNifBlock(thisObj, pcNode, blockName);
		if (niBlock)
		{
			if (doSet) niBlock->m_flags |= (1 << flagID);
			else niBlock->m_flags &= ~(1 << flagID);
		}
	}
	return true;
}

bool Cmd_GetObjectVelocity_Execute(COMMAND_ARGS)
{
	*result = 0;
	char axis = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &axis))
	{
		hkpRigidBody *rigidBody = thisObj->GetRigidBody("");
		if (rigidBody && rigidBody->IsMobile())
		{
			if (axis) *result = rigidBody->motion.linVelocity[axis - 'X'];
			else *result = rigidBody->motion.linVelocity.Length();
		}
	}
	return true;
}

bool Cmd_GetAngularVelocity_Execute(COMMAND_ARGS)
{
	*result = 0;
	char blockName[0x40];
	char axis = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &axis))
	{
		hkpRigidBody *rigidBody = thisObj->GetRigidBody(blockName);
		if (rigidBody && rigidBody->IsMobile())
		{
			__asm
			{
				mov		ecx, rigidBody
				movaps	xmm0, [ecx+0x1C0]
				andps	xmm0, PS_XYZ0Mask
				xorps	xmm1, xmm1
				xor		eax, eax
				mov		al, axis
				sub		al, 'X'
				js		getNet
				shl		al, 4
				mulps	xmm0, [ecx+eax+0xF0]
				haddps	xmm0, xmm1
				haddps	xmm0, xmm1
				jmp		done
			getNet:
				mulps	xmm0, xmm0
				haddps	xmm0, xmm1
				haddps	xmm0, xmm1
				sqrtss	xmm0, xmm0
			done:
				cvtps2pd	xmm0, xmm0
				mov		eax, result
				movq	qword ptr [eax], xmm0
			}
		}
	}
	return true;
}

bool Cmd_SetAngularVelocity_Execute(COMMAND_ARGS)
{
	char blockName[0x40];
	char axis;
	float velocity;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &axis, &velocity))
	{
		hkpRigidBody *rigidBody = thisObj->GetRigidBody(blockName);
		if (rigidBody && rigidBody->IsMobile())
		{
			__asm
			{
				movss	xmm0, velocity
				shufps	xmm0, xmm0, 0x40
				xor		eax, eax
				mov		al, axis
				sub		al, 'X'
				shl		al, 4
				mov		ecx, rigidBody
				mulps	xmm0, [ecx+eax+0xF0]
				movaps	[ecx+0x1C0], xmm0
				CALL_EAX(0xC9C1D0)
			}
		}
	}
	return true;
}

bool Cmd_PlaceAtCell_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm *form;
	UInt32 count;
	TESObjectCELL *worldOrCell;
	TESObjectREFR *tempPosMarker = s_tempPosMarker;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &form, &count, &worldOrCell, &tempPosMarker->position.x, &tempPosMarker->position.y, &tempPosMarker->position.z))
	{
		if NOT_ID(worldOrCell, TESObjectCELL)
		{
			if NOT_ID(worldOrCell, TESWorldSpace)
				return true;
			worldOrCell = ((TESWorldSpace*)worldOrCell)->cell;
		}
		tempPosMarker->parentCell = worldOrCell;
		TESObjectREFR *placedRef = PlaceAtMe(tempPosMarker, form, count, 0, 0, 1);
		if (placedRef) REFR_RES = placedRef->refID;
	}
	return true;
}

bool Cmd_GetRayCastPos_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESGlobal *outX, *outY, *outZ;
	float posZmod, maxRange = 50000.0F;
	UInt32 filter = 6;
	char nodeName[0x40];
	nodeName[0] = 0;
	UInt8 numArgs = NUM_ARGS;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &outX, &outY, &outZ, &posZmod, &filter, &nodeName, &maxRange))
	{
		NiNode *objNode = thisObj->GetNode(nodeName);
		if (objNode)
		{
			NiVector4 coords;
			if (coords.RayCastCoords(objNode->WorldTranslate(), objNode->WorldRotate() + 1, maxRange, filter) || (numArgs >= 7))
			{
				outX->data = coords.x;
				outY->data = coords.y;
				outZ->data = coords.z;
				*result = 1;
			}
		}
	}
	return true;
}

bool Cmd_GetAnimSequenceFrequency_Execute(COMMAND_ARGS)
{
	*result = -1;
	char seqName[0x40];
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &seqName))
	{
		NiNode *rootNode = thisObj->GetNiNode();
		if (rootNode && (NOT_ACTOR(thisObj) || (((Actor*)thisObj)->lifeState != 1)))
		{
			NiControllerManager *ctrlMgr = (NiControllerManager*)rootNode->m_controller;
			if (ctrlMgr && IS_TYPE(ctrlMgr, NiControllerManager))
			{
				NiControllerSequence *sequence = ctrlMgr->FindSequence(seqName);
				if (sequence) *result = sequence->frequency;
			}
		}
	}
	return true;
}

bool Cmd_SetAnimSequenceFrequency_Execute(COMMAND_ARGS)
{
	char seqName[0x40];
	float frequency;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &seqName, &frequency))
	{
		NiNode *rootNode = thisObj->GetNiNode();
		if (rootNode && (NOT_ACTOR(thisObj) || (((Actor*)thisObj)->lifeState != 1)))
		{
			NiControllerManager *ctrlMgr = (NiControllerManager*)rootNode->m_controller;
			if (ctrlMgr && IS_TYPE(ctrlMgr, NiControllerManager))
			{
				if (seqName[0] == '*')
					for (auto iter = ctrlMgr->sequences.Begin(); iter; ++iter)
						iter->frequency = frequency;
				else
				{
					NiControllerSequence *sequence = ctrlMgr->FindSequence(seqName);
					if (sequence) sequence->frequency = frequency;
				}
			}
		}
	}
	return true;
}

bool Cmd_MoveToNode_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESObjectREFR *targetRef;
	char nodeName[0x40];
	NiVector4 posMods(_mm_setzero_ps());
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &targetRef, &nodeName, &posMods.x, &posMods.y, &posMods.z))
	{
		TESObjectCELL *cell = targetRef->GetParentCell();
		if (cell)
		{
			NiNode *targetNode = targetRef->GetNode(nodeName);
			if (targetNode)
			{
				posMods += targetNode->WorldTranslate();
				thisObj->MoveToCell(cell, posMods);
				*result = 1;
			}
		}
	}
	return true;
}

bool Cmd_GetPlayerPerks_Execute(COMMAND_ARGS)
{
	*result = 0;
	TempElements *tmpElements = GetTempElements();
	auto iter = g_thePlayer->perkRanksPC.Head();
	BGSPerk *perk;
	do
	{
		if (iter->data)
		{
			perk = iter->data->perk;
			if (perk && !perk->data.isHidden)
				tmpElements->Append(perk);
		}
	}
	while (iter = iter->next);
	AssignCommandResult(CreateArray(tmpElements->Data(), tmpElements->Size(), scriptObj), result);
	return true;
}

bool Cmd_GetNifBlockParentNodes_Execute(COMMAND_ARGS)
{
	*result = 0;
	char blockName[0x40];
	UInt32 pcNode = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &pcNode))
	{
		NiNode *rootNode;
		if (pcNode && (thisObj->refID == 0x14))
		{
			if (pcNode & 1)
				rootNode = thisObj->GetRefNiNode();
			else rootNode = ((PlayerCharacter*)thisObj)->node1stPerson;
		}
		else rootNode = thisObj->GetNiNode();
		if (rootNode)
		{
			NiAVObject *niBlock = rootNode->GetBlock(blockName);
			if (niBlock)
			{
				TempElements *tmpElements = GetTempElements();
				while ((niBlock != rootNode) && (niBlock = niBlock->m_parent))
					tmpElements->Append(niBlock->GetName());
				AssignCommandResult(CreateArray(tmpElements->Data(), tmpElements->Size(), scriptObj), result);
			}
		}
	}
	return true;
}

__declspec(naked) TESObjectREFR *GetCrosshairRef()
{
	__asm
	{
		push	ebp
		mov		ebp, esp
		sub		esp, 0x10
		mov		ecx, g_thePlayer
		movups	xmm0, [ecx+0xDD4]
		cmp		byte ptr [ecx+0x64B], 0
		jz		firstPerson
		movups	xmm1, [ecx+0xD58]
		addps	xmm0, xmm1
	firstPerson:
		lea		edx, [ebp-0x10]
		movups	[edx], xmm0
		mov		eax, [ecx+0x64]
		mov		ecx, [eax+0x14]
		push	dword ptr [ecx+0x84]
		push	dword ptr [ecx+0x78]
		push	dword ptr [ecx+0x6C]
		lea		ecx, [ebp-0x1C]
		lea		eax, [ebp-4]
		push	eax
		push	eax
		push	0x46400000
		push	ecx
		push	edx
		mov		ecx, g_interfaceManager
		mov		ecx, [ecx+0x13C]
		CALL_EAX(0x631D60)
		leave
		retn
	}
}

bool Cmd_GetCrosshairRefEx_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESObjectREFR *resRefr = g_interfaceManager->crosshairRef;
	if (!resRefr)
	{
		resRefr = GetCrosshairRef();
		if (!resRefr) return true;
	}
	REFR_RES = resRefr->refID;
	return true;
}

bool Cmd_IsMobile_Execute(COMMAND_ARGS)
{
	*result = thisObj->IsMobile();
	return true;
}

bool Cmd_IsGrabbable_Execute(COMMAND_ARGS)
{
	*result = thisObj->IsGrabbable();
	return true;
}

bool Cmd_AttachLight_Execute(COMMAND_ARGS)
{
	*result = 0;
	char nodeName[0x40];
	TESObjectLIGH *lightForm;
	NiVector4 offsetMod(_mm_setzero_ps());
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &nodeName, &lightForm, &offsetMod.x, &offsetMod.y, &offsetMod.z) && IS_ID(lightForm, TESObjectLIGH))
	{
		NiNode *objNode = thisObj->GetNode2(nodeName);
		if (objNode)
		{
			NiPointLight *pointLight = CreatePointLight(lightForm, objNode);
			pointLight->LocalTranslate() = offsetMod;
			pointLight->extraFlags |= 0x80;
			*result = 1;
		}
	}
	return true;
}

bool Cmd_RemoveLight_Execute(COMMAND_ARGS)
{
	char nodeName[0x40];
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &nodeName))
	{
		NiNode *objNode = thisObj->GetNode2(nodeName);
		if (objNode)
		{
			NiPointLight *pointLight;
			for (auto iter = objNode->m_children.Begin(); iter; ++iter)
			{
				if (!(pointLight = (NiPointLight*)*iter) || NOT_TYPE(pointLight, NiPointLight) || !(pointLight->extraFlags & 0x80))
					continue;
				objNode->RemoveObject(pointLight);
				break;
			}
		}
	}
	return true;
}

bool Cmd_GetExtraFloat_Execute(COMMAND_ARGS)
{
	*result = 0;
	ExtraDataList *xData = NULL;
	InventoryRef *invRef = InventoryRefGetForID(thisObj->refID);
	if (invRef)
		xData = invRef->xData;
	else xData = &thisObj->extraDataList;
	if (xData)
	{
		ExtraTimeLeft *xTimeLeft = GetExtraType(xData, TimeLeft);
		if (xTimeLeft)
			*result = xTimeLeft->timeLeft;
	}
	return true;
}

bool Cmd_SetExtraFloat_Execute(COMMAND_ARGS)
{
	float fltVal;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &fltVal))
	{
		ExtraDataList *xData = NULL;
		InventoryRef *invRef = InventoryRefGetForID(thisObj->refID);
		if (invRef)
		{
			xData = invRef->xData;
			if (!xData)
			{
				if (xData = invRef->CreateExtraData())
				{
					SInt32 count = invRef->GetCount();
					if (count > 1)
						xData->AddExtra(ExtraCount::Create(count));
					xData->AddExtra(ExtraTimeLeft::Create(fltVal));
				}
				return true;
			}
		}
		else xData = &thisObj->extraDataList;
		ExtraTimeLeft *xTimeLeft = GetExtraType(xData, TimeLeft);
		if (xTimeLeft)
			xTimeLeft->timeLeft = fltVal;
		else xData->AddExtra(ExtraTimeLeft::Create(fltVal));
	}
	return true;
}

bool Cmd_SetLinearVelocity_Execute(COMMAND_ARGS)
{
	*result = 0;
	char blockName[0x40];
	hkVector4 velocity(_mm_setzero_ps());
	UInt32 setLocal = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &velocity.x, &velocity.y, &velocity.z, &setLocal))
	{
		hkpRigidBody *rigidBody = thisObj->GetRigidBody(blockName);
		if (rigidBody && rigidBody->IsMobile())
		{
			rigidBody->motion.linVelocity = setLocal ? rigidBody->motion.motionState.transform.rotation.MultiplyVectorInv(velocity) : velocity;
			rigidBody->UpdateMotion();
			*result = 1;
		}
	}
	return true;
}

bool __fastcall RegisterInsertObject(TESForm *form, int EDX, char *inData)
{
	static char meshesPath[0x80] = "data\\meshes\\";
	TESObjectREFR *refr = IS_REFERENCE(form) ? (TESObjectREFR*)form : NULL;
	NiNode *rootNode = refr ? refr->GetRefNiNode() : NULL;
	bool result = false, modifyMap = true;
	char doInsert = *inData;
	if (refr)
	{
		if (refr->IsCreated() || kInventoryType[refr->baseForm->typeID])
		{
			if ((doInsert != 3) || !rootNode)
				goto freeDataStr;
			modifyMap = false;
		}
	}
	else if (!form->IsBoundObject())
		goto freeDataStr;

	char *pInData = inData + 2, *nodeName = NULL, *objectName = FindChr(pInData, '|'), *suffix;
	if (objectName)
	{
		*objectName++ = 0;
		nodeName = pInData;
	}
	else objectName = pInData;

	if (!*objectName) goto freeDataStr;

	UInt8 flag = ((UInt8*)inData)[1];
	bool insertNode = flag == kHookFormFlag6_InsertNode;
	auto formsMap = insertNode ? *s_insertNodeMap : *s_attachModelMap;

	if (doInsert & 1)
	{
		if (!insertNode)
		{
			suffix = objectName;
			if (*objectName == '*')
			{
				if (!(suffix = FindChr(objectName + 2, '*')))
					goto freeDataStr;
				suffix++;
			}
			StrCopy(meshesPath + 12, suffix);
			if (!FileExistsEx(meshesPath, false))
				goto freeDataStr;
		}

		NiFixedString blockName(nodeName), dataStr, *pDataStr;
		if (modifyMap)
		{
			NodeNamesMap *namesMap;
			if (formsMap->Insert(form, &namesMap))
				form->SetJIPFlag(flag, true);
			if (!(*namesMap)[blockName].Insert(objectName, &pDataStr))
				goto freeDataStr;
		}
		else pDataStr = &dataStr;

		if (insertNode)
			*pDataStr = objectName + (*objectName == '^');

		if (rootNode && (doInsert & 2))
		{
			bool useRoot = !blockName || (rootNode->m_blockName == blockName);
			NiAVObject *targetObj = useRoot ? rootNode : rootNode->GetBlockByName(blockName);
			if (targetObj)
			{
				if (insertNode)
					DoInsertNode(targetObj, objectName, *pDataStr, rootNode);
				else if ((rootNode = DoAttachModel(targetObj, objectName, pDataStr, rootNode)) && (rootNode->m_flags & 0x20000000))
					AddPointLights(rootNode);
			}
			if ((refr->refID == 0x14) && (rootNode = s_pc1stPersonNode))
			{
				targetObj = useRoot ? rootNode : rootNode->GetBlockByName(blockName);
				if (targetObj)
				{
					if (insertNode)
						DoInsertNode(targetObj, objectName, *pDataStr, rootNode);
					else DoAttachModel(targetObj, objectName, pDataStr, rootNode);
				}
			}
		}
	}
	else
	{
		auto findForm = formsMap->Find(form);
		if (!findForm) goto freeDataStr;
		auto findNode = findForm().FindOp(NiFixedString(nodeName));
		if (!findNode) goto freeDataStr;
		auto findData = findNode().FindOp(objectName);
		if (!findData) goto freeDataStr;
		if (rootNode && (doInsert & 2) && findData() && (!insertNode || (*objectName != '^')))
		{
			NiAVObject *object = rootNode->GetBlockByName(findData());
			if (object)
				object->m_parent->RemoveObject(object);
			if ((refr->refID == 0x14) && (rootNode = s_pc1stPersonNode))
			{
				object = rootNode->GetBlockByName(findData());
				if (object)
					object->m_parent->RemoveObject(object);
			}
		}
		findData.Remove(findNode());
		if (findNode().Empty())
		{
			findNode.Remove(findForm());
			if (findForm().Empty())
			{
				findForm.Remove();
				form->SetJIPFlag(flag, false);
			}
		}
	}
	s_insertObjects = !s_insertNodeMap->Empty() || !s_attachModelMap->Empty();
	result = true;
freeDataStr:
	Pool_Free(inData, 0x80);
	return result;
}

bool Cmd_InsertNode_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm *form;
	char *dataStr = (char*)Pool_Alloc(0x80);
	if (ExtractFormatStringArgs(2, dataStr + 2, EXTRACT_ARGS_EX, kCommandInfo_InsertNode.numParams, &form, dataStr))
	{
		((UInt8*)dataStr)[1] = kHookFormFlag6_InsertNode;
		if (!(*dataStr & 2) || IsInMainThread())
			*result = RegisterInsertObject(form, 0, dataStr);
		else MainLoopAddCallbackArgs(RegisterInsertObject, form, 1, dataStr);
	}
	else Pool_Free(dataStr, 0x80);
	return true;
}

bool Cmd_AttachModel_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm *form;
	char *dataStr = (char*)Pool_Alloc(0x80);
	if (ExtractFormatStringArgs(2, dataStr + 2, EXTRACT_ARGS_EX, kCommandInfo_AttachModel.numParams, &form, dataStr))
	{
		((UInt8*)dataStr)[1] = kHookFormFlag6_AttachModel;
		if (!(*dataStr & 2) || IsInMainThread())
			*result = RegisterInsertObject(form, 0, dataStr);
		else MainLoopAddCallbackArgs(RegisterInsertObject, form, 1, dataStr);
	}
	else Pool_Free(dataStr, 0x80);
	return true;
}

bool Cmd_SynchronizePosition_Execute(COMMAND_ARGS)
{
	TESObjectREFR *targetRef = NULL;
	UInt32 syncRot = 0;
	s_syncPositionMods.z = 0;
	char nodeName[0x40];
	nodeName[0] = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &targetRef, &syncRot, &s_syncPositionMods.z, &nodeName))
	{
		TESObjectCELL *cell;
		if (targetRef)
		{
			if (g_thePlayer->GetDistance(targetRef) > 1024.0F)
			{
				cell = targetRef->GetParentCell();
				if (cell) g_thePlayer->MoveToCell(cell, targetRef->position);
			}
			s_syncPositionFlags = (syncRot != 0);
			s_syncPositionPos = targetRef->position;
			s_syncPositionNode() = nodeName;
			s_syncPositionRef = targetRef;
		}
		else if (targetRef = s_syncPositionRef)
		{
			s_syncPositionRef = NULL;
			cell = targetRef->GetParentCell();
			if (cell) g_thePlayer->MoveToCell(cell, s_syncPositionPos);
		}
	}
	return true;
}

bool Cmd_ModelHasBlock_Execute(COMMAND_ARGS)
{
	char buffer[0x80];
	buffer[0] = '^';
	TESForm *form;
	if (ExtractFormatStringArgs(1, buffer + 1, EXTRACT_ARGS_EX, kCommandInfo_ModelHasBlock.numParams, &form))
	{
		TESObjectREFR *refr = IS_REFERENCE(form) ? (TESObjectREFR*)form : NULL;
		NiNode *rootNode = refr ? refr->GetNiNode() : NULL;
		if (rootNode && rootNode->GetBlock(buffer + 1))
			goto Retn1;
		NodeNamesMap *namesMap = s_insertNodeMap->GetPtr(form);
		if (namesMap)
		{
			for (auto iter = namesMap->Begin(); iter; ++iter)
				if (iter().HasKey(buffer + 1) || iter().HasKey(buffer))
					goto Retn1;
		}
		if (refr)
		{
			form = refr->GetBaseForm2();
			if (!form) goto Retn0;
			namesMap = s_insertNodeMap->GetPtr(form);
			if (namesMap)
			{
				for (auto iter = namesMap->Begin(); iter; ++iter)
					if (iter().HasKey(buffer + 1) || iter().HasKey(buffer))
						goto Retn1;
			}
		}
		if (!rootNode && form->IsBoundObject())
		{
			const char *modelPath = form->GetModelPath();
			if (modelPath)
			{
				rootNode = g_modelLoader->LoadModel(modelPath, 0, 1, 0, 1);
				if (rootNode && rootNode->GetBlock(buffer + 1))
					goto Retn1;
			}
		}
	}
Retn0:
	*result = 0;
	return true;
Retn1:
	*result = 1;
	return true;
}

bool Cmd_GetRayCastRef_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 filter = 6;
	char nodeName[0x40];
	nodeName[0] = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &filter, &nodeName))
	{
		NiNode *objNode = thisObj->GetNode(nodeName);
		if (objNode)
		{
			NiAVObject *rcObject = GetRayCastObject(objNode->WorldTranslate(), objNode->WorldRotate() + 1, 50000.0F, filter & 0x3F);
			if (rcObject)
			{
				TESObjectREFR *resRefr = rcObject->GetParentRef();
				if (resRefr) REFR_RES = resRefr->refID;
			}
		}
	}
	return true;
}

bool Cmd_GetRayCastMaterial_Execute(COMMAND_ARGS)
{
	UInt32 filter = 6;
	char nodeName[0x40];
	nodeName[0] = 0;
	int material = -1;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &filter, &nodeName))
	{
		NiNode *objNode = thisObj->GetNode(nodeName);
		if (objNode)
			material = GetRayCastMaterial(objNode->WorldTranslate(), objNode->WorldRotate() + 1, 50000.0F, filter & 0x3F);
	}
	*result = material;
	return true;
}

void GetCollisionNodes(NiNode *node, TempElements *tmpElements)
{
	if (node->m_collisionObject)
	{
		bhkWorldObject *hWorldObj = node->m_collisionObject->worldObj;
		if (hWorldObj)
		{
			hkpRigidBody *rigidBody = (hkpRigidBody*)hWorldObj->refObject;
			UInt8 motionType = rigidBody->motion.type;
			if ((motionType == 2) || (motionType == 3) || (motionType == 6))
				tmpElements->Append(node->GetName());
		}
	}
	for (auto iter = node->m_children.Begin(); iter; ++iter)
		if (*iter && IS_NODE(*iter))
			GetCollisionNodes((NiNode*)*iter, tmpElements);
}

bool Cmd_GetCollisionNodes_Execute(COMMAND_ARGS)
{
	*result = 0;
	NiNode *rootNode = thisObj->GetRefNiNode();
	if (rootNode)
	{
		TempElements *tmpElements = GetTempElements();
		GetCollisionNodes(rootNode, tmpElements);
		if (!tmpElements->Empty())
			AssignCommandResult(CreateArray(tmpElements->Data(), tmpElements->Size(), scriptObj), result);
	}
	return true;
}

void GetChildBlocks(NiNode *node, TempElements *tmpElements)
{
	tmpElements->Append(node->GetName());
	NiAVObject *block;
	for (auto iter = node->m_children.Begin(); iter; ++iter)
	{
		if (!(block = *iter)) continue;
		if IS_NODE(block)
			GetChildBlocks((NiNode*)block, tmpElements);
		else tmpElements->Append(block->GetName());
	}
}

bool Cmd_GetChildBlocks_Execute(COMMAND_ARGS)
{
	*result = 0;
	char blockName[0x40];
	blockName[0] = 0;
	UInt32 pcNode = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &pcNode))
	{
		NiNode *objNode = (NiNode*)GetNifBlock(thisObj, pcNode, blockName);
		if (objNode && IS_NODE(objNode))
		{
			TempElements *tmpElements = GetTempElements();
			GetChildBlocks(objNode, tmpElements);
			UInt32 size = tmpElements->Size();
			if (size > 1)
				AssignCommandResult(CreateArray(tmpElements->Data() + 1, size - 1, scriptObj), result);
		}
	}
	return true;
}

bool Cmd_GetBlockTextureSet_Execute(COMMAND_ARGS)
{
	*result = 0;
	char blockName[0x40];
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName))
	{
		NiAVObject *block = thisObj->GetNiBlock(blockName);
		if (block && block->GetTriBasedGeom())
		{
			BSShaderProperty *shaderProp = (BSShaderProperty*)block->GetProperty(3);
			if (shaderProp)
			{
				ArrayElementL elements[6];
				const char *filePath;
				bool createArr = false;
				if (shaderProp->shaderType == BSShaderProperty::kType_PPLighting)
				{
					BSShaderPPLightingProperty *lightingProp = (BSShaderPPLightingProperty*)shaderProp;
					if (lightingProp->textureSet)
					{
						createArr = true;
						String *textures = lightingProp->textureSet->textures;
						UInt32 index = 0;
						do
						{
							filePath = textures[index].CStr();
							if (*filePath && StrBeginsCI(filePath, "data\\textures\\"))
								filePath += 14;
							elements[index] = filePath;
						}
						while (++index < 6);
					}
				}
				else if (shaderProp->shaderType == BSShaderProperty::kType_NoLighting)
				{
					BSShaderNoLightingProperty *noLightingProp = (BSShaderNoLightingProperty*)shaderProp;
					if (noLightingProp->srcTexture && IS_TYPE(noLightingProp->srcTexture, NiSourceTexture))
					{
						filePath = ((NiSourceTexture*)noLightingProp->srcTexture)->ddsPath1;
						if (filePath)
						{
							createArr = true;
							if (StrBeginsCI(filePath, "data\\textures\\"))
								filePath += 14;
							UInt32 index = 0;
							do
							{
								elements[index] = filePath;
								filePath = "";
							}
							while (++index < 6);
						}
					}
				}
				if (createArr)
					AssignCommandResult(CreateArray(elements, 6, scriptObj), result);
			}
		}
	}
	return true;
}

bool Cmd_GetPosEx_Execute(COMMAND_ARGS)
{
	ResultVars outPos;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &outPos.x, &outPos.y, &outPos.z))
		outPos.Set(thisObj->position.PS());
	return true;
}

bool Cmd_GetAngleEx_Execute(COMMAND_ARGS)
{
	ResultVars outRot;
	UInt32 getLocal = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &outRot.x, &outRot.y, &outRot.z, &getLocal))
	{
		__m128 angles;
		if (!getLocal)
			angles = thisObj->rotation.PS();
		else
		{
			NiNode *rootNode = thisObj->GetRefNiNode();
			if (rootNode && (thisObj->refID != 0x14))
				angles = rootNode->WorldRotate().ToEulerPRYInv();
			else
			{
				NiMatrix33 rotMat = thisObj->rotation;
				angles = rotMat.ToEulerPRYInv();
			}
		}
		outRot.Set(angles, GET_PS(9));
	}
	return true;
}

bool Cmd_SetTextureTransformKey_Execute(COMMAND_ARGS)
{
	char blockName[0x40];
	UInt32 ctrlIndex, keyIndex;
	float value;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &ctrlIndex, &keyIndex, &value))
	{
		NiAVObject *block = thisObj->GetNiBlock(blockName);
		if (block && block->GetTriBasedGeom())
		{
			NiTexturingProperty *texProp = (NiTexturingProperty*)block->GetProperty(5);
			if (texProp)
			{
				NiTextureTransformController *ctrlr = (NiTextureTransformController*)texProp->m_controller;
				while (ctrlr && ctrlIndex)
				{
					ctrlIndex--;
					ctrlr = (NiTextureTransformController*)ctrlr->nextCtrl;
				}
				if (ctrlr && IS_TYPE(ctrlr, NiTextureTransformController))
				{
					NiFloatInterpolator *intrpl = (NiFloatInterpolator*)ctrlr->interpolator;
					if (intrpl && IS_TYPE(intrpl, NiFloatInterpolator))
					{
						NiFloatData *fltData = intrpl->data;
						if (fltData && IS_TYPE(fltData, NiFloatData) && (keyIndex < fltData->numKeys))
							fltData->data[keyIndex].value = value;
					}
				}
			}
		}
	}
	return true;
}

bool Cmd_AttachExtraCamera_Execute(COMMAND_ARGS)
{
	*result = 0;
	char camName[0x40], nodeName[0x40];
	UInt32 doAttach;
	nodeName[0] = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &camName, &doAttach, &nodeName) && camName[0])
	{
		NiCamera *xCamera;
		if (doAttach)
		{
			NiNode *targetNode = thisObj->GetNode2(nodeName);
			if (targetNode)
			{
				NiCamera **pCamera;
				if (s_extraCamerasMap().Insert(camName, &pCamera))
				{
					*pCamera = xCamera = NiCamera::Create();
					InterlockedIncrement(&xCamera->m_uiRefCount);
					xCamera->SetName(camName);
					xCamera->frustum.n = 5.0F;
					xCamera->frustum.f = 353840.0F;
					xCamera->minNearPlaneDist = 1.0F;
					xCamera->maxFarNearRatio = 70768.0F;
					xCamera->LODAdjust = 0.001F;
				}
				else xCamera = *pCamera;
				if (xCamera->m_parent != targetNode)
				{
					targetNode->AddObject(xCamera, 1);
					xCamera->UpdateDownwardPass(kUpdateParams, 0);
				}
				*result = 1;
			}
		}
		else if (xCamera = s_extraCamerasMap().GetErase(camName))
		{
			if (xCamera->m_parent)
				xCamera->m_parent->RemoveObject(xCamera);
			xCamera->Destructor(true);
			*result = 1;
		}
	}
	return true;
}

void __fastcall GenerateRenderedTexture(TESObjectCELL *cell, int EDX, NiCamera *camera, RenderTarget **outTexture);

__declspec(naked) void __stdcall ProjectExtraCamera(NiCamera *camera, NiTexture **pTexture)
{
	__asm
	{
		push	ebp
		mov		ebp, esp
		mov		byte ptr ds:[0x11AD7B4], 0
		push	0
		push	esp
		push	dword ptr [ebp+8]
		xor		ecx, ecx
		call	GenerateRenderedTexture
		mov		byte ptr ds:[0x11AD7B4], 1
		mov		ecx, [ebp-4]
		test	ecx, ecx
		jz		done
		mov		eax, [ecx+0x30]
		test	eax, eax
		jz		doRelease
		push	eax
		push	dword ptr [ebp+0xC]
		call	NiReleaseAddRef
		mov		ecx, [ebp-4]
	doRelease:
		call	NiReleaseObject
	done:
		leave
		retn	8
	}
}

UInt32 s_projectPixelSize = 0x100;

bool Cmd_ProjectExtraCamera_Execute(COMMAND_ARGS)
{
	*result = 0;
	char camName[0x40], nodeName[0x40];
	float fov;
	UInt32 pixelSize = 0x100;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &camName, &nodeName, &fov, &pixelSize))
	{
		NiCamera *xCamera = s_extraCamerasMap().Get(camName);
		if (xCamera && xCamera->m_parent)
		{
			NiTexture **pTexture = NULL;
			if (nodeName[0] == '*')
			{
				TileImage *targetTile = (TileImage*)GetTargetComponent(nodeName + 1);
				if (targetTile && IS_TYPE(targetTile, TileImage) && targetTile->shaderProp)
					pTexture = &targetTile->shaderProp->srcTexture;
			}
			else if (thisObj)
			{
				NiAVObject *targetGeom = thisObj->GetNiBlock(nodeName);
				if (targetGeom && targetGeom->GetTriBasedGeom())
				{
					BSShaderNoLightingProperty *shaderProp = (BSShaderNoLightingProperty*)targetGeom->GetProperty(3);
					if (shaderProp && (shaderProp->shaderType == BSShaderProperty::kType_NoLighting))
						pTexture = &shaderProp->srcTexture;
				}
			}
			if (pTexture)
			{
				xCamera->frustum.viewPort.SetFOV(fov * FltPId180);
				s_projectPixelSize = pixelSize;
				HighActorCuller::Run(xCamera);
				ProjectExtraCamera(xCamera, pTexture);
				*result = 1;
			}
		}
	}
	return true;
}

bool Cmd_RenameNifBlock_Execute(COMMAND_ARGS)
{
	*result = 0;
	char blockName[0x40], newName[0x40];
	UInt32 pcNode = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &newName, &pcNode))
	{
		NiAVObject *niBlock = GetNifBlock(thisObj, pcNode, blockName);
		if (niBlock)
		{
			niBlock->SetName(newName);
			*result = 1;
		}
	}
	return true;
}

bool Cmd_RemoveNifBlock_Execute(COMMAND_ARGS)
{
	*result = 0;
	char blockName[0x40];
	UInt32 pcNode = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &pcNode))
	{
		NiAVObject *niBlock = GetNifBlock(thisObj, pcNode, blockName);
		if (niBlock)
		{
			niBlock->m_parent->RemoveObject(niBlock);
			*result = 1;
		}
	}
	return true;
}

bool Cmd_PlayAnimSequence_Execute(COMMAND_ARGS)
{
	*result = 0;
	char sequenceName[0x60], nodeName[0x40];
	nodeName[0] = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &sequenceName, &nodeName))
	{
		NiNode *targetNode = thisObj->GetNode(nodeName);
		if (targetNode && (NOT_ACTOR(thisObj) || (((Actor*)thisObj)->lifeState != 1)))
		{
			NiControllerManager *ctrlMgr = (NiControllerManager*)targetNode->m_controller;
			if (ctrlMgr && IS_TYPE(ctrlMgr, NiControllerManager))
			{
				NiControllerSequence *sequence = ctrlMgr->FindSequence(sequenceName);
				if (sequence)
				{
					for (auto iter = ctrlMgr->sequences.Begin(); iter; ++iter)
						if (*iter && iter->sequenceName && (*(UInt32*)iter->sequenceName != 'eldI'))
							iter->Unk_23(0, 0);
					if (sequence->Play())
					{
						//thisObj->Unk_32(1);
						thisObj->MarkAsModified(0x10000000);
						*result = 1;
					}
				}
			}
		}
	}
	return true;
}

bool Cmd_GetTranslatedPos_Execute(COMMAND_ARGS)
{
	NiVector4 posMods;
	ResultVars outPos;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &posMods.x, &posMods.y, &posMods.z, &outPos.x, &outPos.y, &outPos.z))
	{
		outPos.Set(thisObj->GetTranslatedPos(posMods).PS());
		*result = 1;
	}
	else *result = 0;
	return true;
}

bool Cmd_GetNifBlockTranslationAlt_Execute(COMMAND_ARGS)
{
	*result = 0;
	char blockName[0x40];
	ResultVars outPos;
	UInt32 getWorld = 0, pcNode = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &outPos.x, &outPos.y, &outPos.z, &getWorld, &pcNode))
	{
		NiAVObject *niBlock = GetNifBlock(thisObj, pcNode, blockName);
		if (niBlock)
		{
			outPos.Set(getWorld ? niBlock->WorldTranslate().PS() : niBlock->LocalTranslate().PS());
			*result = 1;
		}
	}
	return true;
}

bool Cmd_GetNifBlockRotationAlt_Execute(COMMAND_ARGS)
{
	*result = 0;
	char blockName[0x40];
	ResultVars outRot;
	UInt32 getMode = 0, pcNode = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &outRot.x, &outRot.y, &outRot.z, &getMode, &pcNode))
	{
		NiAVObject *niBlock = GetNifBlock(thisObj, pcNode, blockName);
		if (niBlock)
		{
			NiMatrix33 &rotMat = (getMode & 1) ? niBlock->WorldRotate() : niBlock->LocalRotate();
			__m128 angles = (getMode & 2) ? rotMat.ToEulerPRYInv() : rotMat.ToEulerPRY();
			outRot.Set(angles, GET_PS(9));
			*result = 1;
		}
	}
	return true;
}

bool Cmd_GetLinearVelocityAlt_Execute(COMMAND_ARGS)
{
	*result = 0;
	char blockName[0x40];
	ResultVars outVel;
	UInt32 getLocal = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &outVel.x, &outVel.y, &outVel.z, &getLocal))
	{
		hkpRigidBody *rigidBody = thisObj->GetRigidBody(blockName);
		if (rigidBody && rigidBody->IsMobile())
		{
			if (!getLocal)
				outVel.Set(rigidBody->motion.linVelocity.PS());
			else
			{
				hkVector4 velocity = rigidBody->motion.linVelocity;
				outVel.Set(rigidBody->motion.motionState.transform.rotation.MultiplyVector(velocity));
			}
			*result = 1;
		}
	}
	return true;
}

bool Cmd_GetAngularVelocityAlt_Execute(COMMAND_ARGS)
{
	*result = 0;
	char blockName[0x40];
	ResultVars outVel;
	UInt32 getGlobal = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &outVel.x, &outVel.y, &outVel.z, &getGlobal))
	{
		hkpRigidBody *rigidBody = thisObj->GetRigidBody(blockName);
		if (rigidBody && rigidBody->IsMobile())
		{
			if (getGlobal)
				outVel.Set(rigidBody->motion.angVelocity.PS());
			else
			{
				hkVector4 velocity = rigidBody->motion.angVelocity;
				outVel.Set(rigidBody->motion.motionState.transform.rotation.MultiplyVector(velocity));
			}
			*result = 1;
		}
	}
	return true;
}

bool Cmd_SetAngularVelocityEx_Execute(COMMAND_ARGS)
{
	*result = 0;
	char blockName[0x40];
	hkVector4 velocity(_mm_setzero_ps());
	UInt32 setGlobal = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &velocity.x, &velocity.y, &velocity.z, &setGlobal))
	{
		hkpRigidBody *rigidBody = thisObj->GetRigidBody(blockName);
		if (rigidBody && rigidBody->IsMobile())
		{
			rigidBody->motion.angVelocity = setGlobal ? velocity : rigidBody->motion.motionState.transform.rotation.MultiplyVectorInv(velocity);
			rigidBody->UpdateMotion();
			*result = 1;
		}
	}
	return true;
}

bool Cmd_GetCollisionObjProperty_Execute(COMMAND_ARGS)
{
	*result = 0;
	char blockName[0x40];
	UInt32 propID;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &propID) && (propID <= 7))
	{
		hkpRigidBody *rigidBody = thisObj->GetRigidBody(blockName);
		if (rigidBody)
		{
			switch (propID)
			{
				case 0:
					*result = rigidBody->friction;
					break;
				case 1:
					*result = rigidBody->restitution;
					break;
				case 2:
					*result = rigidBody->motion.motionState.linearDamping;
					break;
				case 3:
					*result = rigidBody->motion.motionState.angularDamping;
					break;
				case 4:
				case 5:
				case 6:
					*result = rigidBody->motion.inertia[propID - 4];
					break;
				case 7:
					if (rigidBody->motion.bodyMassInv > 0)
						*result = 1.0 / rigidBody->motion.bodyMassInv;
					break;
			}
		}
	}
	return true;
}

bool Cmd_SetCollisionObjProperty_Execute(COMMAND_ARGS)
{
	char blockName[0x40];
	UInt32 propID;
	float value;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &blockName, &propID, &value) && (propID <= 7))
	{
		hkpRigidBody *rigidBody = thisObj->GetRigidBody(blockName);
		if (rigidBody)
		{
			switch (propID)
			{
				case 0:
					rigidBody->friction = value;
					break;
				case 1:
					rigidBody->restitution = value;
					break;
				case 2:
					rigidBody->motion.motionState.linearDamping = value;
					break;
				case 3:
					rigidBody->motion.motionState.angularDamping = value;
					break;
				case 4:
				case 5:
				case 6:
					rigidBody->motion.inertia[propID - 4] = value;
					break;
				case 7:
					rigidBody->motion.bodyMassInv = (value > 0) ? (1.0F / value) : 0;
					break;
			}
		}
	}
	return true;
}

bool Cmd_GetCollisionObjLayerType_Execute(COMMAND_ARGS)
{
	*result = 0;
	char nodeName[0x40];
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &nodeName))
	{
		NiNode *targetNode = thisObj->GetNode2(nodeName);
		if (targetNode && targetNode->m_collisionObject)
		{
			bhkWorldObject *worldObj = targetNode->m_collisionObject->worldObj;
			if (worldObj)
				*result = ((hkpWorldObject*)worldObj->refObject)->layerType;
		}
	}
	return true;
}

bool Cmd_SetCollisionObjLayerType_Execute(COMMAND_ARGS)
{
	char nodeName[0x40];
	UInt32 layerType;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &nodeName, &layerType) && layerType && (layerType < LAYER_MAX))
	{
		NiNode *targetNode = thisObj->GetNode2(nodeName);
		if (targetNode && targetNode->m_collisionObject)
		{
			bhkWorldObject *worldObj = targetNode->m_collisionObject->worldObj;
			if (worldObj)
			{
				((hkpWorldObject*)worldObj->refObject)->layerType = layerType;
				worldObj->UpdateCollisionFilter();
			}
		}
	}
	return true;
}

bool Cmd_SetRefrModelPath_Execute(COMMAND_ARGS)
{
	char modelPath[0x80];
	modelPath[0] = 0;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &modelPath))
	{
		if (modelPath[0])
		{
			char **pPath;
			if (s_refrModelPathMap().Insert(thisObj, &pPath))
				HOOK_MOD(GetModelPath, true);
			else free(*pPath);
			*pPath = CopyString(modelPath);
			thisObj->JIPRefFlags() |= kHookRefFlag5F_RefrModelPath;
		}
		else
		{
			if (s_refrModelPathMap().EraseFree(thisObj))
				HOOK_MOD(GetModelPath, false);
			thisObj->JIPRefFlags() &= ~kHookRefFlag5F_RefrModelPath;
		}
	}
	return true;
}

bool Cmd_AttachLine_Execute(COMMAND_ARGS)
{
	*result = 0;
	char nodeName[0x40], lineName[0x40];
	float length;
	NiColorAlpha color;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &nodeName, &lineName, &length, &color.r, &color.g, &color.b, &color.a))
	{
		NiNode *targetNode = thisObj->GetNode2(nodeName);
		if (targetNode)
		{
			color *= 1 / 255.0F;
			NiLines *lines = NiLines::Create(length, color, lineName);
			targetNode->AddObject(lines, 1);
			if ((thisObj->refID == 0x14) && (targetNode = s_pc1stPersonNode->GetNode(nodeName)))
			{
				lines = NiLines::Create(length, color, lineName);
				targetNode->AddObject(lines, 1);
			}
			*result = 1;
		}
	}
	return true;
}

bool Cmd_ToggleNoZPosReset_Execute(COMMAND_ARGS)
{
	UInt32 toggle;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &toggle))
	{
		if (toggle)
		{
			if (*(UInt32*)0x629006 != 0x0C74C085)
			{
				SAFE_WRITE_BUF(0x629006, "\x85\xC0\x74\x0C\xF6\x40\x5F\x10\x0F\x85\x28\x05\x00\x00\x66\x90");					//	kHookRefFlag5F_NoZPosReset
				SAFE_WRITE_BUF(0x6295E9, "\x8B\x4D\x08\xF6\x41\x5F\x10\x75\x56\x8D\x45\xF4\x50\x8B\x11\x0F\x1F\x44\x00\x00");	//	kHookRefFlag5F_NoZPosReset
			}
			thisObj->JIPRefFlags() |= kHookRefFlag5F_NoZPosReset;
		}
		else thisObj->JIPRefFlags() &= ~kHookRefFlag5F_NoZPosReset;
	}
	return true;
}