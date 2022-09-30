#include "pch.h"
#include "processesmodel.h"
#include "processmonitor.h"

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
    const ProcessTableColumn column = static_cast<ProcessTableColumn>(section);

    if(role == Qt::DisplayRole && orientation == Qt::Horizontal){
        switch(column){
        case ProcessTableColumn::PidColumn:
            return "PID";
        case ProcessTableColumn::Executable:
            return "Executable";
        case ProcessTableColumn::ReadPerm:
            return "Read Permission";
        case ProcessTableColumn::WritePerm:
            return "Write Permission";
        case ProcessTableColumn::DeletePerm:
            return "Delete Permission";
        case ProcessTableColumn::OpenPerm:
            return "Open Permission";
        case ProcessTableColumn::IsMonitored:
            return "Monitor Process";
        default:
            break;
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
    return static_cast<int>(ProcessTableColumn::ColumnCount);
}

QVariant ProcessesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    const int row = index.row();
    const ProcessTableColumn column = static_cast<ProcessTableColumn>(index.column());
    ProcessInfo processInfo = processMonitor->getCopyOfProcessInfoByIndex(row);

    switch(role){
    case Qt::DisplayRole:
            switch(column){
            case ProcessTableColumn::PidColumn:
                return QVariant(static_cast<unsigned long long>(processInfo.Pid));
            case ProcessTableColumn::Executable:
                return processInfo.Name;
            case ProcessTableColumn::ReadPerm:
                return "read";
            case ProcessTableColumn::WritePerm:
                return "write";
            case ProcessTableColumn::DeletePerm:
                return "open";
            case ProcessTableColumn::OpenPerm:
                return "delete";
            case ProcessTableColumn::IsMonitored:
                return "monitor";
            default:
                break;
            }
    break;
    case Qt::CheckStateRole:
        switch(static_cast<ProcessTableColumn>(column)){
            case ProcessTableColumn::ReadPerm:
                return boolToCheckStatus(processInfo.readPermission);
            case ProcessTableColumn::WritePerm:
                return boolToCheckStatus(processInfo.writePermission);
            case ProcessTableColumn::DeletePerm:
                return boolToCheckStatus(processInfo.deletePermission);
            case ProcessTableColumn::OpenPerm:
                return boolToCheckStatus(processInfo.openPermission);
            case ProcessTableColumn::IsMonitored:
                return boolToCheckStatus(processInfo.isMonitored);
            default:
                break;
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
        const ProcessTableColumn column = static_cast<ProcessTableColumn>(index.column());
        bool checked = value.toBool();
        std::unique_ptr<ProcessEditableFields> field;

        switch(column){
        case ProcessTableColumn::ReadPerm:
            field = std::make_unique<ProcessEditableFields>(ProcessEditableFields::readPerm);
        break;
        case ProcessTableColumn::WritePerm:
            field = std::make_unique<ProcessEditableFields>(ProcessEditableFields::writePerm);
        break;
        case ProcessTableColumn::OpenPerm:
            field = std::make_unique<ProcessEditableFields>(ProcessEditableFields::openPerm);
        break;
        case ProcessTableColumn::DeletePerm:
            field = std::make_unique<ProcessEditableFields>(ProcessEditableFields::deletePerm);;
        break;
        case ProcessTableColumn::IsMonitored:
            field = std::make_unique<ProcessEditableFields>(ProcessEditableFields::isMonitored);
        break;
        default:
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
    const ProcessTableColumn column = static_cast<ProcessTableColumn>(index.column());
    auto flag = QAbstractTableModel::flags(index);
    if(column == ProcessTableColumn::ReadPerm
            || column == ProcessTableColumn::WritePerm
            || column == ProcessTableColumn::DeletePerm
            || column == ProcessTableColumn::OpenPerm
            || column == ProcessTableColumn::IsMonitored){
        return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | flag;
    }
    return flag;
}

QVariant ProcessesModel::boolToCheckStatus(bool value){
    if(value) return Qt::Checked;
    else return Qt::Unchecked;
}
