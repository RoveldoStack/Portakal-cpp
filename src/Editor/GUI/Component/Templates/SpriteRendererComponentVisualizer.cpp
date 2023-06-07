#include "SpriteRendererComponentVisualizer.h"
#include <Libs/ImGui/imgui.h>
#include <Editor/Renderer/GUICommands.h>

namespace Portakal
{
	void SpriteRendererComponentVisualizer::OnInitialize()
	{
	}
	void SpriteRendererComponentVisualizer::OnPaint()
	{
		/*
		* Get and validate component
		*/
		SpriteRendererComponent* pComponent = (SpriteRendererComponent*)GetComponent();
		if (pComponent == nullptr || pComponent->IsDestroyed())
			return;

		/*
		* Draw position
		*/
		const Vector2F formerPosition = pComponent->GetPosition();
		Vector2F currentPosition = formerPosition;
		ImGui::InputFloat2("##pos",&currentPosition.X);
		if (currentPosition != formerPosition)
			pComponent->SetPosition(currentPosition);

		/*
		* Draw scale
		*/
		const Vector2F formerScale = pComponent->GetScale();
		Vector2F currentScale = formerScale;
		ImGui::InputFloat2("##scale", &currentScale.X);
		if (currentScale != formerScale)
			pComponent->SetScale(currentScale);

		/*
		* Draw rotation z
		*/
		const float formerRotation = pComponent->GetRotation();
		float currentRotation = formerRotation;
		ImGui::InputFloat("##rotation", &currentRotation);
		if (currentRotation != formerRotation)
			pComponent->SetRotation(currentRotation);
	}
	void SpriteRendererComponentVisualizer::OnFinalize()
	{
	}
}