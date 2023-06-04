#include "SamplerResource.h"
#include <Runtime/Graphics/GraphicsDeviceAPI.h>

namespace Portakal
{
	SamplerResource::SamplerResource()
	{
		mOwnerDevice = GraphicsDeviceAPI::GetDefaultDevice();
		mSampler = nullptr;
	}
	SamplerResource::~SamplerResource()
	{
		mSampler = nullptr;
		mOwnerDevice = nullptr;
	}
	void SamplerResource::Create(const SamplerCreateDesc& desc)
	{
		/*
		* Validate if destroyed
		*/
		if (IsDestroyed())
		{
			LOG("SamplerResource", "Cannot create sampler due to this resource is destoryed");
			return;
		}

		/*
		* Validate owner device
		*/
		if (mOwnerDevice == nullptr)
		{
			LOG("SamplerResource","Cannot create sampler due to this resource has no valid owner GraphicsDevice");
			return;
		}

		/*
		* First delete
		*/
		Delete();

		/*
		* Create anew
		*/
		mSampler = mOwnerDevice->CreateSampler(desc);
	}
	void SamplerResource::Delete()
	{
		if(mSampler != nullptr)
			mSampler->Destroy();
		mSampler = nullptr;
	}
	void SamplerResource::DestroyCore()
	{
		mSampler->Destroy();
		mSampler = nullptr;
		mOwnerDevice = nullptr;
	}
}