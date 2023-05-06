#include "EditorResourceModule.h"
#include <Runtime/Platform/PlatformFile.h>
#include <Runtime/Message/MessageAPI.h>
#include <Editor/Resource/EditorImageResource.h>
#include <Editor/Resource/EditorResourceAPI.h>
#include <Runtime/Platform/PlatformPaths.h>
namespace Portakal
{
    EditorResourceModule::EditorResourceModule(const Array<EditorResourceRequest>& requests) : mParams({requests})
    {
       
    }
    void EditorResourceModule::OnInitialize()
    {
        const String imageResourcesFolder = PlatformPaths::GetApplicationLoadPath() + "\\Portakal\\Editor\\Resources\\";

        Array<EditorResource*> loadedResources;
        for (unsigned int i = 0; i < mParams.Requests.GetCursor(); i++)
        {
            const EditorResourceRequest request = mParams.Requests[i];

            /*
            * Validate file
            */
            const String path = imageResourcesFolder + request.Name;
            if (!PlatformFile::IsExist(path))
            {
                MessageAPI::BroadcastMessage("Failed to load editor resource request");
                continue;
            }

            /*
            * Load resource
            */
            EditorResource* pResource = nullptr;

            switch (request.Type)
            {
            case Portakal::EditorResourceType::Image:
            {
                pResource = new EditorImageResource(path, request.Name);
                break;
            }
            case Portakal::EditorResourceType::Font:
                break;
            case Portakal::EditorResourceType::Audio:
                break;
            default:
                break;
            }

            /*
            * Validate if resource loaded
            */
            if (pResource == nullptr)
            {
                MessageAPI::BroadcastMessage("Failed to create the requested resource");
                continue;
            }

            /*
            * Register
            */
            loadedResources.Add(pResource);
        }

        /*
        * Create api
        */
        mAPI = new EditorResourceAPI(loadedResources);
    }
    void EditorResourceModule::OnFinalize()
    {
        delete mAPI;
        mAPI = nullptr;

        EditorResourceAPI::ClearResources();
    }
    void EditorResourceModule::OnPreTick()
    {
    }
    void EditorResourceModule::OnTick()
    {
    }
    void EditorResourceModule::OnPostTick()
    {
    }
    void EditorResourceModule::PreValidate()
    {
    }
    void EditorResourceModule::PostValidate()
    {
    }
    void EditorResourceModule::OnEvent(WindowEvent* pEvent)
    {
    }
}