#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Simple smart unique ptr implementation
	/// </summary>
	/// <typeparam name="TType"></typeparam>
	template<typename TType>
	class OwnedHeap
	{
	public:
		OwnedHeap(TType* pHeap)
		{
			CreateNew(pHeap);
		}
		OwnedHeap(const OwnedHeap<TType>& target) = delete;
		OwnedHeap(const OwnedHeap<TType>&& target) = delete;
		OwnedHeap()
		{
			mHeap = nullptr;
		}
		~OwnedHeap()
		{
			Free();
		}

		void Free()
		{
			if (mHeap == nullptr)
				return;

			delete mHeap;
			mHeap = nullptr;
		}

		void operator ==(TType* pHeap)
		{
			Free();
			CreateNew(pHeap);
		}

		void operator ==(const OwnedHeap<TType>& target) = delete;
		void operator ==(const OwnedHeap<TType>&& target) = delete;
		OwnedHeap<TType>& operator=(const OwnedHeap<TType>& target) = delete;

		TType* operator ->() noexcept
		{
			return mHeap;
		}
	private:
		void CreateNew(TType* pHeap)
		{
			mHeap = pHeap;
		}
	private:
		TType* mHeap;
	};
}