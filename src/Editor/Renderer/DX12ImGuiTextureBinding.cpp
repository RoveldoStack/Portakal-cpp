#include "DX12ImGuiTextureBinding.h"
#include <Runtime/DX12/DX12ResourceTable.h>

namespace Portakal
{
    DX12ImGuiTextureBinding::DX12ImGuiTextureBinding(const TextureResource* pTargetTexture) : ImGuiTextureBinding(pTargetTexture)
    {

    }
    DX12ImGuiTextureBinding::~DX12ImGuiTextureBinding()
    {

    }
    void* DX12ImGuiTextureBinding::GetBinding() const noexcept
    {
        return ((DX12ResourceTable*)GetTable())->GetDXCbvSrvUavHeap();
    }
}