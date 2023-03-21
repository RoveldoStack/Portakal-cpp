#pragma once
#include <Runtime/World/Components/SpriteCamera.h>
#include <Editor/GUI/Component/EditorComponentVisualizer.h>
#include <Editor/GUI/Component/CustomEditorComponentAttribute.h>

namespace Portakal
{
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

	START_GENERATE_TYPE(SpriteCameraComponentVisualizer);
	START_TYPE_PROPERTIES(SpriteCameraComponentVisualizer);
	REGISTER_BASE_TYPE(EditorComponentVisualizer);
	REGISTER_TYPE_ATTRIBUTE(CustomEditorComponentAttribute, typeof(SpriteCamera));
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(SpriteCameraComponentVisualizer);
	END_GENERATE_TYPE(SpriteCameraComponentVisualizer);
}