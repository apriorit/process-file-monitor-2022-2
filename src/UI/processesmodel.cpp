#include "pch.h"
#include "processesmodel.h"
#include "processmonitor.h"
ProcessesModel::ProcessesModel(QObject *parent, IProcessMonitor* processMonitor)
    : QAbstractTableModel(parent),
      processMonitor{processMonitor},
      timer{new QTimer(this)}
{
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout , this, &ProcessesModel::updateProcessesList);
    timer->start();
}
/*
QVariant ProcessesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}
*/
int ProcessesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return rowNumber;
    // FIXME: Implement me!
}

int ProcessesModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return colNumber;
    // FIXME: Implement me!
}

QVariant ProcessesModel::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    const int col = index.column();

    if (!index.isValid())
        return QVariant();

    switch(role){
    case Qt::DisplayRole:
        ProcessInfo processInfo = processMonitor->getCopyOfProcessInfoByIndex(row);
            switch(col){
            case 0:
                return QVariant(static_cast<unsigned long long>(processInfo.Pid));
            case 1:
                return processInfo.Name;

        }
    }
    // FIXME: Implement me!
    return QVariant();
}
/* To DO
 * mergeProcesses Lists receive unsorted vectors and does'nt work properly !
 */

void ProcessesModel::updateProcessesList(){
    qDebug() << "Start";
    processMonitor->updateProcessesTable();
    qDebug() << "get";
    rowNumber = processMonitor->getProcessesCount()-1;
    qDebug() << "Setted row number to " << QVariant(rowNumber);

    emit layoutChanged();
}
