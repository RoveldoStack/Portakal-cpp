#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/String.h>
#include <Runtime/Graphics/Shader/ShaderReflectionEntry.h>
#include <Runtime/Graphics/Shader/ShadingLanguage.h>

namespace Portakal
{
	class PORTAKAL_API ShaderReflectionBlob
	{
	public:
		static ShaderReflectionBlob* Create(const String& source, const ShadingLanguage language);
	public:
		ShaderReflectionBlob() = default;
		~ShaderReflectionBlob() = default;

		FORCEINLINE virtual ShadingLanguage GetLanguage() const noexcept = 0;
		FORCEINLINE Array<ShaderReflectionEntry> GetEntries() const noexcept { return mEntries; }
	protected:
		void SetReflectionData(const Array<ShaderReflectionEntry>& entries) { mEntries = entries; }
	private:
		Array<ShaderReflectionEntry> mEntries;
	};
}