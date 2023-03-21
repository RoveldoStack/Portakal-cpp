#include "SpriteCameraComponentVisualizer.h"
#include <Libs/ImGui/imgui.h>

namespace Portakal
{
	void SpriteCameraComponentVisualizer::OnInitialize()
	{
		mCamera = (SpriteCamera*)GetComponent();
	}
	void SpriteCameraComponentVisualizer::OnPaint()
	{
		ColorRgbaF clearColor = mCamera->GetClearColor();
		ImGui::ColorPicker4("ClearColor", &clearColor.R);
		mCamera->SetClearColor(clearColor);
	}
	void SpriteCameraComponentVisualizer::OnFinalize()
	{

	}
}