#include "SpriteCameraComponentVisualizer.h"
#include <Libs/ImGui/imgui.h>
#include <Runtime/Input/InputAPI.h>
#include <Runtime/Input/Gamepad.h>

namespace Portakal
{
	int right = 0;
	int left = 0;
	void SpriteCameraComponentVisualizer::OnInitialize()
	{
		mCamera = (SpriteCamera*)GetComponent();
	}
	void SpriteCameraComponentVisualizer::OnPaint()
	{
		Gamepad* pGamepad = InputAPI::GetDefaultGamepad();

		if (pGamepad == nullptr)
			return;

		ImGui::InputInt("Right",&right,1);
		ImGui::InputInt("Left", &left, 1);
		
		pGamepad->SetVibration(right, left);

	}
	void SpriteCameraComponentVisualizer::OnFinalize()
	{

	}
}