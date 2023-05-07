#pragma once
#include <Editor/Asset/CustomAssetVisualizerAttribute.h>
#include <Editor/Asset/IAssetVisualizer.h>

namespace Portakal
{
	class EditorImageResource;

	PCLASS_ATTRIBUTE(CustomAssetVisualizerAttribute, "simple-text");
	PCLASS();
	class PORTAKAL_API SimpleTextAssetVisualizer : public IAssetVisualizer
	{
		GENERATE_CLASS(SimpleTextAssetVisualizer);
	public:
		SimpleTextAssetVisualizer();
		~SimpleTextAssetVisualizer();
	private:
		EditorImageResource* mResource;

		// Inherited via IAssetVisualizer
		virtual TextureResource* OnPaint(DomainFile* pFile) override;
	};


#include "SimpleTextAssetVisualizer.reflect.h"
}