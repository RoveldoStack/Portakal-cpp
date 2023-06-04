#pragma once
#include <Runtime/Reflection/Reflection.h>
#include <Runtime/World/Component.h>
#include <Runtime/World/Components/TestEnum.h>
#include <Runtime/World/Components/TestStruct.h>
#include <Runtime/Math/Color4.h>

namespace Portakal
{
	PCLASS();
	class PORTAKAL_API TestComponent : public Component
	{
		GENERATE_CLASS(TestComponent);
	public:

		PFIELD();
		int int0;
		PFIELD();
		int int1;
		PFIELD();
		int int3;

		PFIELD();
		TestEnum myEnum;

		PFIELD();
		TestStruct someTestStruct;

		Array<TestStruct> MyIntArray;
	private:


		// Inherited via Component
		virtual void DestroyCore() override;

		virtual void OnInitialize() override;

		virtual void OnFinalize() override;

		// Inherited via Component
		virtual void OnAspectRemoved(SceneAspect* pAspect) override;
	};
#include "TestComponent.reflect.h"
}