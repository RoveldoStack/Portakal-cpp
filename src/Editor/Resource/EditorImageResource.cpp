#include "EditorImageResource.h"
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/Resource/Texture/TextureResource.h>
#include <Editor/Renderer/ImGuiAPI.h>
#include <Editor/Renderer/ImGuiRenderer.h>
namespace Portakal
{
    EditorImageResource::EditorImageResource(const String& path, const String& name) : EditorResource(path,name,EditorResourceType::Image)
    {
        mResource = new TextureResource(path);
        mResource->SetTagName(name);
        mBinding = ImGuiAPI::GetDefaultRenderer()->GetOrCreateTextureBinding(mResource);
    }
    EditorImageResource::~EditorImageResource()
    {
        if (mResource != nullptr)
            mResource->Destroy();
        if (mBinding != nullptr)
            ImGuiAPI::GetDefaultRenderer()->DeleteTextureBinding(mResource);

        mBinding = nullptr;
        mResource = nullptr;
    }
}