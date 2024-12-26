#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;

class Point
{
public:
    double x, y;
};

int compareX(const void *a, const void *b)
{
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->x - p2->x);
}

int compareY(const void *a, const void *b)
{
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->y - p2->y);
}

void mergeSort(Point *points, int left, int right, int mid, int (*__compar)(const void *, const void *))
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Point *leftArr = new Point[n1];
    Point *rightArr = new Point[n2];

    for (int i = 0; i < n1; ++i)
        leftArr[i] = points[left + i];
    for (int i = 0; i < n2; ++i)
        rightArr[i] = points[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (__compar(&leftArr[i], &rightArr[j]) < 0)
        {
            points[k++] = leftArr[i++];
        }
        else
        {
            points[k++] = rightArr[j++];
        }
    }
    while (i < n1)
        points[k++] = leftArr[i++];
    while (j < n2)
        points[k++] = rightArr[j++];

    delete[] leftArr;
    delete[] rightArr;
}

void sortPoints(Point *points, int left, int rigth, int (*__compar)(const void *, const void *))
{
    if (left < rigth) {
        int mid = left + (rigth - left) / 2;
        sortPoints(points, left, mid, __compar);
        sortPoints(points, mid + 1, rigth, __compar);
        mergeSort(points, left, rigth, mid, __compar);
    }
}

double dist(Point p1, Point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                (p1.y - p2.y) * (p1.y - p2.y));
}

double bruteForce(Point *P, int n)
{
    double min = __DBL_MAX__;

    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (dist(P[i], P[j]) < min)
                min = dist(P[i], P[j]);
    return min;
}

double min(double x, double y)
{
    return (x < y) ? x : y;
}

double stripClosest(Point *strip, int size, double d)
{
    double min = d; // Initialize the minimum distance as d

    sortPoints(strip, 0, size - 1, compareY);

    for (int i = 0; i < size; ++i)
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j)
            if (dist(strip[i], strip[j]) < min)
                min = dist(strip[i], strip[j]);

    return min;
}

double closestUtil(Point *P, int n)
{
    // If there are 2 or 3 points, then use brute force
    if (n <= 3)
        return bruteForce(P, n);

    int mid = n / 2;
    Point midPoint = P[mid];

    double dl = closestUtil(P, mid);
    double dr = closestUtil(P + mid, n - mid);

    double d = min(dl, dr);

    Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (abs(P[i].x - midPoint.x) < d)
            strip[j] = P[i], j++;

    return min(d, stripClosest(strip, j, d));
}

double closest(Point *P, int n)
{
    sortPoints(P, 0, n - 1, compareX);

    return closestUtil(P, n);
}

// Driver code
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

        Point *points = new Point[n];

        for (int i = 0; i < n; ++i)
        {
            string x_input, y_input;
            cin >> x_input >> y_input;

            points[i].x = stod(x_input.substr(1, x_input.length() - 2));
            points[i].y = stod(y_input.substr(0, y_input.length() - 1));
        }

        double result = closest(points, n);
        printf("%.6lf\n", result);

        delete[] points;
    }

    return 0;
}
