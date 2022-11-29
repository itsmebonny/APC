#include <string>
#include <iostream>
using namespace std;
unsigned fun (string &t);
int main (void)
{
string s1 = "Hello World";
unsigned count = fun(s1);
string s2 = s1;
count = fun(s2);
string &s3 = s1;
count = fun(s3);
string &s4 = s1;
count = fun(s4);
cout << s4 << " " << count << endl;
return 0;
}

unsigned fun (string &t)
{
unsigned count = 0;
for (char & c : t)
{
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
    {
        c = 'x';
        count++;
    }
}
return count;
}
 