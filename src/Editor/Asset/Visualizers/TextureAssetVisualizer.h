#pragma once
#include <Editor/Asset/CustomAssetVisualizerAttribute.h>
#include <Editor/Asset/IAssetVisualizer.h>

namespace Portakal
{
	PCLASS_ATTRIBUTE(CustomAssetVisualizerAttribute, "texture");
	PCLASS();
	class PORTAKAL_API TextureAssetVisualizer : public IAssetVisualizer
	{
		GENERATE_CLASS(TextureAssetVisualizer);
	public:
		TextureAssetVisualizer() = default;
		~TextureAssetVisualizer() = default;

		virtual TextureResource* OnPaint(DomainFile* pFile) override;
	};

#include "TextureAssetVisualizer.reflect.h"

}