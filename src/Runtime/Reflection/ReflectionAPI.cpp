#include "ReflectionAPI.h"
#include <Runtime/Reflection/Type.h>
namespace Portakal
{
	Array<const Type*> ReflectionAPI::GetOrCreateSubClassQuery(const Type* pType)
	{
		ReflectionAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return {};

		/*
		* First check if there is an existing query
		*/
		Array<const Type*>* pSubTypes = pAPI->mSubClasses.GetEntryValue(pType);
		if (pSubTypes != nullptr)
			return *pSubTypes;

	
		/*
		* Create query
		*/
		Array<const Type*> newQuery;
		const Array<Type*>& types = Assembly::GetProcessAssembly()->GetTypes();
		for (unsigned int typeIndex = 0; typeIndex < types.GetCursor(); typeIndex++)
		{
			const Type* pType = types[typeIndex];
			if (pType->IsSubClassOf(pType))
				newQuery.Add(pType);
		}

		/*
		* Register query
		*/
		pAPI->mSubClasses.Register(pType, newQuery);

		return newQuery;
	}
	Array<const Type*> ReflectionAPI::GetOrCreateClassWithAttributeQuery(const Type* pAttributeType)
	{
		ReflectionAPI* pAPI = GetUnderlyingAPI();
		if (pAPI == nullptr)
			return {};

		/*
		* First check if there is an existing query
		*/
		Array<const Type*>* pSubTypes = pAPI->mClassesWithAttribute.GetEntryValue(pAttributeType);
		if (pSubTypes != nullptr)
			return *pSubTypes;

		/*
		* Create query
		*/
		Array<const Type*> newQuery;
		const Array<Type*>& types = Assembly::GetProcessAssembly()->GetTypes();
		for (unsigned int typeIndex = 0; typeIndex < types.GetCursor(); typeIndex++)
		{
			const Type* pType = types[typeIndex];
			Attribute* pAttribute = pType->GetAttribute(pType);
			if (pAttribute != nullptr)
				newQuery.Add(pType);
		}

		/*
		* Register query
		*/
		pAPI->mClassesWithAttribute.Register(pAttributeType, newQuery);

		return newQuery;
	}
	ReflectionAPI::ReflectionAPI()
	{

	}
	ReflectionAPI::~ReflectionAPI()
	{

	}
}