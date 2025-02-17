#pragma once

DEFINE_COMMAND_PLUGIN(GetClassTraitNumeric, 0, 2, kParams_OneClass_OneInt);
DEFINE_COMMAND_PLUGIN(SetClassTraitNumeric, 0, 3, kParams_OneClass_TwoInts);
DEFINE_COMMAND_PLUGIN(GetClassFlag, 0, 2, kParams_OneClass_OneInt);
DEFINE_COMMAND_PLUGIN(SetClassFlag, 0, 3, kParams_OneClass_TwoInts);

bool Cmd_GetClassTraitNumeric_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESClass *pClass;
	UInt32 traitID;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &pClass, &traitID) || (traitID > 10)) return true;
	if (traitID < 4) *result = (int)pClass->tagSkills[traitID];
	else *result = pClass->attributes.attributes[traitID - 4];
	return true;
}

bool Cmd_SetClassTraitNumeric_Execute(COMMAND_ARGS)
{
	TESClass *pClass;
	UInt32 traitID;
	int val;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &pClass, &traitID, &val) || (traitID > 10)) return true;
	if (traitID < 4)
	{
		if ((val == -1) || ((val > 31) && (val < 46) && (val != 33)))
			pClass->tagSkills[traitID] = val;
	}
	else if ((val > 0) && (val < 11))
		pClass->attributes.attributes[traitID - 4] = val;
	return true;
}

bool Cmd_GetClassFlag_Execute(COMMAND_ARGS)
{
	*result = 0;
	TESClass *pClass;
	UInt32 flagID;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &pClass, &flagID) || (flagID > 19)) return true;
	if (flagID < 2) *result = (pClass->classFlags & (1 << flagID)) ? 1 : 0;
	else *result = (pClass->services & (1 << (flagID - 2))) ? 1 : 0;
	return true;
}

bool Cmd_SetClassFlag_Execute(COMMAND_ARGS)
{
	TESClass *pClass;
	UInt32 flagID, val;
	if (!ExtractArgsEx(EXTRACT_ARGS_EX, &pClass, &flagID, &val) || (flagID > 19)) return true;
	if (flagID < 2)
	{
		if (val) pClass->classFlags |= (1 << flagID);
		else pClass->classFlags &= ~(1 << flagID);
	}
	else if (val) pClass->services |= (1 << (flagID - 2));
	else pClass->services &= ~(1 << (flagID - 2));
	return true;
}