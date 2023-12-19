#include "receive_message.h"

#include <netinet/in.h>



Receive_Message::Receive_Message(int num) : CLIENT_SOCKET(num)
{
}

void Receive_Message::run()
{
    while (true)
    {
      int bytesReceived = recv(CLIENT_SOCKET, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0)
        {
            buffer[bytesReceived] = '\0';
            QString receivedMessage = QString::fromStdString(buffer);
            emit pastReceivedMessage(receivedMessage);
        }
    }
}
