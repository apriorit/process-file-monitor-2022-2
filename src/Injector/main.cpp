#include "inject.cpp"

int main()
{
    try
    {
        //  path to dll
        LPCSTR DllPath = "C:\\CodeBase\\Apriorit-Project\\build-src-Desktop_Qt_6_3_1_MinGW_64_bit-Debug\\Hooks\\debug\\Hooks.dll";
        // target process PID
        DWORD PID = 26260;

        inject(PID, DllPath);

        return 0;
    }
    catch (const std::exception& e)
    {
        std::cout << std::endl << "Exception occurred during execution: " << e.what();

        return -1;
    }
}
