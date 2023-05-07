#pragma once
#include <Editor/GUI/Component/EditorComponentVisualizer.h>
#include <Editor/GUI/Component/CustomEditorComponentAttribute.h>

namespace Portakal
{
	PCLASS();
	class PORTAKAL_API DefaultComponentVisualizer : public EditorComponentVisualizer
	{
		GENERATE_CLASS(DefaultComponentVisualizer);
	public:


		// Inherited via EditorComponentVisualizer
		virtual void OnInitialize() override;

		virtual void OnFinalize() override;


		// Inherited via EditorComponentVisualizer
		virtual void OnPaint() override;
	private:

	};

#include "DefaultComponentVisualizer.reflect.h"
}