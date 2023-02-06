#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/String.h>



namespace Portakal
{
	class Type;

	class PORTAKAL_API Assembly
	{
	public:
		FORCEINLINE static Assembly* GetProcessAssembly() noexcept;
	private:
		static inline Assembly* sProcessAssembly = nullptr;
	public:
		Assembly();
		~Assembly();

		FORCEINLINE Type* GetType(const String& name) const noexcept;
		FORCEINLINE Array<Type*> GetTypes() const noexcept { return mTypes; }

		void RegisterType(Type* pType);
	private:
		Array<Type*> mTypes;
	};
}

extern "C"
{
	static Portakal::Assembly* GetProcessAssembly() { return Portakal::Assembly::GetProcessAssembly(); }
}