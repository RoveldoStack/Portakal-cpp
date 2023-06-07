#pragma once
#include <functional>
#define GENERATE_DELEGATE(function) std::bind(&function,std::placeholders::_1)
#define GENERATE_DELEGATE_PARAMETERLESS(function) std::bind(&function)
#define GENERATE_MEMBER_DELEGATE0(object,function) std::bind(&function,object)
#define GENERATE_MEMBER_DELEGATE1(object,function,rType,...) Delegate<rType,__VA_ARGS__>(std::bind(&function,object,std::placeholders::_1))
#define GENERATE_MEMBER_DELEGATE2(object,function,rType,...) Delegate<rType,__VA_ARGS__>(std::bind(&function,object,std::placeholders::_1,std::placeholders::_2))
#define GENERATE_MEMBER_DELEGATE3(object,function,rType,...) Delegate<rType,__VA_ARGS__>(std::bind(&function,object,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3))


namespace Portakal
{
	/// <summary>
	/// Templated delegate implementation
	/// </summary>
	template<typename TReturn, typename... TParameters>
	class Delegate final
	{
	public:
		Delegate(const std::function<TReturn(TParameters...)>& function) : mFunctionPtr(function), mEmpty(false) {}
		Delegate() : mEmpty(true) {}
		~Delegate() = default;

		/// <summary>
		/// Returns whether the delegate is set
		/// </summary>
		/// <returns></returns>
		bool IsEmpty() const { return mEmpty; }

		/// <summary>
		/// Invokes the delegate function ptr
		/// </summary>
		/// <param name="...parameters"></param>
		/// <returns></returns>
		TReturn Invoke(TParameters... parameters)
		{
			return mFunctionPtr(parameters...);
		}

		/// <summary>
		/// Returns the delegate address
		/// </summary>
		/// <returns></returns>
		size_t GetAddress() const
		{
			typedef TReturn(fnType)(TParameters...);
			fnType* fnPointer = GetFunctionPtr().template target<fnType>();

			return (size_t)*fnPointer;
		}

		/// <summary>
		/// Returns the delegate function ptr
		/// </summary>
		/// <returns></returns>
		std::function<TReturn(TParameters...)> GetFunctionPtr() const
		{
			return mFunctionPtr;
		}
	private:
		std::function<TReturn(TParameters...)> mFunctionPtr;
		bool mEmpty;
	};

	template<typename TReturn, typename...TParameters>
	static bool operator ==(const Delegate<TReturn, TParameters...>& a, const Delegate<TReturn, TParameters...>& b)
	{
		return a.GetAddress() == b.GetAddress();
	}
	template<typename TReturn, typename...TParameters>
	static bool operator !=(const Delegate<TReturn, TParameters...>& a, const Delegate<TReturn, TParameters...>& b)
	{
		return a.GetAddress() != b.GetAddress();
	}
}