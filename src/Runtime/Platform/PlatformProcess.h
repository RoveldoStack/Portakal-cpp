#pragma once
#include <Runtime/Containers/String.h>

namespace Portakal
{
	class PORTAKAL_API PlatformProcess
	{
	public:
		static PlatformProcess* Create(const String& path, const Array<String>& cmdArguments);

		FORCEINLINE String GetPath() const noexcept { return _path; }
		FORCEINLINE Array<String> GetCmdArguments() const noexcept { return _cmdArguments; }
		FORCEINLINE String GetConcretedCmdArguments() const noexcept { return _concretedCmdArguments; }
		FORCEINLINE bool IsActive() const noexcept { return _active; }

		void Start();
		void End();
	protected:
		PlatformProcess(const String& path,const Array<String>& cmdArguments);
		virtual ~PlatformProcess() {}

		virtual void StartCore() = 0;
		virtual void EndCore() = 0;
	private:
		String _path;
		Array<String> _cmdArguments;
		String _concretedCmdArguments;
		bool _active;
	};
}