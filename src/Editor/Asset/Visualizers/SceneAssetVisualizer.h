#pragma once
#include <Editor/Asset/IAssetVisualizer.h>
#include <Editor/Asset/CustomAssetVisualizerAttribute.h>

namespace Portakal
{
	class PORTAKAL_API SceneAssetVisualizer : public IAssetVisualizer
	{
		GENERATE_CLASS(SceneAssetVisualizer);
	public:
		// Inherited via IAssetVisualizer
		virtual TextureResource* OnPaint(DomainFile* pFile) override;
	};

	START_GENERATE_TYPE(SceneAssetVisualizer);
	START_TYPE_PROPERTIES(SceneAssetVisualizer);
	REGISTER_BASE_TYPE(IAssetVisualizer);
	REGISTER_TYPE_ATTRIBUTE(CustomAssetVisualizerAttribute,"scene");
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(SceneAssetVisualizer);
	END_GENERATE_TYPE(SceneAssetVisualizer);
}