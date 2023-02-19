#pragma once
#include <Runtime/Containers/String.h>

namespace Portakal
{
	/// <summary>
	/// Platform agnostic process interface
	/// </summary>
	class PORTAKAL_API PlatformProcess
	{
	public:
		/// <summary>
		/// Creates anew process
		/// </summary>
		/// <param name="path"></param>
		/// <param name="cmdArguments"></param>
		/// <returns></returns>
		static PlatformProcess* Create(const String& path, const Array<String>& cmdArguments);

		/// <summary>
		/// Returns the process executable path
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String GetPath() const noexcept { return mPath; }

		/// <summary>
		/// Returns the given command line arguments to the process
		/// </summary>
		/// <returns></returns>
		FORCEINLINE Array<String> GetCmdArguments() const noexcept { return mCmdArguments; }

		/// <summary>
		/// Returns the concreted command line arguments to the process
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String GetConcretedCmdArguments() const noexcept { return mConcretedCmdArguments; }

		/// <summary>
		/// Returns whether the process runs or not
		/// </summary>
		/// <returns></returns>
		FORCEINLINE bool IsActive() const noexcept { return mActive; }

		/// <summary>
		/// Starts the process
		/// </summary>
		void Start();

		/// <summary>
		/// Ends or terminates the process
		/// </summary>
		void End();
	protected:
		PlatformProcess(const String& path,const Array<String>& cmdArguments);
		virtual ~PlatformProcess() {}

		virtual void StartCore() = 0;
		virtual void EndCore() = 0;
	private:
		String mPath;
		Array<String> mCmdArguments;
		String mConcretedCmdArguments;
		bool mActive;
	};
}