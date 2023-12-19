#include "client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Use the getInstance() method to obtain the singleton instance
    client* Client = client::getInstance();

    Client->setWindowTitle("Group Chat");
    Client->show();

    return a.exec();
}
