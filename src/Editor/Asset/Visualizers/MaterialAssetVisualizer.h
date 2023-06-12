#pragma once
#include <Runtime/Resource/Material/MaterialResource.h>
#include <Editor/Asset/IAssetVisualizer.h>
#include <Editor/Asset/CustomAssetVisualizerAttribute.h>

namespace Portakal
{
	PCLASS_ATTRIBUTE(CustomAssetVisualizerAttribute, "material");
	PCLASS();
	class PORTAKAL_API MaterialAssetVisualizer : public IAssetVisualizer
	{
		GENERATE_CLASS(MaterialAssetVisualizer);
	public:
		MaterialAssetVisualizer() = default;
		~MaterialAssetVisualizer() = default;
	public:

	private:

		// Inherited via IAssetVisualizer
		virtual TextureResource* OnPaint(DomainFile* pFile) override;
	};

#include "MaterialAssetVisualizer.reflect.h"
}