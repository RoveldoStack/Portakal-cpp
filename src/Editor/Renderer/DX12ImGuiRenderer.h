#pragma once
#include <Editor/Renderer/ImGuiRenderer.h>
#include <Runtime/DX12/Core.h>
#include <d3d12.h>

namespace Portakal
{
	class PORTAKAL_API DX12ImGuiRenderer : public ImGuiRenderer
	{
	public:
		DX12ImGuiRenderer(GraphicsDevice* pDevice);
		virtual ~DX12ImGuiRenderer() override;

		FORCEINLINE ID3D12DescriptorHeap* GetFontDescriptorHeap() const noexcept { return _fontHeap.Get(); }
	protected:
		virtual void StartRenderingCore() override;
		virtual void FinalizeRenderingCore(CommandBuffer* pCmdBuffer) override;
	private:
		DXPTR<ID3D12DescriptorHeap> _fontHeap;
	};
}