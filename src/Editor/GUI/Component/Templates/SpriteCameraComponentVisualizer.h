#pragma once
#include <Runtime/World/Components/SpriteCamera.h>
#include <Editor/GUI/Component/EditorComponentVisualizer.h>
#include <Editor/GUI/Component/CustomEditorComponentAttribute.h>

namespace Portakal
{
	CLASS_ATTRIBUTE(CustomEditorComponentAttribute, typeof(SpriteCamera));
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
		SpriteCamera* mCamera;
	};


#include "SpriteCameraComponentVisualizer.reflect.h"
}