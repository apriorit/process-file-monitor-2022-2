#include "inject.cpp"

using namespace std;

int main()
{
    DWORD PID = 20344;
    inject(PID);
    return 0;
}
