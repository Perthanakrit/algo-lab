#include <iostream>
#include <vector>
using namespace std;

long long mergeSortAndCount(vector<int> &vec, int left, int right);
void printVector(vector<int> &vec);

int main()
{
    int n, val;
    
    while (cin >> n)
    {
        vector<int> v;
        long long count = 0;

        for (int i = 0; i < n; i++)
        {
            cin >> val;
            v.push_back(val);
        }

        cout << mergeSortAndCount(v, 0, n - 1) << endl;
    }

    return 0;
}

long long mergeAndCount(vector<int> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    long long count = 0;

    while (i < n1 && j < n2)
    {
        if (L[i] >= R[j]) // Change to L[i] > R[j] to count strictly greater
        {
            arr[k++] = L[i++];
        }
        else
        {
            arr[k++] = R[j++];
            count += (n1 - i);
        }
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    return count;
}

long long mergeSortAndCount(vector<int> &vec, int left, int right)
{
    long long count = 0;
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        
        count += mergeSortAndCount(vec, left, mid);
        count += mergeSortAndCount(vec, mid + 1, right);

        count += mergeAndCount(vec, left, mid, right);
    }

    return count;
}

void printVector(vector<int> &vec)
{
    for (size_t i = 0; i < vec.size(); i++)
        cout << vec[i] << " ";
    cout << endl;
}