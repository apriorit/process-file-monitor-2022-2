#include "pch.h"
#include "../processesseeker.h"
#include "../processesstorage.h"

using namespace testing;

TEST(ProcessesSeekerTest, ProcessesSeekerCompile){
    ProcessesSeeker processesSeeker;
    processesSeeker.getSystemProcesses();
}
