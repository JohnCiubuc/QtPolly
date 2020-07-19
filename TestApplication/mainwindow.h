#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QtNetwork/QNetworkAccessManager>
#include "qtaws.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget * parent = nullptr);
    ~MainWindow();
public slots:
    void receiveAudioStream(QByteArray stream);
private:
    Ui::MainWindow * ui;
    QtAws * Polly;
};
#endif // MAINWINDOW_H
