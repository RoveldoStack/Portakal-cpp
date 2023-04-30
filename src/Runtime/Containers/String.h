#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Array.h>
namespace Portakal
{
	/// <summary>
	/// Basic string implementation
	/// </summary>
	class PORTAKAL_API String final
	{
	public:
		static String Empty();
		/// <summary>
		/// Returns the string representation of a float
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		static String GetFromFloat(const float value);

		/// <summary>
		/// Returns the string representation of a int
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		static String GetFromInteger(const int value);

		/// <summary>
		/// Returns the string representation of a longlong
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		static String GetFromLongLong(const long long value);

		/// <summary>
		/// Returns the float representation of a string
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		static float ToFloat(const String& value);

		/// <summary>
		/// Returns the integer representation of a string
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		static int ToInteger(const String& value);

		static long long ToLongLong(const String& str);
	public:
		String();
		String(const String& other);
		String(const char* other);
		String(unsigned int size);
		String(const char* target, unsigned int size);
		String(const unsigned char* target, unsigned int size);

		~String();

		/// <summary>
		/// Returns the size of the string
		/// </summary>
		/// <returns></returns>
		FORCEINLINE unsigned int GetCursor() const;

		/// <summary>
		/// Returns the source data ptr of the string
		/// </summary>
		/// <returns></returns>
		FORCEINLINE char* GetSource() const;

		/// <summary>
		/// Returns the copy of the string as a c string
		/// </summary>
		/// <returns></returns>
		FORCEINLINE char* GetSourceCopy() const;

		/// <summary>
		/// Finds the index of the given sub string
		/// </summary>
		/// <param name="targetString"></param>
		/// <param name="startIndex"></param>
		/// <param name="count"></param>
		/// <returns></returns>
		int FindIndex(const String& targetString, const unsigned int startIndex, const unsigned int count = 0) const;

		/// <summary>
		/// Finds the last reoccuruance index of the given sub string
		/// </summary>
		/// <param name="targetString"></param>
		/// <param name="startIndex"></param>
		/// <returns></returns>
		int FindLastIndex(const String& targetString, const unsigned int startIndex) const;

		/// <summary>
		/// Finds the index of the specified char
		/// </summary>
		/// <param name="targetChar"></param>
		/// <returns></returns>
		int FindIndex(const char targetChar) const;
		
		/// <summary>
		/// Finds the index of the specified string
		/// </summary>
		/// <param name="target"></param>
		/// <returns></returns>
		int FindIndex(const String& target) const;

		/// <summary>
		/// Returns the count of the given char
		/// </summary>
		/// <param name="targetChar"></param>
		/// <returns></returns>
		unsigned int GetCount(const char targetChar) const;

		/// <summary>
		/// Splits the string by the given char returns the fragment array
		/// </summary>
		/// <param name="targetChar"></param>
		/// <returns></returns>
		Array<String> SplitByChar(const char targetChar) const;

		/// <summary>
		/// Returns the substring with the given interval
		/// </summary>
		/// <param name="start"></param>
		/// <param name="length"></param>
		/// <returns></returns>
		String GetSubset(const unsigned int start, const unsigned  int length) const;

		/// <summary>
		/// Trims the whitespace entrailling characters
		/// </summary>
		/// <returns></returns>
		String Trim() const;

		/// <summary>
		/// Trims the given blacklist
		/// </summary>
		/// <param name="blackList"></param>
		/// <returns></returns>
		String Trim(const Array<char>& blackList) const;

		/// <summary>
		/// Frees the string data
		/// </summary>
		void Clear();

		/*
		* Operators
		*/
		const char* operator*() const;
		void operator+=(const String& other);
		void operator+=(const char* other);
		void operator+=(const char other);
		void operator-=(const char* other);
		void operator-=(const String& other);
		char operator[](const unsigned int index) const;
		void operator=(const String& other);

	private:
		char* mSource;
		unsigned int mCursor;
	};

	PORTAKAL_API String operator+(const String& target0, const String& target1);
	PORTAKAL_API bool operator==(const String& target0, const String& target1);
	PORTAKAL_API bool operator!=(const String& target0, const String& target1);
}