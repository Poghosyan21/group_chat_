#ifndef RECEIVE_MESSAGE_H
#define RECEIVE_MESSAGE_H
#include <QThread>

class Receive_Message : public QThread
{
    Q_OBJECT
public:
    Receive_Message(int);
    void run() override;
signals:
    void pastReceivedMessage(const QString message);

private:
    char buffer[4096];
    int CLIENT_SOCKET;

};

#endif // RECEIVE_MESSAGE_H
