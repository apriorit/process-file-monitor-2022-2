#include "pch.h"
#include "processesmodel.h"
#include "processmonitor.h"
ProcessesModel::ProcessesModel(QObject *parent)
    : QAbstractTableModel(parent)
{
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
    return 5;
    // FIXME: Implement me!
}

int ProcessesModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 6;
    // FIXME: Implement me!
}

QVariant ProcessesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    const int row = index.row();
    const int col = index.column();
    switch(role){
    case Qt::DisplayRole:
        return QString("Row%1, Column%2")
                    .arg(row + 1)
                    .arg(col +1);
    }
    // FIXME: Implement me!
    return QVariant();
}
