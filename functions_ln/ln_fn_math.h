#pragma once

DEFINE_COMMAND_PLUGIN(fsqrt, 0, 1, kParams_OneDouble);
DEFINE_CMD_COND_PLUGIN(GetDistance2D, 1, 1, kParams_OneObjectRef);
DEFINE_CMD_COND_PLUGIN(GetDistance3D, 1, 1, kParams_OneObjectRef);
DEFINE_COMMAND_PLUGIN(fSin, 0, 2, kParams_OneDouble_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(fCos, 0, 2, kParams_OneDouble_OneOptionalInt);
DEFINE_COMMAND_PLUGIN(fTan, 0, 1, kParams_OneDouble);
DEFINE_COMMAND_PLUGIN(fAsin, 0, 1, kParams_OneFloat);
DEFINE_COMMAND_PLUGIN(fAcos, 0, 1, kParams_OneFloat);
DEFINE_COMMAND_PLUGIN(fAtan, 0, 1, kParams_OneFloat);
DEFINE_COMMAND_PLUGIN(fAtan2, 0, 2, kParams_TwoFloats);

bool Cmd_fsqrt_Execute(COMMAND_ARGS)
{
	double value;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &value))
	{
		__asm
		{
			xorps	xmm1, xmm1
			maxsd	xmm1, value
			sqrtsd	xmm0, xmm1
			mov		eax, result
			movq	qword ptr [eax], xmm0
		}
	}
	else *result = 0;
	return true;
}

bool Cmd_GetDistance2D_Execute(COMMAND_ARGS)
{
	TESObjectREFR *refr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &refr) && thisObj->GetInSameCellOrWorld(refr))
		*result = Point2Distance(thisObj->position, refr->position);
	else *result = FLT_MAX;
	return true;
}

bool Cmd_GetDistance2D_Eval(COMMAND_ARGS_EVAL)
{
	TESObjectREFR *refr = (TESObjectREFR*)arg1;
	*result = thisObj->GetInSameCellOrWorld(refr) ? Point2Distance(thisObj->position, refr->position) : FLT_MAX;
	return true;
}

bool Cmd_GetDistance3D_Execute(COMMAND_ARGS)
{
	TESObjectREFR *refr;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &refr))
		*result = thisObj->GetDistance(refr);
	else *result = FLT_MAX;
	return true;
}

bool Cmd_GetDistance3D_Eval(COMMAND_ARGS_EVAL)
{
	*result = thisObj->GetDistance((TESObjectREFR*)arg1);
	return true;
}

bool Cmd_fSin_Execute(COMMAND_ARGS)
{
	double value;
	UInt32 precision;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &value, &precision))
		*result = Cos(1.5707963267948966 - value * DblPId180);
	else *result = 0;
	return true;
}

bool Cmd_fCos_Execute(COMMAND_ARGS)
{
	double value;
	UInt32 precision;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &value, &precision))
		*result = Cos(value * DblPId180);
	else *result = 0;
	return true;
}

bool Cmd_fTan_Execute(COMMAND_ARGS)
{
	double value;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &value))
		*result = Tan(value * DblPId180);
	else *result = 0;
	return true;
}

bool Cmd_fAsin_Execute(COMMAND_ARGS)
{
	float value;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &value))
		*result = ASin(value) * Dbl180dPI;
	else *result = 0;
	return true;
}

bool Cmd_fAcos_Execute(COMMAND_ARGS)
{
	float value;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &value))
		*result = ACos(value) * Dbl180dPI;
	else *result = 0;
	return true;
}

bool Cmd_fAtan_Execute(COMMAND_ARGS)
{
	float value;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &value))
		*result = ATan2(value, 1.0F) * Dbl180dPI;
	else *result = 0;
	return true;
}

bool Cmd_fAtan2_Execute(COMMAND_ARGS)
{
	float y, x;
	if (ExtractArgsEx(EXTRACT_ARGS_EX, &y, &x))
		*result = ATan2(y, x) * Dbl180dPI;
	else *result = 0;
	return true;
}