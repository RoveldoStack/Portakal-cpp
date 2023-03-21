#pragma once
#include <Runtime/Core/Core.h>
#include <initializer_list>
#include <Runtime/Log/Log.h>

namespace Portakal
{
	template<typename TKey,typename TValue>
	struct RegistryEntry
	{
		RegistryEntry()
		{
			Key = {};
			Value = {};
		}
		TKey Key;
		TValue Value;
	};

	template<typename TKey,typename TValue>
	class Registry
	{
	public:
		Registry(const Registry& target)
		{
			mData = new RegistryEntry<TKey,TValue>[target.mCapacity];
			mCursor = target.mCursor;
			mCapacity = target.mCapacity;
			mCapacityMultiplier = target.mCapacityMultiplier;

			/*
			* Copy the data
			*/
			for (unsigned int i = 0; i < mCursor; i++)
				mData[i] = target.mData[i];
		}
		Registry(const unsigned int preallocatedCount)
		{
			mData = new RegistryEntry<TKey,TValue>[preallocatedCount];
			mCursor = 0;
			mCapacity = preallocatedCount;
			mCapacityMultiplier = 2;
		}
		Registry(std::initializer_list<TValue> initializerList)
		{

			/*
			* Allocate space
			*/
			mData = new TValue[initializerList.size()];
			mCursor = initializerList.size();
			mCapacity = initializerList.size();
			mCapacityMultiplier = 2;

			/*
			* Copy
			*/
			unsigned int index = 0;
			for (const TValue& value : initializerList)
			{
				mData[index] = value;
				index++;
			}
		}
		Registry()
		{
			mData = nullptr;
			mCursor = 0;
			mCapacity = 0;
			mCapacityMultiplier = 2;
		}

		FORCEINLINE unsigned int GetCursor() const noexcept
		{
			return mCursor;
		}
		FORCEINLINE RegistryEntry<TKey, TValue>& GetEntryViaIndex(const unsigned int index) const noexcept
		{
			return mData[index];
		}
		FORCEINLINE RegistryEntry<TKey, TValue> FindEntry(const TKey& key) const noexcept
		{
			for (unsigned int i = 0; i < mCursor; i++)
			{
				RegistryEntry<TKey, TValue>& entry = mData[i];
				if (entry.Key == key)
					return entry;
			}

			return {};
		}
		FORCEINLINE bool HasEntry(const TKey& key) const noexcept
		{
			for (unsigned int i = 0; i < mCursor; i++)
			{
				RegistryEntry<TKey, TValue>& entry = mData[i];
				if (entry.Key == key)
					return true;
			}

			return false;
		}
		FORCEINLINE int FindIndex(const TKey& key) const noexcept
		{
			for (unsigned int i = 0; i < mCursor; i++)
			{
				RegistryEntry<TKey, TValue>& entry = mData[i];
				if (entry.Key == key)
					return i;
			}

			return -1;
		}
		FORCEINLINE RegistryEntry<TKey,TValue> Register(const TKey& key, const TValue& value) noexcept
		{
			const int index = FindIndex(key);
			if (index != -1)
			{
				return GetEntryViaIndex(index);
			}

			if (mCursor + 1 > mCapacity)
				ExtendMemory();

			RegistryEntry<TKey, TValue> entry = {};
			entry.Key = key;
			entry.Value = value;
			mData[mCursor] = entry;
			mCursor++;

			return entry;
		}
		FORCEINLINE bool Remove(const TKey& key) noexcept
		{
			const int index = FindIndex(key);
			if (index == -1)
				return false;

			for (unsigned int i = index + 1; i < mCursor; i++)
			{
				mData[i - 1] = mData[i];
			}

			mCursor--;

			return true;
		}

		void Clear()
		{
			ClearMemory();
		}
	private:
		void ExtendMemory()
		{
			const unsigned int newCapacity = (mCapacity == 0 ? 1 : mCapacity) * mCapacityMultiplier;
			RegistryEntry<TKey, TValue>* pNewHeap = new RegistryEntry<TKey, TValue>[newCapacity];

			for (unsigned int i = 0; i < mCursor; i++)
				pNewHeap[i] = mData[i];

			if (mData != nullptr)
				delete mData;

			mData = pNewHeap;
			mCapacity = newCapacity;
		}
		void ClearMemory()
		{
			if(mData != nullptr)
				delete mData;
			mData = nullptr;
			mCursor = 0;
			mCapacity = 0;
		}
	private:
		RegistryEntry<TKey,TValue>* mData;
		unsigned int mCursor;
		unsigned int mCapacity;
		unsigned int mCapacityMultiplier;
	};
}