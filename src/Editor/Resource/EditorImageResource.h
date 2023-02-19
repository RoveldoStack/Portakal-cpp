#pragma once
#include <Editor/Resource/EditorResource.h>

namespace Portakal
{
	class GraphicsDevice;
	class TextureResource;

	/// <summary>
	/// Editor resource specialized in images
	/// </summary>
	class PORTAKAL_API EditorImageResource : public EditorResource
	{
	public:
		EditorImageResource(const String& path, const String& name);
		virtual ~EditorImageResource() override;

		/// <summary>
		/// Returns the texture resource of the image
		/// </summary>
		/// <returns></returns>
		FORCEINLINE TextureResource* GetTexture() const noexcept { return mResource; }
	private:
		TextureResource* mResource;
	};
}