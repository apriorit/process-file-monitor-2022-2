#include "pch.h"
#include "../pipeserver.h"
#include "../loginfo.h"

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

/*TEST(PipeServerTest, ParseRequestToLogInfo){
    const std::string request = "C:\\whatever.txt?Read?0ABCDEF?Handle?Success?5?6?7?8";
    LogInfo expectedLog(5);
    expectedLog.filePath = "C:\\whatever.txt";
    expectedLog.fileHandle = "Handle";
    expectedLog.numberOfBytes = 6;
    expectedLog.offset = 7;
    expectedLog.operationTime = 8;
    expectedLog.resultOfTheOperation = "Success";
    expectedLog.operationType = "Read";
    expectedLog.preview = "0ABCDEF";
   auto result = PipeServer::parseRequest(request);

   EXPECT_EQ(expectedLog == result, true);
}
*/
TEST(PipeServerTest, WrongFormatedPid){
    const std::string Request = "12PID21\nSendPermission";

    EXPECT_THROW(PipeServer::getCommandAndPidFromRequest(Request), std::invalid_argument);
}

TEST(PipeServerTest, NoDelimiter){
    const std::string Request = "12SendPermission";

    EXPECT_THROW(PipeServer::getCommandAndPidFromRequest(Request), std::invalid_argument);
}

TEST(PipeServerTest, InvalidPid)
{
    const std::string Request = "hahahaha!\nRandomCommand?";

    EXPECT_THROW(PipeServer::getCommandAndPidFromRequest(Request), std::invalid_argument);
}

TEST(PipeServerTest, GetPidAndCommandFromRequest)
{
    const std::string Request = "12\nSendPermission";
    DWORD expectedPid = 12;

    auto result = PipeServer::getCommandAndPidFromRequest(Request);

    EXPECT_EQ(result.first, expectedPid);
    EXPECT_EQ(result.second, Commands::SendPermission);
}

TEST(PipeServerTest, GetPidAndUnknownCommand)
{
    const std::string Request = "12\nRandomCommand?";

    EXPECT_THROW(PipeServer::getCommandAndPidFromRequest(Request), std::invalid_argument);
}
