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

	START_GENERATE_TYPE(ShaderObject);
	START_TYPE_PROPERTIES(ShaderObject);
	REGISTER_BASE_TYPE(ResourceSubObject);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(ShaderObject);
	END_GENERATE_TYPE(ShaderObject);
}