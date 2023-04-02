#pragma once
#include <Runtime/Resource/ResourceSubObject.h>
#include <Runtime/Graphics/TextureCreateDesc.h>

namespace Portakal
{
	class Texture;
	class GraphicsDevice;
	class CommandList;
	class ResourceTable;

	/// <summary>
	/// A resource which is specialized in textures
	/// </summary>
	class PORTAKAL_API TextureResource final : public ResourceSubObject
	{
		GENERATE_CLASS(TextureResource);
	public:
		/// <summary>
		/// Creates a transient texture
		/// </summary>
		/// <param name="type"></param>
		/// <param name="usage"></param>
		/// <param name="format"></param>
		/// <param name="width"></param>
		/// <param name="height"></param>
		/// <param name="depth"></param>
		TextureResource(const TextureType type, const TextureUsage usage, const TextureFormat format, const unsigned int width, const unsigned height, const unsigned depth);

		/// <summary>
		/// Creates a texture from a physical path
		/// </summary>
		/// <param name="path"></param>
		TextureResource(const String& path);
		TextureResource();
		~TextureResource();

		/// <summary>
		/// Returns the texture
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Texture* GetTexture() const noexcept { return mTexture; }

		/// <summary>
		/// Returns the width
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetWidth() const noexcept { return mWidth; }

		/// <summary>
		/// Returns the height
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetHeight() const noexcept { return mHeight; }

		/// <summary>
		/// Returns the depth
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetDepth() const noexcept { return mDepth; }

		/// <summary>
		/// Returns the format
		/// </summary>
		/// <returns></returns>
		FORCEINLINE TextureFormat GetFormat() const noexcept { return mFormat; }

		/// <summary>
		/// Updates the texture data
		/// </summary>
		/// <param name="pData"></param>
		/// <param name="offsetX"></param>
		/// <param name="offsetY"></param>
		/// <param name="offsetZ"></param>
		void UpdateTexture(const unsigned char* pData, const unsigned int offsetX, const unsigned int offsetY, const unsigned int offsetZ);
	private:

		/// <summary>
		/// Deletes the texture contents
		/// </summary>
		void DeleteTexture();

		/// <summary>
		/// Creates cmd list
		/// </summary>
		void CreateCmdList();

		virtual void DestroyCore() override final;
	private:
		GraphicsDevice* mDevice;
		CommandList* mCmdList;
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

	START_GENERATE_TYPE(TextureResource);
	START_TYPE_PROPERTIES(TextureResource);
	REGISTER_BASE_TYPE(ResourceSubObject);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(TextureResource);
	END_GENERATE_TYPE(TextureResource);
}