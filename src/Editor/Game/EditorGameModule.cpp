#include "EditorGameModule.h"
#include <Editor/Game/EditorGameAPI.h>

namespace Portakal
{
    void EditorGameModule::OnInitialize()
    {
        mAPI = new EditorGameAPI();
    }
    void EditorGameModule::OnFinalize()
    {
        delete mAPI;
        mAPI = nullptr;
    }
    void EditorGameModule::OnPreTick()
    {

    }
    void EditorGameModule::OnTick()
    {
    }
    void EditorGameModule::OnPostTick()
    {
    }
    void EditorGameModule::PreValidate()
    {
    }
    void EditorGameModule::PostValidate()
    {
    }
    void EditorGameModule::OnEvent(WindowEvent* pEvent)
    {
    }
}