#ifndef PROCESSESMODEL_H
#define PROCESSESMODEL_H

#include <QAbstractTableModel>

class IProcessMonitor;

class ProcessesModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ProcessesModel(QObject *parent = nullptr);

    // Header:
    //QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    IProcessMonitor* processMonitor;
};

#endif // PROCESSESMODEL_H
