#include "datareceiver.h"
#include "ui_datatransfer.h"

#include<QtNetwork>

DataTransfer::DataTransfer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DataTransfer)
{
    ui->setupUi(this);
    tcpsunucu = new QTcpServer;
    connect(tcpsunucu,SIGNAL(newConnection()),this,SLOT(yeniBaglanti()));

    if(tcpsunucu -> listen(QHostAddress::LocalHost,1234)){
        qDebug() << "sunucu baslatildi";
    }
    else{
        qDebug() << "sunucu baslatilamadi";
    }

    udpReceiver=new QUdpSocket(this);
    udpReceiver->bind(2323,QUdpSocket::ShareAddress);

    connect(udpReceiver,&QUdpSocket::readyRead,this,&DataTransfer::DataTransfer::processPendingDatagram);

}

DataTransfer::~DataTransfer()
{
    delete ui;
}

void DataTransfer::yeniBaglanti()
{
        tcpsoket = tcpsunucu->nextPendingConnection();
        tcpsoket ->waitForBytesWritten();

        connect(tcpsoket,SIGNAL(readyRead()),SLOT(hazir()));
        connect(tcpsoket,SIGNAL(disconnected()),SLOT(baglantiyiKapat()));

}

void DataTransfer::hazir()
{
QByteArray veri = tcpsoket->readAll();
ui->textBrowser->setText(veri);
ui->textBrowser->setStyleSheet("background-color: green");
 QTimer::singleShot(10000,this,[=]{ui->textBrowser->setStyleSheet("background-color:white");});
}

void DataTransfer::baglantiyiKapat()
{
    qDebug() << "Baglanti sonlandi";
}

void DataTransfer::processPendingDatagram()
{
    while(udpReceiver->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpReceiver->pendingDatagramSize());
        udpReceiver->readDatagram(datagram.data(),datagram.size());
        ui->textBrowser->setText(QString::fromLocal8Bit(  datagram));
        ui->textBrowser->setStyleSheet("background-color: green");
         QTimer::singleShot(10000,this,[=]{ui->textBrowser->setStyleSheet("background-color:white");});
        }
    }


