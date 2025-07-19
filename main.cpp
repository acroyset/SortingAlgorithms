#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <random>

bool check(const std::vector<int>& v) {
    for (int i = 1; i < v.size(); ++i) {
        if (v[i-1] > v[i]) {
            return false;
        }
    }
    return true;
}

int getMax(const std::vector<int>& arr) {
    int maxVal = 0;
    for (int num : arr)
        if (num > maxVal)
            maxVal = num;
    return maxVal;
}
int getDigit(int num, int exp) {
    return (num / exp) % 10;
}
void recursiveRadixSort(std::vector<int>& arr, int left, int right, int exp) {
    if (left >= right || exp == 0)
        return;

    std::vector<std::vector<int>> buckets(10);

    // Place elements into buckets by current digit
    for (int i = left; i <= right; ++i) {
        int digit = getDigit(arr[i], exp);
        buckets[digit].push_back(arr[i]);
    }

    // Flatten buckets back into original array and recurse
    int index = left;
    for (int d = 0; d < 10; ++d) {
        if (!buckets[d].empty()) {
            for (int num : buckets[d])
                arr[index++] = num;

            // Recurse for this bucket if more than one element
            if (buckets[d].size() > 1) {
                int start = index - int(buckets[d].size());
                int end = index - 1;
                recursiveRadixSort(arr, start, end, exp / 10);
            }
        }
    }
}
void radixSortMSD(std::vector<int>& arr) {
    int maxVal = getMax(arr);
    int digits = 1;
    for (int tmp = maxVal; tmp >= 10; tmp /= 10)
        digits *= 10;

    recursiveRadixSort(arr, 0, int(arr.size()) - 1, digits);
}

int binarySearch(const std::vector<int>& arr, const int item, int low, int high) {
    while (low <= high) {
        if (const int mid = low + (high - low) / 2; item == arr[mid])
            return mid + 1;
        else if (item > arr[mid])
            low = mid + 1;
        else
            high = mid - 1;
    }

    return low;
}
void binaryInsertionSortHelper(std::vector<int>& arr, const int low, const int high) {
    for (int i = low+1; i <= high; i++) {
        const int key = arr[i];
        const int insertPos = binarySearch(arr, key, 0, i - 1);

        int j = i - 1;
        while (j >= insertPos) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[insertPos] = key;
    }
}
void binaryInsertionSort(std::vector<int>& arr) {
    binaryInsertionSortHelper(arr, 0, int(arr.size())-1);
}

void recursiveQuickSort(std::vector<int>& arr, int low, int high) {
    if (low >= high) {
        return;
    }

    int mid = low + (high - low) / 2;
    std::swap(arr[mid], arr[high]);

    int pivotLoc = high;

    for (int i = high-1; i >= low; --i) {
        if (arr[i] > arr[pivotLoc]) {
            std::swap(arr[i], arr[pivotLoc-1]);
            std::swap(arr[pivotLoc-1], arr[pivotLoc]);
            pivotLoc--;
        }
    }
    recursiveQuickSort(arr, low, pivotLoc-1);
    recursiveQuickSort(arr, pivotLoc+1, high);
}
void quickSort(std::vector<int>& arr) {
    recursiveQuickSort(arr, 0, int(arr.size()) - 1);
}

void stdSort(std::vector<int>& arr) {
    std::ranges::sort(arr);
}

void bubbleSort(std::vector<int>& arr) {
    const int array_size = int(arr.size());
    for (int i = (array_size - 1); i>= 0; i--) {
        int swaps = 0;
        for (int j = 1; j <= i; j++) {
            if (arr[j-1] > arr[j]){
                std::swap(arr[j], arr[j-1]);
                swaps++;
            }
        }
        if (swaps == 0) {
            return;
        }
    }
}

void merge(std::vector<int>& arr, int low, int mid, int high) {
    std::vector<int> temp_arr;

    int left_ptr = low;
    int right_ptr = mid + 1;

    while (left_ptr <= mid and right_ptr <= high) {
        if (arr[left_ptr] <= arr[right_ptr]) {
            temp_arr.push_back(arr[left_ptr]);
            left_ptr = left_ptr + 1;
        }
        else {
            temp_arr.push_back(arr[right_ptr]);
            right_ptr = right_ptr + 1;
        }
    }

    while (left_ptr <= mid) {
       temp_arr.push_back(arr[left_ptr]);
       left_ptr = left_ptr + 1;
    }

    while (right_ptr <= high) {
        temp_arr.push_back(arr[right_ptr]);
        right_ptr = right_ptr + 1;
    }

    int k = low;
    for (int element : temp_arr) {
        arr[k] = element;
        k++;
    }
}
void recursiveMergeSort(std::vector<int>& arr, const int low, const int high) {
    if (high <= low) {
        return;
    }

    int mid = (low + high) / 2;

    recursiveMergeSort(arr, low, mid);
    recursiveMergeSort(arr, mid + 1, high);

    merge(arr, low, mid, high);
}
void mergeSort(std::vector<int>& arr) {
    recursiveMergeSort(arr, 0, int(arr.size()) - 1);
}

void insertionSortHelper(std::vector<int>& arr, const int low, const int high) {
    for (int i = low+1; i <= high; i++) {
        const int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}
void insertionSort(std::vector<int>& arr) {
    insertionSortHelper(arr, 0, int(arr.size()) - 1);
}

float time(void (*func)(std::vector<int>&), std::vector<int>& arr) {
    const auto start = std::chrono::high_resolution_clock::now();
    func(arr);
    const auto end = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    return float(duration.count())/1000;
}
void p(const std::vector<int>& arr) {
    for (const int i : arr) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}
float test(void (*func)(std::vector<int>&), const int n, const std::string& name = "") {
    std::vector<int> arr;
    arr.reserve(n);
    for (int i = 0; i < n; ++i) {
        arr.push_back(rand()%n);
    }

    return time(func, arr);

    //std::cout << name << ": " + std::to_string(time(func, arr)) + "ms" << std::endl;
    //if (!check(arr)) {
    //    std::cout << "Failed" << std::endl;
    //}
}

int main() {
    //test(stdSort, n, "Std::Sort");
    //test(quickSort, n, "QuickSort");
    //test(radixSortMSD, n, "RadixSortMSD");
    //test(mergeSort, n, "MergeSort");
    //test(binaryInsertionSort, n, "BinaryInsertionSort");
    //test(insertionSort, n, "InsertionSort");
    //test(bubbleSort, n, "BubbleSort");

    std::ofstream file("output.txt");

    float t = 0;
    int i = 0;
    while (t < 1000) {
        t = test(quickSort, i);
        i+= 10000;
        for (int i = 0; i < 100; ++i) {
            file << t << std::endl;
        }
        if (i % 100000 == 0) {
            std::cout << t << std::endl;
        }
    }

    file.close();

    return 0;
}
