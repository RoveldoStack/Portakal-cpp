#pragma once
#include <Runtime/Graphics/GraphicsDeviceObject.h>
#include <Runtime/Graphics/SamplerCreateDesc.h>

namespace Portakal
{
	class PORTAKAL_API Sampler : public GraphicsDeviceObject
	{
	public:

		FORCEINLINE SamplerAddress GetAddressU() const noexcept { return _addressU; }
		FORCEINLINE SamplerAddress GetAddressV() const noexcept { return _addressV; }
		FORCEINLINE SamplerAddress GetAddressW() const noexcept { return _addressW; }
		FORCEINLINE SamplerFiltering GetFiltering() const noexcept { return _filtering; }
		FORCEINLINE ComparisionMethod GetComparisionMethod() const noexcept { return _comparision; }
		FORCEINLINE unsigned char GetMaxAnisotropy() const noexcept { return _maxAnisotropy; }
		FORCEINLINE unsigned char GetMinLod() const noexcept { return _minLod; }
		FORCEINLINE unsigned char GetMaxLod() const noexcept { return _maxLod; }
		FORCEINLINE char GetLodBias() const noexcept { return _lodBias; }
		FORCEINLINE SamplerBorderColor GetBorderColor() const noexcept { return _borderColor; }
		FORCEINLINE virtual GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override final { return GraphicsDeviceObjectType::Sampler; }

	protected:
		Sampler(const SamplerCreateDesc& desc) : _addressU(desc.AddressU),_addressV(desc.AddressV),_addressW(desc.AddressW),_filtering(desc.Filtering),_comparision(desc.Comparision),_maxAnisotropy(desc.MaxAnisotropy),_minLod(desc.MinLod),_maxLod(desc.MaxLod),_lodBias(desc.LodBias), _borderColor(desc.BorderColor) {}
		virtual ~Sampler(){}



		
	private:
		const SamplerAddress _addressU;
		const SamplerAddress _addressV;
		const SamplerAddress _addressW;
		const SamplerFiltering _filtering;
		const ComparisionMethod _comparision;
		const unsigned char _maxAnisotropy;
		const unsigned char _minLod;
		const unsigned char _maxLod;
		const char _lodBias;
		const SamplerBorderColor _borderColor;
	};
}