#include "TextureResource.h"
#include <Runtime/Graphics/Texture/Texture.h>
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/Graphics/Texture/TextureUpdateDesc.h>
#include <Runtime/Graphics/Command/CommandList.h>
#include <Runtime/Graphics/Resource/ResourceTable.h>
#include <Runtime/Graphics/Texture/TextureLoader.h>
#include <Runtime/Log/Log.h>

namespace Portakal
{
	TextureResource::TextureResource(const TextureType type, const TextureUsage usage, const TextureFormat format, const unsigned int width, const unsigned height, const unsigned depth)
	{
		mDevice = GraphicsDeviceAPI::GetDefaultDevice();
		mTexture = nullptr;
		mCmdList = nullptr;
		mWidth = width;
		mHeight = height;
		mDepth = depth;
		mFormat = format;
		mUsage = usage;
		mType = type;
		mArrayLevel = 1;
		mMipLevels = 0;

		/*
		* Create texture
		*/
		TextureCreateDesc desc = {};
		desc.Type = type;
		desc.Usage = usage;
		desc.Format = format;
		desc.Width = width;
		desc.Height = height;
		desc.Depth = depth == 0 ? 1 : depth;
		desc.MipLevels = 1;
		desc.ArrayLevels = 1;
		desc.SampleCount = 1;

		mTexture = mDevice->CreateTexture(desc);
	}
	TextureResource::TextureResource(const String& path)
	{
		mDevice = GraphicsDeviceAPI::GetDefaultDevice();
		mTexture = nullptr;
		mCmdList = nullptr;
		mType = TextureType::Texture2D;
		mUsage = TextureUsage::Sampled;
		mFormat = TextureFormat::None;
		mWidth = 0;
		mHeight = 0;
		mDepth = 0;
		mArrayLevel = 0;
		mMipLevels = 0;

		/*
		* Load texture data
		*/
		TextureLoadResult result = {};
		TextureLoader::LoadTextureFromDisk(path, result);

		if (result.pData == nullptr)
			return;

		/*
		* Create texture
		*/
		TextureCreateDesc desc = {};
		desc.Type = TextureType::Texture2D;
		desc.Usage = TextureUsage::Sampled;
		desc.Format = result.Format;
		desc.Width = result.Width;
		desc.Height = result.Height;
		desc.Depth = result.Depth == 0 ? 1 : result.Depth;
		desc.MipLevels = 1;
		desc.ArrayLevels = 1;
		desc.SampleCount = 1;

		mTexture = mDevice->CreateTexture(desc);

		/*
		* Update the texture data
		*/
		UpdateTexture(result.pData, 0, 0, 0);

		/*
		* Initialize
		*/
		mType = TextureType::Texture2D;
		mUsage = TextureUsage::Sampled;
		mFormat = result.Format;
		mWidth = result.Width;
		mHeight = result.Height;
		mDepth = result.Depth == 0 ? 1 : result.Depth;;
		mArrayLevel = 1;
		mMipLevels = 0;
	}
	TextureResource::TextureResource()
	{
		mType = TextureType::Texture2D;
		mUsage = TextureUsage::Sampled;
		mFormat = TextureFormat::None;
		mWidth = 0;
		mHeight = 0;
		mDepth = 0;
		mArrayLevel = 0;
		mMipLevels = 0;
		mTexture = nullptr;
		mCmdList = nullptr;
		mDevice = GraphicsDeviceAPI::GetDefaultDevice();
	}
	TextureResource::~TextureResource()
	{
		LOG("Texture Resource", "Delete");
	}
	
	void TextureResource::UpdateTexture(const unsigned char* pData, const unsigned int offsetX, const unsigned int offsetY, const unsigned int offsetZ)
	{
		if (mTexture == nullptr)
			return;

		CreateCmdList();

		TextureUpdateDesc desc = {};
		desc.pData = pData;
		desc.MipSlice = 0;
		desc.ArrayLevel = 0;
		desc.OffsetWidth = offsetX;
		desc.OffsetHeight = offsetY;
		desc.OffsetDepth = offsetZ;

		mCmdList->Lock();
		mCmdList->UpdateTexture(desc, mTexture);
		mCmdList->Unlock();

		mDevice->SubmitCommands(mCmdList);
		mDevice->WaitForFinish();
	}
	void TextureResource::DeleteTexture()
	{
		if (mTexture != nullptr)
			mTexture->Destroy();

		mTexture = nullptr;
	}
	void TextureResource::DeleteCmdList()
	{
		if (mCmdList != nullptr)
			mCmdList->Destroy();

		mCmdList = nullptr;
	}
	void TextureResource::CreateCmdList()
	{
		if (mCmdList != nullptr)
			return;

		mCmdList = mDevice->CreateCommandList({});
	}
	void TextureResource::DestroyCore()
	{
		LOG("TextureResource", "Destroy core: %s",*GetTagName());
		DeleteTexture();
		DeleteCmdList();
	}
}