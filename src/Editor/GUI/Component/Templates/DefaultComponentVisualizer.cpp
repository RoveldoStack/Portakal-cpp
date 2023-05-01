#include "DefaultComponentVisualizer.h"
#include <Runtime/World/Component.h>
#include <Libs/ImGui/imgui.h>
#include <Runtime/Memory/Memory.h>
#include <Runtime/Math/Color4.h>
#include <Editor/GUI/Window/Templates/WorldObserverWindow.h>
#include <Runtime/World/Entity.h>
#include <Editor/Renderer/GUICommands.h>

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
		DrawDefault();
	}
}