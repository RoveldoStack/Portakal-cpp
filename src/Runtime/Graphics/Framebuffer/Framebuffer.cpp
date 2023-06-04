#include "Framebuffer.h"
#include <Runtime/Graphics/Texture/Texture.h>

namespace Portakal
{
    Framebuffer::Framebuffer(const FramebufferCreateDesc& desc,const bool bSwapchain) : mSwapchain(bSwapchain),mWidth(desc.Width),mHeight(desc.Height)
    {
        /*
        * Create output desc
        */
        OutputDesc outputDesc = {};
        for (unsigned int i = 0; i < desc.ColorTargets.GetCursor(); i++)
        {
            OutputAttachmentDesc attachmentDesc = {};
            attachmentDesc.Format = desc.ColorTargets[i].pTexture->GetTextureFormat();

            outputDesc.ColorAttachments.Add(attachmentDesc);
        }
        outputDesc.DepthStencilAttachment = { desc.DepthStencilTarget.pTexture == nullptr ? TextureFormat::None : desc.DepthStencilTarget.pTexture->GetTextureFormat() };

        mOutputDesc = outputDesc;

        mColorTargets = desc.ColorTargets;
        mDepthStencilTarget = desc.DepthStencilTarget;
    }

    void Framebuffer::OnDestroy()
    {

    }

}