#pragma once
#include <Editor/GUI/Component/EditorComponentVisualizer.h>
#include <Editor/GUI/Component/CustomEditorComponentAttribute.h>

namespace Portakal
{
	class PORTAKAL_API DefaultComponentVisualizer : public EditorComponentVisualizer
	{
		GENERATE_CLASS(DefaultComponentVisualizer);
	public:


		// Inherited via EditorComponentVisualizer
		virtual void OnInitialize() override;

		virtual void OnFinalize() override;


		// Inherited via EditorComponentVisualizer
		virtual void OnPaint() override;

	};

	START_GENERATE_TYPE(DefaultComponentVisualizer);
	START_TYPE_PROPERTIES(DefaultComponentVisualizer);
	REGISTER_BASE_TYPE(EditorComponentVisualizer);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(DefaultComponentVisualizer);
	END_GENERATE_TYPE(DefaultComponentVisualizer);
}