#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class PORTAKAL_API IAssetVisualizer
	{
	public:
		IAssetVisualizer() = default;
		~IAssetVisualizer() = default;
		
		virtual void OnPaint();
	};
}