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

double IRR(int n, int *cf_arr);

int main() 
{
    int n;
    while (cin >> n && n != 0 && n >= 1 && n <= 10)
    {
        int *cf_arr = new int[n + 1];

        for (int i = 0; i <= n; i++)
        {
            cin >> cf_arr[i];
        }
        
        double irr = IRR(n, cf_arr);
        printf("%.2f\n", irr);
    }
    
    return 0;
}

double IRR(int n, int *cf_arr)
{
    double left = -0.99;
    double right = 1e7;   
    double mid;
    double epsilon = 1e-6; 

    while (right - left > epsilon)
    {
        mid = (left + right) / 2.0;

        double npv = 0.0;
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
    
    return (left + right) / 2.0;
}
