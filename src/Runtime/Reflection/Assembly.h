#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/String.h>



namespace Portakal
{
	class Type;

	/// <summary>
	/// Represents a single loaded assembly
	/// </summary>
	class PORTAKAL_API Assembly
	{
	public:
		/// <summary>
		/// Returns the process assembly (it will be replaced)
		/// </summary>
		/// <returns></returns>
		FORCEINLINE static Assembly* GetProcessAssembly() noexcept;
	private:
		static inline Assembly* sProcessAssembly = nullptr;
	public:
		Assembly();
		~Assembly();

		/// <summary>
		/// Returns the type with a name
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		FORCEINLINE Type* GetType(const String& name) const noexcept;

		/// <summary>
		/// Returns all the types
		/// </summary>
		/// <returns></returns>
		FORCEINLINE const Array<Type*>& GetTypes() const noexcept { return mTypes; }

		/// <summary>
		/// Registers a type
		/// </summary>
		/// <param name="pType"></param>
		void RegisterType(Type* pType);
	private:
		Array<Type*> mTypes;
	};
}

extern "C"
{
	static Portakal::Assembly* GetProcessAssembly() { return Portakal::Assembly::GetProcessAssembly(); }
}