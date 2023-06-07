#pragma once
#include <Runtime/Rendering/RenderPassInputOutput.h>

namespace Portakal
{
	class PORTAKAL_API OtherInputOutput : public RenderPassInputOutput
	{
	public:
		OtherInputOutput(const String& name,RenderPass* pOwnerPass);
		~OtherInputOutput();

		void SetOtherData(void* pData) { mData = pData; }
	private:
		// Inherited via RenderPassInputOutput
		virtual void* GetIOData() const noexcept override;
		virtual RenderPassInputOutputType GetIOType() const override;
		virtual void ForwardCore(void* pData) override;
	private:

		void* mData;
	};

}