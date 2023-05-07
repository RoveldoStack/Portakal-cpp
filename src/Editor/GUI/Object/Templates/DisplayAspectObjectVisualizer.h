#pragma once
#include <Editor/GUI/Object/EditorObjectVisualizer.h>
#include <Editor/GUI/Object/CustomEditorObjectAttribute.h>
#include <Runtime/World/Aspects/DisplayAspect.h>

namespace Portakal
{
	PCLASS_ATTRIBUTE(CustomEditorObjectAttribute, typeof(DisplayAspect));
	PCLASS();
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

#include "DisplayAspectObjectVisualizer.reflect.h"
}