#include "SceneModule.h"
#include <Runtime/World/SceneAPI.h>

namespace Portakal
{
    void SceneModule::OnInitialize()
    {
        mAPI = new SceneAPI();
    }
    void SceneModule::OnFinalize()
    {
        delete mAPI;
    }
    void SceneModule::OnPreTick()
    {

    }
    void SceneModule::OnTick()
    {

    }
    void SceneModule::OnPostTick()
    {

    }
    void SceneModule::PreValidate()
    {

    }
    void SceneModule::PostValidate()
    {

    }
    void SceneModule::OnEvent(WindowEvent* pEvent)
    {

    }
}