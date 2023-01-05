#pragma once
#include <Runtime/Graphics/ShaderStage.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/GraphicsResourceTableEntry.h>

namespace Portakal
{
	struct PORTAKAL_API GraphicsResourceTableLayoutDesc
	{
		ShaderStage Stage;
		Array<GraphicsResourceTableEntry> Slots;
	};
}