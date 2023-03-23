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
		PlatformProcess(const String& path, const Array<String>& parameters);
		~PlatformProcess();

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
		FORCEINLINE Array<String> GetParameters() const noexcept { return mParameters; }

		/// <summary>
		/// Returns the concreted command line arguments to the process
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String GetConcretedCommand() const noexcept { return mConcretedCommand; }

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
		/// Terminates the process
		/// </summary>
		void Terminate();

		/// <summary>
		/// Waits for process to finish
		/// </summary>
		void WaitForFinish();

		virtual void StartCore() = 0;
		virtual void WaitForFinishCore() = 0;
		virtual void TerminateCore() = 0;
	private:
		const String mPath;
		const Array<String> mParameters;
		String mConcretedCommand;
		bool mActive;
	};
}