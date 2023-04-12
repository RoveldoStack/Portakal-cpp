#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Object/TaggedObject.h>
#include <Runtime/Resource/ResourceSubObject.h>
#include <Runtime/Log/Log.h>

namespace Portakal
{
	class ResourceSubObject;

	/// <summary>
	/// Non-thread safe shared pointer implementation
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
			if (mRefCount != nullptr)
			{
				*mRefCount = *mRefCount + 1;
			}
		}

		template<typename TOther>
		SharedHeap(const SharedHeap<TOther>& other)
		{
			const SharedHeap<TType>* temp = (const SharedHeap<TType>*) & other;

			mHeap = temp->mHeap;
			mRefCount = temp->mRefCount;
			if (mRefCount != nullptr)
			{
				*mRefCount = *mRefCount + 1;;
			}
		}

		SharedHeap(TType* pData)
		{
			if (pData == nullptr)
			{
				mHeap = nullptr;
				mRefCount = nullptr;
				return;
			}

			pData->GetTagName();

			mHeap = pData;
			mRefCount = new unsigned int(1);
		}

		SharedHeap(const TType& data)
		{
			mHeap = new TType();
			*mHeap = data;
			mRefCount = new unsigned int(1);
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

		FORCEINLINE TType* GetHeap() const noexcept
		{
			return mHeap;
		}

		void Reset()
		{
			if (mHeap == nullptr)
				return;

			*mRefCount = *mRefCount - 1;

			if (*mRefCount == 0)
			{
				mHeap->Destroy();
				delete mHeap;
				delete mRefCount;
				mHeap = nullptr;
				mRefCount = nullptr;
				return;
			}
		}

		FORCEINLINE TType* operator->() const
		{
			return mHeap;
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
			if (mRefCount != nullptr)
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
			if (mRefCount != nullptr)
			{
				*mRefCount = *mRefCount + 1;
			}
		}
	private:
		TType* mHeap;
		unsigned int* mRefCount;
	};
}