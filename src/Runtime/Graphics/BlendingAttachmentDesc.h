#pragma once
#include <Runtime/Graphics/BlendFactor.h>
#include <Runtime/Graphics/BlendFunction.h>
#include <Runtime/Graphics/LogicOperation.h>

namespace Portakal
{
	struct PORTAKAL_API BlendingAttachmentDesc
	{
		bool bEnabled;
		bool bEnableLogicOp;
		BlendFactor SourceColorFactor;
		BlendFactor DestinationColorFactor;
		BlendFunction ColorFunction;

		BlendFactor SourceAlphaFactor;
		BlendFactor DestinationAlphaFactor;
		BlendFunction AlphaFunction;

		LogicOperation LogicOp;

		unsigned char WriteMask;
	};
}