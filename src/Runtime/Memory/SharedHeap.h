#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Platform/PlatformCriticalSection.h>

namespace Portakal
{
	class ResourceSubObject;
	/// <summary>
	/// Simple smart shader ptr implementation
	/// </summary>
	/// <typeparam name="TType"></typeparam>
	template<typename TType>
	class SharedHeap
	{
	public:
		SharedHeap(TType* pHeap)
		{
			mHeap = pHeap;
			mRefCount = new unsigned int(1);
		}
		SharedHeap(const SharedHeap& target)
		{
			if (target.mHeap == nullptr)
			{
				mHeap = nullptr;
				mRefCount = nullptr;
				return;
			}

			mHeap = target.mHeap;
			mRefCount = target.mRefCount;
			*mRefCount++;
		}

		template<typename TOther>
		SharedHeap(const SharedHeap<TOther>& target)
		{
			const SharedHeap<TType>* pTemp = (const SharedHeap<TType>*)&target;

			if (pTemp->mHeap == nullptr)
			{
				mHeap = nullptr;
				mRefCount = nullptr;
				return;
			}

			mHeap = pTemp->mHeap;
			mRefCount = pTemp->mRefCount;
			*mRefCount++;
		}
		
		SharedHeap()
		{
			mHeap = nullptr;
			mRefCount = nullptr;
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
			if (mRefCount == nullptr)
			{
				return;
			}

			if (mRefCount == 0)
			{
				delete mRefCount;
				delete mHeap;
				mHeap = nullptr;
				mRefCount = nullptr;
				return;
			}
		}

		void operator==(TType* pHeap)
		{
			if (pHeap == nullptr)
			{
				Reset();
				return;
			}

			if (pHeap != mHeap)
				Reset();

			mHeap = pHeap;
			mRefCount = new unsigned int(1);
		}

		TType* operator->() noexcept
		{
			return mHeap;
		}

	private:
		TType* mHeap;
		unsigned int* mRefCount;
	};
}