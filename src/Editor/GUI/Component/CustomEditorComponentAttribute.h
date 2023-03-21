#pragma once
#include <Editor/GUI/Component/EditorComponentVisualizer.h>

namespace Portakal
{
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

	START_GENERATE_TYPE(CustomEditorComponentAttribute);
	START_TYPE_PROPERTIES(CustomEditorComponentAttribute);
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(CustomEditorComponentAttribute);
	END_GENERATE_TYPE(CustomEditorComponentAttribute);
}