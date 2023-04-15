#pragma once
#include <Runtime/World/Component.h>
#include <Runtime/World/Components/TestEnum.h>
#include <Runtime/World/Components/TestStruct.h>
#include <Runtime/Math/Color4.h>

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

		FIELD();
		TestEnum myEnum;

		FIELD();
		TestStruct someTestStruct;

		FIELD();
		ColorRgbaF myColor;
	private:


		// Inherited via Component
		virtual void DestroyCore() override;

		virtual void OnInitialize() override;

		virtual void OnFinalize() override;
	};
#include "TestComponent.reflect.h"
}