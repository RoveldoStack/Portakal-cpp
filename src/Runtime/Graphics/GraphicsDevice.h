#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/GraphicsBackend.h>

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

	class PORTAKAL_API GraphicsDevice
	{
	public:
		static GraphicsDevice* CreateStandalone(const StandaloneGraphicsDeviceCreateDesc& desc);
		static GraphicsDevice* CreateWindowed(const WindowedGraphicsDeviceCreateDesc& desc);
	public:
		virtual ~GraphicsDevice();
		void Swapbuffers();

		CommandList* CreateGraphicsCommandList(const CommandListCreateDesc& desc);
		GraphicsBuffer* CreateBuffer(const GraphicsBufferCreateDesc& desc);
		Shader* CreateShader(const ShaderCreateDesc& desc);
		Texture* CreateTexture(const TextureCreateDesc& desc);
		Sampler* CreateSampler(const SamplerCreateDesc& desc);
		Framebuffer* CreateFramebuffer(const FramebufferCreateDesc& desc);
		Pipeline* CreateGraphicsPipeline(const GraphicsPipelineCreateDesc& desc);
		Pipeline* CreateComputePipeline(const ComputePipelineCreateDesc& desc);
		ResourceTable* CreateResourceTable(const ResourceTableCreateDesc& desc);


		void UpdateBuffer(GraphicsBuffer* pBuffer, const GraphicsBufferUpdateDesc& desc);

		void WaitForFinish();
		void SubmitCommands(CommandList* pCmdBuffer);
		void SubmitCommands(const Array<CommandList*>& cmdBuffers);
		void DeleteChildObject(GraphicsDeviceObject* pObject);

		FORCEINLINE Window* GetOwnerWindow() const noexcept { return _ownerWindow; }
		FORCEINLINE bool IsStandalone() const noexcept { return _standalone; }
		FORCEINLINE Swapchain* GetSwapchain() const noexcept { return mSwapchain; }

		FORCEINLINE virtual GraphicsBackend GetBackend() const noexcept = 0;
	protected:
		GraphicsDevice(Window* pOwnerWindow);
		GraphicsDevice();

		void RegisterChildObject(GraphicsDeviceObject* pObject);

		virtual void SwapbuffersCore() = 0;

		virtual CommandList* CreateGraphicsCommandListCore(const CommandListCreateDesc& desc) = 0;
		virtual GraphicsBuffer* CreateBufferCore(const GraphicsBufferCreateDesc& desc) = 0;
		virtual Shader* CreateShaderCore(const ShaderCreateDesc& desc) = 0;
		virtual Texture* CreateTextureCore(const TextureCreateDesc& desc) = 0;
		virtual Sampler* CreateSamplerCore(const SamplerCreateDesc& desc) = 0;
		virtual Framebuffer* CreateFramebufferCore(const FramebufferCreateDesc& desc) = 0;
		virtual Swapchain* CreateSwapchainCore(const SwapchainCreateDesc& desc) = 0;
		virtual Pipeline* CreateGraphicsPipelineCore(const GraphicsPipelineCreateDesc& desc) = 0;
		virtual Pipeline* CreateComputePipelineCore(const ComputePipelineCreateDesc& desc) = 0;
		virtual ResourceTable* CreateResourceTableCore(const ResourceTableCreateDesc& desc) = 0;

		virtual void UpdateBufferCore(GraphicsBuffer* pBuffer, const GraphicsBufferUpdateDesc& desc) = 0;

		virtual void WaitForFinishCore() = 0;
		virtual void SubmitCommandsCore(const Array<CommandList*>& cmdBuffers) = 0;
	private:
		void CreateSwapchain(const SwapchainCreateDesc& desc);
	private:
		Array<GraphicsDeviceObject*> _childObjects;
		Window* _ownerWindow;
		Swapchain* mSwapchain;
		bool _standalone;
	};
}