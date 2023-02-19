#pragma once
#include <Runtime/Graphics/GraphicsDeviceObject.h>
#include <Runtime/Graphics/TextureCreateDesc.h>

namespace Portakal
{
	/// <summary>
	/// Represents a texture allocated on the gpu
	/// </summary>
	class PORTAKAL_API Texture : public GraphicsDeviceObject
	{
	public:
		/// <summary>
		/// Returns the texture type
		/// </summary>
		/// <returns></returns>
		FORCEINLINE TextureType GetTextureType() const noexcept { return mType; }

		/// <summary>
		/// Returns the texture usage
		/// </summary>
		/// <returns></returns>
		FORCEINLINE TextureUsage GetTextureUsage() const noexcept { return mUsage; }

		/// <summary>
		/// Returns the texture format
		/// </summary>
		/// <returns></returns>
		FORCEINLINE TextureFormat GetTextureFormat() const noexcept { return mFormat; }

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
		/// Returns the sample count
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned char GetSampleCount() const noexcept { return mSampleCount; }

		/// <summary>
		/// Returns the mip levels
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned char GetMipLevels() const noexcept { return mMipLevels; }

		/// <summary>
		/// Returns array levels
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned char GetArrayLevels() const noexcept { return mArrayLevels; }

		FORCEINLINE virtual GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override final { return GraphicsDeviceObjectType::Texture; }
	protected:
		Texture(const TextureCreateDesc& desc) : mType(desc.Type), mUsage(desc.Usage), mFormat(desc.Format), mWidth(desc.Width), mHeight(desc.Height), mDepth(desc.Depth), mSampleCount(desc.SampleCount), mMipLevels(desc.MipLevels), mArrayLevels(desc.ArrayLevels)
		{

		}
		virtual ~Texture(){}
	private:
		const TextureType mType;
		const TextureUsage mUsage;
		const TextureFormat mFormat;
		const unsigned int mWidth;
		const unsigned int mHeight;
		const unsigned int mDepth;
		const unsigned char mSampleCount;
		const unsigned char mMipLevels;
		const unsigned char mArrayLevels;
	};
}