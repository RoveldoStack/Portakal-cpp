#pragma once
#include <Runtime/Graphics/StencilFaceDesc.h>

namespace Portakal
{
	struct PORTAKAL_API DepthStencilStateDesc
	{
		bool bDepthTestEnabled;
		bool bDepthWriteEnabled;
		ComparisionMethod DepthComparision;
		bool bStencilTestEnabled;
		StencilFaceDesc StencilFrontFace;
		StencilFaceDesc StencilBackFace;
		unsigned char StencilReadMask;
		unsigned char StencilWriteMask;
		unsigned char StencilReference;
	};
}