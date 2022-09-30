#include "pch.h"
#include "../processesstorage.h"

class ProcessesStorageTest : public ::testing::Test{
protected:
    ProcessesStorageTest(){
        storage.add({0,"proc1"});
        storage.add({2,"proc2"});
        storage.add({1,"proc3"});
    }
    ProcessesStorage storage;
};

TEST_F(ProcessesStorageTest, updateProcessKeepOldSettings){
    ProcessesStorage update;
    update.add({0,"proc1"});
    update.add({2,"proc2"});
    storage.getProcessByPid(2).deletePermission = false;

    storage.update(update);

    EXPECT_EQ(storage.getProcessByPid(2).deletePermission, false);
}

TEST_F(ProcessesStorageTest, updateProcessDeleteProcess){
    ProcessesStorage update;
    update.add({0, "proc1"});
    update.add({2, "proc2"});

    storage.update(update);

    ASSERT_EQ(storage.getSize(), update.getSize());
    EXPECT_THROW(storage.getProcessByPid(1), std::out_of_range);
}

TEST_F(ProcessesStorageTest, updateProcessNewProcesses){
    ProcessesStorage update;
    update.add({0, "proc1"});
    update.add({2, "proc2"});
    update.add({1, "proc3"});
    update.add({4, "proc4"});

    storage.update(update);

    ASSERT_EQ(storage.getSize(), update.getSize());
    EXPECT_EQ(storage.getProcessByPid(4), update.getProcessByPid(4));
}

TEST_F(ProcessesStorageTest, updateProcessNoChanges){
    ProcessesStorage update;
    update.add({0, "proc1"});
    update.add({2, "proc2"});
    update.add({1, "proc3"});

    storage.update(update);

    ASSERT_EQ(storage.getSize(), update.getSize());
    EXPECT_EQ(storage.getProcessByIndex(0), update.getProcessByIndex(0));
    EXPECT_EQ(storage.getProcessByIndex(1), update.getProcessByIndex(1));
    EXPECT_EQ(storage.getProcessByIndex(2), update.getProcessByIndex(2));
}

TEST_F(ProcessesStorageTest, getProcessByPidOutOfRange){
    EXPECT_THROW(storage.getProcessByPid(10000), std::out_of_range);
}

TEST_F(ProcessesStorageTest, changeItemByPid){
    auto& process = storage.getProcessByPid(1);

    process.isDllInjected = true;

    EXPECT_EQ(storage.getProcessByPid(1).isDllInjected, true);
}

TEST_F(ProcessesStorageTest, getItemByPid){
    ProcessInfo expected = {2, "proc2"};

    ProcessInfo result = storage.getProcessByPid(2);

    EXPECT_EQ(result , expected);
}

TEST_F(ProcessesStorageTest, getItemByIndexOutOfRange){
    EXPECT_THROW(storage.getProcessByIndex(999),std::out_of_range);
}

TEST_F(ProcessesStorageTest, changeItemByIndex){
    auto& ProcessInfo = storage.getProcessByIndex(1);

    ProcessInfo.deletePermission = false;

    EXPECT_EQ(storage.getProcessByIndex(1).deletePermission, false);
}

TEST_F(ProcessesStorageTest, getItemByIndex){
    ProcessInfo expected = {0,"proc1"};

    ProcessInfo result = storage.getProcessByIndex(0);

    EXPECT_EQ(result, expected);
}

TEST_F(ProcessesStorageTest, removeLastValue){
    storage.add({9999, "C://lastProcess.exe"});
    size_t lastIndex = storage.getSize() - 1;

    storage.removeByIndex(lastIndex);

    EXPECT_THROW(storage.getProcessByPid(9999), std::out_of_range);
}

TEST_F(ProcessesStorageTest, removeSpecyficValue){
    storage.removeByIndex(1);

    EXPECT_THROW(storage.getProcessByPid(1), std::out_of_range);
}

TEST_F(ProcessesStorageTest, removeValue){
    const size_t size = storage.getSize();

    storage.removeByIndex(0);

    EXPECT_EQ(storage.getSize(), size - 1);
}

TEST_F(ProcessesStorageTest , addNewItemByReference){
    ProcessInfo item(3,"C://ohmygod.exe");
    const size_t expected = storage.getSize() + 1;

    storage.add(item);

    EXPECT_EQ(storage.getSize(), expected);
}

TEST_F(ProcessesStorageTest, addNewItemButItAlreadyExistByReference){
    ProcessInfo process{99,"C://Mandarynka.exe"};

    storage.add(process);

    EXPECT_THROW(storage.add(process) ,std::invalid_argument);
}

TEST_F(ProcessesStorageTest , addNewItem){
    ProcessInfo item(3,"C://ohmygod.exe");
    const size_t expected = storage.getSize() + 1;

    storage.add(std::move(item));

    EXPECT_EQ(storage.getSize(), expected);
}

TEST_F(ProcessesStorageTest, addNewItemButItAlreadyExist){
    storage.add({99,"C://Mandarynka.exe"});

    EXPECT_THROW(storage.add({99,"C://Mandarynka.exe"}) ,std::invalid_argument);
}
