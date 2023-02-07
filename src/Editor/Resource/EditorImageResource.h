#pragma once
#include <Editor/Resource/EditorResource.h>

namespace Portakal
{
	class GraphicsDevice;
	class TextureResource;
	class PORTAKAL_API EditorImageResource : public EditorResource
	{
	public:
		EditorImageResource(const String& path, const String& name);
		virtual ~EditorImageResource() override;

		FORCEINLINE TextureResource* GetTexture() const noexcept { return mResource; }
	private:
		TextureResource* mResource;
	};
}