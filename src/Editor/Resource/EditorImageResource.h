#pragma once
#include <Editor/Resource/EditorResource.h>

namespace Portakal
{
	class GraphicsDevice;
	class TextureResource;
	class ImGuiTextureBinding;

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

		/// <summary>
		/// Returns the imgui texture binding 
		/// </summary>
		/// <returns></returns>
		FORCEINLINE ImGuiTextureBinding* GetImGuiTexture() const noexcept { return mBinding; }
	private:
		TextureResource* mResource;
		ImGuiTextureBinding* mBinding;
	};
}