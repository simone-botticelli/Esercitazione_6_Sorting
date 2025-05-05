#pragma once

#include <iostream>
#include <vector>

using namespace std;

namespace SortLibrary {

template<typename T>
concept Sortable = requires(T& t) {
    {t < t} -> std::convertible_to<bool>;
};

template<Sortable T>
void BubbleSort(std::vector<T>& v)
{
	size_t n = v.size();
	bool swapped;

	for (size_t i = 0; i < n - 1; ++i) {
		swapped = false;
		for (size_t j = 0; j < n - i - 1; ++j) {
			if (v[j + 1] < v[j]) {
				swap(v[j], v[j + 1]);
				swapped = true;
			}
		}
		if (!swapped) break; //vector already ordered 
	}
}

template<Sortable T>
void heapify(std::vector<T>& v, size_t n, size_t i)
{
	size_t largest = i;
	size_t left = 2 * i + 1;
	size_t right = 2 * i + 2;

	if (left < n && v[largest] < v[left])
		largest = left;

	if (right < n && v[largest] < v[right])
		largest = right;

	if (largest != i) {
		swap(v[i], v[largest]);
		heapify(v, n, largest);
	}
}

template<Sortable T>
void HeapSort(std::vector<T>& v)
{
	size_t n = v.size();

	// create heap
	for (int i = n / 2 - 1; i >= 0; --i)
		heapify(v, n, i);

	// heap single element extraction
	for (int i = n - 1; i > 0; --i) {
		swap(v[0], v[i]); // moves max to the end
		heapify(v, i, 0); // rebuilds heap on sub-vector
	}
}

}
