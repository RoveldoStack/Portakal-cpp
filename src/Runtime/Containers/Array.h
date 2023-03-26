#pragma once
#include <initializer_list>
#include <Runtime/Core/Core.h>

namespace Portakal
{
	/// <summary>
	/// Simple array implementation for dynamic heap allocation
	/// </summary>
	/// <typeparam name="TValue"></typeparam>
	template <typename TValue>
	class Array final
	{
	public:
		Array(unsigned int mAllocateMultiplier = 2);
		Array(const Array<TValue>& targetSource);
		Array(const TValue* data, unsigned int count);
		Array(std::initializer_list<TValue> initializerList);
		~Array();

		/// <summary>
		/// Returns the maxiumum capacity of the array
		/// </summary>
		/// <returns></returns>
		unsigned int GetCapacity() const { return mCapacity; }

		/// <summary>
		/// Returns the current cursor of the array
		/// </summary>
		/// <returns></returns>
		unsigned int GetCursor() const { return mCursor; }

		/// <summary>
		/// Returns the array per element size in bytes
		/// </summary>
		/// <returns></returns>
		unsigned int GetItemSýzeInBytes() const { return sizeof(TValue); }

		/// <summary>
		/// Returns the pointer to the data
		/// </summary>
		/// <returns></returns>
		TValue* GetData() const { return mSource; }

		/// <summary>
		/// Returns the allocation multiplier
		/// </summary>
		/// <returns></returns>
		unsigned int GetAllocateMultiplier() const { return mAllocateMultiplier; }

		/// <summary>
		/// Returns whether 
		/// </summary>
		/// <param name="element"></param>
		/// <returns></returns>
		bool Has(const TValue& element) const;

		/// <summary>
		/// Returns whether it has all the elements
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool HasAll(const Array<TValue>& other);

		/// <summary>
		/// Find the index of the corresponding element
		/// </summary>
		/// <param name="element"></param>
		/// <returns></returns>
		int FindIndex(const TValue& element) const;

		/// <summary>
		/// Reservers the capacity upfront
		/// </summary>
		/// <param name="mCapacity"></param>
		void Reserve(unsigned int mCapacity);

		/// <summary>
		/// Reservers the capacity upfront and sets the default value
		/// </summary>
		/// <param name="mCapacity"></param>
		/// <param name="defaultValue"></param>
		void Reserve(unsigned int mCapacity, const TValue& defaultValue);

		/// <summary>
		/// Copies the target data ptr
		/// </summary>
		/// <param name="data"></param>
		/// <param name="count"></param>
		void Copy(const TValue* data, unsigned int count);

		/// <summary>
		/// Copies the target array interval
		/// </summary>
		/// <param name="data"></param>
		/// <param name="start"></param>
		/// <param name="end"></param>
		void Copy(const Array<TValue>& data, unsigned int start, unsigned int end);

		/// <summary>
		/// Moves the target source
		/// </summary>
		/// <param name="targetSource"></param>
		/// <param name="numberOfElements"></param>
		void Move(TValue* targetSource, unsigned long numberOfElements);

		/// <summary>
		/// Adds the new value to the array
		/// </summary>
		/// <param name="element"></param>
		void Add(const TValue& element);

		/// <summary>
		/// Adds the array
		/// </summary>
		/// <param name="elements"></param>
		void AddRange(const Array<TValue>& elements);

		/// <summary>
		/// Inserts anew element
		/// </summary>
		/// <param name="index"></param>
		/// <param name="element"></param>
		void Insert(unsigned int index, const TValue& element);

		/// <summary>
		/// Clars the array
		/// </summary>
		void Clear();

		/// <summary>
		/// Removes the target index
		/// </summary>
		/// <param name="index"></param>
		void RemoveIndex(unsigned int index);

		/// <summary>
		/// Removes the target element
		/// </summary>
		/// <param name="element"></param>
		void Remove(const TValue& element);

		/// <summary>
		/// Compacts ands trims the 
		/// </summary>
		void Compact();

		/// <summary>
		/// Sets the allocate multiplier
		/// </summary>
		/// <param name="amount"></param>
		void SetAllocateMultiplier(unsigned int amount);

	public:
		TValue& operator[](unsigned int index) const;
		void operator=(const Array<TValue>& targetSource);
	private:
		void ClearMemory();
	private:
		TValue* mSource;
		unsigned long mCapacity;
		unsigned int mCursor;
		unsigned int mAllocateMultiplier;
	};

	template<typename TValue>
	static bool operator==(const Array<TValue>& a, const Array<TValue>& b);
	template<typename TValue>
	static bool operator!=(const Array<TValue>& a, const Array<TValue>& b);

	/*
	* Implementation
	*/
	template<typename TValue>
	Array<TValue>::Array(unsigned int allocateMultiplier)
	{
		mCapacity = 0;
		mCursor = 0;
		mSource = nullptr;
		mAllocateMultiplier = allocateMultiplier;
	}

	template<typename TValue>
	Array<TValue>::Array(const Array<TValue>& targetSource)
	{
		/*
		* Get target source properties
		*/
		mCursor = targetSource.mCursor;
		mCapacity = targetSource.mCapacity;
		mAllocateMultiplier = targetSource.mAllocateMultiplier;

		/*
		* Allocate new source
		*/
		mSource = new TValue[mCapacity];

		for (unsigned int i = 0; i < mCursor; i++)
		{
			mSource[i] = targetSource.mSource[i];
		}
	}
	template<typename TValue>
	Array<TValue>::Array(const TValue* data, unsigned int count)
	{
		/*
		* Get properties
		*/
		mCursor = count;
		mCapacity = count;

		/*
		* Allocate new source
		*/
		mSource = new TValue[mCapacity];

		for (unsigned int i = 0; i < mCursor; i++)
		{
			mSource[i] = data[i];
		}
	}

	template<typename TValue>
	Array<TValue>::Array(std::initializer_list<TValue> initializerList)
	{
		/*
		* Allocate space
		*/
		mSource = new TValue[initializerList.size()];
		mCursor = initializerList.size();
		mCapacity = initializerList.size();
		mAllocateMultiplier = 2;

		/*
		* Copy
		*/
		unsigned int index = 0;
		for (const TValue& value : initializerList)
		{
			mSource[index] = value;
			index++;
		}
	}

	template<typename TValue>
	Array<TValue>::~Array()
	{
		ClearMemory();
	}
	template<typename TValue>
	void Array<TValue>::ClearMemory()
	{
		if (mSource == nullptr)
			return;

		delete[] mSource;
	}

	template<typename TValue>
	void Array<TValue>::Reserve(unsigned int mCapacity)
	{
		/*
		* Delete former source
		*/
		ClearMemory();

		/*
		* Allocate new source
		*/
		mSource = new TValue[mCapacity];

		/*
		* Set new mCapacity
		*/
		mCapacity = mCapacity;

		/*
		* Reset the mCursor
		*/
		mCursor = 0;
	}
	template<typename TValue>
	inline void Array<TValue>::Reserve(unsigned int mCapacity, const TValue& defaultValue)
	{
		/*
		* Delete format source
		*/
		ClearMemory();

		/*
		* Allocate new source
		*/
		mSource = new TValue[mCapacity];

		/*
		* Set new mCapacity
		*/
		mCapacity = mCapacity;

		/*
		* Set mCursor
		*/
		mCursor = mCapacity - 1;

		/*
		* Initialize default values
		*/
		for (unsigned int i = 0; i < mCursor; i++)
		{
			mSource[i] = defaultValue;
		}
	}
	template<typename TValue>
	inline void Array<TValue>::Copy(const TValue* data, unsigned int count)
	{
		/*
		* Get properties
		*/
		mCursor = count;
		mCapacity = count;

		/*
		* Allocate new source
		*/
		mSource = new TValue[mCapacity];

		for (unsigned int i = 0; i < mCursor; i++)
		{
			mSource[i] = data[i];
		}
	}
	template<typename TValue>
	inline void Array<TValue>::Copy(const Array<TValue>& data, unsigned int start, unsigned int end)
	{
		/*
		* Get properties
		*/
		mCursor = end - start;
		mCapacity = end - start;

		/*
		* Allocate new source
		*/
		mSource = new TValue[mCapacity];

		for (unsigned int i = 0; i < mCursor; i++)
		{
			mSource[i] = data[i];
		}
	}
	template<typename TValue>
	inline void Array<TValue>::Move(TValue* targetSource, unsigned long numberOfElements)
	{
		/*
		* Set properties
		*/
		mCursor = numberOfElements;
		mCapacity = numberOfElements;
		mSource = targetSource;

	}
	template<typename TValue>
	void Array<TValue>::Add(const TValue& element)
	{
		/*
		* Validate array bounds
		*/
		if (mCursor >= mCapacity) // time to extend the bound of this array
		{
			/*
			* Determine the next mCapacity
			*/
			unsigned int targetCapacity = ((mCapacity == 0) ? 1 : mCapacity) * mAllocateMultiplier;

			/*
			* Allocate new source
			*/
			TValue* newSource = new TValue[targetCapacity];

			/*
			* Fill the new source with the old source data
			*/
			for (unsigned int i = 0; i < mCursor; i++)
			{
				newSource[i] = mSource[i];
			}

			/*
			* Delete the old source
			*/
			ClearMemory();

			/*
			* Set the new source
			*/
			mSource = newSource;

			/*
			* Set mCapacity
			*/
			mCapacity = targetCapacity;
		}

		/*
		* Set the current mCursor data
		*/
		mSource[mCursor] = element;

		/*
		* Increment mCursor
		*/
		mCursor++;
	}

	template<typename TValue>
	void Array<TValue>::AddRange(const Array<TValue>& array)
	{
		/*
		* Validate array bounds
		*/
		const unsigned int increaseInSize = array.GetCursor();
		const unsigned int targetSize = mCursor + increaseInSize + 1;

		/*
		* Validate if it needs new array
		*/
		if (targetSize >= mCapacity)
		{
			/*
			* Allocate new source
			*/
			TValue* newSource = new TValue[targetSize];

			/*
			* First set old source
			*/
			for (unsigned int sourceIndex = 0; sourceIndex < mCursor; sourceIndex++)
			{
				newSource[sourceIndex] = mSource[sourceIndex];
			}

			/*
			* Set target array
			*/
			for (unsigned int sourceIndex = 0; sourceIndex < increaseInSize; sourceIndex++)
			{
				newSource[mCursor + sourceIndex] = array.mSource[sourceIndex];
			}

			/*
			* Clear old array
			*/
			ClearMemory();

			/*
			* Set new source
			*/
			mSource = newSource;

			/*
			* Set mCursor
			*/
			mCursor = targetSize - 1;
			mCapacity = mCursor;
		}
		else // just needs append
		{
			/*
			* Set target array
			*/
			unsigned int targetArrayIndex = 0;
			for (unsigned int sourceIndex = mCursor; sourceIndex < increaseInSize; sourceIndex++)
			{
				mSource[sourceIndex] = array.mSource[targetArrayIndex];
				targetArrayIndex++;
			}

			/*
			* Set mCursor
			*/
			mCursor = targetSize - 1;
		}
	}

	template<typename TValue>
	void Array<TValue>::Insert(unsigned int index, const TValue& element)
	{
		/*
		* Validate array bounds
		*/
		if (mCursor >= mCapacity) // time to extend the bound of this array
		{
			/*
			* Determine the next mCapacity
			*/
			unsigned int targetCapacity = ((mCapacity == 0) ? 1 : mCapacity) * mAllocateMultiplier;

			/*
			* Allocate new source
			*/
			TValue* newSource = new TValue[targetCapacity];

			/*
			* Fill the new source with the old source data
			*/
			for (unsigned int i = 0; i < mCursor; i++)
			{
				newSource[i] = mSource[i];
			}

			/*
			* Delete the old source
			*/
			ClearMemory();

			/*
			* Set the new source
			*/
			mSource = newSource;

			/*
			* Set mCapacity
			*/
			mCapacity = targetCapacity;
		}

		/*
		* Shift elements
		*/
		for (unsigned int i = mCursor; i > index; i--)
		{
			mSource[i] = mSource[i - 1];
		}

		/*
		* Set item
		*/
		mSource[index] = element;

		/*
		* Increment mCursor
		*/
		mCursor++;
	}
	template<typename TValue>
	void Array<TValue>::SetAllocateMultiplier(unsigned int multiplier)
	{
		/*
		* Set multiplier
		*/
		mAllocateMultiplier = multiplier;
	}

	template<typename TValue>
	void Array<TValue>::Clear()
	{
		/*
		* Delete source
		*/
		ClearMemory();

		/*
		* Set variables
		*/
		mSource = nullptr;
		mCapacity = 0;
		mCursor = 0;
	}

	template<typename TValue>
	void Array<TValue>::RemoveIndex(unsigned int index)
	{
		if (mCursor == 0)
			return;

		/*
		* Shift elements
		*/
		for (unsigned int i = index + 1; i < mCursor; i++)
		{
			mSource[i - 1] = mSource[i];
		}

		/*
		* Decrement mCursor
		*/
		mCursor--;
	}

	template<typename TValue>
	void Array<TValue>::Remove(const TValue& element)
	{
		/*
		* Find it
		*/
		int index = -1;
		for (unsigned int i = 0; i < mCursor; i++)
		{
			if (mSource[i] == element)
			{
				index = i;
				break;
			}
		}

		/*
		* Validate index
		*/
		if (index == -1)
		{
			return;
		}

		/*
		* Shift elements
		*/
		for (unsigned int i = index + 1; i < mCursor; i++)
		{
			mSource[i - 1] = mSource[i];
		}

		/*
		* Decrement mCursor
		*/
		mCursor--;
	}
	template<typename TValue>
	void Array<TValue>::Compact()
	{
		/*
		* Create new source
		*/
		TValue* newSource = new TValue[mCursor];

		/*
		* Copy the contens
		*/
		for (unsigned int i = 0; i < mCursor; i++)
		{
			newSource[i] = mSource[i];
		}

		/*
		* Update variables
		*/
		mCapacity = mCursor;
	}

	template<typename TValue>
	bool Array<TValue>::Has(const TValue& element) const
	{
		/*
		* Iterator all elements
		*/
		for (unsigned int i = 0; i < mCursor; i++)
		{
			if (mSource[i] == element) // Has
				return true;
		}

		return false;
	}

	template<typename TValue>
	inline bool Array<TValue>::HasAll(const Array<TValue>& other)
	{
		/*
		* Iterate and check
		*/
		for (unsigned int i = 0; i < other.GetCursor(); i++)
		{
			if (!Has(other[i]))
				return false;
		}

		return true;
	}

	template<typename TValue>
	int Array<TValue>::FindIndex(const TValue& element) const
	{
		int index = -1;

		/*
		* Iterator all elements
		*/
		for (unsigned int i = 0; i < mCursor; i++)
		{
			if (mSource[i] == element)
			{
				index = i;
				break;
			}
		}

		return index;
	}
	template<typename TValue>
	TValue& Array<TValue>::operator[](unsigned int index) const
	{
		return mSource[index];
	}
	template<typename TValue>
	void Array<TValue>::operator=(const Array<TValue>& targetSource)
	{
		/*
		* Get target source properties
		*/
		mCursor = targetSource.mCursor;
		mCapacity = targetSource.mCapacity;
		mAllocateMultiplier = targetSource.mAllocateMultiplier;

		/*
		* Allocate new source
		*/
		mSource = new TValue[mCapacity];

		for (unsigned int i = 0; i < mCursor; i++)
		{
			mSource[i] = targetSource.mSource[i];
		}
	}
	template<typename TValue>
	bool operator==(const Array<TValue>& a, const Array<TValue>& b)
	{
		/*
		* First check sizes
		*/
		if (a.GetCursor() != b.GetCursor())
			return false;

		/*
		* Iterate and check
		*/
		for (unsigned int i = 0; i < a.GetCursor(); i++)
		{
			if (a[i] != b[i])
				return false;
		}

		return true;
	}

	template<typename TValue>
	bool operator!=(const Array<TValue>& a, const Array<TValue>& b)
	{
		/*
		* First check sizes
		*/
		if (a.GetCursor() != b.GetCursor())
			return true;


		/*
		* Iterate and check
		*/
		for (unsigned int i = 0; i < a.GetCursor(); i++)
		{
			if (a[i] != b[i])
				return true;
		}

		return false;
	}

}