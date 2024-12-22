#include <iostream>
#include <cmath>

using namespace std;

/*
find IRR to solve the equation: CF0 + CF1/(1+IRR) + CF2/(1+IRR)^2 + ... + CFn/(1+IRR)^n = 0
where:
- CF0 must be negative (CF0 < 0)
- CF1, CF2, CF3, ... must be positive (CFi > 0)
- IRR is more than -1 (IRR > -1)

Hint: use the bisection & intermediate value theorem
*/

float IRR(int n, int *cf_arr);


int main() 
{
    int n;
    while (cin >> n)
    {
        if (n > 10 || n < 1) break;

        int len = n + 2;
        int *cf_arr = new int[len];

        int i = 0;
        for (; i < len - 1; i++)
        {
            int CF;
            cin >> CF;
            cf_arr[i] = CF;
        }
        cf_arr[i] = n;
        
        float irr = IRR(n, cf_arr);
        printf("%.2f\n", irr);
    }
    
    return 0;
}

float IRR(int n, int *cf_arr)
{
    float left = -0.9999;
    float right = 1.0;   
    float mid;
    float epsilon = 0.000001; 

    while (right - left > epsilon)
    {
        mid = (left + right) / 2.0;

        float npv = 0.0;
        for (int i = 0; i <= n; i++)
        {
            npv += cf_arr[i] / pow(1 + mid, i);
        }

        if (npv > 0)
        {
            left = mid; 
        }
        else
        {
            right = mid; 
        }
    }
    // cout << IRR << endl;
    // const double IRR = roundf(mid * 100) / 100;
    // const bool isTrue = fmod(IRR, 0.5f) == 0.0f; 
    // printf("%s\n", isTrue ? "true" : "false");
    
    return mid;
}
