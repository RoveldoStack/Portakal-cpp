#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	class TextureResource;
	class ResourceTable;
	class PORTAKAL_API ImGuiTextureBinding
	{
	public:
		ImGuiTextureBinding(const TextureResource* pTexture);
		~ImGuiTextureBinding();

		FORCEINLINE const TextureResource* GetTargetTexture() const noexcept { return mTargetTexture; }
		FORCEINLINE const ResourceTable* GetTable() const noexcept { return mTable; }
		FORCEINLINE virtual void* GetBinding() const noexcept = 0;
	private:
		const TextureResource* mTargetTexture;
		ResourceTable* mTable;
	};
}