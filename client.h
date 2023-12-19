#ifndef CLIENT_H
#define CLIENT_H

#include "ip_and_port.h"
#include "chat_interface.h"
#include "receive_message.h"

#include <QMainWindow>
#include <QStackedLayout>
#include <netinet/in.h>
#include <QThread>
#include <thread>

class client : public QMainWindow
{
    Q_OBJECT

public:
    static client* getInstance();  // Static member function to get the instance

private slots:
    void handleConnection();
    void sendInputedMessage(const QString& message);
    void receiveMessage(const QString message);

signals:
    void sendReceivesMessage(const QString& message);

private:
    client();  // Private constructor

    void start_programm();

private:
    static client* instance;  // Static member variable to hold the instance

    Receive_Message* receive;
    QWidget* centralWidget;
    ip_and_port* getIpAndPort;
    chat_interface* chatInterface;
    QStackedLayout* stackedLayout;
    int CLIENT_SOCKET;
    sockaddr_in serverAddress;
    char buffer[4096];
    bool is_connected;
    int SERVER_PORT;
    QString SERVER_IP;
    QThread receiverThread;
};

#endif // CLIENT_H
