#pragma once
#include <Editor/Renderer/ImGuiRenderer.h>
#include <Runtime/DX11/Core.h>
#include <d3d11.h>

namespace Portakal
{
	class PORTAKAL_API  DX11ImGuiRenderer : public ImGuiRenderer
	{
	public:
		DX11ImGuiRenderer(GraphicsDevice* pDevice);
		virtual ~DX11ImGuiRenderer() override;

	private:
		// Inherited via ImGuiRenderer
		virtual void StartRenderingCore() override;

		virtual void FinalizeRenderingCore(CommandList* pCmdBuffer) override;

		virtual ImGuiTextureBinding* CreateTextureBinding(TextureResource* pTexture) override;

	};
}