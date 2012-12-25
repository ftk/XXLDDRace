#ifndef TABLE_MODEL_H
#define TABLE_MODEL_H

#include <QAbstractTableModel>
#include <QItemSelectionModel>
#include "structs.h"
#include <QList>

class table_model : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit table_model(QObject *parent = 0);
    virtual ~table_model();

    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;


    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex & index) const ;

    bool insertRows(int position, int rows, const QModelIndex &index =QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index =QModelIndex());
public:

    QList<friend_t> friends;

signals:
    
public slots:
    
};

#endif // TABLE_MODEL_H
