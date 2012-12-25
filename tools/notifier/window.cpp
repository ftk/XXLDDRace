#include "window.h"
#include "ui_window.h"

#include <QDateTime>

QVector<server_t> servers;


static QList<player_t> check_friends(const QList<friend_t>& friends, const QList<player_t>& players)
{
    QList<player_t> result;
    for(int i = 0; i < players.count(); i++)
    {
        for(int j = 0; j < friends.count(); j++)
        {
            if(players.at(i).is_friend(friends.at(j)))
                result += players.at(i);
        }
    }
    return result;
}

// ---

window::window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::window)
{
    ui->setupUi(this);

    friends_table = new table_model(this);

    ui->tableView->setModel(friends_table);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(ui->add, SIGNAL(clicked()), this, SLOT(add_row()));
    connect(ui->remove, SIGNAL(clicked()), this, SLOT(remove_rows()));
    connect(ui->close, SIGNAL(clicked()), this, SLOT(apply_settings()));

    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(readyRead(QNetworkReply*)));

    // define tray icon

    QAction * quit_action = new QAction(tr("&Quit"), this);
    connect(quit_action, SIGNAL(triggered()), qApp, SLOT(quit()));
    QAction * settings_action = new QAction(tr("&Settings"), this);
    connect(settings_action, SIGNAL(triggered()), this, SLOT(show()));

    QMenu * tray_menu = new QMenu(this);
    tray_menu->addAction(settings_action);
    tray_menu->addSeparator();
    tray_menu->addAction(quit_action);

    tray_icon = new QSystemTrayIcon(this);
    tray_icon->setContextMenu(tray_menu);

    connect(tray_icon, SIGNAL(messageClicked()), this, SLOT(messageClicked()));
    connect(tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));


    QIcon icon(":/images/teeworlds_1.png");
    tray_icon->setIcon(icon);
    setWindowIcon(icon);

    tray_icon->setToolTip("Teeworlds Notifier");

    tray_icon->show();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(mainloop()));
    //timer->start(update_interval * 1000);

    need_correction = 2;
    mainloop();
}

window::~window()
{
    delete ui;
    delete friends_table;
    delete manager;

    delete tray_icon;

    delete timer;
}




void window::readyRead(QNetworkReply * reply)
{
    if(reply->error() != QNetworkReply::NoError)
    {
        tray_icon->setToolTip("Teeworlds Notifier - offline");
        reply->deleteLater();
        return;
    }

    QString notify_text = "";


    QStringList lines = QString(reply->readAll()).split('\n');
    int line = 1;

    reply->deleteLater();
    if(need_correction == 2)
    {
        need_correction = 1;
        unsigned int current_time = QDateTime::currentDateTime().toTime_t();
        unsigned int generation_time = lines.at(0).toUInt();
        int diff = generation_time + update_interval - current_time + 1;
        timer->stop();
        if(diff < update_interval && diff > 0)
            timer->start(diff * 1000);
        else
        {
            timer->start(update_interval * 1000);
            need_correction = 0;
        }
        //qDebug() << current_time << ' ' << diff;

    }
    else if(need_correction == 1)
    {
        timer->stop();
        timer->start(update_interval * 1000);
        need_correction = 0;
    }

    int servers_count = lines.at(line++).toInt();
    servers.resize(servers_count);
    int players_total = 0;

    //Q_ASSERT(servers <= max_servers);
    for(int i = 0; i < servers_count; i++)
    {
        servers[i].player_count = lines.at(line++).toInt();
        servers[i].name = lines.at(line++);
        servers[i].map = lines.at(line++);

        QList<player_t> players;
        players.reserve(servers[i].player_count);
        for(int j = 0; j < servers[i].player_count; j++)
        {
            player_t pl;
            pl.player = lines.at(line++);
            pl.clan = lines.at(line++);
            players.append(pl);
        }

        /* */
        players = check_friends(friends_table->friends, players); // get friends only

        players_total += players.count();

        for(int j = 0; j < players.count(); j++)
        {
            //ui->plainTextEdit->document()->setPlainText(newplayers.at(j).player);
            const player_t& p = players.at(j);
            if(!servers.at(i).players.contains(p))
            {
                // notify
                QString fmt;
                if(p.clan.isEmpty())
                    fmt = QString("\'%1\' is now playing on server %2 (Map: %3)\n").arg(p.player,
                                                                                        servers.at(i).name, servers.at(i).map);
                else
                    fmt = QString("\'%1\' (%2) is now playing on server %3 (Map: %4)\n").arg(p.player, p.clan,
                                                                                             servers.at(i).name, servers.at(i).map);

                notify_text += fmt;
            }
        }
        servers[i].players = players;

    }
    if(!notify_text.isEmpty())
    {
        // show notifier
        tray_icon->showMessage("Teeworlds", notify_text);
    }

    tray_icon->setToolTip(QString("Teeworlds Notifier - %1 player(s) online").arg(QString::number(players_total)));

}


void window::mainloop()
{
    static QNetworkRequest request(QUrl("http://disarmer.ru/tee/custom"));
    //request.setRawHeader("Accept-Charset", "utf-8");
    //request.setRawHeader("Connection", "close");
    /*reply = */
    manager->get(request);
    //connect(reply, SIGNAL(readyRead()), this, SLOT(readyRead()));

}


void window::messageClicked()
{
}

void window::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
        break;
    case QSystemTrayIcon::DoubleClick:
    {
        QString msg;
        //int players_count = 0;
        for(int i = 0; i < servers.count(); i++)
        {
            const QList<player_t>& players = servers.at(i).players;
            //players_count += players.count();
            for(int j = 0; j < players.count(); j++)
                msg += QString("%1 (%5:%2): %3 (%4)\n").arg(servers.at(i).name, servers.at(i).map,
                                                    players.at(j).player, players.at(j).clan,
                                                            QString::number(servers.at(i).player_count));

        }
        if(!msg.isEmpty())
            QMessageBox::information(this, "Teeworlds Notifier", msg);
        break;
    }

    case QSystemTrayIcon::MiddleClick:
        break;
    default:
        ;
    }
}

void window::add_row()
{
    friends_table->insertRows(friends_table->rowCount(), 1);
}
void window::remove_rows()
{
    QList<int> rows;
    foreach(const QModelIndex & index, ui->tableView->selectionModel()->selection().indexes())
    {
        rows.append(index.row());
    }

    qSort(rows);

    int prev = -1;
    for(int i = rows.count() - 1; i >= 0; i--)
    {
        int current = rows[i];
        if(current != prev)
        {
            friends_table->removeRows( current, 1 );
            prev = current;
        }
    }
}

void window::apply_settings()
{
    this->hide();
    if(timer->isActive())
        timer->stop();
    need_correction = 2; // set this to 2 every time manually calling mainloop
    mainloop();
}
