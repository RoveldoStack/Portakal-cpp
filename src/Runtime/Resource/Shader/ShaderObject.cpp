#include "ShaderObject.h"
#include <Runtime/Graphics/GraphicsDeviceAPI.h>

namespace Portakal
{
	ShaderObject::ShaderObject()
	{
		mDevice = GraphicsDeviceAPI::GetDefaultDevice();
		mShader = nullptr;
	}
	ShaderObject::~ShaderObject()
	{
		
	}
	bool ShaderObject::IsCompiled() const noexcept
	{
		if (mShader == nullptr)
			return false;

		return true;
	}
	String ShaderObject::GetSource() const noexcept
	{
		if (mShader == nullptr)
			return "";

		return mShader->GetSource();
	}
	ShaderStage ShaderObject::GetStage() const noexcept
	{
		if (mShader == nullptr)
			return ShaderStage::None;

		return mShader->GetStage();
	}
	
	void ShaderObject::Compile(const String& entryPoint, const String& source, const ShaderStage stage)
	{
		Delete();

		ShaderCreateDesc desc = {};
		desc.Source = source;
		desc.EntryPointMethod = entryPoint;
		desc.Stage = stage;

		mShader = mDevice->CreateShader(desc);
	}
	void ShaderObject::Delete()
	{
		if (mShader == nullptr)
			return;

		mShader->DeleteDeviceObject();
		mShader = nullptr;
		mDevice = nullptr;
	}
	void ShaderObject::DestroyCore()
	{
		Delete();
	}
}