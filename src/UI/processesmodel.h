#ifndef PROCESSESMODEL_H
#define PROCESSESMODEL_H

#include <QAbstractTableModel>

class IProcessMonitor;

class ProcessesModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ProcessesModel(QObject *parent, IProcessMonitor* processMonitor);

    // Header:
    //QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
public slots:
    void updateProcessesList();
private:
    size_t rowNumber = 0;
    const size_t colNumber = 5;
    IProcessMonitor* processMonitor;
    QTimer* timer;
};

#endif // PROCESSESMODEL_H
