#include "ShaderResource.h"
#include <Runtime/Graphics/GraphicsDeviceAPI.h>
#include <Runtime/HLSL/HLSLCompiler.h>

namespace Portakal
{
	ShaderResource::ShaderResource()
	{
		mDevice = GraphicsDeviceAPI::GetDefaultDevice();
		mShader = nullptr;
		mReflectionBlob = nullptr;
	}
	ShaderResource::~ShaderResource()
	{
		
	}
	bool ShaderResource::IsCompiled() const noexcept
	{
		if (mShader == nullptr)
			return false;

		return true;
	}
	String ShaderResource::GetEntryPoint() const noexcept
	{
		if (mShader == nullptr)
			return String();

		return mShader->GetEntryPointMethod();
	}
	ShaderStage ShaderResource::GetStage() const noexcept
	{
		if (mShader == nullptr)
			return ShaderStage::None;

		return mShader->GetStage();
	}
	
	void ShaderResource::Compile(const String& entryPoint, const String& source, const ShaderStage stage)
	{
		/*
		* Delete the former shader
		*/
		Delete();

		/*
		* Compile the source text
		*/
		ByteBlock bytes;
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
		
		/*
		* Invoke event
		*/
		mOnCompiledEvent.Invoke(this);
	}
	void ShaderResource::RegisterOnCompiledEvent(const Delegate<void, ShaderResource*>& del)
	{
		if (IsDestroyed())
			return;

		mOnCompiledEvent += del;
	}
	void ShaderResource::RemoveOnCompiledEvent(const Delegate<void, ShaderResource*>& del)
	{
		if (IsDestroyed())
			return;

		mOnCompiledEvent += del;
	}
	void ShaderResource::Delete()
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
	void ShaderResource::DestroyCore()
	{
		/*
		* Clear the invocation list
		*/
		mOnCompiledEvent.Clear();

		/*
		* Delete the shader
		*/
		Delete();
	}
}