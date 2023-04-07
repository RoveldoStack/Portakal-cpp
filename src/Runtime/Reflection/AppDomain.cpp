#include "AppDomain.h"

namespace Portakal
{
	AppDomain* AppDomain::sDomain = nullptr;

	AppDomain* AppDomain::GetDomain()
	{
		return sDomain;
	}
	Array<Assembly*> AppDomain::GetAssemblies() const noexcept
	{
		return mAssemblies;
	}
	AppDomain::AppDomain()
	{

	}
	AppDomain::~AppDomain()
	{

	}
	void AppDomain::_RegisterAssembly(Assembly* pAssembly)
	{
		mAssemblies.Add(pAssembly);
	}
	void AppDomain::_RemoveAssembly(Assembly* pAssembly)
	{
		mAssemblies.Remove(pAssembly);
	}
}