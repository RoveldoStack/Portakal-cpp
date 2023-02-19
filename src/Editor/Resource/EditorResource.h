#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/String.h>
#include <Editor/Resource/EditorResourceType.h>

namespace Portakal
{
	/// <summary>
	/// Represents a editor specific resource, only for editor usage
	/// </summary>
	class PORTAKAL_API EditorResource
	{
		friend class EditorResourceAPI;
	public:
		EditorResource(const String& path,const String& name,const EditorResourceType type) : mName(name),mPath(path),mType(type) {}
		virtual ~EditorResource() = default;
		
		/// <summary>
		/// Returns the resource name
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String GetName() const noexcept { return mName; }

		/// <summary>
		/// Returns the resource physical path
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String GetPath() const noexcept { return mPath; }

		/// <summary>
		/// Returns the resource type
		/// </summary>
		/// <returns></returns>
		FORCEINLINE EditorResourceType GetResourceType() const noexcept { return mType; }
	private:
		const EditorResourceType mType;
		const String mName;
		const String mPath;
	};
}