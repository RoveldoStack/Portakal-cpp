#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class Component;
	PCLASS(Virtual);
	class PORTAKAL_API EditorComponentVisualizer : Class
	{
		friend class EntityObjectVisualizer;
		GENERATE_CLASS(EditorComponentVisualizer);
	public:
		EditorComponentVisualizer() = default;
		~EditorComponentVisualizer() = default;

		virtual void OnInitialize() = 0;
		virtual void OnPaint() = 0;
		virtual void OnFinalize() = 0;
	protected:
		FORCEINLINE Component* GetComponent() const noexcept { return mComponent; }

		void DrawDefault();
	private:
		void _SetComponent(Component* pComponent) { mComponent = pComponent; }
	private:
		Component* mComponent;
	};

#include "EditorComponentVisualizer.reflect.h"
}