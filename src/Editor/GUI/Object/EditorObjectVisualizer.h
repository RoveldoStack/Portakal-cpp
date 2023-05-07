#pragma once
#include <Runtime/Reflection/Reflection.h>

namespace Portakal
{
	/// <summary>
	/// Represents a base class of all editor object visualizers that will appear on the ObjectObserverWindow
	/// </summary>
	PCLASS(Virtual);
	class PORTAKAL_API EditorObjectVisualizer : Class
	{
		friend class ObjectObserverWindow;
		GENERATE_CLASS(EditorObjectVisualizer,Virtual);
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

#include "EditorObjectVisualizer.reflect.h"
}