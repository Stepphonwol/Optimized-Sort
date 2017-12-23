#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <stack>
#include <algorithm>

using namespace std;

template<class Type>
class OSort {
	public:
		OSort(vector<Type> x) : source(x) {}
		void show() {
			for (auto c : source) {
				cout << c << " ";
			}
		}
		void selection_sort() {
			auto start_time = clock();
			selection_sort_help();
			auto end_time = clock();
			cout << "Total running time : " << (double)(end_time - start_time) / CLOCKS_PER_SEC << endl;
		}
		void bubble_sort() {
			auto start_time = clock();
			bubble_sort_help();
			auto end_time = clock();
			cout << "Total running time : " << (double)(end_time - start_time) / CLOCKS_PER_SEC << endl;
		}
		void insertion_sort() {
			auto start_time = clock();
			insertion_sort_help(0, source.size() - 1);
			auto end_time = clock();
			cout << "Total running time : " << (double)(end_time - start_time) / CLOCKS_PER_SEC << endl;
		}
		void shell_sort() {
			auto start_time = clock();
			shell_sort_help();
			auto end_time = clock();
			cout << "Total running time : " << (double)(end_time - start_time) / CLOCKS_PER_SEC << endl;
		}
		void merge_sort() {
			auto start_time = clock();
			merge_sort_help(0, source.size() - 1);
			auto end_time = clock();
			cout << "Total running time : " << (double)(end_time - start_time) / CLOCKS_PER_SEC << endl;
		}
		void intro_sort() {
			//unsigned long t;
			//int n{ 1 };
			//unsigned long per{ 10000000000 };
			//t = (unsigned long)GetCycleCount();
			double sum{ 0 };
			int t{ 10 };
			//random_shuffle(source.begin(), source.end());
			while (t--) {
				random_shuffle(source.begin(), source.end());
				auto start_time = clock();
				//int len = source.size();
				int threshold = lg(2 * (source.size() - 0));
				intro_sort_help(0, source.size() - 1, threshold);
				auto end_time = clock();
				sum += (double)(end_time - start_time) / CLOCKS_PER_SEC;
			}
			//t -= (unsigned long)GetCycleCount();
			cout << "Total running time : " << sum / 10<< endl;
		}
		void quick_sort_stack() {
			double sum{ 0 };
			int t{ 10 };
			while (t--) {
				random_shuffle(source.begin(), source.end());
				auto start_time = clock();
				quick_sort_stack_help(0, source.size() - 1);
				auto end_time = clock();
				sum += (double)(end_time - start_time) / CLOCKS_PER_SEC;
			}
			cout << "Total running time : " << sum / 10 << endl;
		}
		void triple_quick_sort() {
			auto start_time = clock();
			//random_shuffle(source.begin(), source.end());
			triple_help(0, source.size() - 1);
			auto end_time = clock();
			cout << "Total running time : " << (double)(end_time - start_time) / CLOCKS_PER_SEC << endl;
		}
		void heap_sort() {
			double sum{ 0 };
			int t{ 10 };
			while (t--) {
				random_shuffle(source.begin(), source.end());
				auto start_time = clock();
				heap_sort_help(0, source.size() - 1);
				auto end_time = clock();
				sum += (double)(end_time - start_time) / CLOCKS_PER_SEC;
			}
			//t -= (unsigned long)GetCycleCount();
			cout << "Total running time : " << sum / 10 << endl;
		}
		void verify(long long n) {
			long long i{ 0 };
			for (auto it = source.begin(); it != source.end() - 1; ++it) {
				if (!less(*it, *(it + 1)) && *it != *(it + 1)) {
					cout << "Wrong sorting at index " << it - source.begin() << endl;
					break;
				}
				//cout << *it << endl;
				++i;
			}
			if (i == n - 1) {
				cout << "All elements are in place." << endl
					<< "No elements missing" << endl;
			}
		}
	private:
		vector<Type> source;
		void swap(int i, int j) {
			Type temp = source[i];
			source[i] = source[j];
			source[j] = temp;
		}
		bool less(Type x, Type y) {
			return x < y;
		}
		void selection_sort_help() {
			for (int i = 0; i < source.size(); ++i) {
				int min = i;
				for (int j = i + 1; j < source.size(); ++j) {
					if (less(source[j], source[min])) {
						min = j;
					}
				}
				swap(i, min);
			}
		}
		void bubble_sort_help() {
			for (int i = 0; i < source.size() - 1; ++i) {
				for (int j = i; j < source.size(); ++j) {
					if (less(source[j], source[i])) {
						swap(i, j);
					}
				}
			}
		}
		void insertion_sort_help(int lo, int hi) {
			for (int i = lo + 1; i <= hi; ++i) {
				for (int j = i; j > lo && less(source[j], source[j - 1]); --j) {
					swap(j, j - 1);
				}
			}
		}
		void shell_sort_help() {
			int h{ 1 };
			int n = source.size();
			while (h < n / 3) {
				h = 3 * h + 1;
			} // constructing the ascending sequence for shell sort
			while (h >= 1) {
				for (int i = h; i < n; ++i) {
					for (int j = i; j >= h && less(source[j], source[j - h]); j -= h) {
						swap(j, j - h);
					}
				}
				h = h / 3;
			}
		}
		void merge_sort_help(int lo, int hi) {
			int mid = lo + (hi - lo) / 2;
			if (hi <= lo) {
				return;
			}
			merge_sort_help(lo, mid);
			merge_sort_help(mid + 1, hi);
			merge(lo, mid, hi);
		}
		void merge(int l, int m, int h) {
			vector<Type> aux;
			int i = l, j = m + 1;
			for (auto c : source) {
				aux.push_back(c);
			}
			for (int k = l; k <= h; ++k) {
				if (i > m) {
					source[k] = aux[j++];
				}
				else if (j > h) {
					source[k] = aux[i++];
				}
				else if (less(aux[j], aux[i])) {
					source[k] = aux[j++];
				}
				else {
					source[k] = aux[i++];
				}
			}
		}
		int partition(int lo, int hi) {
			int i = lo, j = hi + 1;
			int mid = lo + (hi - lo) / 2;
			int p = med3(lo, hi, mid);
			Type pivot = source[p];
			swap(lo, p);
			//Type pivot = source[mid];
			//swap(lo, mid);
			while (true) {
				while (less(source[++i], pivot)) {
					if (i == hi) {
						break;
					}
				}
				while (less(pivot, source[--j])) {
					if (j == lo) {
						break;
					}
				}
				if (i >= j) {
					break;
				}
				swap(i, j);
			}
			swap(j, lo);
			return j;
		}
		void intro_sort_help(int lo, int hi, int threshold) {
			//int threshold = lg(2 * (hi - lo + 1));
			if (hi <= lo + 10) {
				insertion_sort_help(lo, hi);
				return;
			}
			if (threshold <= 0) {
				heap_sort_help(lo, hi);
				return;
			}
			--threshold;
			int j = partition(lo, hi);
			intro_sort_help(lo, j - 1, threshold);
			intro_sort_help(j + 1, hi, threshold);
		}
		void quick_sort_stack_help(int lo, int hi) {
			if (hi <= lo + 10) {
				insertion_sort_help(lo, hi);
				return;
			}
			stack<int> s;
			s.push(lo);
			s.push(hi);
			while (!s.empty()) {
				int r = s.top();
				s.pop();
				int l = s.top();
				s.pop();
				if (l < r) {
					int pivot = partition(l, r);
					s.push(l);
					s.push(pivot - 1);
					s.push(pivot + 1);
					s.push(r);
				}
			}
		}
		void triple_help(int lo, int hi) {
			/*if (hi <= lo + 5) {
				insertion_sort_help(lo, hi);
				return;
			}*/
			if (hi <= lo) {
				return;
			}
			//Type pivot = source[(lo + hi) / 2];
			Type pivot = source[lo];
			int lt{ lo }, gt{ hi }, i{ lo + 1 };
			while (i <= gt) {
				if (source[i] == pivot) {
					++i;
				}
				else if (less(source[i], pivot)) {
					swap(i, lt);
					++i;
					++lt;
				}
				else {
					swap(i, gt);
					--gt;
				}
			}
			triple_help(lo, lt - 1);
			triple_help(gt + 1, hi);
		}

		int med3(int i, int j, int k) {
			if ((source[i] <= source[j] && source[i] >= source[k]) || (source[i] >= source[j] && source[i] <= source[k])) {
				return i;
			}
			else if ((source[k] <= source[i] && source[k] >= source[j]) || (source[k] >= source[i] && source[k] <= source[j])) {
				return k;
			}
			else if ((source[j] <= source[i] && source[j] >= source[k]) || (source[j] >= source[i] && source[j] <= source[k])) {
				return j;
			}
			/*if ((i - j) * (i - k) <= 0) {
				return i;
			}
			else if ((j - i) * (j - k) <= 0) {
				return j;
			}
			else if ((k - i) * (k - j) <= 0) {
				return k;
			}*/
		}
		void heap_sort_help(int lo, int hi) {
			int n = hi - lo + 1;
			for (int k = n / 2 - 1; k >= 0; --k) {
				sink(lo, k, n);
			}
			//--n;
			while (n > 1) {
				swap(lo, hi--);
				--n;
				sink(lo, 0, n);
			}
		}
		void sink(int lo, int k, int n) {
			while (2 * k + 1 < n) {
				int j = 2 * k + 1 + lo; // left child of k
				if (j < n - 1 + lo && less(source[j], source[j + 1])) {
					++j;
				}
				if (!less(source[k + lo], source[j])) {
					break;
				}
				swap(k + lo, j);
				k = j - lo;
			}
		}
		int lg(int n) {
			int k{ 0 };
			for (k = 0; n > 1; n >>= 1) {
				++k;
			}
			return k;
		}
		unsigned _int64 GetCycleCount() {
			_asm _emit 0x0F
			_asm _emit 0x31
		}
};
