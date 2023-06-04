#pragma once
#include <Runtime/Containers/String.h>
#include <Runtime/Containers/Array.h>
#include <Runtime/Rendering/RenderPassInputOutputType.h>

namespace Portakal
{
	class RenderPass;

	/// <summary>
	/// Represents a input or ouput pin of a render pass
	/// </summary>
	class PORTAKAL_API RenderPassInputOutput
	{
		friend class RenderPass;
	public:
		RenderPassInputOutput(const String& name,RenderPass* pOwnerPass) : mName(name),mOwnerPass(pOwnerPass),mInput(nullptr)
		{

		}

		/// <summary>
		/// Returns the name of the pin
		/// </summary>
		/// <returns></returns>
		FORCEINLINE String GetName() const noexcept { return mName; }

		/// <summary>
		/// Returns the owner pass of the pin
		/// </summary>
		/// <returns></returns>
		FORCEINLINE RenderPass* GetOwnerPass() const noexcept { return mOwnerPass; }

		/// <summary>
		/// Returns the input node of this IO
		/// </summary>
		/// <returns></returns>
		FORCEINLINE RenderPassInputOutput* GetInput() const noexcept { return mInput; }

		/// <summary>
		/// Returns the output nodes of this IO
		/// </summary>
		/// <returns></returns>
		FORCEINLINE const Array<RenderPassInputOutput*>& GetOutputs() const noexcept { return mOutputs; }

		/// <summary>
		/// REturn the IO data that is abstracted away
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual void* GetIOData() const noexcept = 0;

		/// <summary>
		/// Returns the IO type
		/// </summary>
		/// <returns></returns>
		FORCEINLINE virtual RenderPassInputOutputType GetIOType() const = 0;

		/// <summary>
		/// Forward this value to all outputs connected
		/// </summary>
		/// <param name="pData"></param>
		void Forward(void* pData);

		/// <summary>
		/// Connects this output pin to another IO
		/// </summary>
		/// <param name="pIO"></param>
		void ConnectOutputTo(RenderPassInputOutput* pIO);

		/// <summary>
		/// Connects this output pin to another render pass's input pin
		/// </summary>
		/// <param name="pPass"></param>
		/// <param name="inputPin"></param>
		void ConnectOutputTo(RenderPass* pPass, const String& inputIOName);
	private:
		/// <summary>
		/// Internal method that sets the input pin
		/// </summary>
		/// <param name="pIO"></param>
		void _ConnectInput(RenderPassInputOutput* pIO);

		/// <summary>
		/// Internal method that clears all the input output pins
		/// </summary>
		void _ClearInputOutputs();
	protected:
		virtual void ForwardCore(void* pData) = 0;
	private:
	private:
		const String mName;
		RenderPass* mOwnerPass;
		Array<RenderPassInputOutput*> mOutputs;
		RenderPassInputOutput* mInput;
	};
}