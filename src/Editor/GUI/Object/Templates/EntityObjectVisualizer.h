#pragma once
#include <Editor/GUI/Object/EditorObjectVisualizer.h>
#include <Editor/GUI/Object/CustomEditorObjectAttribute.h>
#include <Runtime/World/Entity.h>
#include <Runtime/Containers/Registry.h>
#
namespace Portakal
{
	class EditorComponentVisualizer;
	class CustomEditorComponentAttribute;

	CLASS_ATTRIBUTE(CustomEditorObjectAttribute, typeof(Entity));
	class PORTAKAL_API EntityObjectVisualizer : public EditorObjectVisualizer
	{
		GENERATE_CLASS(EntityObjectVisualizer);
	public:


		// Inherited via EditorObjectVisualizer
		virtual void OnInitialize() override;

		virtual void OnPaint() override;

		virtual void OnFinalize() override;
	private:
		struct VisualizerEntry
		{
			Type* pComponentType;
			Type* pVisualizerType;
		};
	private:
		Type* GetVisualizerType(Type* pComponentType);
	private:
		Array<Type*> mComponentTypes;
		Array<VisualizerEntry> mVisualizerEntries;
		Registry<Component*, EditorComponentVisualizer*> mVisualizerMap;
		Entity* mEntity;
	};

	/*START_GENERATE_TYPE(EntityObjectVisualizer);
	START_TYPE_PROPERTIES(EntityObjectVisualizer);
	REGISTER_BASE_TYPE(EditorObjectVisualizer);
	REGISTER_TYPE_ATTRIBUTE(CustomEditorObjectAttribute, typeof(Entity));
	END_TYPE_PROPERTIES;
	HAS_DEFAULT_CONSTRUCTOR(EntityObjectVisualizer);
	END_GENERATE_TYPE(EntityObjectVisualizer);*/

#include "EntityObjectVisualizer.reflect.h"
}