#include "AuthoringToolWindow.h"
#include <Editor/Domain/DomainFile.h>
#include <Editor/Asset/IAssetAuthoringTool.h>
#include <Libs/ImGui/imgui.h>

namespace Portakal
{
    void AuthoringToolWindow::SetToolData(DomainFile* pTargetFile)
    {
        mTargetFile = pTargetFile;
        mAuthoringTool = pTargetFile->GetAuthoringTool();

        if (mAuthoringTool == nullptr)
            return;

        mAuthoringTool->OnInitialize();
    }
    void AuthoringToolWindow::OnShow()
    {

    }
    void AuthoringToolWindow::OnHide()
    {

    }
    void AuthoringToolWindow::OnInitialize()
    {

    }
    void AuthoringToolWindow::OnFinalize()
    {
        if (mAuthoringTool == nullptr)
            return;

        mAuthoringTool->OnFinalize();
    }
    void AuthoringToolWindow::OnPaint()
    {
        if (mAuthoringTool == nullptr)
        {
            ImGui::Text("There is no authorization tool implementation!");
            return;
        }

        mAuthoringTool->OnPaint(mTargetFile);
    }
}