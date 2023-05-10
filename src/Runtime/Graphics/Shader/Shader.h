#pragma once
#include <Runtime/Graphics/GraphicsDeviceObject.h>
#include <Runtime/Graphics/Shader/ShaderCreateDesc.h>
#include <Runtime/Graphics/Shader/ShaderReflectionBlob.h>
#include <Runtime/Memory/ByteBlock.h>

namespace Portakal
{
	/// <summary>
	/// Represents a single shader program
	/// </summary>
	class PORTAKAL_API Shader : public GraphicsDeviceObject
	{
	public:
		/// <summary>
		/// Returns the shader stage
		/// </summary>
		/// <returns></returns>
		FORCEINLINE ShaderStage GetStage() const noexcept { return mStage; }

		/// <summary>
		/// Returns the entry point method name
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String GetEntryPointMethod() const noexcept { return mEntryPointMethod; }

		/// <summary>
		/// Returns the shader source in text
		/// </summary>
		/// <returns></returns>
		FORCEINLINE ByteBlock GetBytes() const noexcept { return mBytes; }

		FORCEINLINE virtual GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override final { return GraphicsDeviceObjectType::Shader; }
	protected:
		Shader(const ShaderCreateDesc& desc) : mStage(desc.Stage), mEntryPointMethod(desc.EntryPointMethod), mBytes(desc.Bytes) {}
		~Shader() = default;
	private:
		const ShaderStage mStage;
		const String mEntryPointMethod;
		const ByteBlock mBytes;
	};
}