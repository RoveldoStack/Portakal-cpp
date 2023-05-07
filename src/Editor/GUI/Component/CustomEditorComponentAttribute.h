#pragma once
#include <Editor/GUI/Component/EditorComponentVisualizer.h>

namespace Portakal
{
	PCLASS();
	class PORTAKAL_API CustomEditorComponentAttribute : public Attribute
	{
		GENERATE_CLASS(CustomEditorComponentAttribute);
	public:
		CustomEditorComponentAttribute(Type* pType) : mTargetType(pType) {}
		CustomEditorComponentAttribute() : mTargetType(nullptr) {}
		~CustomEditorComponentAttribute() = default;

		FORCEINLINE Type* GetTargetType() const noexcept { return mTargetType; }
	private:
		Type* mTargetType;
	};

#include "CustomEditorComponentAttribute.reflect.h"
}