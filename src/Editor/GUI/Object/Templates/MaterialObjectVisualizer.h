#pragma once
#include <Editor/GUI/Object/EditorObjectVisualizer.h>
#include <Editor/GUI/Object/CustomEditorObjectAttribute.h>
#include <Runtime/Resource/Material/MaterialResource.h>

namespace Portakal
{
	PCLASS();
	PCLASS_ATTRIBUTE(CustomEditorObjectAttribute, typeof(MaterialResource));
	class PORTAKAL_API MaterialObjectVisualizer : public EditorObjectVisualizer
	{
		GENERATE_CLASS(MaterialObjectVisualizer);
	public:
		MaterialObjectVisualizer() = default;
		~MaterialObjectVisualizer() = default;
	private:

		// Inherited via EditorObjectVisualizer
		virtual void OnInitialize() override;
		virtual void OnPaint() override;
		virtual void OnFinalize() override;
	};

#include "MaterialObjectVisualizer.reflect.h"
}