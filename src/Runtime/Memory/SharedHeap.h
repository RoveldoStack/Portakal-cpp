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
	/// Smart point implementation for TaggedObjects
	/// </summary>
	/// <typeparam name="TType"></typeparam>
	template<typename TType>
	class SharedHeap
	{
	public:
		SharedHeap(const SharedHeap& other)
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
		SharedHeap(const SharedHeap<TOther>& other)
		{
			const SharedHeap<TType>* temp = (const SharedHeap<TType>*)&other;

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

		SharedHeap(TType* pData)
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

		SharedHeap(const TType& data)
		{
			mHeap = new TType();
			*mHeap = data;
			mRefCount = new unsigned int(1);
			mBarrier = PlatformCriticalSection::Create();
		}
		
		SharedHeap()
		{
			mHeap = nullptr;
			mRefCount = nullptr;
			mBarrier = nullptr;
		}

		~SharedHeap()
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
				delete mHeap;
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

		void operator ==(const SharedHeap& other)
		{
			return mHeap == other.mHeap;
		}
		void operator !=(const SharedHeap& other)
		{
			return mHeap != other.mHeap;
		}
		void operator ==(const TType* pOther)
		{
			return mHeap == pOther;
		}
		void operator !=(const TType* pOther)
		{
			return mHeap != pOther;
		}
		void operator =(const SharedHeap& other)
		{
			Reset();

			mHeap = other.mHeap;
			mRefCount = other.mRefCount;
			mBarrier = other.mBarrier;
			if (mBarrier != nullptr)
			{
				*mRefCount = *mRefCount + 1;
			}
		}
		template<typename TOther>
		void operator =(const SharedHeap<TOther>& other)
		{
			const SharedHeap<TType>* pTemp = (const SharedHeap<TType*>) & other;
			Reset();

			mHeap = pTemp->mHeap;
			mRefCount = pTemp->mRefCount;
			mBarrier = pTemp->mBarrier;
			if (mBarrier != nullptr)
			{
				*mRefCount = *mRefCount + 1;
			}
		}
	private:
		TType* mHeap;
		PlatformCriticalSection* mBarrier;
		unsigned int* mRefCount;
	};
}