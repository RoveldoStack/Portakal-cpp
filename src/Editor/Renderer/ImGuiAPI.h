#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Graphics/GraphicsBackend.h>
#include <Runtime/Object/API.h>

namespace Portakal
{
	class GraphicsDevice;
	class CommandList;
	class ImGuiRenderer;

	/// <summary>
	/// API for enabling application using the ImGui operatio
	/// </summary>
	class PORTAKAL_API ImGuiAPI : public API<ImGuiAPI>
	{
		friend class ImGuiExecutorModule;
	public:
		FORCEINLINE static ImGuiRenderer* GetDefaultRenderer();
	private:
		ImGuiAPI(ImGuiRenderer* pRenderer);
		virtual ~ImGuiAPI() override;
	private:
		ImGuiRenderer* mRenderer;
	};
}