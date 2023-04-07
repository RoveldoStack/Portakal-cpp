#pragma once
#include <Editor/Asset/CustomAssetVisualizerAttribute.h>
#include <Editor/Asset/IAssetVisualizer.h>

namespace Portakal
{
	CLASS_ATTRIBUTE(CustomAssetVisualizerAttribute, "texture");
	class PORTAKAL_API TextureAssetVisualizer : public IAssetVisualizer
	{
		GENERATE_CLASS(TextureAssetVisualizer);
	public:
		TextureAssetVisualizer() = default;
		~TextureAssetVisualizer() = default;

		virtual TextureResource* OnPaint(DomainFile* pFile) override;
	};

	/*START_GENERATE_TYPE(TextureAssetVisualizer);
	START_TYPE_PROPERTIES(TextureAssetVisualizer);
	REGISTER_BASE_TYPE(IAssetVisualizer);
	REGISTER_TYPE_ATTRIBUTE(CustomAssetVisualizerAttribute, "texture");
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(TextureAssetVisualizer);
	END_GENERATE_TYPE(TextureAssetVisualizer);*/
#include "TextureAssetVisualizer.reflect.h"

}