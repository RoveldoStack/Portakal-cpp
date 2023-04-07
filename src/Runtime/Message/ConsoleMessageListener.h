#pragma once
#include <Runtime/Message/IMessageListener.h>

namespace Portakal
{
	/// <summary>
	/// Console message listener implementation
	/// </summary>
	class PORTAKAL_API ConsoleMessageListener : public IMessageListener
	{
	public:


		// Inherited via IMessageListener
		virtual void OnInfoRecieved(const String& message) override;

		virtual void OnWarningRecieved(const String& message) override;

		virtual void OnErrorRecieved(const String& message) override;

	};
}