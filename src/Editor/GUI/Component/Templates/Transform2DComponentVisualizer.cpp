#include "Transform2DComponentVisualizer.h"
#include <Libs/ImGui/imgui.h>

namespace Portakal
{
    void Transform2DComponentVisualizer::OnInitialize()
    {
        mTransform = (Transform2DComponent*)GetComponent();
    }
    void Transform2DComponentVisualizer::OnFinalize()
    {
        mTransform = nullptr;
    }
    void Transform2DComponentVisualizer::OnPaint()
    {
        /*
        * Draw position
        */
        Vector2F position = mTransform->GetPosition();
        ImGui::InputFloat2("Position", &position.X);
        mTransform->SetPosition(position);

        /*
        * Draw scale
        */
        Vector2F scale = mTransform->GetScale();
        ImGui::InputFloat2("Scale", &scale.X);
        mTransform->SetScale(scale);

        /*
        * Draw rotation
        */
        float rotation = mTransform->GetRotation();
        ImGui::InputFloat("RotationZ", &rotation);
        mTransform->SetRotation(rotation);
    }
}