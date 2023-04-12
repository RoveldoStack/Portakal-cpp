#include "InputAPI.h"

namespace Portakal
{
    InputAPI* InputAPI::sAPI = nullptr;

    Array<SharedSafeHeap<Gamepad>> InputAPI::GetGamepads()
    {
        if (sAPI == nullptr)
            return {};

        return sAPI->_GetGamepads();
    }

    SharedSafeHeap<Gamepad> InputAPI::GetDefaultGamepad()
    {
        if (sAPI == nullptr)
            return nullptr;

        return sAPI->_GetDefaultGamepad();
    }

    void InputAPI::RegisterGamepad(const SharedSafeHeap<Gamepad>& pGamepad)
    {
        if (sAPI == nullptr)
            return;

        sAPI->_RegisterGamepad(pGamepad);
    }

    void InputAPI::RemoveGamepad(const SharedSafeHeap<Gamepad>& pGamepad)
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
    SharedSafeHeap<Gamepad> InputAPI::_GetDefaultGamepad() const noexcept
    {
        if (mGamepads.GetCursor() > 0)
            return mGamepads[0];

        return nullptr;
    }
    void InputAPI::_RegisterGamepad(const SharedSafeHeap<Gamepad>& pGamepad)
    {
        mGamepads.Add(pGamepad);
    }
    void InputAPI::_RemoveGamepad(const SharedSafeHeap<Gamepad>& pGamepad)
    {
        mGamepads.Remove(pGamepad);
    }
}