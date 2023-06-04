#pragma once
#include <Runtime/Core/Core.h>
#include <initializer_list>
#include <Runtime/Log/Log.h>

namespace Portakal
{
	/// <summary>
	/// Represents a single Registry entry. It contains Key&Value tupple
	/// </summary>
	/// <typeparam name="TKey"></typeparam>
	/// <typeparam name="TValue"></typeparam>
	template<typename TKey,typename TValue>
	struct RegistryEntry
	{
		RegistryEntry()
		{
			Key = {};
			Value = {};
		}

		/// <summary>
		/// The key
		/// </summary>
		TKey Key;

		/// <summary>
		/// The value
		/// </summary>
		TValue Value;
	};

	/// <summary>
	/// Unlike array it holds tupples Key&Value
	/// Acts as a C# Dictionary
	/// </summary>
	/// <typeparam name="TKey"></typeparam>
	/// <typeparam name="TValue"></typeparam>
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
		Registry()
		{
			mData = nullptr;
			mCursor = 0;
			mCapacity = 0;
			mCapacityMultiplier = 2;
		}


		/// <summary>
		/// Returns the entry count of the registry
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetCursor() const noexcept
		{
			return mCursor;
		}

		/// <summary>
		/// Returns the value address of the given key
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		FORCEINLINE TValue* GetEntryValue(const TKey& key) const noexcept
		{
			for (unsigned int i = 0; i < mCursor; i++)
			{
				RegistryEntry<TKey, TValue>& entry = mData[i];
				if (entry.Key == key)
					return &entry.Value;
			}

			return nullptr;
		}

		/// <summary>
		/// Returns whether the given key exists
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
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

		/// <summary>
		/// Finds the index of the given key
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
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

		/// <summary>
		/// Registers anew entry
		/// </summary>
		/// <param name="key"></param>
		/// <param name="value"></param>
		/// <returns></returns>
		FORCEINLINE bool Register(const TKey& key, const TValue& value) noexcept
		{
			const int index = FindIndex(key);
			if (index != -1)
			{
				return false;
			}

			if (mCursor + 1 > mCapacity)
				ExtendMemory();

			RegistryEntry<TKey, TValue> entry = {};
			entry.Key = key;
			entry.Value = value;
			mData[mCursor] = entry;
			mCursor++;

			return true;
		}

		/// <summary>
		/// Removes an existing key entry
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
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

		/// <summary>
		/// Clears the registry
		/// </summary>
		void Clear()
		{
			ClearMemory();
		}

		/// <summary>
		/// Index operator
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		FORCEINLINE RegistryEntry<TKey, TValue>& operator[](const unsigned int index) const noexcept
		{
			return mData[index];
		}
	private:
		void ExtendMemory()
		{
			const unsigned int newCapacity = (mCapacity == 0 ? 1 : mCapacity) * mCapacityMultiplier;
			RegistryEntry<TKey, TValue>* pNewHeap = new RegistryEntry<TKey, TValue>[newCapacity];

			for (unsigned int i = 0; i < mCursor; i++)
				pNewHeap[i] = mData[i];

			if (mData != nullptr)
				delete[] mData;

			mData = pNewHeap;
			mCapacity = newCapacity;
		}
		void ClearMemory()
		{
			if(mData != nullptr)
				delete[] mData;

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