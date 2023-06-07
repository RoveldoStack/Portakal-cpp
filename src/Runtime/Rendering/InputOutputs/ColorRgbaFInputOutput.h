#pragma once
#include <Runtime/Rendering/RenderPassInputOutput.h>
#include <Runtime/Math/Color4.h>

namespace Portakal
{
	class PORTAKAL_API ColorRgbaInputOutput : public RenderPassInputOutput
	{
	public:
		ColorRgbaInputOutput(const String& name,RenderPass* pOwnerPass);
		~ColorRgbaInputOutput();

		FORCEINLINE Color4 GetColor() const noexcept { return mColor; }
		void SetColor(const Color4& color) { mColor = color; }

		// Inherited via RenderPassInputOutput
		virtual void* GetIOData() const noexcept override;
		virtual RenderPassInputOutputType GetIOType() const override { return RenderPassInputOutputType::Color; }
	private:
		// Inherited via RenderPassInputOutput
		virtual void ForwardCore(void* pData) override;
	private:
		Color4 mColor;
	};
}