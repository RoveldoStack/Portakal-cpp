#include "MeshInputOutput.h"

namespace Portakal
{
	MeshInputOutput::MeshInputOutput(const String& name, RenderPass* pOwnerRenderPass) : RenderPassInputOutput(name,pOwnerRenderPass),mMesh(nullptr)
	{
	}
	MeshInputOutput::~MeshInputOutput()
	{
	}
	void* MeshInputOutput::GetIOData() const noexcept
	{
		return mMesh;
	}
	RenderPassInputOutputType MeshInputOutput::GetIOType() const
	{
		return RenderPassInputOutputType::Mesh;
	}
	void MeshInputOutput::ForwardCore(void* pData)
	{
		mMesh = (MeshResource*)pData;
	}
}