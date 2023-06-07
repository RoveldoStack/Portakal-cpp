#include "SpriteCameraComponentVisualizer.h"
#include <Libs/ImGui/imgui.h>
#include <Editor/Renderer/GUICommands.h>

namespace Portakal
{

	void SpriteCameraComponentVisualizer::OnInitialize()
	{

	}

	void SpriteCameraComponentVisualizer::OnPaint()
	{
		SpriteCameraComponent* pCamera = (SpriteCameraComponent*)GetComponent();
		if (pCamera == nullptr || pCamera->IsDestroyed())
			return;

		/*
		* Camera position
		*/
		const Vector2F formerPosition = pCamera->GetPosition();
		Vector2F currentPosition = formerPosition;
		ImGui::InputFloat2("##pos2", &currentPosition.X);

		if (currentPosition != formerPosition)
			pCamera->SetPosition(currentPosition);

		/*
		* Camera rotation
		*/
		const float formerRotation = pCamera->GetRotation();
		float currentRotation = formerRotation;
		ImGui::InputFloat("##rotZ", &currentRotation);

		if (currentRotation != formerRotation)
			pCamera->SetRotation(currentRotation);

		/*
		* Camera clear color
		*/
		const Color4 formerClearColor = pCamera->GetClearColor();
		Color4 currentClearColor = formerClearColor;
		//ImGui::ColorPicker4("##clearColor", &currentClearColor.R);
		/*if (currentClearColor != formerClearColor)
			pCamera->SetClearColor(currentClearColor);*/

		/*
		* Camera orth
		*/
		const float formerOrtho = pCamera->GetOrthoSize();
		float currentOrtho = formerOrtho;
		ImGui::InputFloat("##ortho", &currentOrtho);
		if (currentOrtho != formerOrtho)
			pCamera->SetOrthoSize(currentOrtho);
	}
	void SpriteCameraComponentVisualizer::OnFinalize()
	{

	}
}