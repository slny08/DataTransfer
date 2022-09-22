#ifndef DATATRANSFER_H
#define DATATRANSFER_H

#include "qudpsocket.h"
#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class DataTransfer; }
QT_END_NAMESPACE

class DataTransfer: public QMainWindow
{
    Q_OBJECT

public:
    DataTransfer(QWidget *parent = nullptr);
    ~DataTransfer();

private:
    Ui::DataTransfer *ui;
    QTcpServer *tcpsunucu;
    QTcpSocket *tcpsoket;
    QUdpSocket* udpReceiver;

public slots:
    void yeniBaglanti();
    void hazir();
    void baglantiyiKapat();
    void processPendingDatagram();
};
#endif // DATATRANSFER_H






