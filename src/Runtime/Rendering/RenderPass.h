#pragma once
#include <Runtime/Containers/Array.h>
#include <Runtime/Graphics/GraphicsDeviceObject.h>
#include <Runtime/Resource/ResourceSubObject.h>
#include <Runtime/Graphics/Command/CommandList.h>
#include <Runtime/Assert/Assert.h>
#include <Runtime/Rendering/RenderPassInputOutput.h>

namespace Portakal
{
	class RenderGraph;

	/// <summary>
	/// Represents an isolated function(s)
	/// </summary>
	class PORTAKAL_API RenderPass
	{
		friend class RenderPassInputOutput;
		friend class RenderGraph;
	public:
		RenderPass();
		virtual ~RenderPass() {}

		/// <summary>
		/// Returns the input pins
		/// </summary>
		/// <returns></returns>
		const Array<RenderPassInputOutput*>& GetInputs() const noexcept { return mInputs; }

		/// <summary>
		/// Returns the output pins
		/// </summary>
		/// <returns></returns>
		const Array<RenderPassInputOutput*>& GetOutputs() const noexcept { return mOutputs; }


		/// <summary>
		/// Connects this pass's output to another input pin
		/// </summary>
		/// <param name="name"></param>
		/// <param name="pIO"></param>
		void ConnectOutputTo(const String& name, RenderPassInputOutput* pIO);

		/// <summary>
		/// Returns the output pin with the given name
		/// </summary>
		/// <typeparam name="TOutput"></typeparam>
		/// <param name="name"></param>
		/// <returns></returns>
		template<typename TOutput>
		TOutput* GetOutputTemplated(const String& name) const
		{
			for (unsigned int i = 0; i < mOutputs.GetCursor(); i++)
				if (mOutputs[i]->GetName() == name)
					return (TOutput*)mOutputs[i];

			return nullptr;
		}

		/// <summary>
		/// Returns the input pin with the given name
		/// </summary>
		/// <typeparam name="TInput"></typeparam>
		/// <param name="name"></param>
		/// <returns></returns>
		FORCEINLINE RenderPassInputOutput* GetInput(const String& name) const;

		/// <summary>
		/// Returns the output pin with the given name
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		FORCEINLINE RenderPassInputOutput* GetOutput(const String& name) const;

		/// <summary>
		/// Checks if given pass is dependent on this pass
		/// </summary>
		/// <param name="pPass"></param>
		/// <returns></returns>
		bool IsPassDependent(RenderPass* pPass) const;

		/// <summary>
		/// Checks if this pass is dependent on the given pass
		/// </summary>
		/// <param name="pPass"></param>
		/// <returns></returns>
		bool IsPassDependentOn(RenderPass* pPass) const;

		/// <summary>
		/// Called upon every execution of the render graph
		/// </summary>
		/// <param name="pCmdList"></param>
		virtual void Execute(CommandList* pCmdList) const = 0;
	private:
		/// <summary>
		/// Internal method that binds an another IO to the input pin with the given name
		/// </summary>
		void _ConnectInputTo(const String& name,RenderPassInputOutput* pIO);
	protected:
		/// <summary>
		/// Called upon compilation
		/// </summary>
		virtual void Initialize() = 0;

		/// <summary>
		/// Called upon resource cleaning
		/// </summary>
		virtual void Finalize() = 0;

		/// <summary>
		/// Creates an input pin
		/// </summary>
		/// <typeparam name="TInput"></typeparam>
		/// <param name="name"></param>
		/// <returns></returns>
		template<typename TInput>
		TInput* CreateInput(const String& name)
		{
			/*
			* Validate if name exists
			*/
			for (unsigned int i = 0; i < mInputs.GetCursor(); i++)
				if (mInputs[i]->GetName() == name)
					return nullptr;

			TInput* pInput = new TInput(name,this);

			mInputs.Add(pInput);

			return pInput;
		}

		/// <summary>
		/// Creates an output pin
		/// </summary>
		/// <typeparam name="TOutput"></typeparam>
		/// <param name="name"></param>
		/// <returns></returns>
		template<typename TOutput>
		TOutput* CreateOutput(const String& name)
		{
			/*
			* Validate if name exists
			*/
			for (unsigned int i = 0; i < mOutputs.GetCursor(); i++)
				if (mOutputs[i]->GetName() == name)
					return nullptr;

			TOutput* pOutput = new TOutput(name,this);

			mOutputs.Add(pOutput);

			return pOutput;
		}

		/// <summary>
		/// Forwards the specified output
		/// </summary>
		/// <param name="name"></param>
		/// <param name="pData"></param>
		void ForwardOutput(const String& name,void* pData) const;
	private:
		Array<RenderPassInputOutput*> mInputs;
		Array<RenderPassInputOutput*> mOutputs;
	};
}