#include "pch.h"
#include "../pipeserver.h"
#include "../loginfo.h"

using namespace testing;

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
