#pragma once
#include <Runtime/Core/Core.h>
#include <initializer_list>
#include <Runtime/Log/Log.h>
#include <Runtime/Containers/Array.h>

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
		RegistryEntry(const RegistryEntry& other)
		{
			Key = other.Key;
			Value = other.Value;
		}
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
			mArray = target.mArray;
		}
		Registry(const unsigned int preallocatedCount)
		{
			mArray = Array<RegistryEntry<TKey, TValue>>(preallocatedCount);
		}
		Registry()
		{

		}


		/// <summary>
		/// Returns the entry count of the registry
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetCursor() const noexcept
		{
			return mArray.GetCursor();
		}

		/// <summary>
		/// Returns the value address of the given key
		/// </summary>
		/// <param name="key"></param>
		/// <returns></returns>
		FORCEINLINE TValue* GetEntryValue(const TKey& key) const noexcept
		{
			for (unsigned int i = 0; i < mArray.GetCursor(); i++)
			{
				RegistryEntry<TKey, TValue>& entry = mArray[i];
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
			for (unsigned int i = 0; i < mArray.GetCursor(); i++)
			{
				RegistryEntry<TKey, TValue>& entry = mArray[i];
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
			for (unsigned int i = 0; i < mArray.GetCursor(); i++)
			{
				RegistryEntry<TKey, TValue>& entry = mArray[i];
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

			RegistryEntry<TKey, TValue> entry = {};
			entry.Key = key;
			entry.Value = value;
			mArray.Add(entry);

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

			mArray.RemoveIndex(index);

			return true;
		}

		/// <summary>
		/// Clears the registry
		/// </summary>
		void Clear()
		{
			mArray.Clear();
		}

		/// <summary>
		/// Index operator
		/// </summary>
		/// <param name="index"></param>
		/// <returns></returns>
		FORCEINLINE RegistryEntry<TKey, TValue>& operator[](const unsigned int index) const noexcept
		{
			return mArray[index];
		}

	private:
		Array<RegistryEntry<TKey, TValue>> mArray;
	};
}