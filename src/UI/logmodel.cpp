#include "pch.h"
#include "logmodel.h"

LogModel::LogModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    LogInfo update{"C://Update.exe","Write",0,5,5,"None","handle","24:00:00","Angry User"};
    logs.push_back(update);
}

QVariant LogModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal){
        switch(section){
        case Columns::FilePath:
            return "File Path";
        case Columns::OperationType:
            return "Operation Type";
        case Columns::Pid:
            return "PID";
        case Columns::NumberOfBytes:
            return "Number Of Bytes";
        case Columns::Offset:
            return "Offset";
        case Columns::Preview:
            return "Preview";
        case Columns::FileHandle:
            return "File Handle";
        case Columns::OperationTime:
            return "Operation Time";
        case Columns::ResultOfTheOperation:
            return "Result Of The Operation";
        }
    }
    return QVariant();
}

int LogModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return logs.size();
}

int LogModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return Columns::ColumnCount;
}

QVariant LogModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    int row = index.row();
    int col = index.column();
    auto& log = logs[row];
    if(role == Qt::DisplayRole){
        switch(col){
        case Columns::FilePath:
            return log.filePath;
        case Columns::OperationType:
            return log.operationType;
        case Columns::Pid:
            return QVariant::fromValue(log.pid);
        case Columns::NumberOfBytes:
            return QVariant::fromValue(log.numberOfBytes);
        case Columns::Offset:
            return QVariant::fromValue(log.offset);
        case Columns::Preview:
            return log.preview;
        case Columns::FileHandle:
            return log.fileHandle;
        case Columns::OperationTime:
            return log.operationTime;
        case Columns::ResultOfTheOperation:
            return log.resultOfTheOperation;
        }
    }
    return QVariant();
}

void LogModel::clearLogs(){
    emit beginResetModel();
    logs.clear();
    emit endResetModel();
}
