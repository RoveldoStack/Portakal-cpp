#pragma once
#include <Runtime/Core/Core.h>
#include <Runtime/Containers/String.h>
#include <Editor/Resource/EditorResourceType.h>

namespace Portakal
{
	class PORTAKAL_API EditorResource
	{
		friend class EditorResourceAPI;
	public:
		EditorResource(const String& path,const String& name,const EditorResourceType type) : mName(name),mPath(path),mType(type) {}
		virtual ~EditorResource() = default;
		
		FORCEINLINE String GetName() const noexcept { return mName; }
		FORCEINLINE String GetPath() const noexcept { return mPath; }
		FORCEINLINE EditorResourceType GetResourceType() const noexcept { return mType; }
	private:
		const EditorResourceType mType;
		const String mName;
		const String mPath;
	};
}