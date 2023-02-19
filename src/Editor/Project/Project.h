#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Containers/Guid.h>

namespace Portakal
{
	/// <summary>
	/// Represents a project header data
	/// </summary>
	struct PORTAKAL_API Project
	{
		/// <summary>
		/// Name of the project
		/// </summary>
		String Name;

		/// <summary>
		/// ID of the project
		/// </summary>
		Guid ID;

		/// <summary>
		/// Major version
		/// </summary>
		unsigned int VersionMajor;

		/// <summary>
		/// Minor version
		/// </summary>
		unsigned int VersionMinor;

		/// <summary>
		/// Patch version
		/// </summary>
		unsigned int VersionPatch;

		/// <summary>
		/// Project folder absolute path
		/// </summary>
		String ProjectFolderAbsolutePath;
	};
}