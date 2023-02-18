#pragma once
#include <Runtime/Resource/ResourceSubObject.h>
#include <Runtime/Graphics/TextureCreateDesc.h>

namespace Portakal
{
	class Texture;
	class GraphicsDevice;
	class CommandList;
	class ResourceTable;
	class PORTAKAL_API TextureResource : public ResourceSubObject
	{
	public:
		TextureResource(const TextureType type, const TextureUsage usage, const TextureFormat format, const unsigned int width, const unsigned height, const unsigned depth);
		TextureResource(const String& path);
		~TextureResource();

		FORCEINLINE Texture* GetTexture() const noexcept { return mTexture; }
		FORCEINLINE ResourceTable* GetIsolatedResourceTable() const noexcept { return mIsolatedResourceTable; }
		FORCEINLINE unsigned int GetWidth() const noexcept { return mWidth; }
		FORCEINLINE unsigned int GetHeight() const noexcept { return mHeight; }
		FORCEINLINE unsigned int GetDepth() const noexcept { return mDepth; }
		FORCEINLINE TextureFormat GetFormat() const noexcept { return mFormat; }

		void UpdateTexture(const unsigned char* pData, const unsigned int offsetX, const unsigned int offsetY, const unsigned int offsetZ);
	private:
		void DeleteTexture();
		void CreateCmdList();
		void GenerateIsolatedResourceTable();

		virtual void DestroyCore() override;
	private:
		GraphicsDevice* mDevice;
		CommandList* mCmdList;
		ResourceTable* mIsolatedResourceTable;
		Texture* mTexture;
		TextureType mType;
		TextureUsage mUsage;
		TextureFormat mFormat;
		unsigned int mWidth;
		unsigned int mHeight;
		unsigned int mDepth;
		unsigned int mArrayLevel;
		unsigned int mMipLevels;



	};
}