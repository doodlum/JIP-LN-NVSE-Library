#pragma once

DEFINE_COMMAND_PLUGIN(SetStageAlt, 0, 2, kParams_OneQuest_OneInt);
DEFINE_COMMAND_PLUGIN(ClearActiveQuest, 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(GetObjectiveTargets, 0, 2, kParams_OneQuest_OneInt);
DEFINE_COMMAND_PLUGIN(SetObjectiveNthTarget, 0, 4, kParams_OneQuest_TwoInts_OneObjectRef);
DEFINE_COMMAND_PLUGIN(GetObjectiveHasTarget, 0, 3, kParams_OneQuest_OneInt_OneObjectRef);
DEFINE_COMMAND_PLUGIN(AddObjectiveTarget, 0, 3, kParams_OneQuest_OneInt_OneObjectRef);
DEFINE_COMMAND_PLUGIN(RemoveObjectiveTarget, 0, 3, kParams_OneQuest_OneInt_OneObjectRef);
DEFINE_COMMAND_PLUGIN(GetObjectiveText, 0, 2, kParams_OneQuest_OneInt);
DEFINE_COMMAND_PLUGIN(SetObjectiveText, 0, 23, kParams_OneQuest_OneInt_OneFormatString);
DEFINE_COMMAND_PLUGIN(GetQuests, 0, 1, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(GetQuestObjectives, 0, 2, kParams_OneQuest_OneInt);
DEFINE_COMMAND_PLUGIN(GetActiveObjectives, 0, 0, NULL);
DEFINE_COMMAND_PLUGIN(GetObjectiveTeleportLinks, 0, 2, kParams_OneQuest_OneInt);
DEFINE_COMMAND_PLUGIN(GetQuestFlag, 0, 2, kParams_OneQuest_OneInt);
DEFINE_COMMAND_PLUGIN(SetQuestFlag, 0, 3, kParams_OneQuest_TwoInts);
DEFINE_COMMAND_PLUGIN(FailQuest, 0, 1, kParams_OneQuest);
DEFINE_COMMAND_PLUGIN(GetQuestTargetsChanged, 0, 0, NULL);

bool Cmd_SetStageAlt_Execute(COMMAND_ARGS)
{
	TESQuest *quest;
	UInt32 stageID;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &quest, &stageID) && quest->SetStage(stageID))
	{
		quest->currentStage = stageID;
		*result = 1;
	}
	else *result = 0;
	return true;
}

bool Cmd_ClearActiveQuest_Execute(COMMAND_ARGS)
{
	g_thePlayer->activeQuest = NULL;
	g_thePlayer->questTargetList.RemoveAll();
	return true;
}

bool Cmd_GetObjectiveTargets_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESQuest *quest;
	UInt32 objectiveID;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &quest, &objectiveID)) return true;
	BGSQuestObjective *objective = quest->GetObjective(objectiveID);
	if (!objective || ((objective->status & 3) != 1) || objective->targets.Empty()) return true;
	TempElements *tmpElements = GetTempElements();
	auto iter = objective->targets.Head();
	ObjectiveTarget *target;
	bool evalRes;
	do
	{
		target = iter->data;
		if (target && target->target && target->conditions.Evaluate(target->target, NULL, &evalRes, 0))
			tmpElements->Append(target->target);
	}
	while (iter = iter->next);
	if (!tmpElements->Empty())
		AssignCommandResult(CreateArray(tmpElements->Data(), tmpElements->Size(), scriptObj), result);
	return true;
}

bool Cmd_SetObjectiveNthTarget_Execute(COMMAND_ARGS)
{
	TESQuest *quest;
	UInt32 objectiveID, index;
	TESObjectREFR *refr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &quest, &objectiveID, &index, &refr))
	{
		BGSQuestObjective *objective = quest->GetObjective(objectiveID);
		if (objective)
		{
			ObjectiveTarget *target = objective->targets.GetNthItem(index);
			if (target)
			{
				target->target = refr;
				if (quest == g_thePlayer->activeQuest)
					StdCall(0x952D60, target->target, &target->data, 1);
			}
		}
	}
	return true;
}

bool Cmd_GetObjectiveHasTarget_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESQuest *quest;
	UInt32 objectiveID;
	TESObjectREFR *refr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &quest, &objectiveID, &refr))
	{
		BGSQuestObjective *objective = quest->GetObjective(objectiveID);
		if (objective && objective->targets.Find(ObjTargetFinder(refr)))
			*result = 1;
	}
	return true;
}

bool Cmd_AddObjectiveTarget_Execute(COMMAND_ARGS)
{
	TESQuest *quest;
	UInt32 objectiveID;
	TESObjectREFR *refr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &quest, &objectiveID, &refr))
	{
		BGSQuestObjective *objective = quest->GetObjective(objectiveID);
		if (objective && !objective->targets.Find(ObjTargetFinder(refr)))
		{
			ObjectiveTarget *target = ThisCall<ObjectiveTarget*>(0x60FF70, GameHeapAlloc(sizeof(ObjectiveTarget)));
			target->target = refr;
			objective->targets.Prepend(target);
			if (quest == g_thePlayer->activeQuest)
				ThisCall(0x60F110, quest, &g_thePlayer->questTargetList, &g_thePlayer->questObjectiveList);
		}
	}
	return true;
}

bool Cmd_RemoveObjectiveTarget_Execute(COMMAND_ARGS)
{
	TESQuest *quest;
	UInt32 objectiveID;
	TESObjectREFR *refr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &quest, &objectiveID, &refr))
	{
		BGSQuestObjective *objective = quest->GetObjective(objectiveID);
		if (objective)
		{
			ObjectiveTarget *target = objective->targets.RemoveIf(ObjTargetFinder(refr));
			if (target)
			{
				ThisCall(0x5EC4D0, target, 1);
				if (quest == g_thePlayer->activeQuest)
					ThisCall(0x60F110, quest, &g_thePlayer->questTargetList, &g_thePlayer->questObjectiveList);
			}
		}
	}
	return true;
}

bool Cmd_GetObjectiveText_Execute(COMMAND_ARGS)
{
	TESQuest *quest;
	UInt32 objectiveID;
	const char *resStr = NULL;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &quest, &objectiveID))
	{
		BGSQuestObjective *objective = quest->GetObjective(objectiveID);
		if (objective) resStr = objective->displayText.m_data;
	}
	AssignString(PASS_COMMAND_ARGS, resStr);
	return true;
}

bool Cmd_SetObjectiveText_Execute(COMMAND_ARGS)
{
	TESQuest *quest;
	UInt32 objectiveID;
	char *buffer = GetStrArgBuffer();
	if (ExtractFormatStringArgs(2, buffer, EXTRACT_ARGS_EX, kCommandInfo_SetObjectiveText.numParams, &quest, &objectiveID))
	{
		BGSQuestObjective *objective = quest->GetObjective(objectiveID);
		if (objective) objective->displayText.Set(buffer);
	}
	return true;
}

bool Cmd_GetQuests_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 completed = 0;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &completed))
		return true;
	TempElements *tmpElements = GetTempElements();
	auto iter = g_thePlayer->questObjectiveList.Head();
	BGSQuestObjective *objective;
	TESQuest *quest;
	if (completed) completed = TESQuest::kFlag_Completed;
	do
	{
		objective = iter->data;
		if (!objective || !(objective->status & 1)) continue;
		quest = objective->quest;
		if (completed == (quest->questFlags & TESQuest::kFlag_Completed))
			tmpElements->InsertUnique(quest);
	}
	while (iter = iter->next);
	if (!tmpElements->Empty())
		AssignCommandResult(CreateArray(tmpElements->Data(), tmpElements->Size(), scriptObj), result);
	return true;
}

bool Cmd_GetQuestObjectives_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESQuest *quest;
	UInt32 completed;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &quest, &completed)) return true;
	TempElements *tmpElements = GetTempElements();
	auto iter = quest->lVarOrObjectives.Head();
	BGSQuestObjective *objective;
	if (completed) completed = 2;
	completed++;
	do
	{
		objective = (BGSQuestObjective*)iter->data;
		if (objective && IS_TYPE(objective, BGSQuestObjective) && (completed == (objective->status & 3)))
			tmpElements->Append((int)objective->objectiveId);
	}
	while (iter = iter->next);
	if (!tmpElements->Empty())
		AssignCommandResult(CreateArray(tmpElements->Data(), tmpElements->Size(), scriptObj), result);
	return true;
}

bool Cmd_GetActiveObjectives_Execute(COMMAND_ARGS)
{
	*result = 0;
	if (!g_thePlayer->activeQuest) return true;
	TempElements *tmpElements = GetTempElements();
	auto iter = g_thePlayer->activeQuest->lVarOrObjectives.Head();
	BGSQuestObjective *objective;
	do
	{
		objective = (BGSQuestObjective*)iter->data;
		if (objective && IS_TYPE(objective, BGSQuestObjective) && ((objective->status & 3) == 1))
			tmpElements->Append((int)objective->objectiveId);
	}
	while (iter = iter->next);
	if (!tmpElements->Empty())
		AssignCommandResult(CreateArray(tmpElements->Data(), tmpElements->Size(), scriptObj), result);
	return true;
}

bool Cmd_GetObjectiveTeleportLinks_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESQuest *quest;
	UInt32 objectiveID;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &quest, &objectiveID)) return true;
	BGSQuestObjective *objective = quest->GetObjective(objectiveID);
	if (!objective || ((objective->status & 3) != 1)) return true;
	NVSEArrayVar *linksArr = CreateArray(NULL, 0, scriptObj);
	TempElements *tmpElements = GetTempElements();
	auto trgIter = objective->targets.Head();
	ObjectiveTarget *target;
	TESQuest *activeQuest = g_thePlayer->activeQuest;
	bool evalRes;
	do
	{
		if (!(target = trgIter->data) || !target->conditions.Evaluate(target->target, NULL, &evalRes, 0))
			continue;
		if (quest != activeQuest)
			StdCall(0x952D60, target->target, &target->data, 1);
		for (auto lnkIter = target->data.teleportLinks.Begin(); lnkIter; ++lnkIter)
			tmpElements->Append(lnkIter.Get().door);
		tmpElements->Append(target->target);
		AppendElement(linksArr, ArrayElementL(CreateArray(tmpElements->Data(), tmpElements->Size(), scriptObj)));
		tmpElements->Clear();
	}
	while (trgIter = trgIter->next);
	if (GetArraySize(linksArr)) AssignCommandResult(linksArr, result);
	return true;
}

bool Cmd_GetQuestFlag_Execute(COMMAND_ARGS)
{
	TESQuest *quest;
	UInt32 flagID;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &quest, &flagID) && (flagID <= 7))
		*result = (quest->questFlags & (1 << flagID)) ? 1 : 0;
	else *result = 0;
	return true;
}

bool Cmd_SetQuestFlag_Execute(COMMAND_ARGS)
{
	TESQuest *quest;
	UInt32 flagID, doSet;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &quest, &flagID, &doSet) && (flagID <= 7))
	{
		if (doSet) quest->questFlags |= (1 << flagID);
		else quest->questFlags &= ~(1 << flagID);
	};
	return true;
}

bool Cmd_FailQuest_Execute(COMMAND_ARGS)
{
	TESQuest *quest;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &quest))
		ThisCall(0x60CAF0, quest, 1);
	return true;
}

TempObject<TempFormList> s_lastQuestTargets(0x40);

bool Cmd_GetQuestTargetsChanged_Execute(COMMAND_ARGS)
{
	TempFormList *tmpFormLst = GetTempFormList();
	auto objIter = g_thePlayer->questObjectiveList.Head();
	BGSQuestObjective *objective;
	ObjectiveTarget *target;
	bool evalRes;
	do
	{
		if (!(objective = objIter->data) || (objective->quest->questFlags & TESQuest::kFlag_Completed) || ((objective->status & 3) != 1) || objective->targets.Empty())
			continue;
		auto trgIter = objective->targets.Head();
		do
		{
			if ((target = trgIter->data) && target->target && target->conditions.Evaluate(target->target, NULL, &evalRes, 0))
				tmpFormLst->Insert(target->target);
		}
		while (trgIter = trgIter->next);
	}
	while (objIter = objIter->next);
	if (s_lastQuestTargets() == *tmpFormLst)
		*result = 0;
	else
	{
		s_lastQuestTargets().CopyFrom(*tmpFormLst);
		*result = 1;
	}
	return true;
}