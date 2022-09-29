#pragma once

#include <QAbstractTableModel>

struct LogInfo{
    QString filePath;
    QString operationType;
    DWORD pid;
    DWORD numberOfBytes;
    DWORD offset;
    QString preview;
    QString fileHandle;
    QString operationTime;
    QString resultOfTheOperation;
};

namespace Columns{
    enum Column{
        FilePath,
        OperationType,
        Pid,
        NumberOfBytes,
        Offset,
        Preview,
        FileHandle,
        OperationTime,
        ResultOfTheOperation,
        ColumnCount
    };
}

class LogModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit LogModel(QObject *parent = nullptr);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    std::vector<LogInfo> logs;
};
