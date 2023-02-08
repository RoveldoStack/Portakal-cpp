#pragma once
#include <Editor/Asset/CustomAssetVisualizerAttribute.h>
#include <Editor/Asset/IAssetVisualizer.h>

namespace Portakal
{
	class EditorImageResource;
	class PORTAKAL_API SimpleTextAssetVisualizer : public IAssetVisualizer
	{
		GENERATE_CLASS(SimpleTextAssetVisualizer);
	public:
		SimpleTextAssetVisualizer();
		~SimpleTextAssetVisualizer();
	private:
		EditorImageResource* mResource;

		// Inherited via IAssetVisualizer
		virtual TextureResource* OnPaint(const DomainFile* pFile) override;
	};

	START_GENERATE_TYPE(SimpleTextAssetVisualizer);
	START_TYPE_PROPERTIES(SimpleTextAssetVisualizer);
	REGISTER_BASE_TYPE(IAssetVisualizer);
	REGISTER_TYPE_ATTRIBUTE(CustomAssetVisualizerAttribute, "simple_text");
	END_TYPE_PROPERTIES;
	CONCRETE_TYPE(SimpleTextAssetVisualizer);
	END_GENERATE_TYPE(SimpleTextAssetVisualizer);
}