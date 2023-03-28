#include "DX11ImGuiTextureBinding.h"
#include <Runtime/DX11/DX11ResourceTable.h>
namespace Portakal
{
    DX11ImGuiTextureBinding::DX11ImGuiTextureBinding(const TextureResource* pResource) : ImGuiTextureBinding(pResource)
    {
    }
    DX11ImGuiTextureBinding::~DX11ImGuiTextureBinding()
    {
    }
    void* DX11ImGuiTextureBinding::GetBinding() const noexcept
    {
        DX11ResourceTable* pTable = (DX11ResourceTable*)GetTable();


        return pTable->GetHandle();
    }
}