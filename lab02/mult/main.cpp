#include <iostream>
#include <cmath>
#include <string>
using namespace std;

long long multiply(long long x, long long y)
{
    // Base case
    if (x < 10 || y < 10)
        return x * y;

    // Number of digits
    int n = max(to_string(x).length(), to_string(y).length());
    int m = n / 2;

    long long X1 = x / (long long)pow(10, m);
    long long X0 = x % (long long)pow(10, m);

    long long Y1 = y / (long long)pow(10, m);
    long long Y0 = y % (long long)pow(10, m);

    long long P1 = multiply(X1, Y1);           
    long long P2 = multiply(X0, Y0);           
    long long P3 = multiply(X1 + X0, Y1 + Y0); 

    return P1 * pow(10, 2 * m) + (P3 - P1 - P2) * pow(10, m) + P2;
}

int main()
{
    int n;
    long long x, y;

    cin >> n;
    for(int i=0; i < n; i++)
    {
        cin >> x >> y;
        cout << multiply(x, y) << endl;
    }

    return 0;
}
