#include "pch.h"
#include "../../Common/pipeclient.h"
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
    expect+="10?20?15?25?C:\\SomePath?SomeType?SomePreview?SomeHandle?SomeResult";

    auto result = PipeClient::parseLogInfoIntoRequest(logInfo);

    EXPECT_EQ(result, expect);
}
