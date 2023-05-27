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

		FORCEINLINE ColorRgbaF GetColor() const noexcept { return mColor; }
		void SetColor(const ColorRgbaF& color) { mColor = color; }

		// Inherited via RenderPassInputOutput
		virtual void* GetIOData() const noexcept override;
		virtual RenderPassInputOutputType GetIOType() const override { return RenderPassInputOutputType::Color; }
	private:
		// Inherited via RenderPassInputOutput
		virtual void ForwardCore(void* pData) override;
	private:
		ColorRgbaF mColor;
	};
}