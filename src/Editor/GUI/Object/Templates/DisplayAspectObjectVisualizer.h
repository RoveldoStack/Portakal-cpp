#pragma once
#include <Editor/GUI/Object/EditorObjectVisualizer.h>
#include <Editor/GUI/Object/CustomEditorObjectAttribute.h>
#include <Runtime/World/Aspects/DisplayAspect.h>

namespace Portakal
{
	CLASS_ATTRIBUTE(CustomEditorObjectAttribute, typeof(DisplayAspect));
	class PORTAKAL_API DisplayAspectObjectVisualizer : public EditorObjectVisualizer
	{
		GENERATE_CLASS(DisplayAspectObjectVisualizer);
	public:
		DisplayAspectObjectVisualizer() = default;
		~DisplayAspectObjectVisualizer() = default;

		virtual void OnInitialize() override;
		virtual void OnPaint() override;
		virtual void OnFinalize() override;
	private:
	};

	//START_GENERATE_TYPE(DisplayAspectObjectVisualizer);
	//START_TYPE_PROPERTIES(DisplayAspectObjectVisualizer);
	//REGISTER_BASE_TYPE(EditorObjectVisualizer);
	//REGISTER_TYPE_ATTRIBUTE(CustomEditorObjectAttribute, typeof(DisplayAspect));
	//END_TYPE_PROPERTIES;
	//HAS_DEFAULT_CONSTRUCTOR(DisplayAspectObjectVisualizer);
	//END_GENERATE_TYPE(DisplayAspectObjectVisualizer);

#include "DisplayAspectObjectVisualizer.reflect.h"
}