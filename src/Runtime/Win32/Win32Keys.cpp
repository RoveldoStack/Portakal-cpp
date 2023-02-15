#include "Win32Keys.h"
#include <winuser.rh>

namespace Portakal
{
	unsigned int Win32Keys::GetKey(const unsigned int vk_key)
	{
        switch (vk_key)
        {
            case VK_TAB:
                return PORTAKAL_KEY_TAB;
            case VK_INSERT:
                return PORTAKAL_KEY_INSERT;
            case VK_DELETE:
                return PORTAKAL_KEY_DELETE;
            case VK_BACK:
                return PORTAKAL_KEY_BACKSPACE;
            case VK_SPACE:
                return PORTAKAL_KEY_SPACE;
            case VK_RETURN:
                return PORTAKAL_KEY_BACKSPACE;
            case VK_ESCAPE:
                return PORTAKAL_KEY_ESCAPE;
            case VK_CONTROL:
                return PORTAKAL_KEY_LEFT_CONTROL;
            case VK_LSHIFT:
                return PORTAKAL_KEY_LEFT_SHIFT;
            case VK_RSHIFT:
                return PORTAKAL_KEY_LEFT_SHIFT;
            case VK_CAPITAL:
                return PORTAKAL_KEY_CAPS_LOCK;
            default:
                return 0;
        }
	}
}