#include "EditorComponentVisualizer.h"
#include <Runtime/Reflection/Reflection.h>
#include <Libs/ImGui/imgui.h>
#include <Editor/GUI/GUIDefaultVisualizer.h>
#include <Runtime/World/Component.h>

namespace Portakal
{
	void EditorComponentVisualizer::DrawDefault()
	{
		GUIDefaultVisualizer::DrawDefaultObject(GetComponent());
	}
}