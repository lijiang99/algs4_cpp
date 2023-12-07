#ifndef HEAP_H_
#define HEAP_H_

#include <algorithm>

namespace algs4 {
	template <typename T, typename Compare>
	void Swim(T *arr, int len, int i) {
		Compare compare;
		while (i > 0) {
			int parent = (i - 1) >> 1;
			if (!compare(arr[parent], arr[i])) break;
			std::swap(arr[i], arr[parent]);
			i = parent;
		}
	}

	template <typename T, typename Compare>
	void Sink(T *arr, int len, int i) {
		Compare compare;
		int child = 2 * i + 1;
		while (child < len) {
			if (child+1 < len && compare(arr[child], arr[child+1])) ++child;
			if (!compare(arr[i], arr[child])) break;
			std::swap(arr[i], arr[child]);
			i = child;
			child = 2 * i + 1;
		}
	}

	// 自底向上建堆
	template <typename T, typename Compare = std::less<T>>
	void BuildHeap(T *arr, int len) {
		for (int i = (len - 2) >> 1; i >= 0; --i)
			Sink<T, Compare>(arr, len, i);
	}

	// 自顶向下建堆
	template <typename T, typename Compare = std::less<T>>
	void BuildHeapUB(T *arr, int len) {
		for (int i = 1; i < len; ++i)
			Swim<T, Compare>(arr, len, i);
	}
}

#endif
