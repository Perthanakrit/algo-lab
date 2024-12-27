#include <iostream>
#include <string>

using namespace std;

string addStrings(const string &a, const string &b);
string subtractStrings(const string &a, const string &b);
string multiplyStrings(const string &a, const string &b);
string karatsuba(const string &x, const string &y);
void reverseString(string &s);

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        string a, b;
        cin >> a >> b;

        string result = karatsuba(a, b);

        cout << result << endl;
    }

    return 0;
}

// Add two strings representing large integers
string addStrings(const string &a, const string &b)
{
    string result;
    int carry = 0, sum = 0;
    int i = a.size() - 1, j = b.size() - 1;

    while (i >= 0 || j >= 0 || carry)
    {
        int digitA = (i >= 0) ? a[i--] - '0' : 0;
        int digitB = (j >= 0) ? b[j--] - '0' : 0;
        sum = digitA + digitB + carry;
        carry = sum / 10;
        result.push_back(sum % 10 + '0');
    }

    reverseString(result);

    return result;
}

// Subtract two strings representing large integers
string subtractStrings(const string &a, const string &b)
{
    string result;
    int borrow = 0, diff = 0;
    int i = a.size() - 1, j = b.size() - 1;

    while (i >= 0 || j >= 0)
    {
        int digitA = (i >= 0) ? a[i--] - '0' : 0;
        int digitB = (j >= 0) ? b[j--] - '0' : 0;

        diff = digitA - digitB - borrow;
        borrow = (diff < 0) ? 1 : 0;
        if (diff < 0)
            diff += 10;
        result.push_back(diff + '0');
    }

    // Remove leading zeros
    while (result.size() > 1 && result.back() == '0')
        result.pop_back();

    reverseString(result);

    return result;
}

// Multiply two strings representing large integers
string multiplyStrings(const string &a, const string &b)
{
    int n = a.size(), m = b.size();
    string result(n + m, '0');

    for (int i = n - 1; i >= 0; --i)
    {
        int carry = 0;
        for (int j = m - 1; j >= 0; --j)
        {
            int product = (a[i] - '0') * (b[j] - '0') + (result[i + j + 1] - '0') + carry;
            carry = product / 10;
            result[i + j + 1] = product % 10 + '0';
        }
        result[i] += carry;
    }

    // Find the first non-zero position
    size_t pos = 0;
    while (pos < result.size() && result[pos] == '0')
        ++pos;

    return (pos == result.size()) ? "0" : result.substr(pos);
}

string karatsuba(const string &x, const string &y)
{
    int n = x.size(), m = y.size();
    if (n < 10 || m < 10)
        return multiplyStrings(x, y);

    int maxLen = (n > m) ? n : m;
    int halfLen = maxLen / 2;

    string X1 = x.substr(0, (n > halfLen) ? n - halfLen : 0);
    string X0 = x.substr((n > halfLen) ? n - halfLen : 0);
    string Y1 = y.substr(0, (m > halfLen) ? m - halfLen : 0);
    string Y0 = y.substr((m > halfLen) ? m - halfLen : 0);

    string P1 = karatsuba(X1, Y1);
    string P2 = karatsuba(X0, Y0);
    string P3 = karatsuba(addStrings(X1, X0), addStrings(Y1, Y0));

    string part1 = P1 + string(2 * halfLen, '0');
    string part2 = subtractStrings(subtractStrings(P3, P1), P2) + string(halfLen, '0');

    return addStrings(addStrings(part1, part2), P2);
}

void reverseString(string &s)
{
    int i = 0, j = s.size() - 1;
    while (i < j)
    {
        swap(s[i++], s[j--]);
    }
}