#include "TextureResource.h"
#include <Runtime/Graphics/Texture.h>
#include <Runtime/Graphics/GraphicsDevice.h>
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/Graphics/TextureUpdateDesc.h>
#include <Runtime/Graphics/CommandList.h>
#include <Runtime/Graphics/ResourceTable.h>
#include <Runtime/Graphics/TextureLoader.h>

namespace Portakal
{
	TextureResource::TextureResource()
	{
		mDevice = GraphicsDeviceAPI::GetDefaultDevice();
		mTexture = nullptr;
		mIsolatedResourceTable = nullptr;
		mCmdList = nullptr;
	}
	TextureResource::~TextureResource()
	{
		DeleteTexture();
	}
	void TextureResource::CreateTextureFromPath(const String& path)
	{
		TextureLoadResult result = {};
		TextureLoader::LoadTextureFromDisk(path,result);

		if (result.pData == nullptr)
			return;

		AllocateTexture(TextureType::Texture2D, TextureUsage::ReadOnly, result.Format, result.Width, result.Height, result.Depth);
		UpdateTexture(result.pData, 0, 0, 0);
	}
	void TextureResource::AllocateTexture(const TextureType type, const TextureUsage usage, const TextureFormat format, const unsigned int width, const unsigned height, const unsigned depth)
	{
		DeleteTexture();

		TextureCreateDesc desc = {};
		desc.Type = type;
		desc.Usage = usage;
		desc.Format = format;
		desc.Width = width;
		desc.Height = height;
		desc.Depth = depth == 0 ? 1 : depth;
		desc.MipLevels = 0;
		desc.ArrayLevels = 1;
		desc.SampleCount = 1;

		mTexture = mDevice->CreateTexture(desc);

		GenerateIsolatedResourceTable();
	}
	void TextureResource::UpdateTexture(const unsigned char* pData, const unsigned int offsetX, const unsigned int offsetY, const unsigned int offsetZ)
	{
		if (mTexture == nullptr)
			return;

		CreateCmdList();

		TextureUpdateDesc desc = {};
		desc.pData = pData;
		desc.MipLevel = 0;
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
			mTexture->DeleteDeviceObject();

		if (mIsolatedResourceTable != nullptr)
			mIsolatedResourceTable->DeleteDeviceObject();

		mIsolatedResourceTable = nullptr;
		mTexture = nullptr;
	}
	void TextureResource::CreateCmdList()
	{
		if (mCmdList != nullptr)
			return;

		mCmdList = mDevice->CreateGraphicsCommandList({});
	}
	void TextureResource::GenerateIsolatedResourceTable()
	{
		ResourceTableCreateDesc desc = {};
		desc.Resources.Add(mTexture);

		mIsolatedResourceTable = mDevice->CreateResourceTable(desc);
	}
	void TextureResource::DestroyCore()
	{
		DeleteTexture();
	}
}