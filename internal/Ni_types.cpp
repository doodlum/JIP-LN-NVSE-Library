#include "internal/Ni_types.h"

void NiPoint2::Dump() const
{
	PrintDebug("%.6f\t%.6f\n", x, y);
}

void NiVector3::operator=(const NiMatrix33 &from)
{
	*this = from.ToEulerPRY();
}

void NiVector3::operator=(const NiQuaternion &from)
{
	*this = from.ToEulerPRY();
}

__declspec(naked) float __vectorcall NiVector3::Length() const
{
	__asm
	{
		movups	xmm0, [ecx]
		andps	xmm0, PS_XYZ0Mask
		xorps	xmm1, xmm1
		mulps	xmm0, xmm0
		haddps	xmm0, xmm1
		haddps	xmm0, xmm1
		sqrtss	xmm0, xmm0
		retn
	}
}

__declspec(naked) NiVector3& __fastcall NiVector3::MultiplyMatrix(const NiMatrix33 &mat)
{
	__asm
	{
		movups	xmm1, [ecx]
		andps	xmm1, PS_XYZ0Mask
		xorps	xmm3, xmm3
		movups	xmm0, [edx]
		mulps	xmm0, xmm1
		haddps	xmm0, xmm3
		haddps	xmm0, xmm3
		movups	xmm2, [edx+0xC]
		mulps	xmm2, xmm1
		haddps	xmm2, xmm3
		haddps	xmm2, xmm3
		unpcklps	xmm0, xmm2
		movq	qword ptr [ecx], xmm0
		movups	xmm2, [edx+0x18]
		mulps	xmm2, xmm1
		haddps	xmm2, xmm3
		haddps	xmm2, xmm3
		movss	[ecx+8], xmm2
		unpcklpd	xmm0, xmm2
		mov		eax, ecx
		retn
	}
}

__declspec(naked) NiVector3& __fastcall NiVector3::MultiplyMatrixInv(const NiMatrix33 &mat)
{
	__asm
	{
		movups	xmm3, [ecx]
		andps	xmm3, PS_XYZ0Mask
		movups	xmm0, [edx]
		pshufd	xmm1, xmm3, 0xC0
		mulps	xmm0, xmm1
		movups	xmm1, [edx+0xC]
		pshufd	xmm2, xmm3, 0xD5
		mulps	xmm1, xmm2
		addps	xmm0, xmm1
		movups	xmm1, [edx+0x18]
		shufps	xmm3, xmm3, 0xEA
		mulps	xmm1, xmm3
		addps	xmm0, xmm1
		pshufd	xmm1, xmm0, 2
		movq	qword ptr [ecx], xmm0
		movss	[ecx+8], xmm1
		mov		eax, ecx
		retn
	}
}

__declspec(naked) NiVector3& __fastcall NiVector3::MultiplyMatrixRow(const NiMatrix33 &rotMatrix, UInt32 whichRow)
{
	__asm
	{
		mov		eax, [esp+4]
		movups	xmm0, [edx+eax*4]
		movss	xmm1, [edx+eax*4+0x18]
		shufps	xmm0, xmm0, 0xC
		unpcklpd	xmm0, xmm1
		movups	xmm1, [ecx]
		mulps	xmm0, xmm1
		pshufd	xmm1, xmm0, 2
		movq	qword ptr [ecx], xmm0
		movss	[ecx+8], xmm1
		mov		eax, ecx
		retn	4
	}
}

__declspec(naked) NiVector3& __fastcall NiVector3::MultiplyQuaternion(const NiQuaternion &qt)
{
	__asm
	{
		movups	xmm0, [ecx]
		andps	xmm0, PS_XYZ0Mask
		movups	xmm1, [edx]
		pshufd	xmm2, xmm1, 0
		psrldq	xmm1, 4
		movaps	xmm3, xmm1
		pshufd	xmm4, xmm0, 0xC9
		pshufd	xmm5, xmm3, 0x12
		mulps	xmm4, xmm5
		pshufd	xmm5, xmm0, 0xD2
		pshufd	xmm6, xmm3, 9
		mulps	xmm5, xmm6
		subps	xmm4, xmm5
		addps	xmm4, xmm4
		mulps	xmm2, xmm4
		addps	xmm2, xmm0
		pshufd	xmm0, xmm4, 0xC9
		pshufd	xmm5, xmm1, 0x12
		mulps	xmm0, xmm5
		pshufd	xmm5, xmm4, 0xD2
		pshufd	xmm6, xmm1, 9
		mulps	xmm5, xmm6
		subps	xmm0, xmm5
		addps	xmm0, xmm2
		pshufd	xmm1, xmm0, 2
		movq	qword ptr [ecx], xmm0
		movss	[ecx+8], xmm1
		mov		eax, ecx
		retn
	}
}

__declspec(naked) NiVector3& NiVector3::Normalize()
{
    __asm
    {
		mov		eax, ecx
		movups	xmm1, [eax]
		andps	xmm1, PS_XYZ0Mask
		movaps	xmm2, xmm1
		mulps	xmm2, xmm2
		xorps	xmm0, xmm0
		haddps	xmm2, xmm0
		haddps	xmm2, xmm0
		comiss	xmm2, PS_Epsilon
		jb		zeroLen
		rsqrtss	xmm3, xmm2
		movss	xmm0, SS_3
		mulss	xmm2, xmm3
		mulss	xmm2, xmm3
		subss	xmm0, xmm2
		mulss	xmm0, xmm3
		mulss	xmm0, PS_V3_Half
		shufps	xmm0, xmm0, 0xC0
		mulps	xmm0, xmm1
	zeroLen:
		pshufd	xmm2, xmm0, 2
        movq	qword ptr [eax], xmm0
        movss	[eax+8], xmm2
        retn
    }
}

__declspec(naked) __m128 __vectorcall NiVector3::CrossProduct(const NiVector3 &vB) const
{
	__asm
	{
		movups	xmm1, [edx]
		andps	xmm1, PS_XYZ0Mask
		movups	xmm2, [ecx]
		pshufd	xmm0, xmm1, 0xC9
		pshufd	xmm3, xmm2, 0x12
		mulps	xmm0, xmm3
		pshufd	xmm3, xmm1, 0xD2
		pshufd	xmm4, xmm2, 9
		mulps	xmm3, xmm4
		subps	xmm0, xmm3
		jmp		Normalize_V4
	}
}

__declspec(naked) __m128 __vectorcall NiVector3::Interpolate(const NiVector3 &vB, float t) const
{
	__asm
	{
		pshufd	xmm2, xmm0, 0
		movaps	xmm3, PS_XYZ0Mask
		movups	xmm0, [ecx]
		andps	xmm0, xmm3
		movups	xmm1, [edx]
		andps	xmm1, xmm3
		subps	xmm1, xmm0
		mulps	xmm1, xmm2
		addps	xmm0, xmm1
		retn
	}
}

__declspec(naked) __m128 __vectorcall NiVector3::GetAnglesBetweenPoints(const NiVector3 &pt2) const
{
	__asm
	{
		movups	xmm0, [ecx]
		movups	xmm1, [edx]
		subps	xmm0, xmm1
		andps	xmm0, PS_XYZ0Mask
		pshufd	xmm1, xmm0, 0xFD
		xorps	xmm1, PS_FlipSignMask0
		movaps	xmm2, xmm0
		xorps	xmm6, xmm6
		unpcklpd	xmm2, xmm6
		mulps	xmm2, xmm2
		haddps	xmm2, xmm6
		sqrtss	xmm6, xmm2
		pshufd	xmm7, xmm0, 0xFE
		call	ATan2
		movaps	xmm1, xmm6
		movaps	xmm6, xmm0
		movaps	xmm0, xmm7
		call	ATan2
		xorps	xmm0, PS_FlipSignMask0
		unpcklpd	xmm0, xmm6
		retn
	}
}

void NiVector3::Dump() const
{
	PrintDebug("%.6f\t%.6f\t%.6f\n", x, y, z);
}

__declspec(naked) float __vectorcall NiVector4::Length() const
{
	__asm
	{
		movups	xmm0, [ecx]
		xorps	xmm1, xmm1
		mulps	xmm0, xmm0
		haddps	xmm0, xmm1
		haddps	xmm0, xmm1
		sqrtss	xmm0, xmm0
		retn
	}
}

__declspec(naked) __m128 __vectorcall NiVector4::GetTranslatedPos(const NiTransform &transfrm) const
{
	__asm
	{
		call	NiVector3::MultiplyMatrix
		movups	xmm1, [edx+0x24]
		addps	xmm0, xmm1
		retn
	}
}

void NiVector4::Dump() const
{
	PrintDebug("%.6f\t%.6f\t%.6f\t%.6f\n", x, y, z, w);
}

__declspec(naked) AxisAngle& __vectorcall AxisAngle::FromEulerPRY(__m128 pry)
{
	__asm
	{
		movaps	xmm1, PS_V3_PI
		cmpltps	xmm1, xmm0
		andps	xmm1, PS_V3_PIx2
		subps	xmm0, xmm1
		mulps	xmm0, PS_V3_Half
		call	GetSinCos_V3
		movaps	xmm4, xmm0
		unpcklps	xmm4, xmm1
		shufps	xmm4, xmm1, 0xF0
		pshufd	xmm5, xmm0, 0xF1
		unpcklpd	xmm5, xmm1
		shufps	xmm5, xmm5, 0x5C
		movaps	xmm6, xmm0
		unpckhpd	xmm6, xmm1
		shufps	xmm6, xmm6, 0x58		
		shufps	xmm1, xmm1, 0xC9
		movaps	xmm2, xmm0
		mulps	xmm2, xmm1
		shufps	xmm0, xmm0, 0xC9
		shufps	xmm1, xmm1, 0xC9
		pshufd	xmm3, xmm2, 0xD2
		mulps	xmm2, xmm1
		mulps	xmm3, xmm0
		pshufd	xmm0, PS_FlipSignMask0, 0x44
		xorps	xmm3, xmm0
		addps	xmm2, xmm3
		movups	[ecx], xmm2
		movaps	xmm0, xmm4
		mulps	xmm0, xmm5
		mulps	xmm0, xmm6
		haddps	xmm0, xmm0
		call	ACos
		addss	xmm0, xmm0
		movss	[ecx+0xC], xmm0
		jmp		NiVector3::Normalize
	}
}

__declspec(naked) AxisAngle& __fastcall AxisAngle::FromRotationMatrix(const NiMatrix33 &rotMat)
{
	__asm
	{
		movq	xmm0, qword ptr [edx+0x14]
		movhps	xmm0, [edx+4]
		movss	xmm1, [edx+0x1C]
		movhps	xmm1, [edx+8]
		shufps	xmm1, xmm1, 0x38
		subps	xmm0, xmm1
		movups	[ecx], xmm0
		movss	xmm0, [edx]
		addss	xmm0, [edx+0x10]
		addss	xmm0, [edx+0x20]
		subss	xmm0, PS_V3_One
		mulss	xmm0, PS_V3_Half
		call	ACos
		movss	[ecx+0xC], xmm0
		jmp		NiVector3::Normalize
	}
}

__declspec(naked) AxisAngle& __fastcall AxisAngle::FromQuaternion(const NiQuaternion &qt)
{
	__asm
	{
		movups	xmm0, [edx]
		pshufd	xmm1, xmm0, 0x39
		movups	[ecx], xmm1
		call	ACos
		addss	xmm0, xmm0
		movss	[ecx+0xC], xmm0
		jmp		NiVector3::Normalize
	}
}

__declspec(naked) __m128 __vectorcall AxisAngle::ToEulerPRY() const
{
	__asm
	{
		sub		esp, 0x10
		mov		edx, ecx
		mov		ecx, esp
		call	NiQuaternion::FromAxisAngle
		mov		ecx, eax
		call	NiQuaternion::ToEulerPRY
		add		esp, 0x10
		retn
	}
}

void AxisAngle::Dump() const
{
	PrintDebug("(%.6f, %.6f, %.6f), %.6f\n", axis.x, axis.y, axis.z, theta);
}

__declspec(naked) __m128 __vectorcall NiMatrix33::ToEulerPRY() const
{
	__asm
	{
		movq	xmm1, qword ptr [ecx]
		pshufd	xmm0, xmm1, 0xA9
		call	ATan2
		movaps	xmm6, xmm0
		movss	xmm0, [ecx+8]
		xorps	xmm0, PS_FlipSignMask0
		call	ASin
		movaps	xmm7, xmm0
		movups	xmm0, [ecx+0x14]
		pshufd	xmm1, xmm0, 3
		call	ATan2
		unpcklps	xmm0, xmm7
		unpcklpd	xmm0, xmm6
		retn
	}
}

__declspec(naked) __m128 __vectorcall NiMatrix33::ToEulerPRYInv() const
{
	__asm
	{
		movups	xmm1, [ecx]
		pshufd	xmm0, xmm1, 3
		call	ATan2
		movaps	xmm6, xmm0
		movss	xmm0, [ecx+0x18]
		xorps	xmm0, PS_FlipSignMask0
		call	ASin
		movaps	xmm7, xmm0
		movq	xmm0, qword ptr [ecx+0x1C]
		pshufd	xmm1, xmm0, 0xA9
		call	ATan2
		unpcklps	xmm0, xmm7
		unpcklpd	xmm0, xmm6
		retn
	}
}

__declspec(naked) float __vectorcall NiMatrix33::ExtractPitch(UInt32 invert) const
{
	__asm
	{
		test	dl, dl
		jnz		getInv
		movups	xmm0, [ecx+0x14]
		pshufd	xmm1, xmm0, 3
		jmp		ATan2
	getInv:
		movq	xmm0, qword ptr [ecx+0x1C]
		pshufd	xmm1, xmm0, 0xA9
		jmp		ATan2
	}
}

__declspec(naked) float __vectorcall NiMatrix33::ExtractRoll(UInt32 invert) const
{
	__asm
	{
		shl		dl, 4
		movss	xmm0, [ecx+edx+8]
		xorps	xmm0, PS_FlipSignMask0
		jmp		ASin
	}
}

__declspec(naked) float __vectorcall NiMatrix33::ExtractYaw(UInt32 invert) const
{
	__asm
	{
		test	dl, dl
		jnz		getInv
		movq	xmm1, qword ptr [ecx]
		pshufd	xmm0, xmm1, 0xA9
		jmp		ATan2
	getInv:
		movups	xmm1, [ecx]
		pshufd	xmm0, xmm1, 3
		jmp		ATan2
	}
}

__declspec(naked) NiMatrix33& __vectorcall NiMatrix33::FromEulerPRY(__m128 pry)
{
	__asm
	{
		andps	xmm0, PS_XYZ0Mask
		call	GetSinCos_V3
		movshdup	xmm2, xmm0
		movshdup	xmm3, xmm1
		pshufd	xmm4, xmm0, 0xFE
		pshufd	xmm5, xmm1, 0xFE
		unpcklps	xmm5, xmm4
		movaps	xmm6, xmm3
		mulps	xmm6, xmm5
		movq	qword ptr [ecx], xmm6
		movaps	xmm6, xmm0
		mulss	xmm6, xmm4
		movaps	xmm7, xmm1
		mulss	xmm7, xmm5
		unpcklps	xmm1, xmm7
		mulss	xmm7, xmm2
		addss	xmm7, xmm6
		movaps	xmm6, xmm0
		mulss	xmm6, xmm3
		unpcklps	xmm6, xmm7
		movq	qword ptr [ecx+0x14], xmm6
		movshdup	xmm6, xmm1
		movaps	xmm7, xmm2
		mulss	xmm7, xmm4
		unpcklps	xmm2, xmm7
		mulss	xmm7, xmm0
		addss	xmm7, xmm6
		mulss	xmm0, xmm5
		mulss	xmm4, xmm1
		movaps	xmm5, xmm2
		mulss	xmm5, xmm0
		subss	xmm5, xmm4
		unpcklps	xmm5, xmm7
		movq	qword ptr [ecx+0xC], xmm5
		xorps	xmm2, PS_FlipSignMask0
		movss	[ecx+8], xmm2
		mulss	xmm3, xmm1
		psrldq	xmm2, 4
		mulss	xmm1, xmm2
		subss	xmm1, xmm0
		unpcklps	xmm1, xmm3
		movq	qword ptr [ecx+0x1C], xmm1
		mov		eax, ecx
		retn
	}
}

__declspec(naked) NiMatrix33& __vectorcall NiMatrix33::FromEulerPRYInv(__m128 pry)
{
	__asm
	{
		call	NiMatrix33::FromEulerPRY
		movups	xmm0, [eax]
		movups	xmm1, [eax+0x10]
		pshufd	xmm2, xmm0, 9
		shufps	xmm2, xmm1, 0x94
		shufps	xmm0, xmm2, 0x3C
		shufps	xmm1, xmm2, 0x9C
		movups	[eax], xmm0
		movups	[eax+0x10], xmm1
		retn
	}
}

__declspec(naked) NiMatrix33& __fastcall NiMatrix33::FromQuaternion(const NiQuaternion &qt)
{
	__asm
	{
		movups	xmm0, [edx]
		movaps	xmm3, xmm0
		addps	xmm3, xmm0
		pshufd	xmm1, xmm0, 0
		mulps	xmm1, xmm3
		pshufd	xmm2, xmm0, 0x78
		mulps	xmm2, xmm3
		mulps	xmm0, xmm3
		subss	xmm0, PS_V3_One
		pshufd	xmm3, xmm0, 1
		addss	xmm3, xmm0
		movss	[ecx], xmm3
		pshufd	xmm6, xmm0, 2
		addss	xmm6, xmm0
		pshufd	xmm7, xmm0, 3
		addss	xmm7, xmm0
		pshufd	xmm3, xmm2, 1
		movaps	xmm4, xmm3
		pshufd	xmm5, xmm1, 3
		subss	xmm3, xmm5
		addss	xmm4, xmm5
		unpcklps	xmm3, xmm6
		pshufd	xmm0, xmm2, 3
		movaps	xmm6, xmm0
		pshufd	xmm5, xmm1, 2
		subss	xmm0, xmm5
		addss	xmm6, xmm5
		unpcklps	xmm4, xmm0
		unpcklpd	xmm4, xmm3
		movups	[ecx+4], xmm4
		pshufd	xmm3, xmm2, 2
		movaps	xmm4, xmm3
		pshufd	xmm5, xmm1, 1
		subss	xmm3, xmm5
		addss	xmm4, xmm5
		unpcklps	xmm4, xmm6
		unpcklps	xmm3, xmm7
		unpcklpd	xmm4, xmm3
		movups	[ecx+0x14], xmm4
		mov		eax, ecx
		retn
	}
}

__declspec(naked) NiMatrix33& __fastcall NiMatrix33::FromAxisAngle(const AxisAngle &axisAngle)
{
	__asm
	{
		movss	xmm0, [edx+0xC]
		movups	xmm7, [edx]
		andps	xmm7, PS_XYZ0Mask
		call	GetSinCos
		pshufd	xmm2, xmm0, 0x80
		movaps	xmm3, xmm1
		movss	xmm4, PS_V3_One
		subss	xmm4, xmm3
		shufps	xmm4, xmm4, 0x40
		mulps	xmm2, xmm7
		mulps	xmm4, xmm7
		pshufd	xmm1, xmm7, 0xC9
		mulps	xmm1, xmm4
		mulps	xmm7, xmm4
		movaps	xmm4, xmm7
		addss	xmm4, xmm3
		movss	[ecx], xmm4
		pshufd	xmm6, xmm7, 1
		addss	xmm6, xmm3
		shufps	xmm7, xmm7, 2
		addss	xmm7, xmm3
		movaps	xmm3, xmm1
		movaps	xmm4, xmm3
		pshufd	xmm5, xmm2, 2
		subss	xmm3, xmm5
		addss	xmm4, xmm5
		unpcklps	xmm3, xmm6
		pshufd	xmm0, xmm1, 2
		movaps	xmm6, xmm0
		pshufd	xmm5, xmm2, 1
		subss	xmm0, xmm5
		addss	xmm6, xmm5
		unpcklps	xmm4, xmm0
		unpcklpd	xmm4, xmm3
		movups	[ecx+4], xmm4
		pshufd	xmm3, xmm1, 1
		movaps	xmm4, xmm3
		subss	xmm3, xmm2
		addss	xmm4, xmm2
		unpcklps	xmm4, xmm6
		unpcklps	xmm3, xmm7
		unpcklpd	xmm4, xmm3
		movups	[ecx+0x14], xmm4
		mov		eax, ecx
		retn
	}
}

__declspec(naked) void __fastcall NiMatrix33::operator=(const hkMatrix3x4 &inMatrix)
{
	__asm
	{
		movaps	xmm0, [edx]
		movups	[ecx], xmm0
		movaps	xmm0, [edx+0x10]
		movups	[ecx+0xC], xmm0
		movaps	xmm0, [edx+0x20]
		pshufd	xmm1, xmm0, 2
		movq	qword ptr [ecx+0x18], xmm0
		movss	[ecx+0x20], xmm1
		retn
	}
}

__declspec(naked) NiMatrix33& __fastcall NiMatrix33::MultiplyMatrices(const NiMatrix33 &matB)
{
	__asm
	{
		movaps	xmm3, PS_XYZ0Mask
		movups	xmm0, [edx]
		andps	xmm0, xmm3
		movups	xmm1, [edx+0xC]
		andps	xmm1, xmm3
		movups	xmm2, [edx+0x18]
		andps	xmm2, xmm3
		movups	xmm3, [ecx]
		movups	xmm4, [ecx+0x10]
		pshufd	xmm5, xmm3, 0
		mulps	xmm5, xmm0
		pshufd	xmm6, xmm3, 0x15
		mulps	xmm6, xmm1
		addps	xmm5, xmm6
		pshufd	xmm6, xmm3, 0x2A
		mulps	xmm6, xmm2
		addps	xmm5, xmm6
		movups	[ecx], xmm5
		pshufd	xmm5, xmm3, 0x3F
		mulps	xmm5, xmm0
		pshufd	xmm6, xmm4, 0
		mulps	xmm6, xmm1
		addps	xmm5, xmm6
		pshufd	xmm6, xmm4, 0x15
		mulps	xmm6, xmm2
		addps	xmm5, xmm6
		movups	[ecx+0xC], xmm5
		pshufd	xmm5, xmm4, 0x2A
		mulps	xmm5, xmm0
		pshufd	xmm6, xmm4, 0x3F
		mulps	xmm6, xmm1
		addps	xmm5, xmm6
		movss	xmm3, [ecx+0x20]
		shufps	xmm3, xmm3, 0x40
		mulps	xmm3, xmm2
		addps	xmm5, xmm3
		movq	qword ptr [ecx+0x18], xmm5
		pshufd	xmm6, xmm5, 2
		movss	[ecx+0x20], xmm6
		mov		eax, ecx
		retn
	}
}

__declspec(naked) NiMatrix33& __vectorcall NiMatrix33::Rotate(__m128 rot)
{
	__asm
	{
		sub		esp, 0x24
		push	ecx
		lea		ecx, [esp+4]
		call	NiMatrix33::FromEulerPRYInv
		mov		edx, eax
		pop		ecx
		call	NiMatrix33::MultiplyMatrices
		add		esp, 0x24
		retn
	}
}

__declspec(naked) NiMatrix33& NiMatrix33::Transpose()
{
	__asm
	{
		movups	xmm0, [ecx]
		movups	xmm1, [ecx+0x10]
		pshufd	xmm2, xmm0, 9
		shufps	xmm2, xmm1, 0x94
		shufps	xmm0, xmm2, 0x3C
		shufps	xmm1, xmm2, 0x9C
		movups	[ecx], xmm0
		movups	[ecx+0x10], xmm1
		mov		eax, ecx
		retn
	}
}

void NiMatrix33::Dump() const
{
	PrintDebug("%.6f\t%.6f\t%.6f\n%.6f\t%.6f\t%.6f\n%.6f\t%.6f\t%.6f\n", cr[0][0], cr[1][0], cr[2][0], cr[0][1], cr[1][1], cr[2][1], cr[0][2], cr[1][2], cr[2][2]);
}

__declspec(naked) NiQuaternion& __fastcall NiQuaternion::FromRotationMatrix(const NiMatrix33 &rotMat)
{
	__asm
	{
		movups	xmm1, [edx]
		movups	xmm0, [edx+0x10]
		movss	xmm2, [edx+0x20]
		movaps	xmm3, xmm1
		addss	xmm3, xmm0
		addss	xmm3, xmm2
		xorps	xmm4, xmm4
		comiss	xmm3, xmm4
		jbe		t_xyz
		addss	xmm3, PS_V3_One
		movaps	xmm2, xmm0
		unpckhpd	xmm2, xmm1
		unpcklps	xmm1, xmm0
		unpckhpd	xmm1, xmm0
		shufps	xmm1, xmm1, 0x4E
		pshufd	xmm0, xmm1, 0x8C
		subps	xmm0, xmm2
		movaps	xmm2, xmm0
		unpcklps	xmm0, xmm3
		shufps	xmm0, xmm2, 0xE9
		jmp		done
	t_xyz:
		movss	xmm3, PS_V3_One
		pshufd	xmm4, PS_FlipSignMask0, 0x51
		comiss	xmm1, xmm0
		ja		t_xz
		comiss	xmm0, xmm2
		jbe		t_z
		subss	xmm3, xmm1
		addss	xmm3, xmm0
		subss	xmm3, xmm2
		movaps	xmm2, xmm1
		unpckhps	xmm2, xmm0
		shufps	xmm2, xmm2, 0xE0
		unpcklps	xmm1, xmm0
		shufps	xmm0, xmm1, 0xEA
		xorps	xmm2, xmm4
		addps	xmm0, xmm2
		shufps	xmm3, xmm0, 0x30
		shufps	xmm0, xmm3, 0x89
		jmp		done
	t_xz:
		comiss	xmm1, xmm2
		jbe		t_z
		addss	xmm3, xmm1
		subss	xmm3, xmm0
		subss	xmm3, xmm2
		movaps	xmm2, xmm1
		unpcklps	xmm2, xmm0
		unpckhpd	xmm2, xmm1
		shufps	xmm2, xmm2, 0x86
		unpckhpd	xmm0, xmm1
		shufps	xmm0, xmm0, 0x36
		xorps	xmm0, xmm4
		addps	xmm0, xmm2
		movaps	xmm2, xmm0
		unpcklps	xmm0, xmm3
		shufps	xmm0, xmm2, 0xE6
		jmp		done
	t_z:
		subss	xmm3, xmm1
		subss	xmm3, xmm0
		addss	xmm3, xmm2
		movaps	xmm2, xmm1
		unpcklps	xmm2, xmm0
		unpckhpd	xmm2, xmm1
		shufps	xmm2, xmm2, 0x62
		unpckhpd	xmm0, xmm1
		shufps	xmm0, xmm0, 0x4E
		xorps	xmm0, xmm4
		addps	xmm0, xmm2
		shufps	xmm3, xmm0, 0x30
		shufps	xmm0, xmm3, 0x29
	done:
		andps	xmm3, PS_AbsMask0
		rsqrtss	xmm1, xmm3
		mulss	xmm3, xmm1
		mulss	xmm3, xmm1
		movss	xmm2, SS_3
		subss	xmm2, xmm3
		mulss	xmm2, xmm1
		mulss	xmm2, SS_1d4
		shufps	xmm2, xmm2, 0
		mulps	xmm0, xmm2
		movups	[ecx], xmm0
		mov		eax, ecx
		retn
	}
}

__declspec(naked) NiQuaternion& __vectorcall NiQuaternion::FromEulerPRY(__m128 pry)
{
	__asm
	{
		movaps	xmm1, PS_V3_PI
		cmpltps	xmm1, xmm0
		andps	xmm1, PS_V3_PIx2
		subps	xmm0, xmm1
		mulps	xmm0, PS_V3_Half
		call	GetSinCos_V3
		movaps	xmm2, xmm0
		unpcklpd	xmm2, xmm1
		shufps	xmm2, xmm2, 0xD7
		movaps	xmm3, xmm1
		unpckhpd	xmm3, xmm0
		shufps	xmm3, xmm3, 0x88
		movaps	xmm4, xmm1
		unpcklpd	xmm4, xmm0
		pshufd	xmm0, xmm4, 0xA2
		shufps	xmm4, xmm4, 8
		movaps	xmm5, xmm3
		mulps	xmm5, xmm2
		pshufd	xmm3, xmm5, 0xE0
		mulps	xmm3, xmm4
		pshufd	xmm6, xmm5, 0xB5
		mulps	xmm0, xmm6
		xorps	xmm0, PD_FlipSignMask
		addps	xmm0, xmm3
		movups	[ecx], xmm0
		mov		eax, ecx
		retn
	}
}

__declspec(naked) NiQuaternion& __fastcall NiQuaternion::FromAxisAngle(const AxisAngle &axisAngle)
{
	__asm
	{
		movss	xmm0, [edx+0xC]
		mulss	xmm0, PS_V3_Half
		movups	xmm5, [edx]
		call	GetSinCos
		shufps	xmm0, xmm0, 2
		shufps	xmm5, xmm5, 0x90
		mulps	xmm0, xmm5
		movaps	xmm2, xmm0
		shufps	xmm0, xmm1, 1
		shufps	xmm0, xmm2, 0xE2
		movups	[ecx], xmm0
		mov		eax, ecx
		retn
	}
}

void NiQuaternion::operator=(const hkQuaternion &hkQt)
{
	__m128 m = _mm_load_ps(&hkQt.x);
	*this = _mm_shuffle_ps(m, m, 0x93);
}

__declspec(naked) NiQuaternion& __fastcall NiQuaternion::MultiplyQuaternion(const NiQuaternion &rhs)
{
	__asm
	{
		movups	xmm1, [ecx]
		movups	xmm2, [edx]
		xorps	xmm6, xmm6
		movaps	xmm3, xmm1
		mulps	xmm3, xmm2
		pshufd	xmm5, PS_FlipSignMask0, 1
		xorps	xmm3, xmm5
		haddps	xmm3, xmm6
		haddps	xmm3, xmm6
		movaps	xmm0, xmm3
		pshufd	xmm3, xmm1, 0xB1
		mulps	xmm3, xmm2
		pslldq	xmm5, 8
		xorps	xmm3, xmm5
		haddps	xmm3, xmm6
		haddps	xmm3, xmm6
		unpcklps	xmm0, xmm3
		pshufd	xmm3, xmm1, 0x4E
		mulps	xmm3, xmm2
		psrldq	xmm5, 8
		xorps	xmm3, xmm5
		haddps	xmm3, xmm6
		haddps	xmm3, xmm6
		movaps	xmm4, xmm3
		pshufd	xmm3, xmm1, 0x1B
		mulps	xmm3, xmm2
		pslldq	xmm5, 4
		xorps	xmm3, xmm5
		haddps	xmm3, xmm6
		haddps	xmm3, xmm6
		unpcklps	xmm4, xmm3
		unpcklpd	xmm0, xmm4
		movups	[ecx], xmm0
		mov		eax, ecx
		retn
	}
}

__declspec(naked) __m128 __vectorcall NiQuaternion::ToEulerPRY() const
{
	__asm
	{
		movups	xmm6, [ecx]
		pshufd	xmm0, xmm6, 0x98
		pshufd	xmm1, xmm6, 0x9D
		mulps	xmm0, xmm1
		haddps	xmm0, xmm0
		addps	xmm0, xmm0
		pshufd	xmm1, xmm0, 1
		xorps	xmm1, PS_FlipSignMask0
		addss	xmm1, PS_V3_One
		call	ATan2
		movaps	xmm7, xmm0
		pshufd	xmm0, xmm6, 0xC
		pshufd	xmm1, xmm6, 6
		mulps	xmm0, xmm1
		hsubps	xmm0, xmm0
		addss	xmm0, xmm0
		call	ASin
		unpcklps	xmm7, xmm0
		pshufd	xmm0, xmm6, 0xE4
		pshufd	xmm1, xmm6, 0xEB
		mulps	xmm0, xmm1
		haddps	xmm0, xmm0
		addps	xmm0, xmm0
		pshufd	xmm1, xmm0, 1
		xorps	xmm1, PS_FlipSignMask0
		addss	xmm1, PS_V3_One
		call	ATan2
		unpcklpd	xmm7, xmm0
		movaps	xmm0, xmm7
		retn
	}
}

void __vectorcall NiQuaternion::lerp(const NiQuaternion &qb, float t)
{
	if (t <= 0) return;
	if (t >= 1.0F)
	{
		*this = qb;
		return;
	}
	float cosHalfTheta = DotProduct(qb);
	if (cosHalfTheta < 0)
		Negate();
	*this += (qb - *this) * t;
	Normalize();
}

void __vectorcall NiQuaternion::slerp(const NiQuaternion &qb, float t)
{
	if (t <= 0) return;
	if (t >= 1.0F)
	{
		*this = qb;
		return;
	}
	float cosHalfTheta = DotProduct(qb);
	if (abs(cosHalfTheta) >= 1.0F)
		return;
	if (cosHalfTheta < 0)
		Negate();
	float sinHalfTheta = 1.0F - cosHalfTheta * cosHalfTheta;
	if (sinHalfTheta < 0.001F)
	{
		*this += (qb - *this) * t;
		Normalize();
	}
	else
	{
		float halfTheta = ACos(cosHalfTheta);
		*this *= Cos(FltPId2 + t * halfTheta - halfTheta);
		*this += qb * Cos(FltPId2 - t * halfTheta);
		*this *= 1.0F / sqrtf(sinHalfTheta);
	}
}

void NiQuaternion::Dump() const
{
	PrintDebug("%.6f\t%.6f\t%.6f\t%.6f\n", x, y, z, w);
}

void NiTransform::Dump() const
{
	NiVector4 angles = rotate.ToEulerPRY();
	angles *= GET_PS(9);
	PrintDebug("T (%.4f, %.4f, %.4f) R (%.4f, %.4f, %.4f) S %.4f", translate.x, translate.y, translate.z, angles.x, angles.y, angles.z, scale);
}

__declspec(naked) void __vectorcall NiViewport::SetFOV(float fov)
{
	__asm
	{
		call	Tan
		mulss	xmm0, kFlt2d3
		movsldup	xmm0, xmm0
		xorps	xmm0, PS_FlipSignMask0
		shufps	xmm0, xmm0, 0x14
		movups	[ecx], xmm0
		retn
		ALIGN 16
	kFlt2d3:
		EMIT_DW(3F,2A,AA,AB)
	}
}

void NiTriangle::Dump() const
{
	PrintDebug("%d\t%d\t%d\n", point1, point2, point3);
}

__declspec(naked) float __vectorcall Point2Distance(const NiVector3 &pt1, const NiVector3 &pt2)
{
	__asm
	{
		movq	xmm0, qword ptr [ecx]
		movq	xmm1, qword ptr [edx]
		subps	xmm0, xmm1
		mulps	xmm0, xmm0
		haddps	xmm0, xmm0
		sqrtss	xmm0, xmm0
		retn
	}
}

__declspec(naked) float __vectorcall Point3Distance(const NiVector3 &pt1, const NiVector3 &pt2)
{
	__asm
	{
		movaps	xmm2, PS_XYZ0Mask
		movups	xmm0, [ecx]
		andps	xmm0, xmm2
		movups	xmm1, [edx]
		andps	xmm1, xmm2
		subps	xmm0, xmm1
		mulps	xmm0, xmm0
		xorps	xmm1, xmm1
		haddps	xmm0, xmm1
		haddps	xmm0, xmm1
		sqrtss	xmm0, xmm0
		retn
	}
}

__declspec(naked) __m128 __vectorcall TransformWorldToLocal(const NiVector3 &origin, const NiVector3 &target, __m128 rotation)
{
	__asm
	{
		push	ebp
		mov		ebp, esp
		sub		esp, 0x24
		push	ecx
		push	edx
		lea		ecx, [ebp-0x24]
		call	NiMatrix33::FromEulerPRYInv
		pop		edx
		pop		ecx
		movups	xmm4, [edx]
		movups	xmm1, [ecx]
		subps	xmm4, xmm1
		andps	xmm4, PS_XYZ0Mask
		xorps	xmm5, xmm5
		movups	xmm0, [eax]
		mulps	xmm0, xmm4
		haddps	xmm0, xmm5
		haddps	xmm0, xmm5
		movups	xmm1, [eax+0xC]
		mulps	xmm1, xmm4
		haddps	xmm1, xmm5
		haddps	xmm1, xmm5
		movups	xmm2, [eax+0x18]
		mulps	xmm2, xmm4
		haddps	xmm2, xmm5
		haddps	xmm2, xmm5
		movaps	xmm7, xmm0
		unpcklps	xmm7, xmm1
		unpcklpd	xmm7, xmm5
		mulps	xmm7, xmm7
		haddps	xmm7, xmm5
		sqrtss	xmm7, xmm7
		unpcklpd	xmm7, xmm2
		call	ATan2
		movaps	xmm6, xmm0
		pshufd	xmm0, xmm7, 0xFE
		pshufd	xmm1, xmm7, 0xFC
		call	ATan2
		xorps	xmm0, PS_FlipSignMask0
		unpcklpd	xmm0, xmm6
		leave
		retn
	}
}