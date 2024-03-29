
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QAbstractSocket>
#include <QTcpServer>
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
    void start();
    void acceptConnection();
    void updateServerProgress();
    void displayError(QAbstractSocket::SocketError socketError);
    void startBtnClicked();

private:
    Ui::Widget *ui;
    QTcpServer m_tcpServer;
    QTcpSocket *m_tcpServerConnection;
    qint64 m_totalBytes;
    qint64 m_bytesReceived;
    qint64 m_fileNameSize;
    QString m_fileName;
    QFile *m_localFile;
    QByteArray m_inBlock;
};

#endif // WIDGET_H

