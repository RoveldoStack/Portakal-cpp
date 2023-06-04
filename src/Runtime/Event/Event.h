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
		/// <summary>
		/// Calls all the subscribed delegates
		/// </summary>
		/// <param name="...parameters"></param>
		void Invoke(TParameters... parameters)
		{
			for (unsigned int i = 0; i < mDelegates.GetCursor(); i++)
				mDelegates[i].Invoke(parameters...);
		}

		Array<Delegate<TReturn, TParameters...>> GetInvocationList() const noexcept
		{
			return mDelegates;
		}
		void ClearInvocationList()
		{
			mDelegates.Clear();
		}

		void operator +=(const Delegate<TReturn, TParameters...>& target)
		{
			mDelegates.Add(target);
		}

		void operator -=(const Delegate<TReturn, TParameters...>& target)
		{
			mDelegates.Remove(target);
		}
	private:
		Array<Delegate<TReturn, TParameters...>> mDelegates;
	};
}