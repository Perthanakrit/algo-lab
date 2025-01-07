#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Sprinkler {
    double x; 
    double r; 
};

void merge(vector<double>& leftCoverage, vector<double>& rightCoverage, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<double> L1(n1), R1(n2);
    vector<double> L2(n1), R2(n2);

    for (int i = 0; i < n1; ++i) {
        L1[i] = leftCoverage[left + i];
        L2[i] = rightCoverage[left + i];
    }

    for (int j = 0; j < n2; ++j) {
        R1[j] = leftCoverage[mid + 1 + j];
        R2[j] = rightCoverage[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L1[i] <= R1[j]) {
            leftCoverage[k] = L1[i];
            rightCoverage[k] = L2[i];
            ++i;
        } else {
            leftCoverage[k] = R1[j];
            rightCoverage[k] = R2[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        leftCoverage[k] = L1[i];
        rightCoverage[k] = L2[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        leftCoverage[k] = R1[j];
        rightCoverage[k] = R2[j];
        ++j;
        ++k;
    }
}

void mergeSort(vector<double>& leftCoverage, vector<double>& rightCoverage, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(leftCoverage, rightCoverage, left, mid);
        mergeSort(leftCoverage, rightCoverage, mid + 1, right);

        merge(leftCoverage, rightCoverage, left, mid, right);
    }
}

int calMin(double length, double width, vector<Sprinkler>& sprinklers) {
    vector<double> leftCoverage, rightCoverage;

    for (const Sprinkler& sprinkler : sprinklers) {
        if (sprinkler.r >= width / 2.0) {
            double left = sprinkler.x - sqrt(sprinkler.r * sprinkler.r - (width / 2.0) * (width / 2.0));
            double right = sprinkler.x + sqrt(sprinkler.r * sprinkler.r - (width / 2.0) * (width / 2.0));

            leftCoverage.push_back(left);
            rightCoverage.push_back(right);
        }
    }

    mergeSort(leftCoverage, rightCoverage, 0, leftCoverage.size() - 1);

    double currentCoverage = 0.0;
    int count = 0;
    int i = 0;

    while (currentCoverage < length) {
        double maxReach = currentCoverage;

        while (i < leftCoverage.size() && leftCoverage[i] <= currentCoverage) {
            maxReach = max(maxReach, rightCoverage[i]);
            ++i;
        }

        if (maxReach == currentCoverage) {
            return -1;
        }

        currentCoverage = maxReach;
        ++count;
    }

    return count;
}

int main() {
    double l, w;
    int n;

    while (cin >> l >> w) {
        cin >> n;
        vector<Sprinkler> sprinklers(n);

        for (int i = 0; i < n; ++i) {
            cin >> sprinklers[i].x >> sprinklers[i].r; 
        }

        int result = calMin(l, w, sprinklers);
        cout << result << endl;
    }

    return 0;
}