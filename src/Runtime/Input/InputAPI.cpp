#include "InputAPI.h"

namespace Portakal
{
    InputAPI* InputAPI::sAPI = nullptr;

    Array<Gamepad*> InputAPI::GetGamepads()
    {
        if (sAPI == nullptr)
            return {};

        return sAPI->_GetGamepads();
    }

    Gamepad* InputAPI::GetDefaultGamepad()
    {
        if (sAPI == nullptr)
            return nullptr;

        return sAPI->_GetDefaultGamepad();
    }

    void InputAPI::RegisterGamepad(Gamepad* pGamepad)
    {
        if (sAPI == nullptr)
            return;

        sAPI->_RegisterGamepad(pGamepad);
    }

    void InputAPI::RemoveGamepad(Gamepad* pGamepad)
    {
        if (sAPI == nullptr)
            return;

        sAPI->_RemoveGamepad(pGamepad);
    }

    InputAPI::InputAPI()
    {
        sAPI = this;
    }
    InputAPI::~InputAPI()
    {
        sAPI = nullptr;
    }
}