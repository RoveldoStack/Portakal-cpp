#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Graphics/GraphicsBackend.h>

namespace Portakal
{
	class GraphicsDevice;
	class CommandList;
	class ImGuiRenderer;

	class PORTAKAL_API ImGuiAPI
	{
		friend class ImGuiExecutorModule;
	private:
		static ImGuiAPI* mAPI;
	public:
		static ImGuiRenderer* GetDefaultRenderer() { return mAPI->mRenderer; }
	private:
		ImGuiAPI(ImGuiRenderer* pRenderer) : mRenderer(pRenderer) { mAPI = this; }
		~ImGuiAPI() { mRenderer = nullptr; mAPI = nullptr; }

	private:
		ImGuiRenderer* mRenderer;
	};
}