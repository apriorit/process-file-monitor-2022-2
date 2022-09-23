#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>
#include "qtimer.h"
#include <memory>

const int COLS = 4;
const int ROWS = 2;

class MyModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit MyModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
public slots:
    void timerHit();

private:
    std::unique_ptr<QTimer> timer;
    QString m_gridData[ROWS][COLS];

signals:
    void editCompleted(const QString &);
};

#endif // MYMODEL_H
