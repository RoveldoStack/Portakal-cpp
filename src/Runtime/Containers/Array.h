#pragma once
#include <initializer_list>
#include <Runtime/Core/Core.h>
#include <Runtime/Memory/Memory.h>
#include <Runtime/Log/Log.h>

namespace Portakal
{

	class ArrayBase
	{
	public:
		ArrayBase() = default;
		~ArrayBase() = default;

		virtual void AddIndirect() = 0;
		virtual void CreateIndirect(const unsigned int count) = 0;
		virtual void ClearIndirect() = 0;
	};
	/// <summary>
	/// Simple array implementation for dynamic heap allocation
	/// </summary>
	/// <typeparam name="TValue"></typeparam>
	template <typename TValue>
	class Array : public ArrayBase
	{
	public:
		virtual void ClearIndirect() override
		{
			Clear();
		}
		virtual void AddIndirect() override
		{
			Add({});
		}
		virtual void CreateIndirect(const unsigned int count) override
		{
			mCursor = count;
			mCapacity = count;

			mSource = new TValue[count];
			Memory::Set(mSource, 0, count);
		}
		Array(unsigned int allocateMultiplier = 2)
		{
			mCapacity = 0;
			mCursor = 0;
			mSource = nullptr;
			mAllocateMultiplier = allocateMultiplier;
		}
		Array(const Array<TValue>& targetSource)
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
		Array(const TValue* data, unsigned int count)
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
		Array(std::initializer_list<TValue> initializerList)
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
		~Array()
		{
			ClearMemory();
		}

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
		unsigned int GetItemSizeInBytes() const { return sizeof(TValue); }

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
		bool Has(const TValue& element) const
		{
			/*
			* Iterate all elements
			*/
			for (unsigned int i = 0; i < mCursor; i++)
			{
				if (mSource[i] == element) // Has
					return true;
			}

			return false;
		}

		/// <summary>
		/// Returns whether it has all the elements
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool HasAll(const Array<TValue>& other)
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

		/// <summary>
		/// Find the index of the corresponding element
		/// </summary>
		/// <param name="element"></param>
		/// <returns></returns>
		int FindIndex(const TValue& element) const
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

		/// <summary>
		/// Reservers the capacity upfront
		/// </summary>
		/// <param name="mCapacity"></param>
		void Reserve(unsigned int mCapacity)
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

		/// <summary>
		/// Reservers the capacity upfront and sets the default value
		/// </summary>
		/// <param name="mCapacity"></param>
		/// <param name="defaultValue"></param>
		void Reserve(unsigned int mCapacity, const TValue& defaultValue)
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

		/// <summary>
		/// Copies the target data ptr
		/// </summary>
		/// <param name="data"></param>
		/// <param name="count"></param>
		void Copy(const TValue* data, unsigned int count)
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

		/// <summary>
		/// Copies the target array interval
		/// </summary>
		/// <param name="data"></param>
		/// <param name="start"></param>
		/// <param name="end"></param>
		void Copy(const Array<TValue>& data, unsigned int start, unsigned int end)
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

		/// <summary>
		/// Adds the new value to the array
		/// </summary>
		/// <param name="element"></param>
		void Add(const TValue& element)
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

	
		/// <summary>
		/// Adds the array
		/// </summary>
		/// <param name="elements"></param>
		void AddRange(const Array<TValue>& elements)
		{
			/*
			* Validate array bounds
			*/
			const unsigned int increaseInSize = elements.GetCursor();
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
					newSource[mCursor + sourceIndex] = elements.mSource[sourceIndex];
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
					mSource[sourceIndex] = elements.mSource[targetArrayIndex];
					targetArrayIndex++;
				}

				/*
				* Set mCursor
				*/
				mCursor = targetSize - 1;
			}
		}

		/// <summary>
		/// Inserts anew element
		/// </summary>
		/// <param name="index"></param>
		/// <param name="element"></param>
		void Insert(unsigned int index, const TValue& element)
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

		/// <summary>
		/// Clars the array
		/// </summary>
		void Clear()
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

		/// <summary>
		/// Resets the cursor counter to the 0
		/// Note that this does call delete[]
		/// </summary>
		void Reset()
		{
			mCursor = 0;
		}

		/// <summary>
		/// Removes the target index
		/// </summary>
		/// <param name="index"></param>
		void RemoveIndex(unsigned int index)
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

		/// <summary>
		/// Removes the target element
		/// </summary>
		/// <param name="element"></param>
		bool Remove(const TValue& element)
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
				return false;
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

			return true;
		}

		/// <summary>
		/// Shrinks the array size to the it's cursor, deleting the stride of empty allocated memory
		/// </summary>
		void Compact()
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

		/// <summary>
		/// Revereses the array
		/// </summary>
		void Reverse()
		{
			const unsigned int halfSize = mCursor / 2;
			for (unsigned int i = 0; i < halfSize; i++)
			{
				const unsigned counterIndex = mCursor - i-1;

				const TValue value0 = mSource[i];
				const TValue value1 = mSource[counterIndex];

				mSource[i] = value1;
				mSource[counterIndex] = value0;
			}
		}

		/// <summary>
		/// Sets the allocate multiplier
		/// </summary>
		/// <param name="amount"></param>
		void SetAllocateMultiplier(unsigned int amount)
		{
			/*
			* Set multiplier
			*/
			mAllocateMultiplier = amount;
		}

	public:
		TValue& operator[](unsigned int index) const
		{
			return mSource[index];
		}
		void operator=(const Array<TValue>& targetSource)
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

	private:
		void ClearMemory()
		{
			if (mSource == nullptr)
				return;

			delete[] mSource;
			mSource = nullptr;
		}
	private:
		TValue* mSource;
		unsigned long mCapacity;
		unsigned int mCursor;
		unsigned int mAllocateMultiplier;
	};

	
}