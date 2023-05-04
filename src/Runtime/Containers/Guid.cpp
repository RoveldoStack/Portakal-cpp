#include "Guid.h"
#include <Runtime/Memory/Memory.h>

#ifdef PORTAKAL_OS_WINDOWS
#include <Runtime/Win32/Win32Guid.h>
typedef Portakal::Win32Guid GuidAbstraction;
#endif
#include <stdio.h>

namespace Portakal
{
	Guid Guid::Create()
	{
		Guid output = Guid();
		GuidAbstraction::Create(output);

		return output;
	}
	String Guid::ToString(const Guid& id)
	{
		char* pData = new char[33];

		const unsigned int v = sprintf(pData, "%.8lX%.8lX%.8lX%.8lX%", id.A, id.B, id.C, id.D);

		String str(pData, v);

		delete[] pData;

		return str;
	}
	Guid Guid::FromString(const String& text)
	{
		Guid output;
		sscanf(*text,
			"%8x%8x%8x%8x",
			&output.A, &output.B, &output.C,
			&output.D);

		return output;
	}
	Guid Guid::Zero()
	{
		Guid id = {};
		id.A = 0;
		id.B = 0;
		id.C = 0;
		id.D = 0;

		return id;
	}
	Guid::Guid(unsigned int a, unsigned int b, unsigned int c, unsigned int d) : A(a), B(b), C(c), D(d)
	{

	}
	Guid::Guid() : A(0), B(0), C(0), D(0)
	{

	}
	Guid::~Guid()
	{

	}
	PORTAKAL_API bool operator==(const Guid& a, const Guid& b)
	{
		return
			a.A == b.A &&
			a.B == b.B &&
			a.C == b.C &&
			a.D == b.D;

	}
	PORTAKAL_API bool operator!=(const Guid& a, const Guid& b)
	{
		return
			a.A != b.A ||
			a.B != b.B ||
			a.C != b.C ||
			a.D != b.D;
	}
}