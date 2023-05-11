#pragma once
#include <Runtime/Resource/ResourceSubObject.h>
#include <Runtime/Graphics/Shader/Shader.h>
#include <Runtime/Event/Event.h>

namespace Portakal
{
	PCLASS();
	class PORTAKAL_API ShaderResource : public ResourceSubObject
	{
		GENERATE_CLASS(ShaderResource);
	public:
		ShaderResource();
		~ShaderResource();

		FORCEINLINE bool IsCompiled() const noexcept;
		FORCEINLINE String GetSource() const noexcept { return mSource; }
		FORCEINLINE String GetError() const noexcept { return mErrors; }
		FORCEINLINE String GetEntryPoint() const noexcept;
		FORCEINLINE ShaderStage GetStage() const noexcept;
		FORCEINLINE Shader* GetShader() const noexcept { return mShader; }
		FORCEINLINE const ShaderReflectionBlob* GetReflectionBlob() const noexcept { return mReflectionBlob; }

		void Compile(const String& entryPoint,const String& source,const ShaderStage stage);
		void RegisterOnCompiledEvent(const Delegate<void, ShaderResource*>& del);
		void RemoveOnCompiledEvent(const Delegate<void, ShaderResource*>& del);
	private:
		void Delete();
		virtual void DestroyCore() override;
	private:
		Event<void, ShaderResource*> mOnCompiledEvent;
		ShaderReflectionBlob* mReflectionBlob;
		GraphicsDevice* mDevice;
		Shader* mShader;
		String mSource;
		String mErrors;
		bool mCompiled;

	};

#include "ShaderResource.reflect.h"
}