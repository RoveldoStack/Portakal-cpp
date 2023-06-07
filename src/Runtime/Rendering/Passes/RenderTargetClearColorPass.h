#pragma once
#include <Runtime/Rendering/RenderPass.h>
#include <Runtime/Math/Color4.h>
namespace Portakal
{
	class RenderTargetResource;
	class PORTAKAL_API RenderTargetClearColorPass : public RenderPass
	{
	public:
		RenderTargetClearColorPass();
		virtual ~RenderTargetClearColorPass() override;

		// Inherited via RenderPass
		virtual void Initialize() override;
		virtual void Execute(CommandList* pCmdList) const override;
		virtual void Finalize() override;
	private:
		Color4 mClearColor;
		RenderTargetResource* mRenderTarget;
	};
}