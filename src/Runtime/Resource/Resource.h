#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/Guid.h>

namespace Portakal
{
	class ResourceSubObject;
	class PORTAKAL_API Resource
	{
	public:
		Resource();
		~Resource();

		void LoadSync();
		void UnloadSync();
	private:
		ResourceSubObject* mSubObject;
		Guid mID;
		String mName;
		String mAbsolutePath;
		String mType;
		unsigned long long mByteOffset;
		unsigned long long mSize;

		bool mLoaded;

	};
}