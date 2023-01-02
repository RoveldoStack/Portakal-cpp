#include "ConsoleMessageListener.h"
#include <Runtime/Log/Log.h>

namespace Portakal
{
    void ConsoleMessageListener::OnMessageReceived(const String& message, const MessageType type)
    {
        LOG("ConsoleMessage", *message);
    }
}