#pragma once

DEFINE_COMMAND_PLUGIN(GetNumEffects, 0, 1, kParams_OneMagicItem);
DEFINE_COMMAND_PLUGIN(GetNthEffectBase, 0, 2, kParams_OneMagicItem_OneInt);
DEFINE_COMMAND_PLUGIN(SetNthEffectBase, 0, 3, kParams_OneMagicItem_OneInt_OneMagicEffect);
DEFINE_COMMAND_PLUGIN(GetNthEffectTraitNumeric, 0, 3, kParams_OneMagicItem_TwoInts);
DEFINE_COMMAND_PLUGIN(SetNthEffectTraitNumeric, 0, 4, kParams_OneMagicItem_ThreeInts);
DEFINE_COMMAND_PLUGIN(AddNewEffect, 0, 7, kParams_OneMagicItem_OneEffect_TwoInts_ThreeOptionalInts);
DEFINE_COMMAND_PLUGIN(RemoveNthEffect, 0, 2, kParams_OneMagicItem_OneInt);
DEFINE_COMMAND_PLUGIN(SetObjectEffect, 0, 2, kParams_OneForm_OneOptionalForm);
DEFINE_COMMAND_PLUGIN(GetNumActorEffects, 0, 1, kParams_OneOptionalActorBase);
DEFINE_COMMAND_PLUGIN(GetNthActorEffect, 0, 2, kParams_OneInt_OneOptionalActorBase);
DEFINE_COMMAND_PLUGIN(GetActorUnarmedEffect, 0, 1, kParams_OneOptionalActorBase);
DEFINE_COMMAND_PLUGIN(SetActorUnarmedEffect, 0, 2, kParams_OneForm_OneOptionalActorBase);
DEFINE_COMMAND_PLUGIN(GetAddictionEffect, 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetAddictionEffect, 0, 2, kParams_OneForm_OneOptionalForm);
DEFINE_COMMAND_PLUGIN(GetAddictionChance, 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetAddictionChance, 0, 2, kParams_OneForm_OneFloat);
DEFINE_COMMAND_PLUGIN(GetIsPoison, 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(GetActiveEffects, 1, 1, kParams_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(GetTempEffects, 1, 0, NULL);
DEFINE_COMMAND_PLUGIN(RemoveNthTempEffect, 1, 1, kParams_OneInt);
DEFINE_COMMAND_PLUGIN(GetEffectFlag, 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetEffectFlag, 0, 3, kParams_OneForm_TwoInts);
DEFINE_COMMAND_PLUGIN(GetBaseEffectFlag, 0, 2, kParams_OneForm_OneInt);
DEFINE_COMMAND_PLUGIN(SetBaseEffectFlag, 0, 3, kParams_OneForm_TwoInts);
DEFINE_COMMAND_PLUGIN(GetBaseEffectScript, 0, 1, kParams_OneForm);
DEFINE_COMMAND_PLUGIN(SetBaseEffectScript, 0, 2, kParams_TwoForms);
DEFINE_CMD_COND_PLUGIN(IsSpellTargetAlt, 1, 1, kParams_OneMagicItem);
DEFINE_COMMAND_PLUGIN(CastImmediate, 1, 2, kParams_OneMagicItem_OneOptionalActor);
DEFINE_CMD_COND_PLUGIN(IsSpellTargetList, 1, 1, kParams_FormList);

bool Cmd_GetNumEffects_Execute(COMMAND_ARGS)
{
	MagicItem *magicItem;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &magicItem))
		*result = (int)magicItem->list.list.Count();
	else *result = 0;
	return true;
}

bool Cmd_GetNthEffectBase_Execute(COMMAND_ARGS)
{
	*result = 0;
	MagicItem *magicItem;
	UInt32 idx;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &magicItem, &idx))
	{
		EffectItem *effItem = magicItem->list.list.GetNthItem(idx);
		if (effItem && effItem->setting)
			REFR_RES = effItem->setting->refID;
	}
	return true;
}

bool Cmd_SetNthEffectBase_Execute(COMMAND_ARGS)
{
	MagicItem *magicItem;
	UInt32 idx;
	EffectSetting *effSetting;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &magicItem, &idx, &effSetting))
	{
		EffectItem *effItem = magicItem->list.list.GetNthItem(idx);
		if (effItem)
		{
			effItem->setting = effSetting;
			effItem->actorValueOrOther = effSetting->actorVal;
			magicItem->UpdateEffectsAllActors(effItem);
		}
	}
	return true;
}

bool Cmd_GetNthEffectTraitNumeric_Execute(COMMAND_ARGS)
{
	*result = 0;
	MagicItem *magicItem;
	UInt32 idx, traitID;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &magicItem, &idx, &traitID))
		return true;
	EffectItem *effItem = magicItem->list.list.GetNthItem(idx);
	if (!effItem) return true;
	switch (traitID)
	{
		case 0:
			*result = (int)effItem->magnitude;
			break;
		case 1:
			*result = (int)effItem->area;
			break;
		case 2:
			*result = (int)effItem->duration;
			break;
		case 3:
			*result = (int)effItem->range;
			break;
	}
	return true;
}

bool Cmd_SetNthEffectTraitNumeric_Execute(COMMAND_ARGS)
{
	MagicItem *magicItem;
	UInt32 idx, traitID, val;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &magicItem, &idx, &traitID, &val) || (traitID > 2))
		return true;
	EffectItem *effItem = magicItem->list.list.GetNthItem(idx);
	if (!effItem) return true;
	switch (traitID)
	{
		case 0:
			effItem->magnitude = val;
			break;
		case 1:
			effItem->area = val;
			return true;
		case 2:
			effItem->duration = val;
			break;
	}
	magicItem->UpdateEffectsAllActors(effItem);
	return true;
}

bool Cmd_AddNewEffect_Execute(COMMAND_ARGS)
{
	*result = -1;
	MagicItem *magicItem;
	EffectSetting *effSetting;
	UInt32 duration, magnitude, range = 0, area = 0, append = 0;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &magicItem, &effSetting, &duration, &magnitude, &range, &area, &append) || (range > 2))
		return true;
	UInt32 type = magicItem->GetType();
	if (type == 6)
	{
		EnchantmentItem *enchItem = (EnchantmentItem*)((UInt8*)magicItem - 0x18);
		if (enchItem->type == 2) range = 1;
		else area = range = 0;
	}
	else if (type == 7)
		area = range = 0;
	else
	{
		if ((type == 1) || (type == 4) || (type == 10))
			range = 0;
		if (!range) area = 0;
	}
	if (!(effSetting->effectFlags & (16 << range)))
		return true;
	EffectItem *effItem = (EffectItem*)GameHeapAlloc(sizeof(EffectItem));
	effItem->magnitude = magnitude;
	effItem->area = area;
	effItem->duration = duration;
	effItem->range = range;
	effItem->actorValueOrOther = effSetting->actorVal;
	effItem->setting = effSetting;
	effItem->cost = 0;
	effItem->conditions.Init();
	if (append)
		*result = magicItem->list.list.Append(effItem) + 1;
	else
	{
		magicItem->list.list.Prepend(effItem);
		*result = (int)magicItem->list.list.Count();
	}
	magicItem->UpdateEffectsAllActors(effItem, true);
	return true;
}

bool Cmd_RemoveNthEffect_Execute(COMMAND_ARGS)
{
	MagicItem *magicItem;
	SInt32 idx;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &magicItem, &idx) && magicItem->list.RemoveNthEffect(idx))
		*result = (int)magicItem->list.list.Count();
	else *result = -1;
	return true;
}

bool Cmd_SetObjectEffect_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm *form;
	EnchantmentItem *effect = NULL;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &form, &effect)) return true;
	TESEnchantableForm *enchantable = DYNAMIC_CAST(form, TESForm, TESEnchantableForm);
	if (!enchantable) return true;
	if (effect && IS_ID(effect, EnchantmentItem))
	{
		if IS_TYPE(form, TESObjectARMO)
		{
			if (effect->type != 3) return true;
		}
		else if (effect->type != 2) return true;
		enchantable->enchantItem = effect;
	}
	else enchantable->enchantItem = NULL;
	*result = 1;
	return true;
}

bool Cmd_GetNumActorEffects_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESActorBase *actorBase = NULL;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &actorBase)) return true;
	if (!actorBase)
	{
		if (!thisObj || NOT_ACTOR(thisObj)) return true;
		actorBase = (TESActorBase*)thisObj->baseForm;
	}
	*result = (int)actorBase->spellList.spellList.Count();
	return true;
}

bool Cmd_GetNthActorEffect_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 idx;
	TESActorBase *actorBase = NULL;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &idx, &actorBase)) return true;
	if (!actorBase)
	{
		if (!thisObj || NOT_ACTOR(thisObj)) return true;
		actorBase = (TESActorBase*)thisObj->baseForm;
	}
	SpellItem *splItem = actorBase->spellList.spellList.GetNthItem(idx);
	if (splItem) REFR_RES = splItem->refID;
	return true;
}

bool Cmd_GetActorUnarmedEffect_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESActorBase *actorBase = NULL;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &actorBase)) return true;
	if (!actorBase)
	{
		if (!thisObj || NOT_ACTOR(thisObj)) return true;
		actorBase = (TESActorBase*)thisObj->baseForm;
	}
	if (actorBase->touchSpell.unarmedEffect) REFR_RES = actorBase->touchSpell.unarmedEffect->refID;
	return true;
}

bool Cmd_SetActorUnarmedEffect_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm *effForm;
	TESActorBase *actorBase = NULL;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &effForm, &actorBase)) return true;
	if (!actorBase)
	{
		if (!thisObj || NOT_ACTOR(thisObj)) return true;
		actorBase = (TESActorBase*)thisObj->baseForm;
	}
	if IS_ID(effForm, EnchantmentItem)
	{
		if (((EnchantmentItem*)effForm)->type != 2) return true;
	}
	else if IS_ID(effForm, SpellItem)
	{
		if (((SpellItem*)effForm)->type) return true;
	}
	else return true;
	actorBase->touchSpell.unarmedEffect = effForm;
	*result = 1;
	return true;
}

bool Cmd_GetAddictionEffect_Execute(COMMAND_ARGS)
{
	*result = 0;
	AlchemyItem *alch;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &alch) && IS_ID(alch, AlchemyItem) && alch->withdrawalEffect)
		REFR_RES = alch->withdrawalEffect->refID;
	return true;
}

bool Cmd_SetAddictionEffect_Execute(COMMAND_ARGS)
{
	AlchemyItem *alch;
	SpellItem *effect = NULL;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &alch, &effect) && IS_ID(alch, AlchemyItem))
		alch->withdrawalEffect = (effect && IS_ID(effect, SpellItem)) ? effect : NULL;
	return true;
}

bool Cmd_GetAddictionChance_Execute(COMMAND_ARGS)
{
	AlchemyItem *alch;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &alch) && IS_ID(alch, AlchemyItem) && alch->withdrawalEffect)
		*result = alch->addictionChance;
	else *result = 0;
	return true;
}

bool Cmd_SetAddictionChance_Execute(COMMAND_ARGS)
{
	AlchemyItem *alch;
	float chance;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &alch, &chance) && IS_ID(alch, AlchemyItem) && alch->withdrawalEffect)
		alch->addictionChance = chance;
	return true;
}

bool Cmd_GetIsPoison_Execute(COMMAND_ARGS)
{
	AlchemyItem *alch;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &alch) && IS_ID(alch, AlchemyItem))
		*result = alch->IsPoison() ? 1 : 0;
	else *result = 0;
	return true;
}

bool Cmd_GetActiveEffects_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 filter = 7;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &filter) || NOT_ACTOR(thisObj))
		return true;
	filter = ((filter & 1) ? kFormType_EnchantmentItem : 63) & ((filter & 2) ? kFormType_SpellItem : 63) & ((filter & 4) ? kFormType_AlchemyItem : 63);
	auto iter = ((Actor*)thisObj)->magicTarget.GetEffectList()->Head();
	if (!iter) return true;
	TempElements *tmpElements = GetTempElements();
	ActiveEffect *activeEff;
	TESForm *form;
	do
	{
		activeEff = iter->data;
		if (!activeEff || !activeEff->bActive || activeEff->bTerminated || !activeEff->magicItem || (activeEff->magnitude == 0))
			continue;
		form = DYNAMIC_CAST(activeEff->magicItem, MagicItem, TESForm);
		if (form && (!filter || ((form->typeID & filter) == filter)))
			tmpElements->InsertUnique(form);
	}
	while (iter = iter->next);
	if (!tmpElements->Empty())
		AssignCommandResult(CreateArray(tmpElements->Data(), tmpElements->Size(), scriptObj), result);
	return true;
}

bool __fastcall ValidTempEffect(EffectItem *effectItem)
{
	if (!effectItem || (effectItem->duration <= 0) || !effectItem->setting) return false;
	UInt8 archtype = effectItem->setting->archtype;
	return !archtype || ((archtype == 1) && (effectItem->setting->effectFlags & 0x2000)) || ((archtype > 10) && (archtype < 14)) || (archtype == 24) || (archtype > 33);
}

struct SortEffectsEntry
{
	NVSEArrayVar	*valuesArr;
	float			timeLeft;

	SortEffectsEntry(NVSEArrayVar *_valuesArr, float _timeLeft) : valuesArr(_valuesArr), timeLeft(_timeLeft) {}

	bool operator<(const SortEffectsEntry &rhs) const {return timeLeft < rhs.timeLeft;}
};

bool Cmd_GetTempEffects_Execute(COMMAND_ARGS)
{
	*result = 0;
	if (NOT_ACTOR(thisObj)) return true;
	auto iter = ((Actor*)thisObj)->magicTarget.GetEffectList()->Head();
	if (!iter) return true;
	Vector<SortEffectsEntry> sortEffects;
	ActiveEffect *activeEff;
	TESForm *form;
	float timeLeft;
	do
	{
		activeEff = iter->data;
		if (!activeEff || !activeEff->bActive || activeEff->bTerminated || !ValidTempEffect(activeEff->effectItem) || !activeEff->magicItem) continue;
		form = DYNAMIC_CAST(activeEff->magicItem, MagicItem, TESForm);
		if (!form) continue;
		timeLeft = activeEff->duration - activeEff->timeElapsed;
		ArrayElementL elements[6] =
		{
			form,
			activeEff->effectItem->setting,
			(activeEff->effectItem->setting->effectFlags & 2) ? (int)activeEff->effectItem->magnitude : fabs(activeEff->magnitude),
			timeLeft,
			activeEff->caster ? activeEff->caster->GetActor() : NULL,
			activeEff->duration
		};
		sortEffects.InsertSorted(SortEffectsEntry(CreateArray(elements, 6, scriptObj), timeLeft));
	}
	while (iter = iter->next);
	if (!sortEffects.Empty())
	{
		TempElements *tmpElements = GetTempElements();
		for (auto entry = sortEffects.Begin(); entry; ++entry)
			tmpElements->Append(entry().valuesArr);
		AssignCommandResult(CreateArray(tmpElements->Data(), tmpElements->Size(), scriptObj), result);
	}
	return true;
}

bool Cmd_RemoveNthTempEffect_Execute(COMMAND_ARGS)
{
	*result = 0;
	UInt32 index;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &index) || NOT_ACTOR(thisObj))
		return true;
	ActiveEffect *activeEff;
	for (auto iter = ((Actor*)thisObj)->magicTarget.GetEffectList()->Head(); iter; iter = iter->next)
	{
		activeEff = iter->data;
		if (!activeEff || !activeEff->bActive || activeEff->bTerminated || !ValidTempEffect(activeEff->effectItem) || !activeEff->magicItem ||
			!DYNAMIC_CAST(activeEff->magicItem, MagicItem, TESForm) || index--) continue;
		activeEff->Remove(true);
		*result = 1;
		break;
	}
	return true;
}

bool Cmd_GetEffectFlag_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESForm *effForm;
	UInt32 flagID;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &effForm, &flagID) || (flagID > 7)) return true;
	UInt8 flags;
	switch (effForm->typeID)
	{
	case kFormType_SpellItem:
		flags = ((SpellItem*)effForm)->spellFlags;
		break;
	case kFormType_EnchantmentItem:
		flags = ((EnchantmentItem*)effForm)->enchFlags;
		break;
	case kFormType_AlchemyItem:
		flags = ((AlchemyItem*)effForm)->alchFlags;
		break;
	default:
		return true;
	}
	*result = (flags & (1 << flagID)) ? 1 : 0;
	return true;
}

bool Cmd_SetEffectFlag_Execute(COMMAND_ARGS)
{
	TESForm *effForm;
	UInt32 flagID, val;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &effForm, &flagID, &val) || (flagID > 7)) return true;
	UInt8 *flagsPtr;
	switch (effForm->typeID)
	{
	case kFormType_SpellItem:
		flagsPtr = &((SpellItem*)effForm)->spellFlags;
		break;
	case kFormType_EnchantmentItem:
		flagsPtr = &((EnchantmentItem*)effForm)->enchFlags;
		break;
	case kFormType_AlchemyItem:
		flagsPtr = &((AlchemyItem*)effForm)->alchFlags;
		break;
	default:
		return true;
	}
	if (val) *flagsPtr |= (1 << flagID);
	else *flagsPtr &= ~(1 << flagID);
	return true;
}

bool Cmd_GetBaseEffectFlag_Execute(COMMAND_ARGS)
{
	EffectSetting *effForm;
	UInt32 flagID;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &effForm, &flagID) && IS_ID(effForm, EffectSetting) && (flagID <= 31))
		*result = (effForm->effectFlags & (1 << flagID)) ? 1 : 0;
	else *result = 0;
	return true;
}

bool Cmd_SetBaseEffectFlag_Execute(COMMAND_ARGS)
{
	EffectSetting *effSetting;
	UInt32 flagID, val;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &effSetting, &flagID, &val) && IS_ID(effSetting, EffectSetting) && (flagID <= 31))
	{
		if (val) effSetting->effectFlags |= (1 << flagID);
		else effSetting->effectFlags &= ~(1 << flagID);
	}
	return true;
}

bool Cmd_GetBaseEffectScript_Execute(COMMAND_ARGS)
{
	*result = 0;
	EffectSetting *effect;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &effect) && IS_ID(effect, EffectSetting) && (effect->archtype == 1) && effect->associatedItem)
		REFR_RES = effect->associatedItem->refID;
	return true;
}

bool Cmd_SetBaseEffectScript_Execute(COMMAND_ARGS)
{
	EffectSetting *effect;
	Script *script;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &effect, &script) && IS_ID(effect, EffectSetting) && (effect->archtype == 1) && IS_ID(script, Script))
		effect->associatedItem = script;
	return true;
}

bool __fastcall IsSpellTargetAlt(Actor *actor, MagicItem *magicItem)
{
	if (NOT_ACTOR(actor)) return false;
	ActiveEffect *activeEff;
	for (auto iter = actor->magicTarget.GetEffectList()->Head(); iter; iter = iter->next)
	{
		activeEff = iter->data;
		if (activeEff && (activeEff->magicItem == magicItem) && activeEff->bActive && !activeEff->bTerminated)
			return true;
	}
	return false;
}

bool Cmd_IsSpellTargetAlt_Execute(COMMAND_ARGS)
{
	MagicItem *magicItem;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &magicItem))
		*result = IsSpellTargetAlt((Actor*)thisObj, magicItem);
	else *result = 0;
	return true;
}

bool Cmd_IsSpellTargetAlt_Eval(COMMAND_ARGS_EVAL)
{
	*result = IsSpellTargetAlt((Actor*)thisObj, (MagicItem*)arg1);
	return true;
}

bool Cmd_CastImmediate_Execute(COMMAND_ARGS)
{
	MagicItem *magicItem;
	Actor *target = (Actor*)thisObj, *caster = NULL;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &magicItem, &caster) && IS_ACTOR(target) && target->GetRefNiNode() && (magicItem->GetType() != 4))
	{
		if (!caster) caster = target;
		caster->jipActorFlags2 |= kHookActorFlag2_CastImmediate;
		caster->magicCaster.CastSpell(magicItem, 0, &target->magicTarget, 1, 0);
		caster->jipActorFlags2 &= ~kHookActorFlag2_CastImmediate;
	}
	return true;
}

bool __fastcall IsSpellTargetList(Actor *actor, BGSListForm *splList)
{
	if (NOT_ACTOR(actor)) return false;
	auto effIter = actor->magicTarget.GetEffectList()->Head();
	if (!effIter) return false;
	TempFormList *tmpFormLst = GetTempFormList();
	MagicItem *magicItem;
	auto lstIter = splList->list.Head();
	do
	{
		if (lstIter->data && (magicItem = lstIter->data->GetMagicItem()))
			tmpFormLst->Insert((TESForm*)magicItem);
	}
	while (lstIter = lstIter->next);
	if (tmpFormLst->Empty()) return false;
	ActiveEffect *activeEff;
	do
	{
		activeEff = effIter->data;
		if (activeEff && activeEff->bActive && !activeEff->bTerminated && tmpFormLst->HasKey((TESForm*)activeEff->magicItem))
			return true;
	}
	while (effIter = effIter->next);
	return false;
}

bool Cmd_IsSpellTargetList_Execute(COMMAND_ARGS)
{
	BGSListForm *splList;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &splList))
		*result = IsSpellTargetList((Actor*)thisObj, splList);
	else *result = 0;
	return true;
}

bool Cmd_IsSpellTargetList_Eval(COMMAND_ARGS_EVAL)
{
	*result = IsSpellTargetList((Actor*)thisObj, (BGSListForm*)arg1);
	return true;
}