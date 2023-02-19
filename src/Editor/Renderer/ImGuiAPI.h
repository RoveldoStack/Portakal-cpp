#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Graphics/GraphicsBackend.h>

namespace Portakal
{
	class GraphicsDevice;
	class CommandList;
	class ImGuiRenderer;

	/// <summary>
	/// API for enabling application using the ImGui operatio
	/// </summary>
	class PORTAKAL_API ImGuiAPI
	{
		friend class ImGuiExecutorModule;
	private:
		static ImGuiAPI* sAPI;
	public:
		/// <summary>
		/// Returns the default imgui renderer
		/// </summary>
		/// <returns></returns>
		static ImGuiRenderer* GetDefaultRenderer() { return sAPI->mRenderer; }
	private:
		ImGuiAPI(ImGuiRenderer* pRenderer) : mRenderer(pRenderer) { sAPI = this; }
		~ImGuiAPI() { mRenderer = nullptr; sAPI = nullptr; }

	private:
		ImGuiRenderer* mRenderer;
	};
}