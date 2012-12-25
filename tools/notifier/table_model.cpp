#include "table_model.h"

#include <QtAlgorithms>
#include <QSettings>

table_model::table_model(QObject *parent) :
    QAbstractTableModel(parent)
{
    QSettings settings;
    int size = settings.beginReadArray("friends");
    for (int i = 0; i < size; ++i)
    {
        settings.setArrayIndex(i);
        friend_t p;
        p.player.setPattern(settings.value("name").toString());
        p.clan.setPattern(settings.value("clan").toString());
        friends.append(p);
    }
    settings.endArray();
    if(!size)
    {
        friend_t ruclan;
        ruclan.player.setPattern("*");
        ruclan.clan.setPattern(".ru!");

        friends.append(ruclan);
    }

}

table_model::~table_model()
{
    QSettings settings;
    settings.beginWriteArray("friends", friends.size());
    for (int i = 0; i < friends.size(); ++i) {
        settings.setArrayIndex(i);
        settings.setValue("name", friends.at(i).player.pattern());
        settings.setValue("clan", friends.at(i).clan.pattern());
    }
	settings.endArray();
}


int table_model::rowCount(const QModelIndex & /*parent*/) const
{
    return friends.count();
}

int table_model::columnCount(const QModelIndex & /*parent*/) const
{
    return 2;
}

QVariant table_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("Name");
            case 1:
                return QString("Clan");
            }
        }
    }
    return QVariant();
}

QVariant table_model::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if(index.column() == 0)
            return friends.at(index.row()).player.pattern();
        else if(index.column() == 1)
            return friends.at(index.row()).clan.pattern();
    }
    return QVariant();
}

bool table_model::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (role == Qt::EditRole)
    {
        QString val = value.toString();
        if(index.column() == 0)
            friends[index.row()].player.setPattern(val);
        else if(index.column() == 1)
            friends[index.row()].clan.setPattern(val);
    }
    return true;
}


Qt::ItemFlags table_model::flags(const QModelIndex & /*index*/) const
{
    return Qt::ItemIsSelectable |  Qt::ItemIsEditable | Qt::ItemIsEnabled ;
}


bool table_model::removeRows(int position, int rows, const QModelIndex &)
{
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row=0; row < rows; ++row) {
        friends.removeAt(position);
    }

    endRemoveRows();
    return true;
}

bool table_model::insertRows(int position, int rows, const QModelIndex &)
{
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row=0; row < rows; row++) {
        friend_t dummy;
        friends.insert(position, dummy);
    }

    endInsertRows();
    return true;
}

