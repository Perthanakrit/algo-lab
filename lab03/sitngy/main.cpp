#include <iostream>
#include <vector>

using namespace std;

struct Negotiation
{
    int work_duration; // work duration in minutes
    int compensation; // compensation per minute
};

void mergeSort(vector<Negotiation> &negotiations, int left, int right);
void printVector(const vector<Negotiation> &negotiations);
long long findMinAmount(vector<Negotiation> &negotiations, int n);
bool isWorked(const vector<int> &worked_idies, int index);

int main() 
{
    int n;
    cin >> n;
    
    vector<Negotiation> negotiations(n);

    for(int i = 0; i < n; i++)
    {
        Negotiation negotiation;
        
        cin >> negotiation.work_duration >> negotiation.compensation;

        negotiations[i] = negotiation;
    }

    mergeSort(negotiations, 0, n - 1);

    // printVector(negotiations);

    cout << findMinAmount(negotiations, n) << endl;
    
    return 0;
}

void merge(vector<Negotiation> &negotiation, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Negotiation> leftArr(n1);
    vector<Negotiation> rightArr(n2);

    for (int i = 0; i < n1; ++i)
        leftArr[i] = negotiation[left + i]; 
    for (int i = 0; i < n2; ++i)
        rightArr[i] = negotiation[mid + 1 + i];

    int i = 0, j = 0, k = left;
    // Merge the temp arrays back into arr[l..r]
    while (i < n1 && j < n2)
    {
        if (leftArr[i].work_duration * rightArr[j].compensation <= rightArr[j].work_duration * leftArr[i].compensation)
        {
            negotiation[k++] = leftArr[i++];
        }
        else
        {
            negotiation[k++] = rightArr[j++];
        }
    }

    // Copy the remaining elements of leftArr[], if there are any
    while (i < n1)
    {
        negotiation[k++] = leftArr[i++];
    }

    // Copy the remaining elements of rightArr[], if there are any
    while (j < n2)
    {
        negotiation[k++] = rightArr[j++];
    }

    leftArr.clear();
    rightArr.clear();
}

void mergeSort(vector<Negotiation> &negotiations, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(negotiations, left, mid);
        mergeSort(negotiations, mid + 1, right);

        // Merge the sorted halves
        merge(negotiations, left, mid, right);
    }
}

bool isWorked(const vector<int> &worked_idies, int index)
{
    for (size_t i = 0; i < worked_idies.size(); i++)
    {
        if (worked_idies[i] == index)
        {
            return true;
        }
    }

    return false;
}

long long findMinAmount(vector<Negotiation> &negotiations, int n)
{
    vector<int> worked_idies;

    long long totalCost = 0, accumulatedDuration = 0;

    for (const Negotiation &negotiation : negotiations)
    {
        totalCost += accumulatedDuration * negotiation.compensation;
        accumulatedDuration += negotiation.work_duration;
    }

    return totalCost;
}