#include "AuthorizationToolWindow.h"
#include <Editor/Domain/DomainFile.h>
#include <Editor/Asset/IAssetAuthorizationTool.h>
#include <Libs/ImGui/imgui.h>

namespace Portakal
{
    void AuthorizationToolWindow::SetToolData(DomainFile* pTargetFile)
    {
        mTargetFile = pTargetFile;
        mAuthorizationTool = pTargetFile->GetAuthorizationTool();

        if (mAuthorizationTool == nullptr)
            return;

        mAuthorizationTool->OnInitialize();
    }
    void AuthorizationToolWindow::OnShow()
    {

    }
    void AuthorizationToolWindow::OnHide()
    {

    }
    void AuthorizationToolWindow::OnInitialize()
    {

    }
    void AuthorizationToolWindow::OnFinalize()
    {
        if (mAuthorizationTool == nullptr)
            return;

        mAuthorizationTool->OnFinalize();
    }
    void AuthorizationToolWindow::OnPaint()
    {
        if (mAuthorizationTool == nullptr)
        {
            ImGui::Text("There is no authorization tool implementation!");
            return;
        }

        mAuthorizationTool->OnPaint(mTargetFile);
    }
}