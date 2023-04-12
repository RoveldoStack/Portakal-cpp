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
		SharedSafeHeap<Gamepad> pGamepad = InputAPI::GetDefaultGamepad();

		if (pGamepad == nullptr)
			return;
		if (pGamepad->IsDestroyed())
			return;

		Vector2F rightThumb = pGamepad->GetRightThumb();
		Vector2F leftThumb = pGamepad->GetLeftThumb();

		ImGui::InputFloat2("Right thumb", &rightThumb.X,"%.3f", ImGuiInputTextFlags_ReadOnly);
		ImGui::InputFloat2("Left thumb", &leftThumb.X, "%.3f", ImGuiInputTextFlags_ReadOnly);

	}
	void SpriteCameraComponentVisualizer::OnFinalize()
	{

	}
}