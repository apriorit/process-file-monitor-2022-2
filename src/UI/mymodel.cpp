#include "pch.h"
#include "mymodel.h"

MyModel::MyModel(QObject *parent)
    : QAbstractTableModel(parent),
      timer{std::make_unique<QTimer>(this)}

{
    timer->setInterval(1000);
    connect(timer.get(), &QTimer::timeout , this, &MyModel::timerHit);
    timer->start();
}

int MyModel::rowCount(const QModelIndex & /*parent*/) const
{
   return 2;
}

int MyModel::columnCount(const QModelIndex & /*parent*/) const
{
    return 3;
}

void MyModel::timerHit(){
    QModelIndex topLeft = createIndex(0,0);
    emit dataChanged(topLeft, topLeft, {Qt::DisplayRole});
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    const int row = index.row();
    const int col = index.column();
    qDebug() << QString("row %1, col&2, role %3").arg(row).arg(col).arg(role);
    switch(role){
    case Qt::DisplayRole:
        if(row == 0 && col == 0){
            return QTime::currentTime().toString();
        }
        return QString("Row%1, Column%2")
                    .arg(row + 1)
                    .arg(col +1);
    case Qt::FontRole:
    {
        QFont boldFont;
        boldFont.setBold(true);
        return boldFont;
    }
    case Qt::BackgroundRole:
        return QBrush(Qt::red);
    }


    return QVariant();
}

bool MyModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if (role == Qt::EditRole) {
        if (!checkIndex(index))
            return false;
        //save value from editor to member m_gridData
        m_gridData[index.row()][index.column()] = value.toString();
        //for presentation purposes only: build and emit a joined string
        QString result;
        for (int row = 0; row < ROWS; row++) {
            for (int col= 0; col < COLS; col++)
                result += m_gridData[row][col] + ' ';
        }
        emit editCompleted(result);
        return true;
    }
    return false;
}

Qt::ItemFlags MyModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}
