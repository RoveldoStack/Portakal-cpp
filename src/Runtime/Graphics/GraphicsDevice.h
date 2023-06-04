#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/GraphicsBackend.h>
#include <Runtime/Platform/PlatformCriticalSection.h>

namespace Portakal
{
	class GraphicsDeviceObject;
	class Window;

	class CommandList;
	struct CommandListCreateDesc;

	class GraphicsBuffer;
	struct GraphicsBufferCreateDesc;
	struct GraphicsBufferUpdateDesc;

	class Texture;
	struct TextureCreateDesc;
	struct TextureUpdateDesc;

	class Framebuffer;
	struct FramebufferCreateDesc;

	struct SwapchainCreateDesc;
	class Swapchain;

	class Pipeline;
	struct GraphicsPipelineCreateDesc;
	struct ComputePipelineCreateDesc;

	class Shader;
	struct ShaderCreateDesc;

	class Sampler;
	struct SamplerCreateDesc;

	class ResourceTable;
	struct ResourceTableCreateDesc;

	struct StandaloneGraphicsDeviceCreateDesc;
	struct WindowedGraphicsDeviceCreateDesc;

	class Fence;

	/// <summary>
	/// Represents a both physical and logical graphics device, it may only target one physical device!
	/// </summary>
	class PORTAKAL_API GraphicsDevice
	{
		friend GraphicsDeviceObject;
	public:
		/// <summary>
		/// Creates a standalone graphics device without a window 
		/// </summary>
		/// <param name="desc"></param>
		/// <returns></returns>
		static GraphicsDevice* CreateStandalone(const StandaloneGraphicsDeviceCreateDesc& desc);

		/// <summary>
		/// Creates a windowed graphics device
		/// </summary>
		/// <param name="desc"></param>
		/// <returns></returns>
		static GraphicsDevice* CreateWindowed(const WindowedGraphicsDeviceCreateDesc& desc);
	public:
		virtual ~GraphicsDevice();

		/// <summary>
		/// Returns the gpu total memory in bytes
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned long long GetMemory() const noexcept { return mMemory; }

		/// <summary>
		/// Returns the owner window (if any)
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Window* GetOwnerWindow() const noexcept { return mOwnerWindow; }

		/// <summary>
		/// Returns whether it's a standalone device or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool IsStandalone() const noexcept { return mStandalone; }

		/// <summary>
		/// Returns the swapchain (if any)
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Swapchain* GetSwapchain() const noexcept { return mSwapchain; }

		/// <summary>
		/// Returns the backend type
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual GraphicsBackend GetBackend() const noexcept = 0;

		/// <summary>
		/// Swaps the swapchain buffers
		/// </summary>
		void Swapbuffers();

		/// <summary>
		/// Creates a graphics command list
		/// </summary>
		/// <param name="desc"></param>
		/// <returns></returns>
		CommandList* CreateCommandList(const CommandListCreateDesc& desc);

		/// <summary>
		/// Creates a buffer
		/// </summary>
		/// <param name="desc"></param>
		/// <returns></returns>
		GraphicsBuffer* CreateBuffer(const GraphicsBufferCreateDesc& desc);

		/// <summary>
		/// Creates a shader
		/// </summary>
		/// <param name="desc"></param>
		/// <returns></returns>
		Shader* CreateShader(const ShaderCreateDesc& desc);

		/// <summary>
		/// Creates a texture
		/// </summary>
		/// <param name="desc"></param>
		/// <returns></returns>
		Texture* CreateTexture(const TextureCreateDesc& desc);

		/// <summary>
		/// Creates a sampler
		/// </summary>
		/// <param name="desc"></param>
		/// <returns></returns>
		Sampler* CreateSampler(const SamplerCreateDesc& desc);

		/// <summary>
		/// Creats a framebuffer
		/// </summary>
		/// <param name="desc"></param>
		/// <returns></returns>
		Framebuffer* CreateFramebuffer(const FramebufferCreateDesc& desc);

		/// <summary>
		/// Creats a graphics pipeline
		/// </summary>
		/// <param name="desc"></param>
		/// <returns></returns>
		Pipeline* CreateGraphicsPipeline(const GraphicsPipelineCreateDesc& desc);

		/// <summary>
		/// Creates a compute pipeline
		/// </summary>
		/// <param name="desc"></param>
		/// <returns></returns>
		Pipeline* CreateComputePipeline(const ComputePipelineCreateDesc& desc);

		/// <summary>
		/// Creates a resource table
		/// </summary>
		/// <param name="desc"></param>
		/// <returns></returns>
		ResourceTable* CreateResourceTable(const ResourceTableCreateDesc& desc);

		/// <summary>
		/// Creates anew fence
		/// </summary>
		/// <returns></returns>
		Fence* CreateFence();

		
		void SignalFence();

		/// <summary>
		/// Waits for the device to be come idle
		/// </summary>
		void WaitForFinish();

		/// <summary>
		/// Submits the target command list
		/// </summary>
		/// <param name="pCmdBuffer"></param>
		void SubmitCommands(CommandList* pCmdBuffer);

		/// <summary>
		/// Submits the target command lists
		/// </summary>
		/// <param name="cmdBuffers"></param>
		void SubmitCommands(const Array<CommandList*>& cmdBuffers);
	protected:
		GraphicsDevice(Window* pOwnerWindow);
		GraphicsDevice();

		/// <summary>
		/// Registers a child objectg
		/// </summary>
		/// <param name="pObject"></param>
		void RegisterChildObject(GraphicsDeviceObject* pObject);
		void SetMemory(const unsigned long long amount) { mMemory = amount; }
		virtual void SwapbuffersCore() = 0;

		virtual CommandList* CreateCommandListCore(const CommandListCreateDesc& desc) = 0;
		virtual GraphicsBuffer* CreateBufferCore(const GraphicsBufferCreateDesc& desc) = 0;
		virtual Shader* CreateShaderCore(const ShaderCreateDesc& desc) = 0;
		virtual Texture* CreateTextureCore(const TextureCreateDesc& desc) = 0;
		virtual Sampler* CreateSamplerCore(const SamplerCreateDesc& desc) = 0;
		virtual Framebuffer* CreateFramebufferCore(const FramebufferCreateDesc& desc) = 0;
		virtual Swapchain* CreateSwapchainCore(const SwapchainCreateDesc& desc) = 0;
		virtual Pipeline* CreateGraphicsPipelineCore(const GraphicsPipelineCreateDesc& desc) = 0;
		virtual Pipeline* CreateComputePipelineCore(const ComputePipelineCreateDesc& desc) = 0;
		virtual ResourceTable* CreateResourceTableCore(const ResourceTableCreateDesc& desc) = 0;
		virtual Fence* CreateFenceCore() = 0;
		virtual void WaitForFinishCore() = 0;
		virtual void SubmitCommandsCore(const Array<CommandList*>& cmdBuffers) = 0;
	private:

		/// <summary>
		/// Internal swapchain creation method
		/// </summary>
		/// <param name="desc"></param>
		void _CreateSwapchain(const SwapchainCreateDesc& desc);

		/// <summary>
		/// Deletes the target device object
		/// </summary>
		/// <param name="pObject"></param>
		void _NotifyChildObjectDestroyed(GraphicsDeviceObject* pObject);
	private:
		Array<GraphicsDeviceObject*> mChildObjects;
		PlatformCriticalSection* mChildObjectBarrier;
		Window* mOwnerWindow;
		Swapchain* mSwapchain;
		bool mStandalone;
		unsigned long long mMemory;
	};
}