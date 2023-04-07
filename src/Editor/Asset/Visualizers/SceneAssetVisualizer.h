#pragma once
#include <Editor/Asset/IAssetVisualizer.h>
#include <Editor/Asset/CustomAssetVisualizerAttribute.h>

namespace Portakal
{
	CLASS_ATTRIBUTE(CustomAssetVisualizerAttribute, "scene");
	class PORTAKAL_API SceneAssetVisualizer : public IAssetVisualizer
	{
		GENERATE_CLASS(SceneAssetVisualizer);
	public:
		// Inherited via IAssetVisualizer
		virtual TextureResource* OnPaint(DomainFile* pFile) override;
	};


#include "SceneAssetVisualizer.reflect.h"
}