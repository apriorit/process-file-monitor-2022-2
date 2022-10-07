#include "pch.h"
#include "../../Common/pipeserver.h"
#include "../../Common/loginfo.h"

using namespace testing;

TEST(PipeServerTest, ParseDWORDProperties){
    std::string request = "<PID>5</PID><NOB>15</NOB>";
    request+="<OFFSET>85</OFFSET>";
    request+="<OTIME>123</OTIME>";
    LogInfo expect(5);
    expect.numberOfBytes = 15;
    expect.offset = 85;
    expect.operationTime = 123;

    auto result = PipeServer::parseRequest(request);

    EXPECT_EQ(result == expect, true);
}

TEST(PipeServerTest, ParseQStringProperties){
    std::string request = "<PID>5</PID><FPATH>C:\\test.txt</FPATH>";
    request+="<OTYPE>Read</OTYPE>";
    request+="<PREVIEW>0ABCDED01010</PREVIEW>";
    request+="<FHANDLE>SomeHandle</FHANDLE>";
    request+="<RESULT>Success</RESULT>";
    LogInfo expect(5);
    expect.filePath = "C:\\test.txt";
    expect.operationType = "Read";
    expect.preview = "0ABCDED01010";
    expect.fileHandle = "SomeHandle";
    expect.resultOfTheOperation = "Success";

    auto result = PipeServer::parseRequest(request);

    EXPECT_EQ(result == expect, true);
}

TEST(PipeServerTest, ParseFilePathFromRequest){
    const std::string request = "<PID>5</PID><FPATH>C:\\Somedir\\main.cpp</FPATH>";
    LogInfo expect(5);
    expect.filePath = "C:\\Somedir\\main.cpp";

    auto result = PipeServer::parseRequest(request);

    EXPECT_EQ(result == expect, true);
}

TEST(PipeServerTest, ParsePidWrongPidPassed){
    const std::string request = "<PID>Ziemniaczek</PID>";

    EXPECT_THROW(PipeServer::parseRequest(request), std::invalid_argument);
};

TEST(PipeServerTest, ParsePidCanNotBeZero){
    const std::string request = "<PID>0</PID>";

    EXPECT_THROW(PipeServer::parseRequest(request), std::invalid_argument);
};

TEST(PipeServerTest, ParsePidFromRequest){
    const std::string request = "<PID>15</PID>";
    LogInfo expect(15);

    auto result = PipeServer::parseRequest(request);

    EXPECT_EQ(result == expect, true);
}
