#include "InputAPI.h"

namespace Portakal
{
    InputAPI* InputAPI::sAPI = nullptr;

    InputAPI::InputAPI()
    {
        sAPI = this;
    }
    InputAPI::~InputAPI()
    {
        sAPI = nullptr;
    }
}