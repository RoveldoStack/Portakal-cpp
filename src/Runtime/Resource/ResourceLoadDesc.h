#include <Runtime/Containers/String.h>

namespace Portakal
{
	struct PORTAKAL_API ResourceLoadDesc
	{
		String Name;
		String AbsolutePath;
		unsigned long long SourceByteStart;
		unsigned long long SourceByteEnd;
		bool bPackedFile;
		String Type;
	};
}