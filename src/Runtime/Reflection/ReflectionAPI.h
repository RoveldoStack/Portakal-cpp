#pragma once
#include <Runtime/Reflection/AppDomain.h>
#include <Runtime/Reflection/Assembly.h>
#include <Runtime/Object/API.h>
#include <Runtime/Containers/Registry.h>

namespace Portakal
{
	class PORTAKAL_API ReflectionAPI : public API<ReflectionAPI>
	{
	public:
		static Array<const Type*> GetOrCreateSubClassQuery(const Type* pType);
		static Array<const Type*> GetOrCreateClassWithAttributeQuery(const Type* pAttributeType);
	public:
		ReflectionAPI();
		virtual ~ReflectionAPI() override;
	private:
		Registry<const Type*, Array<const Type*>> mClassesWithAttribute;
		Registry<const Type*, Array<const Type*>> mSubClasses;
	};
}