#include "SceneModule.h"
#include <Runtime/World/SceneAPI.h>
#include <Runtime/World/SceneAspect.h>
#include <Runtime/World/Scene.h>

namespace Portakal
{
    void SceneModule::OnInitialize()
    {
        mAPI = new SceneAPI();
    }
    void SceneModule::OnFinalize()
    {
        delete mAPI;
        mAPI = nullptr;
    }
    void SceneModule::OnPreTick()
    {

    }
    void SceneModule::OnTick()
    {
        const Array<Scene*> scenes = SceneAPI::GetScenes();
        for (unsigned int sceneIndex = 0; sceneIndex < scenes.GetCursor(); sceneIndex++)
        {
            Scene* pScene = scenes[sceneIndex];
            const Array<SceneAspect*> aspects = pScene->GetAspects();
            for (unsigned int aspectIndex = 0; aspectIndex < aspects.GetCursor(); aspectIndex++)
            {
                SceneAspect* pAspect = aspects[aspectIndex];
                pAspect->Execute();
            }
        }
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