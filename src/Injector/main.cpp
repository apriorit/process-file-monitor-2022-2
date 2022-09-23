#include <iostream>
#include "inject.cpp"

using namespace std;

int main()
{
    DWORD PID = 20344;
    inject(PID);

    cout << "Hello World!" << endl;
    return 0;
}
