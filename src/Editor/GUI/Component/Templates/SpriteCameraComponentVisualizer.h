#pragma once
#include <Editor/GUI/Component/EditorComponentVisualizer.h>
#include <Editor/GUI/Component/CustomEditorComponentAttribute.h>
#include <Runtime/Renderers/2DRenderer/SpriteCameraComponent.h>


namespace Portakal
{
	PCLASS_ATTRIBUTE(CustomEditorComponentAttribute, typeof(SpriteCameraComponent));
	PCLASS();
	class PORTAKAL_API SpriteCameraComponentVisualizer : public EditorComponentVisualizer
	{
		GENERATE_CLASS(SpriteCameraComponentVisualizer);
	public:
		SpriteCameraComponentVisualizer() = default;
		~SpriteCameraComponentVisualizer() = default;

		// Inherited via EditorComponentVisualizer
		virtual void OnInitialize() override;

		virtual void OnPaint() override;

		virtual void OnFinalize() override;
	private:

	};


#include "SpriteCameraComponentVisualizer.reflect.h"
}