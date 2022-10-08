#include "pch.h"
#include "../pipeserver.h"
#include "../../Common/loginfo.h"

using namespace testing;

TEST(PipeServerTest, ParsePidCanNotBeZero){
    std::string request = "0?10?20?30?C:\\SomePath?SomeType?SomePreview?SomeHandle?SomeResult";

    EXPECT_THROW(PipeServer::parseRequest(request), std::invalid_argument);
}

TEST(PipeServerTest, ParseStandardRequest){
    std::string request = "15?10?20?30?C:\\SomePath?SomeType?SomePreview?SomeHandle?SomeResult";
    LogInfo expect(15);
    expect.offset = 10;
    expect.numberOfBytes = 20;
    expect.operationTime = 30;
    expect.filePath = "C:\\SomePath";
    expect.operationType = "SomeType";
    expect.preview = "SomePreview";
    expect.fileHandle = "SomeHandle";
    expect.resultOfTheOperation = "SomeResult";

    auto result = PipeServer::parseRequest(request);

    EXPECT_EQ(result == expect, true);
}

TEST(PipeServerTest, ParseDefaultRequest){
    std::string request = "15?0?0?0????";
    LogInfo expect(15);

    auto result = PipeServer::parseRequest(request);

    EXPECT_EQ(result == expect, true);
}
