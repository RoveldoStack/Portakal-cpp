#pragma once
#include <Runtime/Event/Delegate.h>
#include <Runtime/Containers/Array.h>

namespace Portakal
{
	/// <summary>
	/// Simple event implementation
	/// </summary>
	template<typename TReturn, typename... TParameters>
	class Event final
	{
	public:
		void Invoke(TParameters... parameters)
		{
			for (unsigned int i = 0; i < mDelegates.GetCursor(); i++)
				mDelegates[i].Invoke(parameters...);
		}

		void operator +=(Delegate<TReturn, TParameters...>& target)
		{
			mDelegates.Add(target);
		}

		void operator -=(Delegate<TReturn, TParameters...>& target)
		{
			mDelegates.Remove(target);
		}
	private:
		Array<Delegate<TReturn, TParameters...>> mDelegates;
	};
}