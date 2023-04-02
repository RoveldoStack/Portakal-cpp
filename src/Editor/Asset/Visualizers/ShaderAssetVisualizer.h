#pragma once
#include <Editor/Asset/IAssetVisualizer.h>
#include <Editor/Asset/CustomAssetVisualizerAttribute.h>

namespace Portakal
{
	class PORTAKAL_API ShaderAssetVisualizer : public IAssetVisualizer
	{
		GENERATE_CLASS(ShaderAssetVisualizer);
	public:
		// Inherited via IAssetVisualizer
		virtual TextureResource* OnPaint(DomainFile* pFile) override;
	};

	START_GENERATE_TYPE(ShaderAssetVisualizer);
	START_TYPE_PROPERTIES(ShaderAssetVisualizer);
	REGISTER_BASE_TYPE(IAssetVisualizer);
	REGISTER_TYPE_ATTRIBUTE(CustomAssetVisualizerAttribute, "shader");
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(ShaderAssetVisualizer);
	END_GENERATE_TYPE(ShaderAssetVisualizer);
}