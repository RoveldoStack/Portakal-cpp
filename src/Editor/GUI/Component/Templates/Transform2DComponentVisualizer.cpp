#include "Transform2DComponentVisualizer.h"
#include <Libs/ImGui/imgui.h>
#include <Editor/Renderer/GUICommands.h>

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
        mTransform->SetPosition(GUICommands::Vector2FField("Position", mTransform->GetPosition()));

        /*
        * Draw scale
        */
        mTransform->SetScale(GUICommands::Vector2FField("Scale", mTransform->GetScale()));

        /*
        * Draw rotation
        */
        mTransform->SetRotation(GUICommands::FloatField("RotationZ", mTransform->GetRotation()));
    }
}