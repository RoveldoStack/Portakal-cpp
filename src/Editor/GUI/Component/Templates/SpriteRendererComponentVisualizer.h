#pragma once
#include <Runtime/Renderers/2DRenderer/SpriteRendererComponent.h>
#include <Editor/GUI/Component/EditorComponentVisualizer.h>
#include <Editor/GUI/Component/CustomEditorComponentAttribute.h>


namespace Portakal
{
	PCLASS_ATTRIBUTE(CustomEditorComponentAttribute, typeof(SpriteRendererComponent));
	PCLASS();
	class PORTAKAL_API SpriteRendererComponentVisualizer : public EditorComponentVisualizer
	{
		GENERATE_CLASS(SpriteRendererComponentVisualizer);
	public:
		SpriteRendererComponentVisualizer() = default;
		~SpriteRendererComponentVisualizer() = default;

	private:


		// Inherited via EditorComponentVisualizer
		virtual void OnInitialize() override;

		virtual void OnPaint() override;

		virtual void OnFinalize() override;

	};

#include "SpriteRendererComponentVisualizer.reflect.h"
}