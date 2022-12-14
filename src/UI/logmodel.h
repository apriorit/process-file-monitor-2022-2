#pragma once
#include <QAbstractTableModel>
#include "../Common/loginfo.h"

class LogBuffer;

enum class LogTableColumn{
    OperationTime,
    Pid,
    FilePath,
    OperationType,
    ResultOfTheOperation,
    FileHandle,
    NumberOfBytes,
    Offset,
    Preview,
    ColumnCount
};

class LogModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit LogModel(QObject *parent, LogBuffer* logBuffer);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void getDataFromBuffer();
    void clearLogs();
private:
    std::vector<LogInfo> logs;
    LogBuffer* logBuffer;
    QTimer* timer;
};
