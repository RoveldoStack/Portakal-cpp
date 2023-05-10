#pragma once
#include <Runtime/Core/Core.h>
#include <Libs/ImGui/imgui.h>
#include <Runtime/Graphics/GraphicsBackend.h>
#include <Runtime/Containers/Registry.h>

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

	class ImGuiTextureBinding;
	class TextureResource;
	class Sampler;
	class Texture;
	class GraphicsBuffer;
	class Pipeline;
	class ResourceTable;
	class Shader;
	class Framebuffer;
	/// <summary>
	/// Represents a imgui renderer (later it will be revised for suiting any type of user imgui renderer implementation)
	/// </summary>
	class PORTAKAL_API ImGuiRenderer
	{
	public:
	public:
		ImGuiRenderer(GraphicsDevice* pDevice);
		virtual ~ImGuiRenderer();

		/// <summary>
		/// Returns an existing binding o creating anew binding for the texture
		/// </summary>
		/// <param name="pTexture"></param>
		/// <returns></returns>
		FORCEINLINE ImGuiTextureBinding* GetOrCreateTextureBinding(TextureResource* pTexture);

		/// <summary>
		/// Deletes an existing binding
		/// </summary>
		/// <param name="pTexture"></param>
		FORCEINLINE void DeleteTextureBinding(TextureResource* pTexture);

		/// <summary>
		/// Starts the rendering session
		/// </summary>
		/// <param name="deltaTime"></param>
		void StartRendering(const float deltaTime);

		/// <summary>
		/// Finalizes the rendering session
		/// </summary>
		/// <param name="pCmdBuffer"></param>
		void FinalizeRendering(Framebuffer* pFramebuffer);

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
		Registry<TextureResource*, ImGuiTextureBinding*> mTextureBindings;
		ImGuiContext* mContext;
		GraphicsDevice* mDevice;

		TextureResource* mFontTexture;
		Pipeline* mPipeline;
		GraphicsBuffer* mVertexBuffer;
		GraphicsBuffer* mIndexBuffer;
		GraphicsBuffer* mConstantBuffer;
		Sampler* mSampler;
		ResourceTable* mFontTable;
		ResourceTable* mSamplerTable;
		ResourceTable* mProjectionTable;
		Shader* mVertexShader;
		Shader* mFragmentShader;
		CommandList* mCmdList;
	};
}