#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QByteArray access_key = "AWS Access Key Here";
    QByteArray secret_key = "AWS Secret Key Here";

    Polly = new QtAws(access_key, secret_key);
    connect(Polly, &QtAws::requestStream, this, &MainWindow::receiveAudioStream);

    Polly->requestPolly("This is an Polly request from Qt Polly", "Amy");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::receiveAudioStream(QByteArray stream)
{
    QFile cacheAudio(QApplication::applicationDirPath().append("/output.mp3"));

    if(cacheAudio.open(QFile::ReadWrite))
    {
        cacheAudio.write(stream);
        cacheAudio.close();
    }
}
