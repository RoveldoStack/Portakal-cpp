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
	public:
		FORCEINLINE static ImGuiRenderer* GetDefaultRenderer() { return sRenderer; }
	private:
		static ImGuiRenderer* sRenderer;
	};
}