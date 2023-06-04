#pragma once
#include <Runtime/Rendering/RenderPassInputOutput.h>

namespace Portakal
{
	class MeshResource;
	class PORTAKAL_API MeshInputOutput : public RenderPassInputOutput
	{
	public:
		MeshInputOutput(const String& name,RenderPass* pOwnerRenderPass);
		~MeshInputOutput();

		void SetMesh(MeshResource* pMesh) { mMesh = pMesh; }
	private:
		// Inherited via RenderPassInputOutput
		virtual void* GetIOData() const noexcept override;
		virtual RenderPassInputOutputType GetIOType() const override;
		virtual void ForwardCore(void* pData) override;
	private:
		MeshResource* mMesh;
	};
}