#pragma once
#include <Runtime/Core/Core.h>
#include <Libs/ImGui/imgui.h>
#include <Runtime/Graphics/GraphicsBackend.h>

namespace Portakal
{
	class GraphicsDevice;
	class CommandList;
	class WindowEvent;

	class WindowResizedEvent;
	class MouseMovedEvent;
	class MouseButtonDownEvent;
	class MouseButtonUpEvent;
	class MouseWheelEvent;
	class KeyboardKeyDownEvent;
	class KeyboardKeyUpEvent;
	class KeyboardCharEvent;

	/// <summary>
	/// Represents a imgui renderer (later it will be revised for suiting any type of user imgui renderer implementation)
	/// </summary>
	class PORTAKAL_API ImGuiRenderer
	{
	public:
		/// <summary>
		/// Creates an imgui renderer
		/// </summary>
		/// <param name="pDevice"></param>
		/// <returns></returns>
		static ImGuiRenderer* Create(GraphicsDevice* pDevice);
	public:
		ImGuiRenderer(GraphicsDevice* pDevice);
		virtual ~ImGuiRenderer();

		/// <summary>
		/// Starts the rendering session
		/// </summary>
		/// <param name="deltaTime"></param>
		void StartRendering(const float deltaTime);

		/// <summary>
		/// Finalizes the rendering session
		/// </summary>
		/// <param name="pCmdBuffer"></param>
		void FinalizeRendering(CommandList* pCmdBuffer);

		/// <summary>
		/// Called upon reciving an event
		/// </summary>
		/// <param name="pEvent"></param>
		void OnEvent(const WindowEvent* pEvent);

		/// <summary>
		/// Returns the target backend
		/// </summary>
		/// <returns></returns>
		FORCEINLINE GraphicsBackend GetTargetBackend() const noexcept;

		/// <summary>
		/// Returns the target device
		/// </summary>
		/// <returns></returns>
		FORCEINLINE GraphicsDevice* GetTargetDevice() const noexcept { return mDevice; }

	protected:
		virtual void StartRenderingCore() = 0;
		virtual void FinalizeRenderingCore(CommandList* pCmdBuffer) = 0;
	private:
		/// <summary>
		/// Called on when window is resized
		/// </summary>
		/// <param name="pEvent"></param>
		void OnWindowResized(const WindowResizedEvent* pEvent);

		/// <summary>
		/// Called when mouse moved
		/// </summary>
		/// <param name="pEvent"></param>
		void OnMouseMoved(const MouseMovedEvent* pEvent);

		/// <summary>
		/// Called when mouse button pressed
		/// </summary>
		/// <param name="pEvent"></param>
		void OnMouseButtonDown(const MouseButtonDownEvent* pEvent);

		/// <summary>
		/// Called when mouse button released
		/// </summary>
		/// <param name="pEvent"></param>
		void OnMouseButtonUp(const MouseButtonUpEvent* pEvent);

		/// <summary>
		/// Called when mouse wheel scrolled
		/// </summary>
		/// <param name="pEvent"></param>
		void OnMouseWheel(const MouseWheelEvent* pEvent);

		/// <summary>
		/// Called when keyboard key pressed
		/// </summary>
		/// <param name="pEvent"></param>
		void OnKeyboardDown(const KeyboardKeyDownEvent* pEvent);

		/// <summary>
		/// Called when keyboard key released
		/// </summary>
		/// <param name="pEvent"></param>
		void OnKeyboardUp(const KeyboardKeyUpEvent* pEvent);

		/// <summary>
		/// Called when keyboard char emitted
		/// </summary>
		/// <param name="pEvent"></param>
		void OnKeyboardChar(const KeyboardCharEvent* pEvent);
	private:
		ImGuiContext* mContext;
		GraphicsDevice* mDevice;
	};
}