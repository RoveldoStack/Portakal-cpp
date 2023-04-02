#include "SpriteCameraComponentVisualizer.h"
#include <Libs/ImGui/imgui.h>

namespace Portakal
{
	void SpriteCameraComponentVisualizer::OnInitialize()
	{
		mCamera = (SpriteCamera*)GetComponent();
	}
	void SpriteCameraComponentVisualizer::OnPaint()
	{
		
	}
	void SpriteCameraComponentVisualizer::OnFinalize()
	{

	}
}