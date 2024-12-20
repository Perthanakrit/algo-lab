#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

long double gcd_array(const vector<double> &arr);
long double lcm_array(const vector<double> &arr);

int main()
{
    vector<double> arr;

    double num;
    while (cin >> num)
    {
        if (num < 1 || num > 1000)
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

long double gcd(long long a, long long b)
{
    while (b != 0)
    {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return static_cast<long double>(a);
}

long double gcd_array(const vector<double> &arr)
{
    const long long scale = 100000;
    vector<long long> intArr(arr.size());

    for (size_t i = 0; i < arr.size(); i++)
    {
        intArr[i] = static_cast<long long>(round(arr[i] * scale));
    }

    long long result = intArr[0];
    for (size_t i = 1; i < intArr.size(); i++)
    {
        result = static_cast<long long>(gcd(result, intArr[i]));
    }

    return static_cast<long double>(result) / scale;
}

long double lcm(long long a, long long b)
{
    return static_cast<long double>(a) * b / gcd(a, b);
}

long double lcm_array(const vector<double> &arr)
{
    const long long scale = 100000;
    vector<long long> intArr(arr.size());

    for (size_t i = 0; i < arr.size(); i++)
    {
        intArr[i] = static_cast<long long>(round(arr[i] * scale));
    }

    long double result = intArr[0];
    for (size_t i = 1; i < intArr.size(); i++)
    {
        result = lcm(result, intArr[i]);
        if (result > LLONG_MAX / scale)
        {
            return 0.0;
        }
    }

    return result / scale;
}
