#include "inject.cpp"

int main(int argc, char** argv)
{
    try
    {
        if (argc != 2) throw std::runtime_error("PID of the target function must be passed to the injector");

        // target process PID
        DWORD PID = (DWORD)(atol(argv[1]));
        std::cout << std::endl << "PID: " << PID << std::endl;

        //  path to dll
        LPCSTR DllPath = "C:\\CodeBase\\Apriorit-Project\\build-src-Desktop_Qt_6_3_1_MinGW_64_bit-Debug\\Hooks\\debug\\Hooks.dll";        

        inject(PID, DllPath);

        return 0;
    }
    catch (const std::exception& e)
    {
        std::cout << std::endl << "Exception occurred during execution: " << e.what();

        return -1;
    }
}
