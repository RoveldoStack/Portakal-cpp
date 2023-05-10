#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Platform/PlatformCriticalSection.h>
#include <Runtime/Object/TaggedObject.h>
#include <Runtime/Resource/ResourceSubObject.h>
#include <Runtime/Log/Log.h>
namespace Portakal
{
	class ResourceSubObject;

	/// <summary>
	/// Thread-safe smart pointer implementation
	/// </summary>
	/// <typeparam name="TType"></typeparam>
	template<typename TType>
	class SharedSafeHeap
	{
	public:
		SharedSafeHeap(const SharedSafeHeap& other)
		{
			mHeap = other.mHeap;
			mRefCount = other.mRefCount;
			mBarrier = other.mBarrier;
			if (mBarrier != nullptr)
			{
				mBarrier->Lock();
				*mRefCount = *mRefCount + 1;
				mBarrier->Release();
			}
		}

		template<typename TOther>
		SharedSafeHeap(const SharedSafeHeap<TOther>& other)
		{
			const SharedSafeHeap<TType>* temp = (const SharedSafeHeap<TType>*)&other;

			mHeap = temp->mHeap;
			mRefCount = temp->mRefCount;
			mBarrier = temp->mBarrier;
			if (mBarrier != nullptr)
			{
				mBarrier->Lock();
				*mRefCount = *mRefCount + 1;
				mBarrier->Release();
			}
		}

		SharedSafeHeap(TType* pData)
		{
			if (pData == nullptr)
			{
				mHeap = nullptr;
				mRefCount = nullptr;
				mBarrier = nullptr;
				return;
			}

			mHeap = pData;
			mRefCount = new unsigned int(1);
			mBarrier = PlatformCriticalSection::Create();
		}

		template<typename TOther>
		SharedSafeHeap(TOther* pData)
		{
			if (pData == nullptr)
			{
				mHeap = nullptr;
				mRefCount = nullptr;
				mBarrier = nullptr;
				return;
			}

			pData->GetTagName();

			mHeap = pData;
			mRefCount = new unsigned int(1);
			mBarrier = PlatformCriticalSection::Create();
		}

		SharedSafeHeap(const TType& data)
		{
			mHeap = new TType();
			*mHeap = data;
			mRefCount = new unsigned int(1);
			mBarrier = PlatformCriticalSection::Create();
		}
		
		SharedSafeHeap()
		{
			mHeap = nullptr;
			mRefCount = nullptr;
			mBarrier = nullptr;
		}

		~SharedSafeHeap()
		{
			Reset();
		}

		FORCEINLINE TType* GetHeap() const noexcept
		{
			if (mBarrier == nullptr)
				return nullptr;

			mBarrier->Lock();
			TType* pTemp = mHeap;
			mBarrier->Release();

			return pTemp;
		}

		void Reset()
		{
			if (mHeap == nullptr)
				return;

			mBarrier->Lock();

			*mRefCount = *mRefCount - 1;

			if (*mRefCount == 0)
			{
				mHeap->Destroy();
				delete mRefCount;
				mBarrier->Release();
				delete mBarrier;
				mHeap = nullptr;
				mRefCount = nullptr;
				mBarrier = nullptr;
				return;
			}

			mBarrier->Release();
		}

		FORCEINLINE TType* operator->() const
		{
			if (mBarrier == nullptr)
				return nullptr;

			mBarrier->Lock();
			TType* pTemp = mHeap;
			mBarrier->Release();

			return pTemp;
		}

		bool operator ==(const SharedSafeHeap& other)
		{
			return mRefCount == other.mRefCount;
		}
		bool operator !=(const SharedSafeHeap& other)
		{
			return mRefCount != other.mRefCount;
		}
		bool operator ==(const TType* pOther)
		{
			return mHeap == pOther;
		}
		bool operator !=(const TType* pOther)
		{
			return mHeap != pOther;
		}
		void operator =(const SharedSafeHeap& other)
		{
			Reset();

			mHeap = other.mHeap;
			mRefCount = other.mRefCount;
			mBarrier = other.mBarrier;
			if (mBarrier != nullptr)
			{
				mBarrier->Lock();
				*mRefCount = *mRefCount + 1;
				mBarrier->Release();
			}
		}
		template<typename TOther>
		void operator=(const SharedSafeHeap<TOther>& other)
		{
			Reset();
			const SharedSafeHeap<TType>* pTemp = (const SharedSafeHeap<TType>*)&other;

			mHeap = pTemp->mHeap;
			mRefCount = pTemp->mRefCount;
			mBarrier = pTemp->mBarrier;
			if (mBarrier != nullptr)
			{
				mBarrier->Lock();
				*mRefCount = *mRefCount + 1;
				mBarrier->Release();
			}
		}
	
	private:
		TType* mHeap;
		PlatformCriticalSection* mBarrier;
		unsigned int* mRefCount;
	};
}