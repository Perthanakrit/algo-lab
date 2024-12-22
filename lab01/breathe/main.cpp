#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

long double gcd_array(const vector<long double> &arr);
long double lcm_array(const vector<long double> &arr);

int main()
{
    vector<long double> arr;

    long double num;
    while (cin >> num)
    {
        if (num < 1.0l || num > 1000.0l)
        {
            continue;
        }
        arr.push_back(num);
    }

    if (arr.size() < 2 || arr.size() > 10)
    {
        return 0;
    }

    long double gcd_result = gcd_array(arr);
    long double lcm_result = lcm_array(arr);

    printf("(%.04LF, %.04LF)\n", gcd_result, lcm_result);

    return 0;
}

long double gcd(const long double &a, const long double &b)
{
    long long scale = 10000;
    long long aInt = static_cast<long long>(round(a * scale));
    long long bInt = static_cast<long long>(round(b * scale));
    
    while (bInt != 0LL)
    {
        long long temp = bInt;
        bInt = aInt % bInt;
        aInt = temp;
    }
    
    return static_cast<long double>(aInt) / scale;
}

long double gcd_array(const vector<long double> &arr)
{
    long double result = arr[0];

    for (size_t i = 1; i < arr.size(); i++)
    {
        result = gcd(result, arr[i]);
        
        if (result == 1.0l)
        {
            break;
        }
    }

    return result;
}

long double lcm(const long double &a, const long double &b)
{
    return a / gcd(a, b) * b;
}

long double lcm_array(const vector<long double> &arr)
{
    long double result = arr[0];
    for (size_t i = 1; i < arr.size(); i++)
    {
        result = lcm(result, arr[i]);
    }

    return result;
}
