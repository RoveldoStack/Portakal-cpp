#include "SpriteCameraComponentVisualizer.h"
#include <Libs/ImGui/imgui.h>
#include <Editor/Renderer/GUICommands.h>
namespace Portakal
{

	void SpriteCameraComponentVisualizer::OnInitialize()
	{
		mCamera = (SpriteCamera*)GetComponent();
	}

	void SpriteCameraComponentVisualizer::OnPaint()
	{
		mCamera->SetClearColor(GUICommands::RgbaFField("ClearColor", mCamera->GetClearColor()));
	}
	void SpriteCameraComponentVisualizer::OnFinalize()
	{

	}
}