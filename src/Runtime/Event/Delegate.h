#include <functional>
#define GENERATE_DELEGATE(function) std::bind(&function,std::placeholders::_1)
#define GENERATE_DELEGATE_PARAMETERLESS(function) std::bind(&function)
#define GENERATE_MEMBER_DELEGATE(object,function) std::bind(&function,object,std::placeholders::_1)
#define GENERATE_MEMBER_DELEGATE_PARAMETERLESS(object,function) std::bind(&function,object)

namespace Portakal
{
	/// <summary>
	/// Templated delegate implementation
	/// </summary>
	template<typename TReturn, typename... TParameters>
	class Delegate final
	{
	public:
		Delegate(const std::function<TReturn(TParameters...)>& function) : _functionPtr(function), _empty(false) {}
		Delegate() : mEmpty(true) {}
		~Delegate() = default;

		/// <summary>
		/// Returns whether the delegate is set
		/// </summary>
		/// <returns></returns>
		bool IsEmty() const { return _empty; }

		/// <summary>
		/// Invokes the delegate function ptr
		/// </summary>
		/// <param name="...parameters"></param>
		/// <returns></returns>
		TReturn Invoke(TParameters... parameters)
		{
			return _functionPtr(parameters...);
		}
	private:
		/// <summary>
		/// Returns the delegate function ptr
		/// </summary>
		/// <returns></returns>
		std::function<TReturn(TParameters...)> GetFunctionPtr() const
		{
			return _functionPtr;
		}

		/// <summary>
		/// Returns the delegate address
		/// </summary>
		/// <returns></returns>
		size_t GetAddress() const
		{
			typedef TReturn(fnType)(TParameters...);
			fnType** fnPointer = GetFunctionPtr().template target<fnType*>();

			return (size_t)*fnPointer;
		}
	private:
		std::function<TReturn(TParameters...)> _functionPtr;
		bool _empty;
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