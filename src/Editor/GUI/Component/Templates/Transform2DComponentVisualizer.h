#pragma once
#include <Editor/GUI/Component/EditorComponentVisualizer.h>
#include <Runtime/World/Components/Transform2DComponent.h>
#include <Editor/GUI/Component/CustomEditorComponentAttribute.h>

namespace Portakal
{
	class PORTAKAL_API Transform2DComponentVisualizer : public EditorComponentVisualizer
	{
		GENERATE_CLASS(Transform2DComponentVisualizer);
	public:
		Transform2DComponentVisualizer() = default;
		~Transform2DComponentVisualizer() = default;
	private:


		// Inherited via EditorComponentVisualizer
		virtual void OnInitialize() override;

		virtual void OnFinalize() override;


		// Inherited via EditorComponentVisualizer
		virtual void OnPaint() override;
	private:
		Transform2DComponent* mTransform;
	};

	START_GENERATE_TYPE(Transform2DComponentVisualizer);
	START_TYPE_PROPERTIES(Transform2DComponentVisualizer);
	REGISTER_BASE_TYPE(EditorComponentVisualizer);
	REGISTER_TYPE_ATTRIBUTE(CustomEditorComponentAttribute, typeof(Transform2DComponent));
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(Transform2DComponentVisualizer);
	END_GENERATE_TYPE(Transform2DComponentVisualizer);
}