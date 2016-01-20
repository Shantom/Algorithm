#include <iostream>
#include <ctime>
#include <iomanip>
#include <array>
#include <fstream>
#include <vector>
#include <map>
#include <stack>
using namespace std;

ifstream file("sort.txt");
class Sort
{
public:
	Sort(int N);
	~Sort();
	void Print();
	void Reverse() { for (int i = 0; i <= num / 2; ++i) Swap(i, num - i - 1); cout << "Reversed.\n" << endl; };
	void InsertSort();
	void ShellSort(vector<int> d);
	void BubbleSort();
	void QuickSort();
	void QuickSort_nonRecur();
	void SelectSort();
	void HeapSort();
	void MergeSort();
	void RadixSort();
private:
	array<int, 10000> data;
	int num;
	int move;
	int swap;
	int seek;
	double time;
	void QSort(int left, int right);
	int Partition(int i, int j);
	void Heapify(int start, int end);
	void MSort(int left, int right);
	int *reg;
	int Maxbit();
	inline void Swap(int a, int b);
	inline void PrintComplex() { cout << left << "Seek: " << setw(10) << seek << " Move: " << setw(10) << move << " Swap: " << setw(10) << swap << " Time: " << time << "ms\n" << endl; }
};

Sort::Sort(int N) :num(N)
{
	data.fill(-1);
	for (int i = 0; i < num; i++)
		file >> data[i];
}

Sort::~Sort()
{
}

void Sort::Print()
{
	for (int i = 0; i < num; ++i)
		cout << data[i] << ' ';
	cout << endl;
}

void Sort::InsertSort()
{
	cout << "InsertSort:" << endl;
	move = swap = seek = 0;
	clock_t start, finish;
	start = clock();

	int tmp;
	for (int i = 1; i < num; i++)
	{
		tmp = data[i];
		for (int j = i - 1; j >= -1; j--)
		{
			++seek;
			if (j == -1 || data[j] <= data[i])
			{
				for (int k = i - 1; k > j; k--)
				{
					data[k + 1] = data[k];
					++move;
				}
				data[j + 1] = tmp;
				break;
			}
		}
	}

	finish = clock();
	time = (double)(finish - start);
	//Print();
	PrintComplex();
	swap = move = seek = 0;
}

void Sort::ShellSort(vector<int> d)
{
	cout << "ShellSort: \t\t";
	for (auto a : d)
		cout << a << " ";
	cout << endl;
	move = swap = seek = time = 0;
	clock_t start, finish;
	start = clock();
	for (auto a : d)
	{
		for (int m = 0; m < a; m++)
		{
			int tmp;
			for (int i = m + a; i < num; i += a)
			{
				tmp = data[i];
				for (int j = i - a; true; j -= a)
				{
					++seek;
					if (j < 0 || data[j] <= data[i])
					{
						for (int k = i - a; k > j; k -= a)
						{
							data[k + a] = data[k];
							++move;
						}
						data[j + a] = tmp;
						break;
					}
				}
			}
		}
	}
	finish = clock();
	time = (double)(finish - start);
	//Print();
	PrintComplex();
	swap = move = seek = time = 0;
}

void Sort::BubbleSort()
{
	cout << "BubbleSort:" << endl;
	move = swap = seek = time = 0;
	clock_t start, finish;
	start = clock();
	bool flag;
	for (int i = 0; i < num; i++)
	{
		flag = false;
		for (int j = 0; j < num - i - 1; j++)
		{
			++seek;
			if (data[j] > data[j + 1])
			{
				Swap(j, j + 1);
				++swap;
				flag = true;
			}
		}
		if (!flag)
			break;
	}
	finish = clock();
	time = (double)(finish - start);
	//Print();
	PrintComplex();
	swap = move = seek = time = 0;
}

void Sort::QuickSort()
{
	cout << "QuickSort:" << endl;
	move = swap = seek = time = 0;
	clock_t start, finish;
	start = clock();

	QSort(0, num - 1);

	finish = clock();
	time = (double)(finish - start);
	//Print();
	PrintComplex();
	swap = move = seek = time = 0;

	InsertSort();
}

void Sort::QuickSort_nonRecur()
{
	cout << "QuickSort_NonRecerrance:" << endl;
	move = swap = seek = time = 0;
	clock_t start, finish;
	start = clock();

	//stack<pair<int, int>> S;//for effectency, template stack is not used
	//S.push({ 0, num - 1 });
	int S[10000];
	int top = -1;
	S[0] = 0;
	S[1] = num - 1;
	top = 1;
	int left, right;
	while (top != -1)
	{
		right = S[top--];
		left = S[top--];
		if (right <= left)
			continue;

		int pivot = left;
		int i = left;
		int j = right;

		while (i < j)
		{
			while (data[j] >= data[pivot] && i < j)
			{
				--j;
				++seek;
			}
			while (data[i] <= data[pivot] && i < j)
			{
				++i;
				++seek;
			}
			if (i < j)
			{
				Swap(i, j);
				++swap;
			}
		}
		Swap(i, pivot);
		++swap;

		S[++top] = left;
		S[++top] = i - 1;
		S[++top] = i + 1;
		S[++top] = right;
	}
	finish = clock();
	time = (double)(finish - start);
	//Print();
	PrintComplex();
	swap = move = seek = time = 0;
}

void Sort::SelectSort()
{
	cout << "SelectSort:" << endl;
	move = swap = seek = time = 0;
	clock_t start, finish;
	start = clock();

	for (int i = 0; i < num; i++)
	{
		int min = data[i], k = i;
		for (int j = i + 1; j < num; j++)
		{
			if (data[j] < min)
			{
				min = data[j];
				k = j;
			}
			++seek;
		}
		if (k != i)
		{
			Swap(k, i);
			++swap;
		}
	}

	finish = clock();
	time = (double)(finish - start);
	//Print();
	PrintComplex();
	swap = move = seek = time = 0;
}

void Sort::HeapSort()
{
	cout << "HeapSort:" << endl;
	move = swap = seek = time = 0;
	clock_t start, finish;
	start = clock();

	for (int i = (num - 1) / 2; i >= 0; i--)
		Heapify(i, num);
	for (int i = num - 1; i > 0; i--)
	{
		Swap(i, 0);
		++swap;
		Heapify(0, i);
	}

	finish = clock();
	time = (double)(finish - start);
	//Print();
	PrintComplex();
	swap = move = seek = time = 0;
}

void Sort::MergeSort()
{
	cout << "HeapSort:" << endl;
	move = swap = seek = time = 0;
	clock_t start, finish;
	start = clock();

	reg = new int[num];
	MSort(0, num);
	delete[] reg;

	finish = clock();
	time = (double)(finish - start);
	//Print();
	PrintComplex();
	swap = move = seek = time = 0;
}

void Sort::RadixSort()
{
	cout << "RadixSort:" << endl;
	move = swap = seek = time = 0;
	clock_t start, finish;
	start = clock();

	int d = Maxbit();
	int count[10];
	int radix = 1;
	reg = new int[num];
	int j, k;
	for (int i = 0; i < d; i++)
	{
		for (j = 0; j < 10; j++)
			count[j] = 0;
		for (j = 0; j < num; j++)
		{
			k = (data[j] / radix) % 10;
			++count[k];
			++seek;
		}
		for (j = 0; j < 9; j++)
			count[j + 1] = count[j] + count[j + 1];
		for (j = num - 1; j >= 0; j--)
		{
			k = (data[j] / radix) % 10;
			reg[--count[k]] = data[j];
			++move;
		}
		for (j = 0; j < num; j++)
		{
			data[j] = reg[j];
			++move;
		}
		radix *= 10;
	}
	delete[] reg;

	finish = clock();
	time = (double)(finish - start);
	//Print();
	PrintComplex();
	swap = move = seek = time = 0;
}

void Sort::QSort(int left, int right)
{
	if (right - left <= 8)
		return;

	int i = Partition(left, right);

	QSort(left, i - 1);
	QSort(i + 1, right);

}

int Sort::Partition(int i, int j)
{
	if (data[i] > data[j])
	{
		Swap(i, j);
		++swap;
	}
	if (data[(i+j)/2] > data[j])
	{
		Swap(i, j);
		++swap;
	}
	if (data[i] > data[(i+j)/2])
	{
		Swap(i, j);
		++swap;
	}
	Swap(i, (i + j) / 2);
	++swap;

	int pivot = i;
	while (i < j)
	{
		while (data[j] >= data[pivot] && i < j)
		{
			--j;
			++seek;
		}
		while (data[i] <= data[pivot] && i < j)
		{
			++i;
			++seek;
		}
		if (i < j)
		{
			Swap(i, j);
			++swap;
		}
	}
	Swap(i, pivot);
	++swap;
	return i;
}

void Sort::Heapify(int start, int end)
{
	int parent = start;
	int child = start * 2 + 1;

	while (child < end)
	{
		if (child + 1 < end && data[child] < data[child + 1])
			++child;
		++seek;
		++seek;
		if (data[parent] < data[child])
		{
			Swap(parent, child);
			++swap;
			parent = child;
			child = parent * 2 + 1;
		}
		else
			return;
	}
}

void Sort::MSort(int left, int right)
{
	if (left + 1 >= right)
		return;

	int len = right - left;
	int mid = left + (len >> 1);
	int start1 = left, end1 = mid;
	int start2 = mid, end2 = right;

	MSort(start1, end1);
	MSort(start2, end2);

	int k = left;
	while (start1 < end1&&start2 < end2)
	{
		reg[k++] = data[start1] < data[start2] ? data[start1++] : data[start2++];
		++seek;
		++move;
	}
	while (start1 < end1)
	{
		reg[k++] = data[start1++];
		++move;
	}
	while (start2 < end2)
	{
		reg[k++] = data[start2++];
		++move;
	}
	for (k = left; k < right; ++k)
	{
		data[k] = reg[k];
		++move;
	}
}

int Sort::Maxbit()
{
	int max = 0;
	for (int i = 0; i < num; i++)
	{
		int tmp = data[i];
		int d = 1;
		while (tmp)
		{
			tmp /= 10;
			++d;
		}
		max = max > d ? max : d;
		++seek;
	}
	return max;
}

inline void Sort::Swap(int a, int b)
{
	if (a == b || data[a] == data[b]) {
		--swap;
		return;
	}
	data[a] = data[a] ^ data[b];
	data[b] = data[a] ^ data[b];
	data[a] = data[a] ^ data[b];
}

int main()
{
	Sort S(10000);
	vector<int> d = { 501,251,126,64,33,17,8,5,3,1 };
	//S.ShellSort(d);
	S.QuickSort();
	//S.Print();
	//ofstream ofile("sort.txt");
	//for (int i = 0; i < 10000; i++)
	//{
	//	srand(i*1000000);
	//	ofile << rand() << endl;
	//}
}