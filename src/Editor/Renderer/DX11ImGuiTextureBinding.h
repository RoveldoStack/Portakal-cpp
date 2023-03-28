#include <Editor/Renderer/ImGuiTextureBinding.h>

namespace Portakal
{
	class PORTAKAL_API DX11ImGuiTextureBinding : public ImGuiTextureBinding
	{
	public:
		DX11ImGuiTextureBinding(const TextureResource* pResource);
		~DX11ImGuiTextureBinding();

		virtual void* GetBinding() const noexcept override;
	private:
	};
}