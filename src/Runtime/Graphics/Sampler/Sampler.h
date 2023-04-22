#pragma once
#include <Runtime/Graphics/GraphicsDeviceObject.h>
#include <Runtime/Graphics/Sampler/SamplerCreateDesc.h>

namespace Portakal
{
	/// <summary>
	/// The texture sampling unit
	/// </summary>
	class PORTAKAL_API Sampler : public GraphicsDeviceObject
	{
	public:
		/// <summary>
		/// Returns the U sampling address
		/// </summary>
		/// <returns></returns>
		FORCEINLINE SamplerAddress GetAddressU() const noexcept { return mAddressU; }

		/// <summary>
		/// Returns the V sampling address
		/// </summary>
		/// <returns></returns>
		FORCEINLINE SamplerAddress GetAddressV() const noexcept { return mAddressV; }

		/// <summary>
		/// Returns the U sampling address
		/// </summary>
		/// <returns></returns>
		FORCEINLINE SamplerAddress GetAddressW() const noexcept { return mAddressW; }

		/// <summary>
		/// Returns filtering type
		/// </summary>
		/// <returns></returns>
		FORCEINLINE SamplerFiltering GetFiltering() const noexcept { return mFiltering; }

		/// <summary>
		/// Returns the comparision method
		/// </summary>
		/// <returns></returns>
		FORCEINLINE ComparisionMethod GetComparisionMethod() const noexcept { return mComparision; }

		/// <summary>
		/// Returns the max anisotropy
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned char GetMaxAnisotropy() const noexcept { return mMaxAnisotropy; }

		/// <summary>
		/// Returns the min lod
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned char GetMinLod() const noexcept { return mMinLod; }

		/// <summary>
		/// Returns the max lod
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned char GetMaxLod() const noexcept { return mMaxLod; }

		/// <summary>
		/// Returns the lod bias
		/// </summary>
		/// <returns></returns>
		FORCEINLINE char GetLodBias() const noexcept { return mLodBias; }

		/// <summary>
		/// Returns the border color
		/// </summary>
		/// <returns></returns>
		FORCEINLINE SamplerBorderColor GetBorderColor() const noexcept { return mBorderColor; }
		FORCEINLINE virtual GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override final { return GraphicsDeviceObjectType::Sampler; }

	protected:
		Sampler(const SamplerCreateDesc& desc) : mAddressU(desc.AddressU),mAddressV(desc.AddressV),mAddressW(desc.AddressW),mFiltering(desc.Filtering),mComparision(desc.Comparision),mMaxAnisotropy(desc.MaxAnisotropy),mMinLod(desc.MinLod),mMaxLod(desc.MaxLod),mLodBias(desc.LodBias), mBorderColor(desc.BorderColor) {}
		virtual ~Sampler(){}
	private:
		const SamplerAddress mAddressU;
		const SamplerAddress mAddressV;
		const SamplerAddress mAddressW;
		const SamplerFiltering mFiltering;
		const ComparisionMethod mComparision;
		const unsigned char mMaxAnisotropy;
		const unsigned char mMinLod;
		const unsigned char mMaxLod;
		const char mLodBias;
		const SamplerBorderColor mBorderColor;
	};
}