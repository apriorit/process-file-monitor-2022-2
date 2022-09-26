#include "pch.h"
#include "processesmodel.h"
#include "processmonitor.h"
#include "processinfo.h"

ProcessesModel::ProcessesModel(QObject *parent, IProcessMonitor* processMonitor)
    : QAbstractTableModel(parent),
      processMonitor{processMonitor},
      timer{new QTimer(this)}
{
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout , this, &ProcessesModel::updateProcessesList);
    timer->start();
}

QVariant ProcessesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal){
        switch(section){
        case 0:
            return "PID";
        case 1:
            return "Executable";
        case 2:
            return "Read Permission";
        case 3:
            return "Write Permission";
        case 4:
            return "Delete Permission";
        case 5:
            return "Open Permission";
        case 6:
            return "Monitor Process";
        }
    }
    return QVariant();
}

int ProcessesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return rowNumber;
}

int ProcessesModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return colNumber;
}

QVariant ProcessesModel::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    const int col = index.column();

    if (!index.isValid())
        return QVariant();
    ProcessInfo processInfo = processMonitor->getCopyOfProcessInfoByIndex(row);
    switch(role){
    case Qt::DisplayRole:
            switch(col){
            case 0:
                return QVariant(static_cast<unsigned long long>(processInfo.Pid));
            case 1:
                return processInfo.Name;
            case 2:
                return "read";
            case 3:
                return "write";
            case 4:
                return "open";
            case 5:
                return "delete";
            case 6:
                return "monitor";
            }
    break;
    case Qt::CheckStateRole:
        if(col < 2 || col > 6) break;
        switch(col){
            case 2:
                return boolToCheckStatus(processInfo.readPermission);
            case 3:
                return boolToCheckStatus(processInfo.writePermission);
            case 4:
                return boolToCheckStatus(processInfo.openPermission);
            case 5:
                return boolToCheckStatus(processInfo.deletePermission);
            case 6:
                return boolToCheckStatus(processInfo.isMonitored);
        }
        break;
    }
    return QVariant();
}

void ProcessesModel::updateProcessesList(){
    qDebug() << "Start";
    processMonitor->updateProcessesTable();
    qDebug() << "get";
    rowNumber = processMonitor->getProcessesCount();
    qDebug() << "Setted row number to " << QVariant(rowNumber);

    emit layoutChanged();
}

bool ProcessesModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if(role == Qt::CheckStateRole){
        if(!checkIndex(index))
            return false;
        const int row = index.row();
        const int col = index.column();
        bool checked = value.toBool();

        if(col >= 2 && col <=6){
            ProcessEditableFields field = ProcessEditableFields::readPerm;
            switch(col){
            case 2:
                field = ProcessEditableFields::readPerm;
            break;
            case 3:
                field = ProcessEditableFields::writePerm;
            break;
            case 4:
                field = ProcessEditableFields::openPerm;
            break;
            case 5:
                field = ProcessEditableFields::deletePerm;
            break;
            case 6:
                field = ProcessEditableFields::isMonitored;
            break;

            }
            processMonitor->setProcessEditableFieldByIndex(row, field, checked);
            return true;
        }
    }
    return false;
}

Qt::ItemFlags ProcessesModel::flags(const QModelIndex &index) const{
    const int col = index.column();
    auto flag = QAbstractTableModel::flags(index);
    if(col >= 2 && col <= 6){
        return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | flag;
    }
    return flag;
}

QVariant ProcessesModel::boolToCheckStatus(bool value){
    if(value) return Qt::Checked;
    else return Qt::Unchecked;
}
