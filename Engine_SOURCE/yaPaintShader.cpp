﻿#include "yaPaintShader.h"


namespace md::graphics
{
	PaintShader::PaintShader()
		: ComputeShader()
		, mTarget(nullptr)
	{
	}

	PaintShader::~PaintShader()
	{
	}

	void PaintShader::Binds()
	{
		mTarget->BindUnorderedAccessView(0);

		mGroupX = (static_cast<UINT>(mTarget->GetWidth()) / mThreadGroupCountX) + 1;
		mGroupY = (static_cast<UINT>(mTarget->GetHeight()) / mThreadGroupCountY) + 1;
		mGroupZ = 1;
	}

	void PaintShader::Clear()
	{
		mTarget->ClearUnorderedAccessView(0);
	}

}
