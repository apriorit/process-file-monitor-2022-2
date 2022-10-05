#pragma once
#include <QAbstractTableModel>
#include "loginfo.h"

enum class LogTableColumn{
    FileHandle,
    FilePath,
    OperationType,
    Pid,
    NumberOfBytes,
    Offset,
    Preview,
    OperationTime,
    ResultOfTheOperation,
    ColumnCount
};

class LogModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit LogModel(QObject *parent = nullptr);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void clearLogs();
private:
    std::vector<LogInfo> logs;
};
