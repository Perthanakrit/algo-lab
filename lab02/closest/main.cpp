#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Point
{
    long double x, y;
};

long double closestPair(vector<Point> &points);

int main()
{
    int t;
    cin >> t;

    if (t < 1 || t > 20)
    {
        return 0;
    }

    while (t--)
    {
        int n;
        cin >> n;
        cin.ignore();

        if (n < 2 || n > 20000)
        {
            continue;
        }

        vector<Point> points(n);

        for (int i = 0; i < n; ++i)
        {
            string x_input, y_input;
            cin >> x_input >> y_input;

            points[i].x = stold(x_input.substr(1, x_input.length() - 2));
            points[i].y = stold(y_input.substr(0, y_input.length() - 1));
        }

        long double result = closestPair(points);
        printf("%.6Lf\n", result);
    }

    return 0;
}

// Function to calculate distance between two points
long double calculateDistance(const Point &p1, const Point &p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

void mergeSortByX(vector<Point> &points, int left, int right, int mid)
{
    int n1 = right - left + 1;
    int n2 = right - mid;

    vector<Point> leftArr(n1);
    vector<Point> rightArr(n2);

    // Divide the array into two halves
    for (int i = 0; i < n1; ++i)
        leftArr[i] = points[left + i];
    for (int i = 0; i < n2; ++i)
        rightArr[i] = points[mid + 1 + i];

    // Merge the two halves
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i].x < rightArr[j].x)
        {
            points[k++] = leftArr[i++];
        }
        else
        {
            points[k++] = rightArr[j++];
        }
    }

    // Copy the remaining elements of leftArr
    while (i < n1)
    {
        points[k++] = leftArr[i++];
    }

    // Copy the remaining elements of rightArr
    while (j < n2)
    {
        points[k++] = rightArr[j++];
    }
}

void mergeSortByY(vector<Point> &points, int left, int right, int mid)
{
    int n1 = right - left + 1;
    int n2 = right - mid;

    vector<Point> leftArr(n1);
    vector<Point> rightArr(n2);

    // Divide the array into two halves
    for (int i = 0; i < n1; ++i)
        leftArr[i] = points[left + i];
    for (int i = 0; i < n2; ++i)
        rightArr[i] = points[mid + 1 + i];

    // Merge the two halves
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i].y < rightArr[j].y)
        {
            points[k++] = leftArr[i++];
        }
        else
        {
            points[k++] = rightArr[j++];
        }
    }

    // Copy the remaining elements of leftArr
    while (i < n1)
    {
        points[k++] = leftArr[i++];
    }

    // Copy the remaining elements of rightArr
    while (j < n2)
    {
        points[k++] = rightArr[j++];
    }
}

long double closestPairRec(vector<Point> &pointsSortedX, vector<Point> &pointsSortedY)
{
    int n = pointsSortedX.size();

    if (n <= 3)
    {
        // Brute force for small datasets
        long double minDist = __LDBL_MAX__;
        for (int i = 0; i < n; ++i)
        {
            for (int j = i + 1; j < n; ++j)
            {
                minDist = min(minDist, calculateDistance(pointsSortedX[i], pointsSortedX[j]));
            }
        }
        return minDist;
    }

    // Split the points into two halves
    int mid = n / 2;
    Point midPoint = pointsSortedX[mid];

    vector<Point> leftPointsX(pointsSortedX.begin(), pointsSortedX.begin() + mid);
    vector<Point> rightPointsX(pointsSortedX.begin() + mid, pointsSortedX.end());

    vector<Point> leftPointsY, rightPointsY;
    for (const Point &p : pointsSortedY)
    {
        if (p.x <= midPoint.x)
        {
            leftPointsY.push_back(p);
        }
        else
        {
            rightPointsY.push_back(p);
        }
    }

    // Recursive calls for left and right halves
    long double leftMinDist = closestPairRec(leftPointsX, leftPointsY);
    long double rightMinDist = closestPairRec(rightPointsX, rightPointsY);

    // Find the smaller distance
    long double minDist = min(leftMinDist, rightMinDist);

    // Check for points in the strip
    vector<Point> strip;
    for (const Point &p : pointsSortedY)
    {
        if (abs(p.x - midPoint.x) < minDist)
        {
            strip.push_back(p);
        }
    }

    for (size_t i = 0; i < strip.size(); ++i)
    {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; ++j)
        {
            minDist = min(minDist, calculateDistance(strip[i], strip[j]));
        }
    }

    return minDist;
}

long double closestPair(vector<Point> &points)
{
    vector<Point> pointsSortedX(points);
    vector<Point> pointsSortedY(points);

    mergeSortByX(pointsSortedX, 0, pointsSortedX.size() - 1, pointsSortedX.size() / 2);
    mergeSortByY(pointsSortedY, 0, pointsSortedY.size() - 1, pointsSortedY.size() / 2);

    return closestPairRec(pointsSortedX, pointsSortedY);
}