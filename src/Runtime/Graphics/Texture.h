#pragma once
#include <Runtime/Graphics/GraphicsDeviceObject.h>
#include <Runtime/Graphics/TextureCreateDesc.h>

namespace Portakal
{
	class PORTAKAL_API Texture : public GraphicsDeviceObject
	{
	public:
		FORCEINLINE TextureType GetTextureType() const noexcept { return _type; }
		FORCEINLINE TextureUsage GetTextureUsage() const noexcept { return _usage; }
		FORCEINLINE TextureFormat GetTextureFormat() const noexcept { return _format; }
		FORCEINLINE unsigned int GetWidth() const noexcept { return _width; }
		FORCEINLINE unsigned int GetHeight() const noexcept { return _height; }
		FORCEINLINE unsigned int GetDepth() const noexcept { return _depth; }
		FORCEINLINE unsigned char GetSampleCount() const noexcept { return _sampleCount; }
		FORCEINLINE unsigned char GetMipLevels() const noexcept { return _mipLevels; }
		FORCEINLINE unsigned char GetArrayLevels() const noexcept { return _arrayLevels; }

		FORCEINLINE virtual GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override final { return GraphicsDeviceObjectType::Texture; }
	protected:
		Texture(const TextureCreateDesc& desc) : _type(desc.Type), _usage(desc.Usage), _format(desc.Format), _width(desc.Width), _height(desc.Height), _depth(desc.Depth), _sampleCount(desc.SampleCount), _mipLevels(desc.MipLevels), _arrayLevels(desc.ArrayLevels)
		{

		}
		virtual ~Texture(){}
	private:
		const TextureType _type;
		const TextureUsage _usage;
		const TextureFormat _format;
		const unsigned int _width;
		const unsigned int _height;
		const unsigned int _depth;
		const unsigned char _sampleCount;
		const unsigned char _mipLevels;
		const unsigned char _arrayLevels;
	};
}