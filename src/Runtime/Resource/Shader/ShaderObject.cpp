#include "ShaderObject.h"
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/HLSL/HLSLCompiler.h>

namespace Portakal
{
	ShaderObject::ShaderObject()
	{
		mDevice = GraphicsDeviceAPI::GetDefaultDevice();
		mShader = nullptr;
		mReflectionBlob = nullptr;
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
	String ShaderObject::GetEntryPoint() const noexcept
	{
		if (mShader == nullptr)
			return String();

		return mShader->GetEntryPointMethod();
	}
	ShaderStage ShaderObject::GetStage() const noexcept
	{
		if (mShader == nullptr)
			return ShaderStage::None;

		return mShader->GetStage();
	}
	
	void ShaderObject::Compile(const String& entryPoint, const String& source, const ShaderStage stage)
	{
		/*
		* Delete the former shader
		*/
		Delete();

		/*
		* Compile the source text
		*/
		Array<Byte> bytes;
		HLSLCompiler::Compile(source, entryPoint, stage, 4, 0,bytes, mErrors);

		/*
		* Validate compilation
		*/
		if (mErrors.GetCursor() > 0)
			return;

		/*
		* Create reflection blob
		*/
		mReflectionBlob = ShaderReflectionBlob::Create(source, ShadingLanguage::HLSL);

		/*
		* Create shader
		*/
		ShaderCreateDesc desc = {};
		desc.EntryPointMethod = entryPoint;
		desc.Stage = stage;
		desc.Bytes = bytes;

		mShader = mDevice->CreateShader(desc);
		mSource = source;
		mCompiled = true;
		
	}
	void ShaderObject::Delete()
	{
		if (mShader == nullptr)
			return;

		mShader->Destroy();
		mShader = nullptr;
		mSource = String();

		if (mReflectionBlob != nullptr)
		{
			delete mReflectionBlob;
			mReflectionBlob = nullptr;
		}
	}
	void ShaderObject::DestroyCore()
	{
		Delete();
	}
}