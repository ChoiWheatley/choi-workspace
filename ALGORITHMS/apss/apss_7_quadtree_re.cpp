#include<iostream>
#include<vector>
#include<string>
#include<unistd.h>
using namespace std;

string reverse(string::iterator& it);

int main(void)
{
    int c;
    cin >> c;
    while (c-->0)
    {
        string sample;
        cin >> sample;
        auto i = sample.begin();
        cout << reverse(i) << '\n';
    }
    return 0;
}
string reverse(string::iterator& it)
{
    char c = *it;
    if (c != 'x')
        return string(1,c);
    string chunk[4] = {""};
    for (int i = 0; i < 4; i++)
    {
        chunk[i] = reverse(++it);
    }
    return 'x' + chunk[2] + chunk[3] + chunk[0] + chunk[1];
}
