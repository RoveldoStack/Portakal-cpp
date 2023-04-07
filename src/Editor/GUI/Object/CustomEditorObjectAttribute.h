#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
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

	//START_GENERATE_TYPE(CustomEditorObjectAttribute);
	//START_TYPE_PROPERTIES(CustomEditorObjectAttribute);
	//END_TYPE_PROPERTIES;
	//HAS_DEFAULT_CONSTRUCTOR(CustomEditorObjectAttribute);
	//END_GENERATE_TYPE(CustomEditorObjectAttribute);

#include "CustomEditorObjectAttribute.reflect.h"
}