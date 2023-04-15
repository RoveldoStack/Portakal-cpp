#pragma once
#include <Runtime/Resource/ResourceSubObject.h>
#include <Runtime/Graphics/Shader.h>

namespace Portakal
{
	class PORTAKAL_API ShaderObject : public ResourceSubObject
	{
		GENERATE_CLASS(ShaderObject);
	public:
		ShaderObject();
		~ShaderObject();

		FORCEINLINE bool IsCompiled() const noexcept;
		FORCEINLINE String GetSource() const noexcept;
		FORCEINLINE String GetError() const noexcept;
		FORCEINLINE String GetEntryPoint() const noexcept;
		FORCEINLINE ShaderStage GetStage() const noexcept;
		FORCEINLINE Shader* GetShader() const noexcept { return mShader; }

		void Compile(const String& entryPoint,const String& source,const ShaderStage stage);
	private:
		void Delete();
		virtual void DestroyCore() override;
	private:
		GraphicsDevice* mDevice;
		Shader* mShader;

	};

#include "ShaderObject.reflect.h"
}