#include "pch.h"
#include "../../Common/pipeclient.h"
#include "../pipeserver.h"
#include "../../Common/loginfo.h"

using namespace testing;

TEST(PipeClientTest, ParseLogInfoIntoRequest){
    LogInfo logInfo(10);
    logInfo.numberOfBytes = 15;
    logInfo.offset = 20;
    logInfo.operationTime = 25;
    logInfo.filePath = "C:\\SomePath";
    logInfo.operationType = "SomeType";
    logInfo.fileHandle = "SomeHandle";
    logInfo.preview = "SomePreview";
    logInfo.resultOfTheOperation = "SomeResult";
    std::string expect = "";
    expect+="<PID>10</PID>";
    expect+="<OFFSET>20</OFFSET>";
    expect+="<NOB>15</NOB>";
    expect+="<OTIME>25</OTIME>";
    expect+="<FPATH>C:\\SomePath</FPATH>";
    expect+="<OTYPE>SomeType</OTYPE>";
    expect+="<PREVIEW>SomePreview</PREVIEW>";
    expect+="<FHANDLE>SomeHandle</FHANDLE>";
    expect+="<RESULT>SomeResult</RESULT>";

    auto result = PipeClient::parseLogInfoIntoRequest(logInfo);
    auto logResult = PipeServer::parseRequest(result);

    EXPECT_EQ(result, expect);
    EXPECT_EQ(logResult == logInfo, true);
}
