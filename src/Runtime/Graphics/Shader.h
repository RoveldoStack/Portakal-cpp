#pragma once
#include <Runtime/Graphics/GraphicsDeviceObject.h>
#include <Runtime/Graphics/ShaderCreateDesc.h>

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
		FORCEINLINE String GetSource() const noexcept { return mSource; }

		FORCEINLINE virtual GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override final { return GraphicsDeviceObjectType::Shader; }
	protected:
		Shader(const ShaderCreateDesc& desc) : mStage(desc.Stage), mEntryPointMethod(desc.EntryPointMethod), mSource(desc.Source) {}
		~Shader() = default;
	private:
		const ShaderStage mStage;
		const String mEntryPointMethod;
		const String mSource;
	};
}