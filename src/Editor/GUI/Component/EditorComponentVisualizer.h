#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	class Component;
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

	START_GENERATE_TYPE(EditorComponentVisualizer);
	START_TYPE_PROPERTIES(EditorComponentVisualizer);
	END_TYPE_PROPERTIES;
	NO_DEFAULT_CONSTRUCTOR;
	END_GENERATE_TYPE(EditorComponentVisualizer);
}