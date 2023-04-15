#include "ImGuiKeys.h"

namespace Portakal
{
	ImGuiKey ImGuiKeys::GetKey(KeyboardKeys key)
	{
		switch (key)
		{
		case Portakal::KeyboardKeys::Unknown:
			break;
		case Portakal::KeyboardKeys::Space:
			return ImGuiKey_Space;
		case Portakal::KeyboardKeys::Apostrophe:
			return ImGuiKey_Apostrophe;
		case Portakal::KeyboardKeys::Comma:
			return ImGuiKey_Comma;
		case Portakal::KeyboardKeys::Minus:
			return ImGuiKey_Minus;
		case Portakal::KeyboardKeys::Period:
			return ImGuiKey_Period;
		case Portakal::KeyboardKeys::Slash:
			return ImGuiKey_Slash;
		case Portakal::KeyboardKeys::Num0:
		case Portakal::KeyboardKeys::Num1:
		case Portakal::KeyboardKeys::Num2:
		case Portakal::KeyboardKeys::Num3:
		case Portakal::KeyboardKeys::Num4:
		case Portakal::KeyboardKeys::Num5:
		case Portakal::KeyboardKeys::Num6:
		case Portakal::KeyboardKeys::Num7:
		case Portakal::KeyboardKeys::Num8:
		case Portakal::KeyboardKeys::Num9:
		{
			const ImGuiKey imKey = ImGuiKey_0 + ((long long)key - (long long)KeyboardKeys::Num0);
			return imKey;
		}
		case Portakal::KeyboardKeys::SemiColon:
			return ImGuiKey_Semicolon;
		case Portakal::KeyboardKeys::Equal:
			return ImGuiKey_Equal;
		case Portakal::KeyboardKeys::A:
		case Portakal::KeyboardKeys::B:
		case Portakal::KeyboardKeys::C:
		case Portakal::KeyboardKeys::D:
		case Portakal::KeyboardKeys::E:
		case Portakal::KeyboardKeys::F:
		case Portakal::KeyboardKeys::G:
		case Portakal::KeyboardKeys::H:
		case Portakal::KeyboardKeys::I:
		case Portakal::KeyboardKeys::J:
		case Portakal::KeyboardKeys::K:
		case Portakal::KeyboardKeys::L:
		case Portakal::KeyboardKeys::M:
		case Portakal::KeyboardKeys::N:
		case Portakal::KeyboardKeys::O:
		case Portakal::KeyboardKeys::P:
		case Portakal::KeyboardKeys::Q:
		case Portakal::KeyboardKeys::R:
		case Portakal::KeyboardKeys::S:
		case Portakal::KeyboardKeys::T:
		case Portakal::KeyboardKeys::U:
		case Portakal::KeyboardKeys::V:
		case Portakal::KeyboardKeys::W:
		case Portakal::KeyboardKeys::X:
		case Portakal::KeyboardKeys::Y:
		case Portakal::KeyboardKeys::Z:
		{
			const ImGuiKey imKey = ImGuiKey_A + ((long long)key - (long long)KeyboardKeys::A);
			return imKey;
		}
		case Portakal::KeyboardKeys::LeftBracket:
			return ImGuiKey_LeftBracket;
		case Portakal::KeyboardKeys::Backslash:
			return ImGuiKey_Backslash;
		case Portakal::KeyboardKeys::RightBracket:
			return ImGuiKey_RightBracket;
		case Portakal::KeyboardKeys::GraveAccent:
			return ImGuiKey_GraveAccent;
		case Portakal::KeyboardKeys::World1:
			return ImGuiKey_None;
		case Portakal::KeyboardKeys::World2:
			return ImGuiKey_None;
		case Portakal::KeyboardKeys::Escape:
			return ImGuiKey_Escape;
		case Portakal::KeyboardKeys::Enter:
			return ImGuiKey_Enter;
		case Portakal::KeyboardKeys::Tab:
			return ImGuiKey_Tab;
		case Portakal::KeyboardKeys::Backspace:
			return ImGuiKey_Backspace;
		case Portakal::KeyboardKeys::Insert:
			return ImGuiKey_Insert;
		case Portakal::KeyboardKeys::Delete:
			return ImGuiKey_Delete;
		case Portakal::KeyboardKeys::Right:
			return ImGuiKey_RightArrow;
		case Portakal::KeyboardKeys::Left:
			return ImGuiKey_LeftArrow;
		case Portakal::KeyboardKeys::Down:
			return ImGuiKey_DownArrow;
		case Portakal::KeyboardKeys::Up:
			return ImGuiKey_UpArrow;
		case Portakal::KeyboardKeys::PageUp:
			return ImGuiKey_PageUp;
		case Portakal::KeyboardKeys::PageDown:
			return ImGuiKey_PageDown;
		case Portakal::KeyboardKeys::Home:
			return ImGuiKey_Home;
		case Portakal::KeyboardKeys::End:
			return ImGuiKey_End;
		case Portakal::KeyboardKeys::CapsLock:
			return ImGuiKey_CapsLock;
		case Portakal::KeyboardKeys::ScrollLock:
			return ImGuiKey_ScrollLock;
		case Portakal::KeyboardKeys::NumLock:
			return ImGuiKey_NumLock;
		case Portakal::KeyboardKeys::PrintScreen:
			return ImGuiKey_PrintScreen;
		case Portakal::KeyboardKeys::Pause:
			return ImGuiKey_Pause;
		case Portakal::KeyboardKeys::F1:
		case Portakal::KeyboardKeys::F2:
		case Portakal::KeyboardKeys::F3:
		case Portakal::KeyboardKeys::F4:
		case Portakal::KeyboardKeys::F5:
		case Portakal::KeyboardKeys::F6:
		case Portakal::KeyboardKeys::F7:
		case Portakal::KeyboardKeys::F8:
		case Portakal::KeyboardKeys::F9:
		case Portakal::KeyboardKeys::F10:
		case Portakal::KeyboardKeys::F11:
		case Portakal::KeyboardKeys::F12:
		case Portakal::KeyboardKeys::F13:
		case Portakal::KeyboardKeys::F14:
		case Portakal::KeyboardKeys::F15:
		case Portakal::KeyboardKeys::F16:
		case Portakal::KeyboardKeys::F17:
		case Portakal::KeyboardKeys::F18:
		case Portakal::KeyboardKeys::F19:
		case Portakal::KeyboardKeys::F20:
		case Portakal::KeyboardKeys::F21:
		case Portakal::KeyboardKeys::F22:
		case Portakal::KeyboardKeys::F23:
		case Portakal::KeyboardKeys::F24:
		case Portakal::KeyboardKeys::F25:
		{
			const ImGuiKey imKey = ImGuiKey_F + ((long long)key - (long long)KeyboardKeys::F);
			return imKey;
		}
		case Portakal::KeyboardKeys::Kp0:
		case Portakal::KeyboardKeys::Kp1:
		case Portakal::KeyboardKeys::Kp2:
		case Portakal::KeyboardKeys::Kp3:
		case Portakal::KeyboardKeys::Kp4:
		case Portakal::KeyboardKeys::Kp5:
		case Portakal::KeyboardKeys::Kp6:
		case Portakal::KeyboardKeys::Kp7:
		case Portakal::KeyboardKeys::Kp8:
		case Portakal::KeyboardKeys::Kp9:
		{
			const ImGuiKey imKey = ImGuiKey_Keypad0 + ((long long)key - (long long)KeyboardKeys::Kp0);
			return imKey;
		}
		case Portakal::KeyboardKeys::KpDecimal:
			return ImGuiKey_KeypadDecimal;
		case Portakal::KeyboardKeys::KpDivide:
			return ImGuiKey_KeypadDivide;
		case Portakal::KeyboardKeys::KpMultiply:
			return ImGuiKey_KeypadMultiply;
		case Portakal::KeyboardKeys::KpSubtract:
			return ImGuiKey_KeypadSubtract;
		case Portakal::KeyboardKeys::KpAdd:
			return ImGuiKey_KeypadAdd;
		case Portakal::KeyboardKeys::KpEnter:
			return ImGuiKey_KeypadEnter;
		case Portakal::KeyboardKeys::KpEqual:
			return ImGuiKey_KeypadEqual;
		case Portakal::KeyboardKeys::LeftShift:
			return ImGuiKey_LeftShift;
		case Portakal::KeyboardKeys::LeftControl:
			return ImGuiKey_LeftCtrl;
		case Portakal::KeyboardKeys::LeftAlt:
			return ImGuiKey_LeftAlt;
		case Portakal::KeyboardKeys::LeftSuper:
			return ImGuiKey_LeftSuper;
		case Portakal::KeyboardKeys::RightShift:
			return ImGuiKey_RightShift;
		case Portakal::KeyboardKeys::RightControl:
			return ImGuiKey_RightCtrl;
		case Portakal::KeyboardKeys::RightAlt:
			return ImGuiKey_RightAlt;
		case Portakal::KeyboardKeys::RightSuper:
			return ImGuiKey_RightSuper;
		case Portakal::KeyboardKeys::Menu:
			return ImGuiKey_Menu;
		default:
			return ImGuiKey_None;
			break;
		}
	}
}