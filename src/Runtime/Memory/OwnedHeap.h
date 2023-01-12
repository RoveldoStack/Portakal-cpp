#pragma once
#include <Runtime/Core/Core.h>

namespace Portakal
{
	template<typename TType>
	class OwnedHeap
	{
	public:
		OwnedHeap(TType* pHeap)
		{
			CreateNew(pHeap);
		}
		OwnedHeap(const OwnedHeap<TType>& target) = delete;
		OwnedHeap(const OwnedHeap<TType>&& target) = delete;
		OwnedHeap()
		{
			_heap = nullptr;
		}
		~OwnedHeap()
		{
			Free();
		}

		void Free()
		{
			if (_heap == nullptr)
				return;

			delete _heap;
			_heap = nullptr;
		}

		void operator ==(TType* pHeap)
		{
			Free();
			CreateNew(pHeap);
		}

		void operator ==(const OwnedHeap<TType>& target) = delete;
		void operator ==(const OwnedHeap<TType>&& target) = delete;
		OwnedHeap<TType>& operator=(const OwnedHeap<TType>& target) = delete;

		TType* operator ->() noexcept
		{
			return _heap;
		}
	private:
		void CreateNew(TType* pHeap)
		{
			_heap = pHeap;
		}
	private:
		TType* _heap;
	};
}