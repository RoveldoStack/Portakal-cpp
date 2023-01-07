#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/GraphicsBackend.h>

namespace Portakal
{
	class GraphicsDeviceObject;
	class Window;

	class CommandBuffer;
	struct CommandBufferCreateDesc;

	class GraphicsBuffer;
	struct GraphicsBufferCreateDesc;
	struct GraphicsBufferUpdateDesc;

	class Texture;
	struct TextureCreateDesc;
	struct TextureUpdateDesc;

	class Framebuffer;
	class SwapchainFramebuffer;
	struct FramebufferCreateDesc;
	struct SwapchainFramebufferCreateDesc;

	class Pipeline;
	struct GraphicsPipelineCreateDesc;
	struct ComputePipelineCreateDesc;

	class Shader;
	struct ShaderCreateDesc;

	class Sampler;
	struct SamplerCreateDesc;

	class GraphicsResourceTable;
	struct GraphicsResourceTableCreateDesc;

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

		CommandBuffer* CreateCommandBuffer(const CommandBufferCreateDesc& desc);
		GraphicsBuffer* CreateBuffer(const GraphicsBufferCreateDesc& desc);
		Shader* CreateShader(const ShaderCreateDesc& desc);
		Texture* CreateTexture(const TextureCreateDesc& desc);
		Sampler* CreateSampler(const SamplerCreateDesc& desc);
		Framebuffer* CreateFramebuffer(const FramebufferCreateDesc& desc);
		Pipeline* CreateGraphicsPipeline(const GraphicsPipelineCreateDesc& desc);
		Pipeline* CreateComputePipeline(const ComputePipelineCreateDesc& desc);
		GraphicsResourceTable* CreateResourceTable(const GraphicsResourceTableCreateDesc& desc);


		void UpdateBuffer(GraphicsBuffer* pBuffer, const GraphicsBufferUpdateDesc& desc);

		void WaitForFinish();
		void SubmitCommands(CommandBuffer* pCmdBuffer);
		void SubmitCommands(const Array<CommandBuffer*>& cmdBuffers);
		void DeleteChildObject(GraphicsDeviceObject* pObject);

		FORCEINLINE Window* GetOwnerWindow() const noexcept { return _ownerWindow; }
		FORCEINLINE bool IsStandalone() const noexcept { return _standalone; }
		FORCEINLINE Framebuffer* GetSwapchainFramebuffer() const noexcept { return _swapchainFramebuffer; }

		FORCEINLINE virtual GraphicsBackend GetBackend() const noexcept = 0;
	protected:
		GraphicsDevice(Window* pOwnerWindow);
		GraphicsDevice();

		void RegisterChildObject(GraphicsDeviceObject* pObject);

		virtual void SwapbuffersCore() = 0;

		virtual CommandBuffer* CreateCommandBufferCore(const CommandBufferCreateDesc& desc) = 0;
		virtual GraphicsBuffer* CreateBufferCore(const GraphicsBufferCreateDesc& desc) = 0;
		virtual Shader* CreateShaderCore(const ShaderCreateDesc& desc) = 0;
		virtual Texture* CreateTextureCore(const TextureCreateDesc& desc) = 0;
		virtual Sampler* CreateSamplerCore(const SamplerCreateDesc& desc) = 0;
		virtual Framebuffer* CreateFramebufferCore(const FramebufferCreateDesc& desc) = 0;
		virtual Framebuffer* CreateSwapchainFramebufferCore(const SwapchainFramebufferCreateDesc& desc) = 0;
		virtual Pipeline* CreateGraphicsPipelineCore(const GraphicsPipelineCreateDesc& desc) = 0;
		virtual Pipeline* CreateComputePipelineCore(const ComputePipelineCreateDesc& desc) = 0;
		virtual GraphicsResourceTable* CreateResourceTableCore(const GraphicsResourceTableCreateDesc& desc) = 0;

		virtual void UpdateBufferCore(GraphicsBuffer* pBuffer, const GraphicsBufferUpdateDesc& desc) = 0;

		virtual void WaitForFinishCore() = 0;
		virtual void SubmitCommandsCore(const Array<CommandBuffer*>& cmdBuffers) = 0;
	private:
		void CreateSwapchainFramebuffer(const SwapchainFramebufferCreateDesc& desc);
	private:
		Array<GraphicsDeviceObject*> _childObjects;
		Window* _ownerWindow;
		Framebuffer* _swapchainFramebuffer;
		bool _standalone;
	};
}