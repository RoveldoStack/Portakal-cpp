#include "DefaultComponentVisualizer.h"
#include <Libs/ImGui/imgui.h>

namespace Portakal
{
	void DefaultComponentVisualizer::OnInitialize()
	{

	}
	void DefaultComponentVisualizer::OnFinalize()
	{

	}
	void DefaultComponentVisualizer::OnPaint()
	{
		ImGui::Text("DEFAULT COMPONENT VISUALIZER");
	}
}