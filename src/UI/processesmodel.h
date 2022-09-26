#pragma once

#include <QAbstractTableModel>

class IProcessMonitor;

class ProcessesModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ProcessesModel(QObject *parent, IProcessMonitor* processMonitor);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    static QVariant boolToCheckStatus(bool value);

public slots:
    void updateProcessesList();
private:
    size_t rowNumber = 0;
    const size_t colNumber = 7;
    IProcessMonitor* processMonitor;
    QTimer* timer;
};
