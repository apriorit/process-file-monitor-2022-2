#include "pch.h"
#include "logmodel.h"

LogModel::LogModel(QObject *parent)
    : QAbstractListModel(parent),
      timer{new QTimer(this)}
{
    timer->setInterval(100);
    connect(timer, &QTimer::timeout , this, &LogModel::test);
    timer->start();
}

int LogModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return logs.size();
}

QVariant LogModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    int row = index.row();
    if(role == Qt::DisplayRole){
        return logs[row];
    }
    return QVariant();
}

bool LogModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    logs.push_back("Update.exe Always Surprise !");
    endInsertRows();
    if(logs.size() > logsLimit){
        removeRows(0, 1);
    }
    return true;
}

bool LogModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    auto firstToDelete = logs.begin() + row;
    auto lastToDelete = firstToDelete + count;
    logs.erase(firstToDelete, lastToDelete);
    endRemoveRows();
    return true;
}

void LogModel::clearData(){
    beginResetModel();
    logs.clear();
    endResetModel();
}

void LogModel::test(){
    insertRows(logs.size(), 1 , QModelIndex());
}
