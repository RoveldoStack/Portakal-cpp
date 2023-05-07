#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class DomainFile;
	class TextureResource;

	/// <summary>
	/// Asster visualizer interface, it's used to customize the behaviour of the asset icons
	/// </summary>
	PCLASS();
	class PORTAKAL_API IAssetVisualizer : public Class
	{
		GENERATE_CLASS(IAssetVisualizer,Virtual);
	public:
		IAssetVisualizer() = default;
		~IAssetVisualizer() = default;
		
		/// <summary>
		/// Called every frame for painting the icon
		/// </summary>
		/// <param name="pFile"></param>
		/// <returns></returns>
		virtual TextureResource* OnPaint(DomainFile* pFile) = 0;
	};
#include "IAssetVisualizer.reflect.h"
}