#pragma once
#include <Editor/GUI/Component/EditorComponentVisualizer.h>
#include <Runtime/World/Components/Transform2DComponent.h>
#include <Editor/GUI/Component/CustomEditorComponentAttribute.h>

namespace Portakal
{
	PCLASS_ATTRIBUTE(CustomEditorComponentAttribute, typeof(Transform2DComponent));
	PCLASS();
	class PORTAKAL_API Transform2DComponentVisualizer : public EditorComponentVisualizer
	{
		GENERATE_CLASS(Transform2DComponentVisualizer);
	public:
		Transform2DComponentVisualizer() = default;
		~Transform2DComponentVisualizer() = default;
	private:


		// Inherited via EditorComponentVisualizer
		virtual void OnInitialize() override;

		virtual void OnFinalize() override;


		// Inherited via EditorComponentVisualizer
		virtual void OnPaint() override;
	private:
		Transform2DComponent* mTransform;
	};

#include "Transform2DComponentVisualizer.reflect.h"
}