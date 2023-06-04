#pragma once
#include <Runtime/Rendering/RenderPassInputOutput.h>

namespace Portakal
{
	class MaterialResource;
	class PORTAKAL_API MaterialInputOutput : public RenderPassInputOutput
	{
	public:
		MaterialInputOutput(const String& name,RenderPass* pOwnerPass);
		~MaterialInputOutput();

		void SetMaterial(MaterialResource* pMaterial) { mMaterial = pMaterial; }
	private:
		// Inherited via RenderPassInputOutput
		virtual void* GetIOData() const noexcept override;
		virtual RenderPassInputOutputType GetIOType() const override;
		virtual void ForwardCore(void* pData) override;
	private:
		MaterialResource* mMaterial;
	};
}