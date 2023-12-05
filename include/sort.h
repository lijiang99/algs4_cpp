#ifndef ALGS4_SORT_H_
#define ALGS4_SORT_H_

#include <algorithm>

namespace algs4 {
	template <typename T, typename Compare = std::less<T>>
	class Sort {
		public:
			static void SelectionSort(T *arr, int len);
			static void InsertionSort(T *arr, int len);
			static void ShellSort(T *arr, int len);
			static void MergeSort(T *arr, int len);
			static void MergeSortBU(T *arr, int len);
		private:
			static void MergeSortCore(T *arr, T *aux_arr, int low, int high);
			static void Merge(T *arr, T *aux_arr, int low, int mid, int high);
		private:
			static Compare compare_;
	};

	template <typename T, typename Compare>
	Compare Sort<T, Compare>::compare_ = Compare();

	template <typename T, typename Compare>
	void Sort<T, Compare>::SelectionSort(T *arr, int len) {
		for (int i = 0; i < len; ++i) {
			int min_idx = i;
			for (int j = i + 1; j < len; ++j)
				if (compare_(arr[j], arr[min_idx])) min_idx = j;
			std::swap(arr[i], arr[min_idx]);
		}
	}

	template <typename T, typename Compare>
	void Sort<T, Compare>::InsertionSort(T *arr, int len) {
		for (int i = 1; i < len; ++i) {
			for (int j = i; j > 0 && compare_(arr[j], arr[j-1]); --j)
				std::swap(arr[j], arr[j-1]);
		}
	}

	// 插入排序优化
	// 将所有较大的元素一次性右移一位可减少交换两个元素的次数(std::swap)
	/* template <typename T, typename Compare> */
	/* void Sort<T, Compare>::InsertionSort(T *arr, int len) { */
	/* 	for (int i = 1; i < len; ++i) { */
	/* 		int j = i - 1; */
	/* 		while (j >= 0 && compare_(arr[i], arr[j])) --j; */
	/* 		++j; */
	/* 		T tmp = arr[i]; */
	/* 		std::copy_backward(arr+j, arr+i, arr+i+1); */
	/* 		arr[j] = tmp; */
	/* 	} */
	/* } */

	template <typename T, typename Compare>
	void Sort<T, Compare>::ShellSort(T *arr, int len) {
		int h = 1;
		while (h < len/3) h = 3 * h + 1;
		while (h > 0) {
			for (int i = h; i < len; ++i) {
				for (int j = i; j >= h && compare_(arr[j], arr[j-h]); j -= h)
					std::swap(arr[j], arr[j-h]);
			}
			h /= 3;
		}
	}

	// 希尔排序优化
	// 使用预先设置的固定增长序列，可将性能提升20%-40%
	/* template <typename T, typename Compare> */
	/* void Sort<T, Compare>::ShellSort(T *arr, int len) { */
	/* 	static int h[16] = {1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905, */
	/* 						8929, 16001, 36289, 64769, 146305, 260609}; */
	/* 	int k = 15; */
	/* 	while (k > 0 && h[k] >= len) --k; */
	/* 	while (k >= 0) { */
	/* 		for (int i = h[k]; i < len; ++i) { */
	/* 			for (int j = i; j >= h[k] && compare_(arr[j], arr[j-h[k]]); j -= h[k]) */
	/* 				std::swap(arr[j], arr[j-h[k]]); */
	/* 		} */
	/* 		--k; */
	/* 	} */
	/* } */

	template <typename T, typename Compare>
	void Sort<T, Compare>::MergeSort(T *arr, int len) {
		T *aux_arr = new T[len];
		MergeSortCore(arr, aux_arr, 0, len);
		delete[] aux_arr;
	}

	template <typename T, typename Compare>
	void Sort<T, Compare>::MergeSortCore(T *arr, T *aux_arr, int low, int high) {
		if (high - low < 2) return;
		int mid = (low + high) >> 1;
		MergeSortCore(arr, aux_arr, low, mid);
		MergeSortCore(arr, aux_arr, mid, high);
		Merge(arr, aux_arr, low, mid, high);
	}

	template <typename T, typename Compare>
	void Sort<T, Compare>::Merge(T *arr, T *aux_arr, int low, int mid, int high) {
		std::copy(arr+low, arr+high, aux_arr+low);
		for (int i = low, j = mid, k = low; k < high; ++k) {
			if (i >= mid) arr[k] = aux_arr[j++];
			else if (j >= high) arr[k] = aux_arr[i++];
			else arr[k] = compare_(aux_arr[i], aux_arr[j]) ? aux_arr[i++] : aux_arr[j++];
		}
	}

	// 归并排序优化
	/* template <typename T, typename Compare> */
	/* void Sort<T, Compare>::MergeSort(T *arr, int len) { */
	/* 	T *aux_arr = new T[len]; */
	/* 	std::copy(arr, arr+len, aux_arr); */
	/* 	MergeSortCore(arr, aux_arr, 0, len); */
	/* 	delete[] aux_arr; */
	/* } */

	/* template <typename T, typename Compare> */
	/* void Sort<T, Compare>::MergeSortCore(T *arr, T *aux_arr, int low, int high) { */
	/* 	// 改进1: 使用插入排序处理小规模数组(len <= 15) */
	/* 	if (high - low <= 15) { */
	/* 		InsertionSort(arr+low, high-low); */
	/* 		return; */
	/* 	} */
	/* 	int mid = (low + high) >> 1; */
	/* 	// 改进3: 递归调用中通过交换arr和aux_arr来避免元素复制到辅助空间的开销 */
	/* 	MergeSortCore(aux_arr, arr, low, mid); */
	/* 	MergeSortCore(aux_arr, arr, mid, high); */
	/* 	Merge(arr, aux_arr, low, mid, high); */
	/* } */

	/* template <typename T, typename Compare> */
	/* void Sort<T, Compare>::Merge(T *arr, T *aux_arr, int low, int mid, int high) { */
	/* 	// 改进2: 若左子序列的最大值(arr[mid-1])小于等于右子序列的最小值(arr[mid]) */
	/* 	// 则可认为两个子序列的组合已经有序，无需再进行合并 */
	/* 	if (!compare_(arr[mid], arr[mid-1])) return; */
	/* 	for (int i = low, j = mid, k = low; k < high; ++k) { */
	/* 		if (i >= mid) arr[k] = aux_arr[j++]; */
	/* 		else if (j >= high) arr[k] = aux_arr[i++]; */
	/* 		else arr[k] = compare_(aux_arr[i], aux_arr[j]) ? aux_arr[i++] : aux_arr[j++]; */
	/* 	} */
	/* } */

	template <typename T, typename Compare>
	void Sort<T, Compare>::MergeSortBU(T *arr, int len) {
		T *aux_arr = new T[len];
		for (int sz = 1; sz < len; sz *= 2) {
			for (int low = 0; low < len-sz; low += 2*sz)
				Merge(arr, aux_arr, low, low+sz, std::min(low+2*sz, len));
		}
		delete[] aux_arr;
	}


}

#endif