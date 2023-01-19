#include "TestWindow.h"
#include <Libs/ImGui/imgui.h>

namespace Portakal
{
    void TestWindow::OnShow()
    {
    }
    void TestWindow::OnHide()
    {
    }
    void TestWindow::OnInitialize()
    {
    }
    void TestWindow::OnFinalize()
    {
    }
    void TestWindow::OnPaint()
    {
        ImGui::Text("Test text");
    }
}