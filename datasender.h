#ifndef DATATRANSFER_H
#define DATATRANSFER_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class DataTransfer; }
QT_END_NAMESPACE

class QUdpSocket;
class DataTransfer : public QMainWindow
{
    Q_OBJECT

public:
    DataTransfer(QWidget *parent = nullptr);
    ~DataTransfer();
      enum class comboItems { TCP, UDP,};

private slots:
    void on_pushButton_clicked();
    void chooseConnection (comboItems which );

private:
    Ui::DataTransfer *ui;
     QTcpSocket *tcpsoket;

     QUdpSocket* udpsoket;
};


#endif // DATATRANSFER_H




