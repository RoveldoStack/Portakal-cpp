#include "RenderTarget.h"
#include <Runtime/Graphics/Texture.h>
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/Graphics/Framebuffer.h>
#include <Runtime/Graphics/ResourceTable.h>
#include <Runtime/Assert/Assert.h>

namespace Portakal
{
	RenderTarget::RenderTarget(const unsigned int width, const unsigned int height, const Array<TextureFormat>& colorTargetFormats, const TextureFormat depthStencilFormat, const Array<String>& colorTargetNames)
	{
		mDevice = GraphicsDeviceAPI::GetDefaultDevice();

		ASSERT(colorTargetFormats.GetCursor() == colorTargetNames.GetCursor(),"RenderTarget","Given color target names are not matched with the given format count");

		/*
		* Create resources
		*/
		CreateResources(width, height, colorTargetFormats, depthStencilFormat,colorTargetNames);
	}
	RenderTarget::~RenderTarget()
	{
		mFramebuffer = nullptr;
		mDevice = nullptr;
	}
	unsigned int RenderTarget::GetWidth() const noexcept
	{
		return mWidth;
	}
	unsigned int RenderTarget::GetHeight() const noexcept
	{
		return mHeight;
	}
	void RenderTarget::Resize(const unsigned int width, const unsigned int height)
	{
		/*
		* Create a copy of the former attachment descriptions
		*/
		Array<TextureFormat> colorTargetFormats;
		Array<String> colorTargetNames;
		for (unsigned int i = 0; i < mColorTargets.GetCursor(); i++)
		{
			colorTargetFormats.Add(mColorTargets[i]->GetFormat());
			colorTargetNames.Add(mColorTargets[i]->GetTagName());
		}
		TextureFormat depthStencilFormat = mDepthStencilTarget != nullptr ? mDepthStencilTarget->GetFormat() : TextureFormat::None;

		/*
		* Delete the existing framebuffer
		*/
		Delete();

		/*
		* Create the new attachments and the framebuffer
		*/
		CreateResources(width, height, colorTargetFormats, depthStencilFormat,colorTargetNames);
	}
	void RenderTarget::Delete()
	{
		/*
		* Validate framebuffer
		*/
		if (mFramebuffer == nullptr)
			return;

		/*
		* Delete the framebuffer targets
		*/
		for (unsigned int i = 0; i < mColorTargets.GetCursor(); i++)
		{
			mColorTargets[i]->Destroy();
			delete mColorTargets[i];
		}
		mColorTargets.Clear();

		if (mDepthStencilTarget != nullptr)
		{
			mDepthStencilTarget->Destroy();
			delete mDepthStencilTarget;
			mDepthStencilTarget = nullptr;
		}
	}
	void RenderTarget::CreateResources(const unsigned int width, const unsigned int height, const Array<TextureFormat>& colorTargetFormats, const TextureFormat depthStencilFormat, const Array<String>& colorTargetNames)
	{
		/*
		* Create color targets
		*/
		Array<TextureResource*> colorTextures;
		for (unsigned int i = 0; i < colorTargetFormats.GetCursor(); i++)
		{
			const TextureFormat format = colorTargetFormats[i];

			TextureResource* pColorTarget = new TextureResource(TextureType::Texture2D, TextureUsage::RenderTarget, format, width, height, 1);
			pColorTarget->SetTagName(colorTargetNames[i]);

			colorTextures.Add(pColorTarget);
		}

		/*
		* Create depth stencil target
		*/
		TextureResource* pDepthStencilTexture = nullptr;
		if (depthStencilFormat != TextureFormat::None)
		{
			pDepthStencilTexture = new TextureResource(TextureType::Texture2D, TextureUsage::DepthStencil, depthStencilFormat, width, height, 1);
			pDepthStencilTexture->SetTagName("Depth stencil");
		}

		/*
		* Create framebuffer
		*/
		FramebufferCreateDesc framebufferDesc = {};
		ResourceTableCreateDesc tableCreateDesc = {};
		Array<FramebufferAttachmentDesc> colorAttachments;
		for (unsigned int i = 0; i < colorTextures.GetCursor(); i++)
		{
			FramebufferAttachmentDesc desc = {};
			desc.ArrayLayer = 0;
			desc.MipLevel = 0;
			desc.pTexture = colorTextures[i]->GetTexture();

			framebufferDesc.ColorTargets.Add(desc);
			tableCreateDesc.Resources.Add(desc.pTexture);
		}

		if (pDepthStencilTexture != nullptr)
		{
			FramebufferAttachmentDesc desc = {};
			desc.ArrayLayer = 0;
			desc.MipLevel = 0;
			desc.pTexture = pDepthStencilTexture->GetTexture();

			framebufferDesc.DepthStencilTarget = desc;
		}

		mFramebuffer = mDevice->CreateFramebuffer(framebufferDesc);
		mColorTargets = colorTextures;
		mDepthStencilTarget = pDepthStencilTexture;
		mWidth = width;
		mHeight = height;

	}
	void RenderTarget::DestroyCore()
	{
		Delete();
	}
}