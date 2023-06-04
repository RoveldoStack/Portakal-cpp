#include "MaterialInputOutput.h"

namespace Portakal
{
	MaterialInputOutput::MaterialInputOutput(const String& name, RenderPass* pOwnerPass) : RenderPassInputOutput(name,pOwnerPass),mMaterial(nullptr)
	{
	}
	MaterialInputOutput::~MaterialInputOutput()
	{
	}
	void* MaterialInputOutput::GetIOData() const noexcept
	{
		return mMaterial;
	}
	RenderPassInputOutputType MaterialInputOutput::GetIOType() const
	{
		return RenderPassInputOutputType::Material;
	}
	void MaterialInputOutput::ForwardCore(void* pData)
	{
		mMaterial = (MaterialResource*)pData;
	}
}