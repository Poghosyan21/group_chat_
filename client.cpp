#include "client.h"
#include <arpa/inet.h>

#include <QStackedLayout>
#include <sstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>


client* client::instance = nullptr;

client::client()
    : is_connected(false)
{
    getIpAndPort = new ip_and_port(this);
    chatInterface = new chat_interface(this);
    stackedLayout = new QStackedLayout();

    centralWidget = new QWidget(this);
    centralWidget->setLayout(stackedLayout);
    setCentralWidget(centralWidget);

    stackedLayout->addWidget(getIpAndPort);
    stackedLayout->addWidget(chatInterface);

    connect(getIpAndPort, &ip_and_port::connectionEstablished, this, &client::handleConnection);
    connect(chatInterface, &chat_interface::sendMessage, this, &client::sendInputedMessage);
    connect(this, &client::sendReceivesMessage, chatInterface, &chat_interface::printReceivedMessage);

    stackedLayout->setCurrentIndex(0);
}

client* client::getInstance()
{
    if (!instance)
    {
        instance = new client();
    }
    return instance;
}

void client::handleConnection()
{
    SERVER_PORT = getIpAndPort->getPort().toInt();
    SERVER_IP = getIpAndPort->getIP();
    QString NICKNAME = "Nickname: " +(getIpAndPort->getNickname());
    CLIENT_SOCKET = socket(AF_INET, SOCK_STREAM, 0);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);
    serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP.toUtf8().constData());
    int result = ::connect(CLIENT_SOCKET, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if (result >= 0)
    {
        stackedLayout->setCurrentIndex(1);
        is_connected = true;

        send(CLIENT_SOCKET, NICKNAME.toUtf8().constData(), NICKNAME.length(), 0);

        receive = new Receive_Message(CLIENT_SOCKET);
        connect(receive, &Receive_Message::pastReceivedMessage, this, &client::receiveMessage);
        receive->start();
    }
    else
    {
        ::close(CLIENT_SOCKET);
        is_connected = false;
        stackedLayout->setCurrentIndex(0);
    }
}

void client::sendInputedMessage(const QString& message)
{
    if (is_connected)
        send(CLIENT_SOCKET, message.toUtf8().constData(), message.length(), 0);
}

void client::receiveMessage(const QString receivedMessage)
{
    emit sendReceivesMessage(receivedMessage);
}
