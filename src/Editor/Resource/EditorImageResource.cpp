#include "EditorImageResource.h"
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/Resource/Texture/TextureResource.h>

namespace Portakal
{
    EditorImageResource::EditorImageResource(const String& path, const String& name) : EditorResource(path,name,EditorResourceType::Image)
    {
        mResource = new TextureResource(path);
    }
    EditorImageResource::~EditorImageResource()
    {
        if (mResource != nullptr)
            mResource->Destroy();

        mResource = nullptr;
    }
}