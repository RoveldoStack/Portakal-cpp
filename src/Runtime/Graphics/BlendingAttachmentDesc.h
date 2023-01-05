#pragma once
#include <Runtime/Graphics/BlendFactor.h>
#include <Runtime/Graphics/BlendFunction.h>


namespace Portakal
{
	struct PORTAKAL_API BlendingAttachmentDesc
	{
		bool bEnabled;
		BlendFactor SourceColorFactor;
		BlendFactor DestinationColorFactor;
		BlendFunction ColorFunction;
		BlendFactor SourceAlphaFactor;
		BlendFactor DestinationAlphaFactor;
		BlendFunction AlphaFunction;
	};
}