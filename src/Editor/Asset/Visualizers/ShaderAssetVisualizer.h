#pragma once
#include <Editor/Asset/IAssetVisualizer.h>
#include <Editor/Asset/CustomAssetVisualizerAttribute.h>

namespace Portakal
{
	PCLASS_ATTRIBUTE(CustomAssetVisualizerAttribute, "shader");
	PCLASS();
	class PORTAKAL_API ShaderAssetVisualizer : public IAssetVisualizer
	{
		GENERATE_CLASS(ShaderAssetVisualizer);
	public:
		virtual TextureResource* OnPaint(DomainFile* pFile) override;


		int abc;
	};

#include "ShaderAssetVisualizer.reflect.h"
}