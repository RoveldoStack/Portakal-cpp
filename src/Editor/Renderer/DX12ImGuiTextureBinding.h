#pragma once
#include <Editor/Renderer/ImGuiTextureBinding.h>

namespace Portakal
{
	class PORTAKAL_API DX12ImGuiTextureBinding : public ImGuiTextureBinding
	{
	public:
		DX12ImGuiTextureBinding(const TextureResource* pTargetTexture);
		virtual ~DX12ImGuiTextureBinding();



		virtual void* GetBinding() const noexcept override;
	private:

	};
}