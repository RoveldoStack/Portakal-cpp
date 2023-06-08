#pragma once
#include <Runtime/Resource/ResourceSubObject.h>
#include <Runtime/Graphics/Sampler/Sampler.h>

namespace Portakal
{
	class PORTAKAL_API SamplerResource : public ResourceSubObject
	{
	public:
		SamplerResource();
		~SamplerResource();

		FORCEINLINE Sampler* GetSampler() const noexcept { return mSampler; }

		void Create(const SamplerCreateDesc& desc);
	private:
		void Delete();

		// Inherited via ResourceSubObject
		virtual void DestroyCore() override;
		virtual void SetTagNameCore(const String& name) override;
	private:
		GraphicsDevice* mOwnerDevice;
		Sampler* mSampler;
	};
}