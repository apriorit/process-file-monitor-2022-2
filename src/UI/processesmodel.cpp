#include "pch.h"
#include "processesmodel.h"
#include "processmonitor.h"

namespace Column{
    enum Columns{
        PidColumn,
        Executable,
        ReadPerm,
        WritePerm,
        DeletePerm,
        OpenPerm,
        IsMonitored,
        ColumnCount
    };
}

ProcessesModel::ProcessesModel(QObject *parent, IProcessMonitor* processMonitor)
    : QAbstractTableModel(parent),
      processMonitor{processMonitor},
      timer{new QTimer(this)}
{
    updateProcessesList();
    const int updateIntervalInMs = 1000;
    timer->setInterval(updateIntervalInMs);
    connect(timer, &QTimer::timeout , this, &ProcessesModel::updateProcessesList);
    timer->start();
}

QVariant ProcessesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole && orientation == Qt::Horizontal){
        switch(section){
        case Column::PidColumn:
            return "PID";
        case Column::Executable:
            return "Executable";
        case Column::ReadPerm:
            return "Read Permission";
        case Column::WritePerm:
            return "Write Permission";
        case Column::DeletePerm:
            return "Delete Permission";
        case Column::OpenPerm:
            return "Open Permission";
        case Column::IsMonitored:
            return "Monitor Process";
        }
    }
    return QVariant();
}

int ProcessesModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return processMonitor->getProcessesCount();;
}

int ProcessesModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return Column::ColumnCount;
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
            case Column::PidColumn:
                return QVariant(static_cast<unsigned long long>(processInfo.Pid));
            case Column::Executable:
                return processInfo.Name;
            case Column::ReadPerm:
                return "read";
            case Column::WritePerm:
                return "write";
            case Column::DeletePerm:
                return "open";
            case Column::OpenPerm:
                return "delete";
            case Column::IsMonitored:
                return "monitor";
            }
    break;
    case Qt::CheckStateRole:
        switch(col){
            case Column::ReadPerm:
                return boolToCheckStatus(processInfo.readPermission);
            case Column::WritePerm:
                return boolToCheckStatus(processInfo.writePermission);
            case Column::DeletePerm:
                return boolToCheckStatus(processInfo.deletePermission);
            case Column::OpenPerm:
                return boolToCheckStatus(processInfo.openPermission);
            case Column::IsMonitored:
                return boolToCheckStatus(processInfo.isMonitored);
        }
        break;
    }
    return QVariant();
}

void ProcessesModel::updateProcessesList(){
    processMonitor->updateProcessesTable();
    emit layoutChanged();
}

bool ProcessesModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if(role == Qt::CheckStateRole){
        if(!checkIndex(index))
            return false;
        const int row = index.row();
        const int col = index.column();
        bool checked = value.toBool();
        std::unique_ptr<ProcessEditableFields> field;

        switch(col){
        case Column::ReadPerm:
            field = std::make_unique<ProcessEditableFields>(ProcessEditableFields::readPerm);
        break;
        case Column::WritePerm:
            field = std::make_unique<ProcessEditableFields>(ProcessEditableFields::writePerm);
        break;
        case Column::OpenPerm:
            field = std::make_unique<ProcessEditableFields>(ProcessEditableFields::openPerm);
        break;
        case Column::DeletePerm:
            field = std::make_unique<ProcessEditableFields>(ProcessEditableFields::deletePerm);;
        break;
        case Column::IsMonitored:
            field = std::make_unique<ProcessEditableFields>(ProcessEditableFields::isMonitored);
        break;
        }
        if(field){
            processMonitor->setProcessEditableFieldByIndex(row, *field, checked);
            return true;
        }
    }
    return false;
}

Qt::ItemFlags ProcessesModel::flags(const QModelIndex &index) const{
    const int col = index.column();
    auto flag = QAbstractTableModel::flags(index);
    if(col == Column::ReadPerm
            || col == Column::WritePerm
            || col == Column::DeletePerm
            || col == Column::OpenPerm
            || col == Column::IsMonitored){
        return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | flag;
    }
    return flag;
}

QVariant ProcessesModel::boolToCheckStatus(bool value){
    if(value) return Qt::Checked;
    else return Qt::Unchecked;
}
