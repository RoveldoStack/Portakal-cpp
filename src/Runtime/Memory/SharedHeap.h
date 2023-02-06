#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	template<typename TType>
	class SharedHeap
	{
	public:
		SharedHeap(TType* pHeap)
		{
			CreateNew(pHeap);
		}
		SharedHeap(const SharedHeap<TType>& target)
		{
			mHeap = target.mHeap;
			mCount = target.mCount;
			*mCount++;
		}
		SharedHeap()
		{
			mHeap = nullptr;
			mCount = nullptr;
		}
		~SharedHeap()
		{
			Reset();
		}

		FORCEINLINE TType* GetHeap()
		{
			return mHeap;
		}
		void Reset()
		{
			if (mCount == nullptr)
				return;

			*mCount--;

			if (mCount == 0)
			{
				delete mCount;
				delete mHeap;
				mHeap = nullptr;
				mCount = nullptr;
			}

		}

		void operator==(TType* pHeap)
		{
			if (pHeap != mHeap)
				Reset();

			CreateNew(pHeap);
		}

		TType* operator->() noexcept
		{
			return mHeap;
		}

		
	private:
		void CreateNew(TType* pHeap)
		{
			mHeap = pHeap;
			mCount = new unsigned int(1);
		}
	private:
		TType* mHeap;
		unsigned int* mCount;
	};
}