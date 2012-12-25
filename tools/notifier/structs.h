#ifndef STRUCTS_H
#define STRUCTS_H

#include <QRegExp>
#include <QString>
#include <QList>

const int update_interval = 60;

struct friend_t
{
    QRegExp player;
    QRegExp clan;

    friend_t()
    {
        player.setPatternSyntax(QRegExp::Wildcard);
        clan.setPatternSyntax(QRegExp::Wildcard);
    }
};
struct player_t
{
    QString player;
    QString clan;

    bool is_friend(const friend_t& f) const
    {
        return f.player.exactMatch(player) && f.clan.exactMatch(clan);
    }

    bool operator ==(const player_t& rhs) const
    {
        return(player == rhs.player && clan == rhs.clan);
    }
};

struct server_t
{
    QString name;
    QString map;

    int player_count;

    QList<player_t> players;
};

#endif // STRUCTS_H
