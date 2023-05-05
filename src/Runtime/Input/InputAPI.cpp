#include "InputAPI.h"

namespace Portakal
{
    Array<Gamepad*> InputAPI::GetGamepads()
    {
        InputAPI* pAPI = GetUnderlyingAPI();
        if (pAPI == nullptr)
            return {};

        return pAPI->mGamepads;
    }

    Gamepad* InputAPI::GetDefaultGamepad()
    {
        InputAPI* pAPI = GetUnderlyingAPI();
        if (pAPI == nullptr)
            return nullptr;

        if (pAPI->mGamepads.GetCursor() > 0)
            return pAPI->mGamepads[0];

        return nullptr;
    }

    void InputAPI::RegisterGamepad(Gamepad* pGamepad)
    {
        InputAPI* pAPI = GetUnderlyingAPI();
        if (pAPI == nullptr)
            return;

        pAPI->mGamepads.Add(pGamepad);
    }

    void InputAPI::RemoveGamepad(Gamepad* pGamepad)
    {
        InputAPI* pAPI = GetUnderlyingAPI();
        if (pAPI == nullptr)
            return;

        pAPI->mGamepads.Remove(pGamepad);
    }

    InputAPI::InputAPI()
    {

    }
    InputAPI::~InputAPI()
    {

    }
}