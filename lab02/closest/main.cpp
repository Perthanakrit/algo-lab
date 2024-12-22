#include <iostream>
#include <string>
#include <float.h>
#include <cmath>
#include <regex>

using namespace std;
struct Point
{
    double x, y;
};

int compareX(const void *a, const void *b)
{
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->x > p2->x) - (p1->x < p2->x);
}

int compareY(const void *a, const void *b)
{
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->y > p2->y) - (p1->y < p2->y);
}

double dist(Point p1, Point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                (p1.y - p2.y) * (p1.y - p2.y));
}

double bruteForce(Point P[], int n)
{
    double min = DBL_MAX;
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

double stripClosest(Point strip[], int size, double d)
{
    double min = d; 

    for (int i = 0; i < size; ++i)
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j)
            if (dist(strip[i], strip[j]) < min - 1e-9)
                min = dist(strip[i], strip[j]);

    return min;
}

double closestUtil(Point *Px, Point *Py, int n)
{
    
    if (n <= 3)
        return bruteForce(Px, n);

    int mid = n / 2;
    Point midPoint = Px[mid];
    
    Point Pyl[mid];     
    Point Pyr[n - mid]; 
    int li = 0, ri = 0; 
    for (int i = 0; i < n; i++)
    {
        if (Py[i].x <= midPoint.x && li < mid)
            Pyl[li++] = Py[i];
        else
            Pyr[ri++] = Py[i];
    }

    double dl = closestUtil(Px, Pyl, mid);
    double dr = closestUtil(Px + mid, Pyr, n - mid);

    double d = min(dl, dr);

    Point *strip = new Point[n];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (abs(Py[i].x - midPoint.x) < d)
            strip[j] = Py[i], j++;

    return stripClosest(strip, j, d);
}

double closest(Point *P, int n)
{
    Point *Px = new Point[n];
    Point *Py = new Point[n]; 
    for (int i = 0; i < n; i++)
    {
        Px[i] = P[i];
        Py[i] = P[i];
    }

    qsort(Px, n, sizeof(Point), compareX);
    qsort(Py, n, sizeof(Point), compareY);
    
    return closestUtil(Px, Py, n);
}

int main()
{
    int t;
    cin >> t;

    if (t < 1 || t > 20)
    {
        return 0;
    }

    for (int i = 0; i < t; i++)
    {
        int n;
        cin >> n;
        cin.ignore();

        if (n < 2 || n > 2000)
        {
            continue;
        }

        Point *points = new Point[n];

        for (int j = 0; j < n; j++)
        {
            string input;

            getline(cin, input);

            regex r("\\(\\s*(\\d*\\.?\\d+)\\s*,\\s*(\\d*\\.?\\d+)\\s*\\)");
            smatch m;
            
            double x = 0.0, y = 0.0;

            if (regex_search(input, m, r))
            {
                x = stod(m[1]);
                y = stod(m[2]);
            }

            Point p;
            p.x = x;
            p.y = y;

            points[j] = p;
        }

        printf("%.6lf\n", closest(points, n));
    }

    return 0;
}