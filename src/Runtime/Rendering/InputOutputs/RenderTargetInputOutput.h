#pragma once
#include <Runtime/Rendering/RenderPassInputOutput.h>
#include <Runtime/Resource/RenderTarget/RenderTargetResource.h>

namespace Portakal
{
	class PORTAKAL_API RenderTargetInputOutput : public RenderPassInputOutput
	{
	public:
		RenderTargetInputOutput(const String& name, RenderPass* pOwnerPass);
		~RenderTargetInputOutput() = default;
		
		void SetRenderTarget(RenderTargetResource* pRenderTarget) { mRenderTarget = pRenderTarget; }
		virtual void* GetIOData() const noexcept override;
		virtual RenderPassInputOutputType GetIOType() const override { return RenderPassInputOutputType::RenderTarget; }
	private:
		virtual void ForwardCore(void* pData) override;
	private:
		RenderTargetResource* mRenderTarget;

	};
}