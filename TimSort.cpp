#include <iostream>
#include <cstdio>
#include <vector>

// implementing tim sort

void timSort(std::vector<int>& arr, const int left, const int right, const bool desc = false)
{
    // arr: a vector array for merge sort
    // left: index of the first unit of the (partial) array
    // right: index of the last unit of the (partial) array
    // desc: sort in descending order (default = false, it means sorting in ascending order)

    int size = right - left + 1;

    // inversion for descending sort
    int invert = (desc) ? -1 : 1;

    if (size <= 1)
    {
        // left alone
        return;
    }
    else if (size <= 32)
    {
        // pass separation, initiate insertion sort
        for (int i = 1; i < size; i++)
        {
            for (int j = i; j > 0; j--)
            {
                if (invert * arr[left + j - 1] > invert* arr[left + j])
                {
                    // swap values
                    int swap = arr[left + j - 1];
                    arr[left + j - 1] = arr[left + j];
                    arr[left + j] = swap;
                }
                else
                {
                    break;
                }
            }
        }
    }
    else if (size % 2 == 0)
    {
        // Separate: left ... left + size/2 - 1 || left + size/2 ... right
        timSort(arr, left, left + size / 2 - 1, desc);
        timSort(arr, left + size / 2, right, desc);
    }
    else if (size % 2 == 1)
    {
        // the left separation will have more
        // Separate: left ... left + size/2 || left + size/2 + 1 ... right
        timSort(arr, left, left + size / 2, desc);
        timSort(arr, left + size / 2 + 1, right, desc);
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
    while (leftCursor <= leftLimit && rightCursor <= rightLimit)
    {
        if (arr[leftCursor] == arr[rightCursor])
        {
            // if two variables have a same value each other,
            // the earlier(left) one should come first.
            // (Merge Sort is one of stable sorts.)

            tmpspace[totalCursor] = arr[leftCursor];

            leftCursor++;
            totalCursor++;

            tmpspace[totalCursor] = arr[rightCursor];

            rightCursor++;
            totalCursor++;
        }
        else if (invert * arr[leftCursor] < invert * arr[rightCursor])
        {
            tmpspace[totalCursor] = arr[leftCursor];

            leftCursor++;
            totalCursor++;
        }
        else // if(invert * arr[leftCursor] > invert * arr[rightCursor])
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

    timSort(arr, 0, arr.size() - 1);
    //timSort(arr, 0, arr.size() - 1, true);

    for (int i = 0; i < n; i++)
    {
        std::cout << arr[i] << ' ';
    }

    std::cout << std::endl;

    return 0;
}