#include "pch.h"
#include "../pipeserver.h"

using namespace testing;

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
