#pragma once

char s_lastLoadedPath[0x80] = {0};
UInt8 s_lastChangedFlags = 0;

void __fastcall RestoreLinkedRefs(UnorderedMap<UInt32, UInt32> *tempMap = NULL)
{
	if (s_linkedRefDefault().Empty()) return;
	UInt32 key;
	auto linkIter = s_linkedRefDefault().Begin();
	while (linkIter)
	{
		key = linkIter.Key();
		++linkIter;
		if (!tempMap || !tempMap->HasKey(key))
			SetLinkedRefID(key);
	}
}

__declspec(noinline) void CleanMLCallbacks()
{
	for (auto iter = s_mainLoopCallbacks().Begin(); iter; ++iter)
	{
		if (iter->cmdPtr == JIPScriptRunner::RunScript)
		{
			((Script*)iter->thisObj)->Destructor();
			GameHeapFree(iter->thisObj);
			iter->bRemove = true;
		}
		else if (iter->flags & 8)
			iter->bRemove = true;
	}
}

void MiniMapLoadGame();

void DoPreLoadGameHousekeeping()
{
	UInt8 changedFlags = s_dataChangedFlags;
	s_dataChangedFlags = 0;
	s_lastChangedFlags = changedFlags;

	if (changedFlags & kChangedFlag_AuxVars) s_auxVariablesPerm().Clear();
	if (changedFlags & kChangedFlag_RefMaps) s_refMapArraysPerm().Clear();
	if (changedFlags & kChangedFlag_LinkedRefs) s_linkedRefModified().Clear();
	s_scriptVariablesBuffer().Clear();
	s_linkedRefsTemp().Clear();
	s_serializedFlags = 0;

	UInt32 size = s_NPCPerksInfoMap().Size();
	if (size && (changedFlags & kChangedFlag_NPCPerks))
	{
		Actor *actor;
		for (auto refIter = s_NPCPerksInfoMap().Begin(); refIter; ++refIter)
		{
			if ((actor = (Actor*)LookupFormByRefID(refIter.Key())) && IS_ACTOR(actor))
				actor->extraDataList.perksInfo = NULL;
			if (!--size) break;
		}
		s_NPCPerksInfoMap().Clear();
	}

	if ((changedFlags == kChangedFlag_All) && !s_resolvedGlobals().Empty())
	{
		for (auto globIter = s_resolvedGlobals().Begin(); globIter; ++globIter)
			globIter->jipFormFlags6 = 0;
		s_resolvedGlobals().Clear();
	}

	HOOK_SET(StartCombat, false);
	if (s_forceCombatTargetMap().Clear())
		HOOK_SET(SetCombatTarget, false);
	HOOK_SET(TeleportWithPC, false);
	if (HOOK_SET(EquipItem, false))
	{
		HOOK_SET(ReEquipAll, false);
		HOOK_SET(WeaponSwitchSelect, false);
		HOOK_SET(WeaponSwitchUnequip, false);
		HOOK_SET(GetPreferedWeapon, false);
	}
	if (s_forceDetectionValueMap().Clear())
		HOOK_SET(GetDetectionValue, false);
	HOOK_SET(AddVATSTarget, false);

	size = s_fireWeaponEventMap().Size() + s_fireWeaponEventScripts().Size();
	if (!size) HOOK_SET(RemoveAmmo, false);
	else s_hookInfos[kHook_RemoveAmmo].SetCount(size);

	TESForm *form;
	if (!s_eventInformedObjects().Empty())
	{
		for (auto userIter = s_eventInformedObjects().Begin(); userIter; ++userIter)
		{
			form = LookupFormByRefID(*userIter);
			if (form) form->jipFormFlags5 &= ~kHookFormFlag5_ScriptInformed;
		}
		s_eventInformedObjects().Clear();

		if (s_pcFastTravelInformed().Clear())
			HOOK_MOD(PCFastTravel, false);
		if (s_pcCellChangeInformed().Clear())
			HOOK_SET(PCCellChange, false);
	}

	if (!s_scriptWaitInfoMap().Empty())
	{
		for (auto waitIter = s_scriptWaitInfoMap().Begin(); waitIter; ++waitIter)
		{
			form = LookupFormByRefID(waitIter().refID);
			if (form) form->jipFormFlags5 &= ~kHookFormFlag5_ScriptOnWait;
		}
		s_scriptWaitInfoMap().Clear();
		HOOK_SET(ScriptRunner, false);
		HOOK_SET(EvalEventBlock, false);
		s_scriptWaitInfo = nullptr;
	}

	for (auto lgtIter = s_activePtLights().Begin(); lgtIter; ++lgtIter)
		if ((lgtIter->extraFlags & 0x80) && lgtIter->m_parent)
			lgtIter->m_parent->RemoveObject(*lgtIter);

	if (!s_swapObjLODMap().Empty())
	{
		s_swapObjLODMap().Clear();
		HOOK_SET(MakeObjLODPath, false);
	}

	if (!s_extraCamerasMap().Empty())
	{
		for (auto camIter = s_extraCamerasMap().Begin(); camIter; ++camIter)
		{
			if (camIter->m_parent)
				camIter->m_parent->RemoveObject(*camIter);
			camIter->Destructor(true);
		}
		s_extraCamerasMap().Clear();
	}

	if (!s_refNamesMap().Empty())
	{
		for (auto nameIter = s_refNamesMap().Begin(); nameIter; ++nameIter)
			free(*nameIter);
		s_refNamesMap().Clear();
		HOOK_SET(GetRefName, false);
	}

	if (!s_refrModelPathMap().Empty())
	{
		for (auto pathIter = s_refrModelPathMap().Begin(); pathIter; ++pathIter)
			free(*pathIter);
		s_refrModelPathMap().Clear();
		HOOK_SET(GetModelPath, false);
	}

	if (s_refMapMarkersCount)
	{
		while (--s_refMapMarkersCount)
			s_refMapMarkersList.RemoveNth(0);
		s_refMapMarkersList.Init();
		HOOK_SET(CreateMapMarkers, false);
	}

	auto pcAprUndo = s_appearanceUndoMap().Find((TESNPC*)g_thePlayer->baseForm);
	if (pcAprUndo)
	{
		pcAprUndo->Destroy();
		pcAprUndo.Remove();
	}

	CleanMLCallbacks();
	s_gameLoadFlagLN = true;
	HOOK_SET(OnRagdoll, false);
	s_onRagdollEventScripts().Clear();
	s_excludedCombatActionsMap().Clear();
	MiniMapLoadGame();
	s_syncPositionRef = nullptr;
	g_thePlayer->killer = nullptr;
}

void RestoreJIPFormFlags()
{
	for (auto flagsIter = s_jipFormFlagsMap().Begin(); flagsIter; ++flagsIter)
	{
		TESForm *form = LookupFormByRefID(flagsIter.Key());
		if (form && *flagsIter) form->jipFormFlags6 = *flagsIter;
		else flagsIter.Remove();
	}
}

void DoLoadGameHousekeeping()
{
	RestoreJIPFormFlags();

	if (g_thePlayer->teammateCount)
	{
		auto perkIter = g_thePlayer->perkRanksTM.Head();
		PerkRank *perkRank;
		do
		{
			perkRank = perkIter->data;
			if (perkRank && perkRank->perk)
				ThisCall(0x5EB6A0, perkRank->perk, g_thePlayer, 0, perkRank->rank, 1);
		}
		while (perkIter = perkIter->next);
	}

	Actor *actor;
	if (s_NPCWeaponMods && !(g_thePlayer->actorFlags & 0x10000000))
	{
		g_thePlayer->actorFlags |= 0x10000000;
		auto actorIter = ProcessManager::Get()->highActors.Head();
		do
		{
			if (!(actor = actorIter->data) || (actor->actorFlags & 0x10000000))
				continue;
			actor->actorFlags |= 0x10000000;
			if (!actor->isTeammate)
				DistributeWeaponMods(actor);
		}
		while (actorIter = actorIter->next);
	}

	if (s_NPCPerks && (s_lastChangedFlags & kChangedFlag_NPCPerks))
	{
		auto actorIter = ProcessManager::Get()->highActors.Head();
		do
		{
			if (actor = actorIter->data)
				InitNPCPerks(actor);
		}
		while (actorIter = actorIter->next);
	}

	if (s_lastChangedFlags & kChangedFlag_LinkedRefs)
		RestoreLinkedRefs(*s_linkedRefsTemp);
}

UInt8 *s_loadGameBuffer = nullptr;
UInt32 s_loadGameBufferSize = 0x10000;

__declspec(noinline) UInt8* __fastcall GetLoadGameBuffer(UInt32 length)
{
	if (s_loadGameBufferSize < length)
	{
		s_loadGameBufferSize = length;
		if (s_loadGameBuffer)
			_aligned_free(s_loadGameBuffer);
		s_loadGameBuffer = (UInt8*)_aligned_malloc(length, 0x10);
	}
	else if (!s_loadGameBuffer)
		s_loadGameBuffer = (UInt8*)_aligned_malloc(s_loadGameBufferSize, 0x10);
	ReadRecordData(s_loadGameBuffer, length);
	return s_loadGameBuffer;
}

void LoadGameCallback(void*)
{
	UInt8 changedFlags = s_lastChangedFlags;

	UInt32 type, version, length, nRecs, nRefs, nVars, buffer4, refID;
	UInt8 buffer1, modIdx;
	UInt8 *bufPos, *namePos;

	while (GetNextRecordInfo(&type, &version, &length))
	{
		switch (type)
		{
			case 'VSPJ':
			{
				bufPos = GetLoadGameBuffer(length);
				TESForm *form;
				Script *script;
				ScriptEventList *eventList;
				ScriptVar *var;
				VarData *varData;
				nRecs = *(UInt16*)bufPos;
				bufPos += 2;
				while (nRecs)
				{
					nRecs--;
					refID = *(UInt32*)bufPos;
					bufPos += 4;
					nVars = *(UInt16*)bufPos;
					bufPos += 2;
					if (ResolveRefID(refID, &refID) && (form = LookupFormByRefID(refID)) && form->GetScriptAndEventList(&script, &eventList))
					{
						while (nVars)
						{
							nVars--;
							modIdx = *bufPos++;
							buffer1 = *bufPos++;
							namePos = bufPos;
							bufPos += buffer1;
							buffer1 = *bufPos;
							*bufPos = 0;
							varData = (VarData*)bufPos;
							bufPos += 8;
							if (!ResolveRefID(modIdx << 24, &buffer4)) continue;
							if (var = script->AddVariable((char*)namePos, eventList, refID, buffer4 >> 24))
							{
								*(UInt8*)varData = buffer1;
								if (varData->refID && !varData->pad && !ResolveRefID(varData->refID, &varData->refID))
									varData->refID = 0;
								var->data.num = varData->num;
							}
						}
					}
					else
					{
						while (nVars)
						{
							nVars--;
							buffer1 = *++bufPos + 8;
							bufPos += buffer1;
						}
					}
				}
				break;
			}
			case 'VAPJ':
			{
				if (!(changedFlags & kChangedFlag_AuxVars))
					break;
				if (version < 10)
				{
					PrintLog("LOAD GAME: AuxVars version obsolete > Skipping records.");
					break;
				}
				bufPos = GetLoadGameBuffer(length);
				AuxVarOwnersMap *ownersMap;
				AuxVarVarsMap *aVarsMap;
				AuxVarValsArr *valsArr;
				UInt16 nElems;
				nRecs = *(UInt16*)bufPos;
				bufPos += 2;
				while (nRecs)
				{
					buffer1 = *bufPos++;
					nRecs--;
					if ((buffer1 > 5) && (ResolveRefID(buffer1 << 24, &buffer4)))
					{
						ownersMap = NULL;
						modIdx = buffer4 >> 24;
						nRefs = *(UInt16*)bufPos;
						bufPos += 2;
						while (nRefs)
						{
							refID = *(UInt32*)bufPos;
							bufPos += 4;
							nVars = *(UInt16*)bufPos;
							bufPos += 2;
							if (ResolveRefID(refID, &refID) && LookupFormByRefID(refID))
							{
								if (!ownersMap) ownersMap = s_auxVariablesPerm().Emplace(modIdx, nRefs);
								aVarsMap = ownersMap->Emplace(refID, nVars);
								while (nVars)
								{
									buffer1 = *bufPos++;
									if (!buffer1)
										goto avSkipVars;
									namePos = bufPos;
									bufPos += buffer1;
									nElems = *(UInt16*)bufPos;
									*bufPos = 0;
									bufPos += 2;
									valsArr = aVarsMap->Emplace((char*)namePos, nElems);
									while (nElems)
									{
										buffer1 = *bufPos++;
										bufPos += valsArr->Append(buffer1)->ReadValData(bufPos);
										nElems--;
									}
									nVars--;
								}
							}
							else
							{
								while (nVars)
								{
									buffer1 = *bufPos++;
									bufPos += buffer1;
								avSkipVars:
									nElems = *(UInt16*)bufPos;
									bufPos += 2;
									while (nElems)
									{
										buffer1 = *bufPos++;
										if (buffer1 == 1)
											bufPos += 8;
										else if (buffer1 == 2)
											bufPos += 4;
										else bufPos += *(UInt16*)bufPos + 2;
										nElems--;
									}
									nVars--;
								}
							}
							nRefs--;
						}
					}
					else
					{
						nRefs = *(UInt16*)bufPos;
						bufPos += 2;
						while (nRefs)
						{
							bufPos += 4;
							nVars = *(UInt16*)bufPos;
							bufPos += 2;
							while (nVars)
							{
								buffer1 = *bufPos++;
								bufPos += buffer1;
								nElems = *(UInt16*)bufPos;
								bufPos += 2;
								while (nElems)
								{
									buffer1 = *bufPos++;
									if (buffer1 == 1)
										bufPos += 8;
									else if (buffer1 == 2)
										bufPos += 4;
									else bufPos += *(UInt16*)bufPos + 2;
									nElems--;
								}
								nVars--;
							}
							nRefs--;
						}
					}
				}
				break;
			}
			case 'MRPJ':
			{
				if (!(changedFlags & kChangedFlag_RefMaps))
					break;
				if (version < 10)
				{
					PrintLog("LOAD GAME: RefMaps version obsolete > Skipping records.");
					break;
				}
				bufPos = GetLoadGameBuffer(length);
				RefMapVarsMap *rVarsMap;
				RefMapIDsMap *idsMap;
				nRecs = *(UInt16*)bufPos;
				bufPos += 2;
				while (nRecs)
				{
					buffer1 = *bufPos++;
					nRecs--;
					nVars = *(UInt16*)bufPos;
					bufPos += 2;
					if ((buffer1 > 5) && (ResolveRefID(buffer1 << 24, &buffer4)))
					{
						rVarsMap = NULL;
						modIdx = buffer4 >> 24;
						while (nVars)
						{
							buffer1 = *bufPos++;
							if (!buffer1)
								goto rmSkipVars;
							namePos = bufPos;
							bufPos += buffer1;
							nRefs = *(UInt16*)bufPos;
							*bufPos = 0;
							bufPos += 2;
							idsMap = NULL;
							while (nRefs)
							{
								refID = *(UInt32*)bufPos;
								bufPos += 4;
								buffer1 = *bufPos++;
								if (ResolveRefID(refID, &refID) && LookupFormByRefID(refID))
								{
									if (!idsMap)
									{
										if (!rVarsMap) rVarsMap = s_refMapArraysPerm().Emplace(modIdx, nVars);
										idsMap = rVarsMap->Emplace((char*)namePos, nRefs);
									}
									bufPos += idsMap->Emplace(refID, buffer1)->ReadValData(bufPos);
								}
								else if (buffer1 == 1)
									bufPos += 8;
								else if (buffer1 == 2)
									bufPos += 4;
								else bufPos += *(UInt16*)bufPos + 2;
								nRefs--;
							}
							nVars--;
						}
					}
					else
					{
						while (nVars)
						{
							buffer1 = *bufPos++;
							bufPos += buffer1;
						rmSkipVars:
							nRefs = *(UInt16*)bufPos;
							bufPos += 2;
							while (nRefs)
							{
								bufPos += 4;
								buffer1 = *bufPos++;
								if (buffer1 == 1)
									bufPos += 8;
								else if (buffer1 == 2)
									bufPos += 4;
								else bufPos += *(UInt16*)bufPos + 2;
								nRefs--;
							}
							nVars--;
						}
					}
				}
				break;
			}
			case 'RLPJ':
			{
				if (!(changedFlags & kChangedFlag_LinkedRefs)) break;
				bufPos = GetLoadGameBuffer(length);
				UInt32 lnkID;
				nRecs = *(UInt16*)bufPos;
				bufPos += 2;
				while (nRecs)
				{
					nRecs--;
					refID = *(UInt32*)bufPos;
					bufPos += 4;
					lnkID = *(UInt32*)bufPos;
					bufPos += 4;
					buffer1 = *bufPos++;
					if (ResolveRefID(refID, &refID) && ResolveRefID(lnkID, &lnkID) &&
						ResolveRefID(buffer1 << 24, &buffer4) && SetLinkedRefID(refID, lnkID, buffer4 >> 24))
						s_linkedRefsTemp()[refID] = lnkID;
				}
				break;
			}
			case 'FGPJ':
			{
				s_serializedFlags = ReadRecord32();
				break;
			}
			case 'UAPJ':
			{
				AppearanceUndo *aprUndo = (AppearanceUndo*)malloc(sizeof(AppearanceUndo));
				ReadRecordData(aprUndo->values0, 0x214);
				refID = ReadRecord32();
				if (!ResolveRefID(refID, &refID) || !(aprUndo->race = (TESRace*)LookupFormByRefID(refID)))
					aprUndo->race = (TESRace*)LookupFormByRefID(0x19);
				refID = ReadRecord32();
				if (!ResolveRefID(refID, &refID) || !(aprUndo->hair = (TESHair*)LookupFormByRefID(refID)))
				{
					refID = (aprUndo->flags & 1) ? 0x22E4E : 0x14B90;
					aprUndo->hair = (TESHair*)LookupFormByRefID(refID);
				}
				refID = ReadRecord32();
				if (!ResolveRefID(refID, &refID) || !(aprUndo->eyes = (TESEyes*)LookupFormByRefID(refID)))
					aprUndo->eyes = (TESEyes*)LookupFormByRefID(0x4255);
				buffer1 = ReadRecord8();
				aprUndo->numParts = buffer1;
				if (buffer1)
				{
					BGSHeadPart **ptr = aprUndo->headParts = (BGSHeadPart**)malloc(buffer1 * 4);
					do
					{
						refID = ReadRecord32();
						if (ResolveRefID(refID, &refID) && (*ptr = (BGSHeadPart*)LookupFormByRefID(refID)))
							ptr++;
						else aprUndo->numParts--;
					}
					while (--buffer1);
				}
				else aprUndo->headParts = NULL;
				s_appearanceUndoMap()[(TESNPC*)g_thePlayer->baseForm] = aprUndo;
				break;
			}
			case 'PNPJ':
			{
				if (!s_NPCPerks || !(changedFlags & kChangedFlag_NPCPerks)) break;
				bufPos = GetLoadGameBuffer(length);
				nRecs = *(UInt16*)bufPos;
				bufPos += 2;
				Actor *actor;
				NPCPerksInfo *perksInfo;
				UInt8 rank;
				BGSPerk *perk;
				while (nRecs)
				{
					nRecs--;
					refID = *(UInt32*)bufPos;
					bufPos += 4;
					buffer1 = *bufPos++;
					if (!ResolveRefID(refID, &refID) || !(actor = (Actor*)LookupFormByRefID(refID)) || NOT_ACTOR(actor))
					{
						bufPos += buffer1 * 5;
						continue;
					}
					perksInfo = NULL;
					while (buffer1)
					{
						buffer1--;
						buffer4 = *(UInt32*)bufPos;
						bufPos += 4;
						rank = *bufPos++;
						if (!ResolveRefID(buffer4, &buffer4) || !(perk = (BGSPerk*)LookupFormByRefID(buffer4)) || NOT_ID(perk, BGSPerk))
							continue;
						if (rank > perk->data.numRanks)
							rank = perk->data.numRanks;
						if (!perksInfo)
							perksInfo = &s_NPCPerksInfoMap()[refID];
						perksInfo->perkRanks[perk] = rank;
					}
					actor->extraDataList.perksInfo = perksInfo;
				}
			}
			default:
				break;
		}
	}
}

void SaveGameCallback(void*)
{
	UInt8 buffer1;
	UInt32 buffer2;

	if (buffer2 = s_scriptVariablesBuffer().Size())
	{
		WriteRecord('VSPJ', 9, &buffer2, 2);
		for (auto svOwnerIt = s_scriptVariablesBuffer().Begin(); svOwnerIt; ++svOwnerIt)
		{
			WriteRecord32(svOwnerIt.Key());
			WriteRecord16(svOwnerIt().Size());
			for (auto svVarIt = svOwnerIt().Begin(); svVarIt; ++svVarIt)
			{
				WriteRecord8(svVarIt().modIdx);
				buffer1 = StrLen(svVarIt.Key());
				WriteRecord8(buffer1);
				WriteRecordData(svVarIt.Key(), buffer1);
				WriteRecord64(&svVarIt().value->data);
			}
		}
	}
	if (buffer2 = s_auxVariablesPerm().Size())
	{
		WriteRecord('VAPJ', 10, &buffer2, 2);
		for (auto avModIt = s_auxVariablesPerm().Begin(); avModIt; ++avModIt)
		{
			WriteRecord8(avModIt.Key());
			WriteRecord16(avModIt().Size());
			for (auto avOwnerIt = avModIt().Begin(); avOwnerIt; ++avOwnerIt)
			{
				WriteRecord32(avOwnerIt.Key());
				WriteRecord16(avOwnerIt().Size());
				for (auto avVarIt = avOwnerIt().Begin(); avVarIt; ++avVarIt)
				{
					buffer1 = StrLen(avVarIt.Key());
					WriteRecord8(buffer1);
					WriteRecordData(avVarIt.Key(), buffer1);
					WriteRecord16(avVarIt().Size());
					for (auto avValIt = avVarIt().Begin(); avValIt; ++avValIt)
						avValIt().WriteValData();
				}
			}
		}
	}
	if (buffer2 = s_refMapArraysPerm().Size())
	{
		WriteRecord('MRPJ', 10, &buffer2, 2);
		for (auto rmModIt = s_refMapArraysPerm().Begin(); rmModIt; ++rmModIt)
		{
			WriteRecord8(rmModIt.Key());
			WriteRecord16(rmModIt().Size());
			for (auto rmVarIt = rmModIt().Begin(); rmVarIt; ++rmVarIt)
			{
				buffer1 = StrLen(rmVarIt.Key());
				WriteRecord8(buffer1);
				WriteRecordData(rmVarIt.Key(), buffer1);
				WriteRecord16(rmVarIt().Size());
				for (auto rmRefIt = rmVarIt().Begin(); rmRefIt; ++rmRefIt)
				{
					WriteRecord32(rmRefIt.Key());
					rmRefIt().WriteValData();
				}
			}
		}
	}
	if (buffer2 = s_linkedRefModified().Size())
	{
		WriteRecord('RLPJ', 9, &buffer2, 2);
		for (auto lrRefIt = s_linkedRefModified().Begin(); lrRefIt; ++lrRefIt)
		{
			WriteRecord32(lrRefIt.Key());
			WriteRecord32(lrRefIt().linkID);
			WriteRecord8(lrRefIt().modIdx);
		}
	}
	if (s_serializedFlags)
		WriteRecord('FGPJ', 9, &s_serializedFlags, 4);
	AppearanceUndo *aprUndo = s_appearanceUndoMap().Get((TESNPC*)g_thePlayer->baseForm);
	if (aprUndo)
	{
		WriteRecord('UAPJ', 9, aprUndo->values0, 0x214);
		WriteRecord32(aprUndo->race->refID);
		WriteRecord32(aprUndo->hair->refID);
		WriteRecord32(aprUndo->eyes->refID);
		buffer1 = aprUndo->numParts;
		WriteRecord8(buffer1);
		if (buffer1)
		{
			BGSHeadPart **ptr = aprUndo->headParts;
			do
			{
				WriteRecord32((*ptr)->refID);
				ptr++;
			}
			while (--buffer1);
		}
	}
	if (buffer2 = s_NPCPerksInfoMap().Size())
	{
		Actor *actor;
		for (auto refIter = s_NPCPerksInfoMap().Begin(); refIter; ++refIter)
		{
			if ((actor = (Actor*)LookupFormByRefID(refIter.Key())) && IS_ACTOR(actor))
			{
				if (!refIter().perkRanks.Empty() && !actor->lifeState && (actor->isTeammate || !(((TESActorBase*)actor->baseForm)->baseData.flags & 8) || actor->GetRefNiNode()))
					goto isValid;
				actor->extraDataList.perksInfo = NULL;
			}
			refIter.Remove();
		isValid:
			if (!--buffer2) break;
		}
		if (buffer2 = s_NPCPerksInfoMap().Size())
		{
			WriteRecord('PNPJ', 10, &buffer2, 2);
			for (auto refIter = s_NPCPerksInfoMap().Begin(); refIter; ++refIter)
			{
				WriteRecord32(refIter.Key());
				WriteRecord8(refIter().perkRanks.Size());
				for (auto perkIter = refIter().perkRanks.Begin(); perkIter; ++perkIter)
				{
					WriteRecord32(perkIter.Key()->refID);
					WriteRecord8(perkIter());
				}
				if (!--buffer2) break;
			}
		}
	}
}