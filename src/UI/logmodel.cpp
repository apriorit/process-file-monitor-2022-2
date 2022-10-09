#include "pch.h"
#include "logbuffer.h"
#include "logmodel.h"

LogModel::LogModel(QObject *parent, LogBuffer* logBuffer)
    : QAbstractTableModel(parent),
      logBuffer{logBuffer},
      timer{new QTimer(this)}
{
    const int updateIntervalInMs = 100;
    timer->setInterval(updateIntervalInMs);
    connect(timer, &QTimer::timeout , this, &LogModel::getDataFromBuffer);
    timer->start();
}

QVariant LogModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal){
        switch(static_cast<LogTableColumn>(section)){
        case LogTableColumn::FilePath:
            return "File Path";
        case LogTableColumn::OperationType:
            return "Operation Type";
        case LogTableColumn::Pid:
            return "PID";
        case LogTableColumn::NumberOfBytes:
            return "Number Of Bytes";
        case LogTableColumn::Offset:
            return "Offset";
        case LogTableColumn::Preview:
            return "Preview";
        case LogTableColumn::FileHandle:
            return "File Handle";
        case LogTableColumn::OperationTime:
            return "Operation Time";
        case LogTableColumn::ResultOfTheOperation:
            return "Result";
        default:
            return QVariant();
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
    return static_cast<int>(LogTableColumn::ColumnCount);
}

QVariant LogModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    int row = index.row();
    int col = index.column();
    auto& log = logs[row];
    if(role == Qt::DisplayRole){
        switch(static_cast<LogTableColumn>(col)){
        case LogTableColumn::FilePath:
            return log.filePath;
        case LogTableColumn::OperationType:
            return log.operationType;
        case LogTableColumn::Pid:
            return QVariant::fromValue(log.pid);
        case LogTableColumn::NumberOfBytes:
            return QVariant::fromValue(log.numberOfBytes);
        case LogTableColumn::Offset:
            return QVariant::fromValue(log.offset);
        case LogTableColumn::Preview:
            return log.preview;
        case LogTableColumn::FileHandle:
            return log.fileHandle;
        case LogTableColumn::OperationTime:
            return QVariant::fromValue(log.operationTime);
        case LogTableColumn::ResultOfTheOperation:
            return log.resultOfTheOperation;
        default:
            return QVariant();
        }
    }
    return QVariant();
}

void LogModel::getDataFromBuffer(){
    size_t logsCountBeforeAddingBuffer = logs.size();
    auto logsFromBuffer = logBuffer->getLogsFromTheBuffer();
    if(logsFromBuffer.size() == 0 ) return;
    beginInsertRows(QModelIndex(), logsCountBeforeAddingBuffer , logsCountBeforeAddingBuffer + logsFromBuffer.size() - 1);
    logs.insert(logs.end(), logsFromBuffer.begin(), logsFromBuffer.end());
    endInsertRows();
}

void LogModel::clearLogs(){
    beginResetModel();
    logs.clear();
    endResetModel();
}
