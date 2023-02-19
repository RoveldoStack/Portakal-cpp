#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Containers/Guid.h>

namespace Portakal
{
	class ResourceSubObject;

	/// <summary>
	/// Represents a single resource registered to the application
	/// </summary>
	class PORTAKAL_API Resource
	{
	public:
		Resource();
		~Resource();

		/// <summary>
		/// Loads sync
		/// </summary>
		void LoadSync();

		/// <summary>
		/// Unloads sync
		/// </summary>
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