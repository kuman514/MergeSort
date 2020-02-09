#include <iostream>
#include <cstdio>
#include <vector>

// implementing merge sort

void mergeSort(std::vector<int>& arr, const int left, const int right)
{
    // arr: a vector array for merge sort
    // left: index of the first unit of the (partial) array
    // right: index of the last unit of the (partial) array

    int size = right - left + 1;

    if (size <= 1)
    {
        // left alone
        return;
    }
    else if (size == 2)
    {
        // pass separation
    }
    else if (size % 2 == 0)
    {
        // Separate: left ... left + size/2 - 1 || left + size/2 ... right
        mergeSort(arr, left, left + size / 2 - 1);
        mergeSort(arr, left + size / 2, right);
    }
    else if (size % 2 == 1)
    {
        // the left separation will have more
        // Separate: left ... left + size/2 || left + size/2 + 1 ... right
        mergeSort(arr, left, left + size / 2);
        mergeSort(arr, left + size / 2 + 1, right);
    }

    // temporary space for merge sort
    int tmpspace[size];

    // fixed pivot components
    const int leftLimit = (size % 2 == 0) ? (left + size / 2 - 1) : (left + size / 2);
    const int rightLimit = right;

    // cursors
    int leftCursor = left;
    int rightCursor = leftLimit + 1;
    int totalCursor = 0;

    // compare between two separations
    // Sorting ASC
    while (leftCursor <= leftLimit && rightCursor <= rightLimit)
    {
        if (arr[leftCursor] < arr[rightCursor])
        {
            tmpspace[totalCursor] = arr[leftCursor];

            leftCursor++;
            totalCursor++;
        }
        else // if(arr[leftCursor] >= arr[rightCursor])
        {
            tmpspace[totalCursor] = arr[rightCursor];

            rightCursor++;
            totalCursor++;
        }

        // if one side has been done...
        if (leftCursor > leftLimit)
        {
            // left side done
            while (rightCursor <= rightLimit)
            {
                tmpspace[totalCursor] = arr[rightCursor];

                rightCursor++;
                totalCursor++;
            }
        }
        else if (rightCursor > rightLimit)
        {
            // right side done
            while (leftCursor <= leftLimit)
            {
                tmpspace[totalCursor] = arr[leftCursor];

                leftCursor++;
                totalCursor++;
            }
        }
    }

    // copy the temporary to the real array
    for (int i = 0; i < size; i++)
    {
        arr[left + i] = tmpspace[i];
    }
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::vector<int> arr;

    int n, input;
    std::cin >> n;

    for (int i = 0; i < n; i++)
    {
        std::cin >> input;
        arr.push_back(input);
    }

    mergeSort(arr, 0, arr.size() - 1);

    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << ' ';
    }

    std::cout << std::endl;

    return 0;
}