#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	template<typename TType>
	class SharedHeap
	{
	public:
		SharedHeap(TType* pHeap)
		{
			CreateNew(pHeap);
		}
		SharedHeap(const SharedHeap<TType>& target)
		{
			_heap = target._heap;
			_count = target._count;
			*_count++;
		}
		SharedHeap()
		{
			_heap = nullptr;
			_count = nullptr;
		}
		~SharedHeap()
		{
			Reset();
		}

		FORCEINLINE TType* GetHeap()
		{
			return _heap;
		}
		void Reset()
		{
			if (_count == nullptr)
				return;

			*_count--;

			if (_count == 0)
			{
				delete _count;
				delete _heap;
				_heap = nullptr;
				_count = nullptr;
			}

		}

		void operator==(TType* pHeap)
		{
			if (pHeap != _heap)
				Reset();

			CreateNew(pHeap);
		}

		TType* operator->() noexcept
		{
			return _heap;
		}

		
	private:
		void CreateNew(TType* pHeap)
		{
			_heap = pHeap;
			_count = new unsigned int(1);
		}
	private:
		TType* _heap;
		unsigned int* _count;
	};
}