#pragma once
#include <Runtime/Rendering/RenderPassInputOutput.h>

namespace Portakal
{
	class PORTAKAL_API FinishInputOutput : public RenderPassInputOutput
	{
	public:
		FinishInputOutput(const String& name, RenderPass* pOwnerPass) : RenderPassInputOutput(name,pOwnerPass) {}
		~FinishInputOutput() = default;

		// Inherited via RenderPassInputOutput
		virtual void* GetIOData() const noexcept override;
		virtual RenderPassInputOutputType GetIOType() const override { return RenderPassInputOutputType::Finish; }
		virtual void ForwardCore(void* pData) override;

	};
}