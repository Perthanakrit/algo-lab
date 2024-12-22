#include <iostream>
#include <regex>
#include <string>

using namespace std;

// Point: (1.34, 2.56)
string readPoint()
{
    string s;
    getline(cin, s);
    cout << s << endl;
    return s;
}

int main()
{
    string s = "(0, 1)";
    double x, y;

    regex r;
    r = regex("\\((\\d*\\.?\\d+), (\\d*\\.?\\d+)\\)");
    smatch m;

    if (regex_search(s, m, r))
    {
        x = stod(m[1]);
        y = stod(m[2]);

        cout << x << " " << y << endl;
    }

    return 0;
}