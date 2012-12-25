#ifndef WINDOW_H
#define WINDOW_H
#include <QtGui>
#include <QtCore>
#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QSystemTrayIcon>
#include <QDialog>

#include "structs.h"
#include "table_model.h"

namespace Ui {
class window;
}

class window : public QDialog
{
    Q_OBJECT
    
public:
    explicit window(QWidget *parent = 0);
    ~window();
    
private:
    Ui::window *ui;

    QSystemTrayIcon * tray_icon;


    /***/
    QNetworkAccessManager * manager;

    //QList<friend_t> friends;

    QTimer *timer;

    table_model * friends_table;

    int need_correction;
    //

public slots:
    void readyRead(QNetworkReply * reply);

    void mainloop();

    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    //void showMessage();
    void messageClicked();

    void remove_rows();
    void add_row();
    void apply_settings();

};

#endif // WINDOW_H
