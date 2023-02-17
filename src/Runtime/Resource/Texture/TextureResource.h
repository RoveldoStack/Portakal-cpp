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
		TextureResource();
		~TextureResource();

		FORCEINLINE Texture* GetTexture() const noexcept { return mTexture; }
		FORCEINLINE ResourceTable* GetIsolatedResourceTable() const noexcept { return mIsolatedResourceTable; }
		FORCEINLINE unsigned int GetWidth() const noexcept;
		FORCEINLINE unsigned int GetHeight() const noexcept;
		FORCEINLINE unsigned int GetDepth() const noexcept;

		void CreateTextureFromPath(const String& path);
		void AllocateTexture(const TextureType type, const TextureUsage usage, const TextureFormat format, const unsigned int width, const unsigned height, const unsigned depth);
		void UpdateTexture(const unsigned char* pData, const unsigned int offsetX, const unsigned int offsetY, const unsigned int offsetZ);
	private:
		void DeleteTexture();
		void CreateCmdList();
		void GenerateIsolatedResourceTable();

	private:
		GraphicsDevice* mDevice;
		CommandList* mCmdList;
		ResourceTable* mIsolatedResourceTable;
		Texture* mTexture;

		// Inherited via ResourceSubObject
		virtual void DestroyCore() override;
	};
}