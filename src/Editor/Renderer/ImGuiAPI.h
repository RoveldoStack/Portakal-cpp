#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Graphics/GraphicsBackend.h>

namespace Portakal
{
	class GraphicsDevice;
	class CommandBuffer;
	class ImGuiRenderer;

	class PORTAKAL_API ImGuiAPI
	{
		friend class ImGuiExecutorModule;
	private:
		static ImGuiAPI* _api;
	public:
		static ImGuiRenderer* GetDefaultRenderer() { return _api->_renderer; }
	private:
		ImGuiAPI(ImGuiRenderer* pRenderer) : _renderer(pRenderer) { _api = this; }
		~ImGuiAPI() { _renderer = nullptr; _api = nullptr; }

	private:
		ImGuiRenderer* _renderer;
	};
}