#include <QtGui>
#include <QApplication>
#include <QSystemTrayIcon>

#include "window.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Teeworlds Notifier"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));
        return 1;
    }

    QCoreApplication::setOrganizationName("Disarmer Inc.");
    QCoreApplication::setOrganizationDomain("disarmer.ru");
    QCoreApplication::setApplicationName("Teeworlds notifier");


    QApplication::setQuitOnLastWindowClosed(false);

    window w;
    //w.show();
    
    return a.exec();
}
