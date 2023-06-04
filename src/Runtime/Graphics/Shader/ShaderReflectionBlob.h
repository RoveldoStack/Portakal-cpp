#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Graphics/Shader/ShaderReflectionResource.h>
#include <Runtime/Memory/ByteBlock.h>

namespace Portakal
{
	class PORTAKAL_API ShaderReflectionBlob
	{
	public:
		static ShaderReflectionBlob* Create(const ByteBlock& byteBlock);
	public:
		ShaderReflectionBlob() = default;
		~ShaderReflectionBlob() = default;

		FORCEINLINE Array<ShaderReflectionResource> GetResources() const noexcept { return mResources; }
	protected:
		void SetReflectionData(const Array<ShaderReflectionResource>& resources) { mResources = resources; }
	private:
		Array<ShaderReflectionResource> mResources;
	};
}