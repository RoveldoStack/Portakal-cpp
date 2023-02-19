#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Message/MessageType.h>

namespace Portakal
{
	/// <summary>
	/// The general message interface
	/// </summary>
	class PORTAKAL_API IMessage
	{
	public:
		/// <summary>
		/// Returns the message text
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual String GetMessage() const noexcept = 0;

		/// <summary>
		/// Returns the message type
		/// </summary>
		/// <returns></returns>
		FORCEINLINE MessageType GetMessageType() const noexcept = 0;
	};
}