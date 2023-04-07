#pragma once
#include <Runtime/World/Component.h>

namespace Portakal
{
	class PORTAKAL_API TestComponent : public Component
	{
		GENERATE_CLASS(TestComponent);
	public:

		FIELD();
		int int0;
		FIELD();
		int int1;
		FIELD();
		int int3;
	private:


		// Inherited via Component
		virtual void DestroyCore() override;

		virtual void OnInitialize() override;

		virtual void OnFinalize() override;
	};
#include "TestComponent.reflect.h"
}