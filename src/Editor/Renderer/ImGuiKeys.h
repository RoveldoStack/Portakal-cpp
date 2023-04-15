#pragma once
#include <Runtime/Core/Core.h>
#include <Libs/ImGui/imgui.h>
#include <Runtime/Input/KeyboardKeys.h>


namespace Portakal
{
	class PORTAKAL_API ImGuiKeys
	{
	public:
		static ImGuiKey GetKey(const KeyboardKeys key);
	public:
		ImGuiKeys() = delete;
		~ImGuiKeys() = delete;

	};
}