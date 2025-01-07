#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Sprinkler
{
    double x;
    double r;
};

int findMinSprinklers(double l, double w, const vector<Sprinkler> &sprinklers);
void mergeSort(vector<pair<double, double> > &arr, int left, int right);

int main() 
{
    double l, w;
    int n;

    while (cin >> l >> w)
    {
        cin >> n;

        vector<Sprinkler> sprinklers(n);
        
        for(int i = 0; i < n; i++)
        {
            Sprinkler sprinkler;
            cin >> sprinkler.x >> sprinkler.r;

            sprinklers[i] = sprinkler;
        }

        cout << findMinSprinklers(l, w, sprinklers) << endl;
    }
    
    return 0;
}

void printSprinklers(const vector<Sprinkler> &sprinklers)
{
    for (const Sprinkler &sprinkler : sprinklers)
    {
        cout << "x: " << sprinkler.x << " r: " << sprinkler.r << endl;
    }
}

int findMinSprinklers(double l, double w, const vector<Sprinkler> &sprinklers)
{
    vector<pair<double, double> > coverage;
    double halfWidth = w / 2.0;

    for (const Sprinkler &sprinkler : sprinklers)
    {
        if (sprinkler.r < halfWidth) continue;

        double offset = sqrt(sprinkler.r * sprinkler.r - halfWidth * halfWidth);
        double left = sprinkler.x - offset;
        double right = sprinkler.x + offset;

        coverage.push_back(pair<double, double>(left, right));
    }

    mergeSort(coverage, 0, coverage.size() - 1);

    int amount = 0;
    double covered = 0.0;
    size_t i = 0;

    while (covered < l)
    {
        double farthest = covered; 

        while (i < coverage.size() && coverage[i].first <= covered)
        {
            farthest = max(farthest, coverage[i].second);
            ++i;
        }

        if (farthest == covered)
        {
            return -1;
        }

        covered = farthest;
        ++amount;
    }

    return amount;
}

void merge(vector<pair<double, double> > &coverages, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<pair<double, double> > L(n1), R(n2);

    for (int i = 0; i < n1; i++)
    {
        L[i] = coverages[left + i];
    }

    for (int i = 0; i < n2; i++)
    {
        R[i] = coverages[mid + 1 + i];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (L[i].first <= R[j].first)
        {
            coverages[k] = L[i++]; 
        }
        else
        {
            coverages[k] = R[j++];
        }

        ++k;
    }

    while (i < n1)
    {
        coverages[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2)
    {
        coverages[k] = R[j];
        ++j;
        ++k;
    }
}


void mergeSort(vector<pair<double, double> > &arr, int left, int right)
{
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    merge(arr, left, mid, right);
}