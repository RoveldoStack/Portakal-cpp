#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	PCLASS();
	class PORTAKAL_API CustomEditorObjectAttribute : public Attribute
	{
		GENERATE_CLASS(CustomEditorObjectAttribute);
	public:
		CustomEditorObjectAttribute(Type* pType) : mTargetObjectType(pType) {}
		CustomEditorObjectAttribute() : mTargetObjectType(nullptr) {}
		~CustomEditorObjectAttribute() = default;

		FORCEINLINE Type* GetTargetObjectType() const noexcept { return mTargetObjectType; }
	private:
		Type* mTargetObjectType;
	};

#include "CustomEditorObjectAttribute.reflect.h"
}