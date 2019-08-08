#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAbstractSocket>
class QTcpSocket;
class QFile;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void openFile();
    void send();
    void startTransfer();
    void updateClientProgress(qint64);
    void displayError(QAbstractSocket::SocketError);
    void openBtnClicked();
    void sendBtnClicked();

private:
    Ui::Widget *ui;
    QTcpSocket *m_tcpClient;
    QFile *m_localFile;
    qint64 m_totalBytes;
    qint64 m_bytesWritten;
    qint64 m_bytesToWrite;
    qint64 m_payloadSize;
    QString m_fileName;
    QByteArray m_outBlock;
};

#endif // WIDGET_H
