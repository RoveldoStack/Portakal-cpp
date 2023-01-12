#pragma once
#include <Runtime/Core/Core.h>
#include <Libs/ImGui/imgui.h>
#include <Runtime/Graphics/GraphicsBackend.h>

namespace Portakal
{
	class GraphicsDevice;
	class CommandBuffer;
	class WindowEvent;

	class WindowResizedEvent;
	class MouseMovedEvent;
	class MouseButtonDownEvent;
	class MouseButtonUpEvent;
	class MouseWheelEvent;
	class KeyboardKeyDownEvent;
	class KeyboardKeyUpEvent;
	class KeyboardCharEvent;

	class PORTAKAL_API ImGuiRenderer
	{
	public:
		static ImGuiRenderer* Create(GraphicsDevice* pDevice);
	public:
		ImGuiRenderer(GraphicsDevice* pDevice);
		virtual ~ImGuiRenderer();

		void StartRendering(const float deltaTime);
		void FinalizeRendering(CommandBuffer* pCmdBuffer);
		void OnEvent(const WindowEvent* pEvent);

		FORCEINLINE GraphicsBackend GetTargetBackend() const noexcept;
		FORCEINLINE GraphicsDevice* GetTargetDevice() const noexcept { return _device; }

	protected:
		virtual void StartRenderingCore() = 0;
		virtual void FinalizeRenderingCore(CommandBuffer* pCmdBuffer) = 0;
	private:
		void OnWindowResized(const WindowResizedEvent* pEvent);
		void OnMouseMoved(const MouseMovedEvent* pEvent);
		void OnMouseButtonDown(const MouseButtonDownEvent* pEvent);
		void OnMouseButtonUp(const MouseButtonUpEvent* pEvent);
		void OnMouseWheel(const MouseWheelEvent* pEvent);
		void OnKeyboardDown(const KeyboardKeyDownEvent* pEvent);
		void OnKeyboardUp(const KeyboardKeyUpEvent* pEvent);
		void OnKeyboardChar(const KeyboardCharEvent* pEvent);
	private:
		ImGuiContext* _context;
		GraphicsDevice* _device;
	};
}