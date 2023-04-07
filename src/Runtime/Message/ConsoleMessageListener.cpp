#include "ConsoleMessageListener.h"
#include <Runtime/Log/Log.h>

namespace Portakal
{
    void ConsoleMessageListener::OnInfoRecieved(const String& message)
    {
        LOG("ConsoleMessage", *message);
    }
    void ConsoleMessageListener::OnWarningRecieved(const String& message)
    {

    }
    void ConsoleMessageListener::OnErrorRecieved(const String& message)
    {

    }
}