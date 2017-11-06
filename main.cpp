#include "OSort.h"

int main(void)
{
	//vector<int> in = { 10, 4, 23, 56, 24, 56, 87, 12, 45, 78, 34, 89, 2, 35 };
	vector<int> in;
	srand(10);
	/*for (int i = 0; i < 100000; ++i) {
		in.push_back(rand() % 1000000);
	}
	for (int i = 0; i < 900000; ++i) {
		in.push_back(1);
	}*/
	for (int i = 0; i < 100000; ++i) {
		in.push_back(rand() % 1000000);
	}
	OSort<int> s(in);
	char sign;
	cout << "Press 1 for selection sort, 2 for bubble sort, 3 for insertion sort, 4 for merge sort, 5 for quick sort, 6 for shell sort" << endl;
	cin >> sign;
	auto start_time = clock();
	sort(in.begin(), in.end());
	auto end_time = clock();
	cout << (double)(end_time - start_time) / CLOCKS_PER_SEC << endl;
	if (sign == '1') {
		s.selection_sort();
	}
	else if (sign == '2') {
		s.bubble_sort();
	}
	else if (sign == '3') {
		s.insertion_sort();
	}
	else if (sign == '4') {
		s.merge_sort();
	}
	else if (sign == '5') {
		s.quick_sort();
	}
	else if (sign == '6') {
		s.shell_sort();
	}
	else if (sign == '7') {
		s.triple_quick_sort();
	}
	else if (sign == '8') {
		s.heap_sort();
	}
	//s.show();

	return 0;
}