#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Array.h>

namespace Portakal
{
	class Assembly;
	class PORTAKAL_API AppDomain
	{
		friend class ReflectionModule;
	private:
		static AppDomain* sDomain;
	public:
		static AppDomain* GetDomain();

		FORCEINLINE Array<Assembly*> GetAssemblies() const noexcept;
	private:
		AppDomain();
		~AppDomain();

		void _RegisterAssembly(Assembly* pAssembly);
		void _RemoveAssembly(Assembly* pAssembly);
		void _SetDomain(AppDomain* pDomain) { sDomain = pDomain; }
	private:
		Array<Assembly*> mAssemblies;
	};
}