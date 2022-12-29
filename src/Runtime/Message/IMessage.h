#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Message/MessageType.h>

namespace Portakal
{
	class PORTAKAL_API IMessage
	{
	public:
		FORCEINLINE virtual String GetMessage() const noexcept = 0;
		FORCEINLINE MessageType GetMessageType() const noexcept = 0;
	};
}