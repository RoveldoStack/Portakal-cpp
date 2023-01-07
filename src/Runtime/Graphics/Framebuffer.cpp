#include "Framebuffer.h"
#include <Runtime/Graphics/Texture.h>

namespace Portakal
{
    Framebuffer::Framebuffer(const FramebufferCreateDesc& desc)
    {
        /*
        * Setup color targets,width and height
        */
        for (unsigned int i = 0; i < desc.ColorTargets.GetCursor(); i++)
        {
            _colorTargets.Add(desc.ColorTargets[i].pTexture);
        }
      
        _depthStencilTarget = desc.DepthStencilTarget.pTexture;

        _width = desc.ColorTargets[0].pTexture->GetWidth();
        _height = desc.ColorTargets[0].pTexture->GetHeight();

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

        _outputDesc = outputDesc;
    }
    Framebuffer::Framebuffer(const unsigned int width, const unsigned int height)
    {
        _depthStencilTarget = nullptr;
        _width = width;
        _height = height;
    }
}