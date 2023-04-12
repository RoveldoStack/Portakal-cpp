#include "String.h"
#include <stdio.h>
#include <string>
#include <sstream>
#include <Runtime/Memory/Memory.h>
#define MAX_INT_DIGITS 10

namespace Portakal
{
	unsigned int get_char_pointer_size(const char* target)
	{
		unsigned int size = 0;
		while (target[size] != '\0')
			size++;
		return size;
	}

	String::String()
	{
		mSource = nullptr;
		mCursor = 0;
	}
	String::String(const char* target)
	{
		mCursor = get_char_pointer_size(target);

		mSource = new char[(double)mCursor + 1];

		Memory::Copy((void*)target, mSource, mCursor);

		mSource[mCursor] = '\0';

	}
	String::String(const unsigned int size)
	{
		mCursor = size;
		mSource = new char[mCursor + 1];
		mSource[mCursor] = '\0';
	}
	String::String(const char* target, const unsigned int size)
	{
		mCursor = size;
		mSource = new char[(double)mCursor + 1];

		Memory::Copy((void*)target,mSource, size);

		mSource[mCursor] = '\0';

	}
	String::String(const unsigned char* target, const unsigned int size)
	{
		mCursor = size;
		mSource = new char[(double)mCursor + 1];

		Memory::Copy((void*)target, mSource, size);

		mSource[mCursor] = '\0';

	}
	String::String(const String& target)
	{

		mCursor = target.mCursor;
		mSource = new char[(double)mCursor + 1];

		for (unsigned int i = 0; i < mCursor; i++)
		{
			mSource[i] = target.mSource[i];
		}
		mSource[mCursor] = '\0';
	}
	String::~String()
	{
		mCursor = 0;
		if(mSource != nullptr)
			delete[] mSource;
		mSource = nullptr;
	}
	String String::GetSubset(const unsigned int start, const unsigned  int length) const
	{

		unsigned int end = start + length;
		/*if (end >= mCursor)
			end = mCursor - 1;*/

		unsigned int gap = end - start;

		char* subsetSource = new char[gap + 1];

		int subsetIndex = 0;
		for (unsigned int i = start; i < end; i++)
		{
			subsetSource[subsetIndex] = mSource[i];
			subsetIndex++;
		}

		subsetSource[gap] = '\0';

		return String(subsetSource);
	}

	String String::Trim() const
	{
		String output;
		bool bStartFound = false;
		unsigned int start = 0;
		unsigned int end = 0;

		for (unsigned int i = 0; i < mCursor; i++)
		{
			if (mSource[i] >= 33 && mSource[i] <= 126)
			{
				end = i;
				if (!bStartFound)
				{
					start = i;
					bStartFound = true;
				}
			}
		}

		for (unsigned int i = start; i <= end; i++)
		{
			output += mSource[i];
		}

		return output;
	}

	char* String::GetSource() const
	{
		return mSource;
	}

	char* String::GetSourceCopy() const
	{
		char* copyData = new char[mCursor + 1];

		Memory::Copy(mSource, copyData, mCursor);
		copyData[mCursor] = '\0';

		return copyData;
	}

	unsigned int String::GetCursor() const
	{
		return mCursor;
	}



	Array<String> String::SplitByChar(const char targetChar) const
	{
		Array<String> fragments;

		unsigned int startLocation = 0;
		for (unsigned int letterIndex = 0; letterIndex < mCursor; letterIndex++)
		{
			if (mSource[letterIndex] == targetChar)
			{
				const unsigned int difference = letterIndex - startLocation;
				if (difference == 0)
					continue;

				String fragment(&mSource[startLocation], difference + 1);

				startLocation = letterIndex + 1;

				fragments.Add(fragment);
			}

		}

		const unsigned int difference = mCursor - startLocation;
		if (difference != 0)
		{
			String fragment(&mSource[startLocation], difference + 1);
			fragments.Add(fragment);
		}


		return fragments;
	}
	int String::FindIndex(const String& targetString, const unsigned int startIndex, const unsigned int targetCount) const
	{
		const unsigned int searchLength = targetString.GetCursor();

		unsigned int foundSoFar = 0;
		int index = -1;
		for (unsigned int charIndex = startIndex; charIndex < mCursor; charIndex++)
		{
			if (mSource[charIndex] == targetString[0])
			{
				if (charIndex + targetString.GetCursor() > mCursor) // discard
				{
					continue;
				}

				String subset = GetSubset(charIndex, searchLength);
				if (subset == targetString && foundSoFar == targetCount)
				{
					index = charIndex;
					foundSoFar++;
				}
			}
		}

		return index;
	}
	unsigned int String::FindIndex(const char targetChar) const
	{
		for (unsigned int i = 0; i < mCursor; i++)
		{
			if (mSource[i] == targetChar)
			{
				return i;
			}

		}

		return 0;
	}

	unsigned int String::GetCount(const char targetChar) const
	{
		unsigned int count = 0;
		for (unsigned int i = 0; i < mCursor; i++)
		{
			if (mSource[i] == targetChar)
			{
				count++;
			}

		}

		return count;
	}

	int String::FindLastIndex(const String& targetString, const unsigned int startIndex) const
	{
		const unsigned int searchLength = targetString.GetCursor();

		unsigned int lastIndexFound = -1;
		for (unsigned int charIndex = startIndex; charIndex < mCursor; charIndex++)
		{
			if (mSource[charIndex] == targetString[0])
			{
				if (charIndex + targetString.GetCursor() > mCursor) // discard
				{
					continue;
				}

				String subset = GetSubset(charIndex, searchLength);
				if (subset == targetString)
				{
					lastIndexFound = charIndex;
				}
			}
		}

		return lastIndexFound;
	}


	void String::Clear()
	{
		delete[] mSource;

		mSource = new char[1];
		mSource[0] = '\0';

		mCursor = 0;
	}

	/*
	* Operators
	*/
	const char* String::operator*() const
	{
		return mSource;
	}
	char String::operator[](const unsigned int index) const
	{
		return mSource[index];
	}

	void String::operator=(const String& target)
	{
		if (target.mCursor == 0)
		{
			mCursor = 1;
			mSource = new char[1];
			mSource[0] = '\0';
			return;
		}

		if (mSource != nullptr)
			delete[] mSource;

		mCursor = target.mCursor;
		mSource = new char[(double)mCursor + 1];

		for (unsigned int i = 0; i < mCursor; i++)
		{
			mSource[i] = target.mSource[i];
		}
		mSource[mCursor] = '\0';
	}
	void String::operator+=(const char target)
	{
		const unsigned int targetLength = mCursor + 1;

		char* newSource = new char[targetLength + 1];

		for (unsigned int i = 0; i < mCursor; i++)
		{
			newSource[i] = mSource[i];
		}

		newSource[mCursor] = target;

		newSource[mCursor + 1] = '\0';

		delete[] mSource;

		mSource = newSource;

		mCursor = targetLength;
	}
	void String::operator-=(const char* target)
	{
		const unsigned int targetCharLength = get_char_pointer_size(target);
		const unsigned int newLength = mCursor < targetCharLength ? 0 : mCursor - targetCharLength;

		if (newLength == 0)
			return;

		char* newSource = new char[newLength + (unsigned int)1];

		for (unsigned int i = 0; i < newLength; i++)
		{
			newSource[i] = mSource[i];
		}

		newSource[newLength] = '\0';

		delete[] mSource;

		mCursor = newLength;
		mSource = newSource;
	}
	void String::operator-=(const String& other)
	{
		const unsigned int targetCharLength = other.GetCursor();
		const unsigned int newLength = mCursor < targetCharLength ? 0 : mCursor - targetCharLength;

		if (newLength == 0)
			return;

		char* newSource = new char[newLength + (unsigned int)1];

		for (unsigned int i = 0; i < newLength; i++)
		{
			newSource[i] = mSource[i];
		}

		newSource[newLength] = '\0';

		delete[] mSource;

		mCursor = newLength;
		mSource = newSource;
	}
	void String::operator+=(const char* target)
	{
		unsigned int target_sourceCharLength = get_char_pointer_size(target);
		unsigned int newLength = target_sourceCharLength + mCursor;

		char* newSource = new char[newLength + (unsigned int)1];

		for (unsigned int i = 0; i < mCursor; i++)
		{
			newSource[i] = mSource[i];
		}

		{
			int targetIndex = 0;
			for (unsigned int i = mCursor; i < newLength; i++)
			{
				newSource[i] = target[targetIndex];
				targetIndex++;
			}
		}

		newSource[newLength] = '\0';

		delete[] mSource;

		mCursor = newLength;
		mSource = newSource;

	}
	void String::operator+=(const String& target)
	{
		const unsigned int targetLength = mCursor + target.GetCursor();

		char* newSource = new char[targetLength + 1];

		for (unsigned int i = 0; i < mCursor; i++)
		{
			newSource[i] = mSource[i];
		}

		int targetIndex = 0;
		for (unsigned int i = mCursor; i < targetLength; i++)
		{
			newSource[i] = target[targetIndex];
			targetIndex++;
		}

		newSource[targetLength] = '\0';

		delete[] mSource;

		mSource = newSource;

		mCursor = targetLength;
	}
	String operator+(const String& target0, const String& target1)
	{
		unsigned int newLength = target0.GetCursor() + target1.GetCursor() + 1;

		char* newSource = new char[newLength + 1];

		{
			int targetIndex = 0;
			for (unsigned int i = 0; i < target0.GetCursor(); i++)
			{
				newSource[i] = target0[targetIndex];
				targetIndex++;
			}
		}

		{
			int targetIndex = 0;
			for (unsigned int i = target0.GetCursor(); i < newLength; i++)
			{
				newSource[i] = target1[targetIndex];
				targetIndex++;
			}
		}

		newSource[newLength] = '\0';

		String newStr(newSource);
		return newStr;
	}
	bool operator==(const String& target0, const String& target1)
	{
		unsigned int target0Length = target0.GetCursor();
		unsigned int target1Length = target1.GetCursor();
		const char* target0Source = *target0;
		const char* target1Source = *target1;

		if (target0Length != target1Length)
			return false;

		for (unsigned int i = 0; i < target0Length; i++)
		{
			if (target0Source[i] != target1Source[i])
			{
				return false;
			}
		}

		return true;
	}
	bool operator!=(const String& target0, const String& target1)
	{
		unsigned int target0Length = target0.GetCursor();
		unsigned int target1Length = target1.GetCursor();
		const char* target0Source = *target0;
		const char* target1Source = *target1;

		if (target0Length != target1Length)
			return true;

		for (unsigned int i = 0; i < target0Length; i++)
		{
			if (target0Source[i] != target1Source[i])
			{
				return true;
			}
		}

		return false;
	}

	String String::GetFromFloat(const float value)
	{
		char* chars = new char[MAX_INT_DIGITS];

		sprintf(chars, "%f", value);

		return chars;
	}
	String String::GetFromInteger(const int value)
	{
		char* chars = new char[MAX_INT_DIGITS];

		sprintf(chars, "%d", value);

		return chars;
	}

	float String::ToFloat(const String& str)
	{
		float value = -1;
		std::stringstream stream(*str);
		stream >> value;
		return value;
	}

	int String::ToInteger(const String& str)
	{
		int value = -1;
		std::stringstream stream(*str);
		stream >> value;
		return value;
	}
}