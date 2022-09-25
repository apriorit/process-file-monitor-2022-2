#include "inject.cpp"

int main()
{    
    // path to dll
    LPCSTR DllPath = "C:\\CodeBase\\Apriorit-Project\\build-src-Desktop_Qt_6_3_1_MinGW_64_bit-Debug\\Hooks\\debug\\Hooks.dll";
    // target process PID
    DWORD PID = 20344;

    inject(PID, DllPath);

    return 0;
}
