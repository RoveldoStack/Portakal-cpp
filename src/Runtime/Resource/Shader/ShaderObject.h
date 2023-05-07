#pragma once
#include <Runtime/Resource/ResourceSubObject.h>
#include <Runtime/Graphics/Shader/Shader.h>

namespace Portakal
{
	PCLASS();
	class PORTAKAL_API ShaderObject : public ResourceSubObject
	{
		GENERATE_CLASS(ShaderObject);
	public:
		ShaderObject();
		~ShaderObject();

		FORCEINLINE bool IsCompiled() const noexcept;
		FORCEINLINE String GetSource() const noexcept { return mSource; }
		FORCEINLINE String GetError() const noexcept { return mErrors; }
		FORCEINLINE String GetEntryPoint() const noexcept;
		FORCEINLINE ShaderStage GetStage() const noexcept;
		FORCEINLINE Shader* GetShader() const noexcept { return mShader; }
		FORCEINLINE const ShaderReflectionBlob* GetReflectionBlob() const noexcept { return mReflectionBlob; }

		void Compile(const String& entryPoint,const String& source,const ShaderStage stage);
	private:
		void Delete();
		virtual void DestroyCore() override;
	private:
		ShaderReflectionBlob* mReflectionBlob;
		GraphicsDevice* mDevice;
		Shader* mShader;
		String mSource;
		String mErrors;
		bool mCompiled;

	};

#include "ShaderObject.reflect.h"
}