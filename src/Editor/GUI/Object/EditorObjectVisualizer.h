#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	/// <summary>
	/// Represents a base class of all editor object visualizers that will appear on the ObjectObserverWindow
	/// </summary>
	class PORTAKAL_API EditorObjectVisualizer : Class
	{
		friend class ObjectObserverWindow;
		GENERATE_CLASS(EditorObjectVisualizer);
	public:
		EditorObjectVisualizer() = default;
		~EditorObjectVisualizer() = default;

		virtual void OnInitialize() = 0;
		virtual void OnPaint() = 0;
		virtual void OnFinalize() = 0;
	protected:
		FORCEINLINE Class* GetTargetObject() const noexcept { return mTargetObject; }
	private:
		void _SetTargetObject(Class* pTargetObject) { mTargetObject = pTargetObject; }
	private:
		Class* mTargetObject;
	};

	START_GENERATE_TYPE(EditorObjectVisualizer);
	START_TYPE_PROPERTIES(EditorObjectVisualizer);
	END_TYPE_PROPERTIES;
	NO_DEFAULT_CONSTRUCTOR;
	END_GENERATE_TYPE(EditorObjectVisualizer);
}