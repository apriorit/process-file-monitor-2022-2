#pragma once

#include <QAbstractListModel>
#include <vector>

class LogModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit LogModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    void clearData();
    void test();
private:
    size_t logsLimit = 20;
    std::vector<QString> logs;
    QTimer* timer;
};
