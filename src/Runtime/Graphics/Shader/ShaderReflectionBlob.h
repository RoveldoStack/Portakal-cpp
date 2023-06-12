#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Graphics/Shader/ShaderReflectionResource.h>
#include <Runtime/Graphics/Shader/ShaderReflectionData.h>
#include <Runtime/Memory/ByteBlock.h>
#include <Runtime/Graphics/GraphicsBackend.h>
namespace Portakal
{
	class PORTAKAL_API ShaderReflectionBlob
	{
	public:
		static ShaderReflectionBlob* Create(const ByteBlock& byteBlock,const GraphicsBackend backend);
	public:
		ShaderReflectionBlob() = default;
		~ShaderReflectionBlob() = default;

		FORCEINLINE Array<ShaderReflectionResource> GetResources() const noexcept { return mData.Resources; }
	protected:
		void SetReflectionData(const ShaderReflectionData& data) { mData = data; }
	private:
		Array<ShaderReflectionResource> mResources;
		ShaderReflectionData mData;
	};
}