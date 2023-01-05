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
		FORCEINLINE ShaderStage GetStage() const noexcept { return _stage; }
		FORCEINLINE String GetEntryPoint() const noexcept { return _entryPoint; }
		FORCEINLINE String GetSource() const noexcept { return _source; }

		FORCEINLINE virtual GraphicsDeviceObjectType GetDeviceObjectType() const noexcept override final { return GraphicsDeviceObjectType::Shader; }
	protected:
		Shader(const ShaderCreateDesc& desc) : _stage(desc.Stage), _entryPoint(desc.EntryPoint), _source(desc.Source) {}
		virtual ~Shader() {}

	private:
		const ShaderStage _stage;
		const String _entryPoint;
		const String _source;
	};
}