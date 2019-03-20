#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void setMinAndMax(int arr[], int size, int *min, int *max) {
	if (size < 1) {
		return;
	}
	int tmpMin = arr[0], tmpMax = arr[0];
	for (int i = 0; i < size; i++) {
		if (arr[i] < tmpMin) {
			tmpMin = arr[i];
		}
		if (arr[i] > tmpMax) {
			tmpMax = arr[i];
		}
	}
	*min = tmpMin;
	*max = tmpMax;
}

void bubbleSort(vector<int> *vec) {
	for (int i = 0; i < (*vec).size(); i++) {
		for (int j = 1; j < (*vec).size(); j++) {
			if ((*vec)[j - 1] > (*vec)[j]) {
				int temp = (*vec)[j - 1];
				(*vec)[j - 1] = (*vec)[j];
				(*vec)[j] = temp;
			}
		}
	}
}

void bucketSort(int arr[], int size) {
	int min = 0, max = 0;
	setMinAndMax(arr, size, &min, &max);
	if (min == max) {
		return;
	}

	int bucketsCount = size / 10 < 5 ? size / 2 : size / 10;
	float delta = (float(max - min)) / bucketsCount;
	vector<vector<int>> buckets;

	for (int i = 0; i < bucketsCount; i++) {
		buckets.push_back(vector<int>());
	}

	for (int i = 0; i < size; i++) {
		int index = (int)((arr[i] - min) / delta);
		buckets[index >= bucketsCount ? bucketsCount - 1 : index].push_back(arr[i]);
	}

	for (int i = 0; i < bucketsCount; i++) {
		bubbleSort(&buckets[i]);
	}

	int curIndex = 0;

	for (int i = 0; i < bucketsCount; i++) {
		for (int j = 0; j < buckets[i].size(); j++) {
			arr[curIndex] = buckets[i][j];
			curIndex++;
		}
	}
}

int main()
{
	int size;

	ifstream input("input.txt");

	input >> size;

	int *inputArray = new int[size];

	for (int i = 0; i < size; i++) {
		input >> inputArray[i];
	}

	input.close();
	ofstream output("output.txt");

	bucketSort(inputArray, size);

	for (int i = 0; i < size; i++) {
		output << inputArray[i] << " ";
	}

	output.close();

	return 0;
}
