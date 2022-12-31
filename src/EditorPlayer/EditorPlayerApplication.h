#pragma once
#include <Runtime/Application/Application.h>

namespace Portakal
{
	class PORTAKAL_API EditorPlayerApplication : public Application
	{
	public:
		virtual void RunCore() override;
	};
}