#include "pch.h"
#include "../processesseeker.h"

using namespace testing;

TEST(ProcessesSeekerTest, ProcessesSeekerCompile){
    ProcessesSeeker processesSeeker;
    processesSeeker.getSystemProcesses();
}
