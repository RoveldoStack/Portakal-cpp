#include "RenderTargetResource.h"
#include <Runtime/Graphics/Texture/Texture.h>
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/Graphics/Framebuffer/Framebuffer.h>
#include <Runtime/Graphics/Resource/ResourceTable.h>
#include <Runtime/Graphics/Swapchain/Swapchain.h>
#include <Runtime/Assert/Assert.h>

namespace Portakal
{
	RenderTargetResource::RenderTargetResource(const unsigned int width, const unsigned int height, const Array<TextureFormat>& colorTargetFormats, const TextureFormat depthStencilFormat, const Array<String>& colorTargetNames) : mSwapchain(false)
	{
		mDevice = GraphicsDeviceAPI::GetDefaultDevice();

		ASSERT(colorTargetFormats.GetCursor() == colorTargetNames.GetCursor(),"RenderTargetResource","Given color target names are not matched with the given format count");

		/*
		* Create resources
		*/
		CreateResources(width, height, colorTargetFormats, depthStencilFormat,colorTargetNames);
	}
	RenderTargetResource::RenderTargetResource(Swapchain* pSwapchain) : mSwapchain(true)
	{
		/*
		* Get and validate
		*/
		Framebuffer* pSwapchainFramebuffer = pSwapchain->GetFramebuffer();
		ASSERT(pSwapchainFramebuffer != nullptr, "RenderTargetResource", "The given swapchain has no framebuffer!");

		/*
		* Initialize
		*/
		mFramebuffer = pSwapchainFramebuffer;
		mDepthStencilTarget = nullptr;
		mDevice = GraphicsDeviceAPI::GetDefaultDevice();
	}
	RenderTargetResource::~RenderTargetResource()
	{
		mFramebuffer = nullptr;
		mDevice = nullptr;
	}
	unsigned int RenderTargetResource::GetWidth() const noexcept
	{
		if (mFramebuffer == nullptr)
			return 0;

		return mFramebuffer->GetWidth();
	}
	unsigned int RenderTargetResource::GetHeight() const noexcept
	{
		if (mFramebuffer == nullptr)
			return 0;

		return mFramebuffer->GetHeight();
	}
	void RenderTargetResource::Resize(const unsigned int width, const unsigned int height)
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
	void RenderTargetResource::Delete()
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
	void RenderTargetResource::CreateResources(const unsigned int width, const unsigned int height, const Array<TextureFormat>& colorTargetFormats, const TextureFormat depthStencilFormat, const Array<String>& colorTargetNames)
	{
		/*
		* Create color targets
		*/
		Array<TextureResource*> colorTextures;
		for (unsigned int i = 0; i < colorTargetFormats.GetCursor(); i++)
		{
			const TextureFormat format = colorTargetFormats[i];

			TextureResource* pColorTarget = new TextureResource(TextureType::Texture2D, TextureUsage::RenderTarget | TextureUsage::Sampled, format, width, height, 1);
			pColorTarget->SetTagName(colorTargetNames[i]);

			colorTextures.Add(pColorTarget);
		}

		/*
		* Create depth stencil target
		*/
		TextureResource* pDepthStencilTexture = nullptr;
		if (depthStencilFormat != TextureFormat::None)
		{
			pDepthStencilTexture = new TextureResource(TextureType::Texture2D, TextureUsage::DepthStencil | TextureUsage::Sampled, depthStencilFormat, width, height, 1);
			pDepthStencilTexture->SetTagName("Depth stencil");
		}

		/*
		* Create framebuffer
		*/
		FramebufferCreateDesc framebufferDesc = {};
		for (unsigned int i = 0; i < colorTextures.GetCursor(); i++)
		{
			FramebufferAttachmentDesc desc = {};
			desc.ArrayLayer = 0;
			desc.MipLevel = 0;
			desc.pTexture = colorTextures[i]->GetTexture();

			framebufferDesc.ColorTargets.Add(desc);
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
	}
	void RenderTargetResource::DestroyCore()
	{
		Delete();
	}
}