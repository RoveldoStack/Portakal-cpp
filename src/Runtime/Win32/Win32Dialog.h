#include <Runtime/Containers/String.h>

namespace Portakal
{
	class PORTAKAL_API Win32Dialog
	{
	public:
		Win32Dialog() = delete;
		~Win32Dialog() = delete;

		static void CreateOpenFileDialog(const String& filter);
		static String CreateOpenFolderDialog();
	};
}