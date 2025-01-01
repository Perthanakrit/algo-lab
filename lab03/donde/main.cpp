#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

void getInput(vector<int> &list);
void mergeSort(vector<int> &sprinklers, int left, int right);

int main() 
{
    vector<int> wantCookies;
    vector<int> sizeOfCookies;

    getInput(wantCookies);
    getInput(sizeOfCookies);
    
    mergeSort(wantCookies, 0, wantCookies.size() - 1);
    mergeSort(sizeOfCookies, 0, sizeOfCookies.size() - 1);

    int count = 0;

    for (int i = 0, j = 0; i < wantCookies.size() && j < sizeOfCookies.size();)
    {
        if (wantCookies[i] <= sizeOfCookies[j])
        {
            count++;
            i++;
            j++;
        }
        else
        {
            j++;
        }
    }

    cout << count << endl;

    return 0;
}

void merge(vector<int> &sprinklers, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> leftArr(n1);
    vector<int> rightArr(n2);

    for (int i = 0; i < n1; ++i)
        leftArr[i] = sprinklers[left + i];
    for (int i = 0; i < n2; ++i)
        rightArr[i] = sprinklers[mid + 1 + i];

    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2)
    {
        if (leftArr[i] < rightArr[j])
        {
            sprinklers[k++] = leftArr[i++];
        }
        else
        {
            sprinklers[k++] = rightArr[j++];
        }
    }

    while (i < n1)
    {
        sprinklers[k++] = leftArr[i++];
    }

    while (j < n2)
    {
        sprinklers[k++] = rightArr[j++];
    }
}

void mergeSort(vector<int> &sprinklers, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(sprinklers, left, mid);
        mergeSort(sprinklers, mid + 1, right);

        merge(sprinklers, left, mid, right);
    }
}

void getInput(vector<int> &list)
{
    string input;
    getline(cin, input);
    stringstream ss(input);
    int n;
    while (ss >> n)
    {
        list.push_back(n);
    }
}