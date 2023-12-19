#include "ip_and_port.h"
#include <QVBoxLayout>
#include <QLabel>
#include <cstring>
#include <string>
#include <regex>


ip_and_port::ip_and_port(QWidget* parent) : QWidget(parent)
{
    QLabel* nicknameLabel = new QLabel("Enter your nickname:");
    nicknameLabel->setFont(QFont("Arial", 14, QFont::Bold));  // Set a larger font
    nicknameEdit = new QLineEdit(this);
    joinButton = new QPushButton("Join", this);

    connect(joinButton, &QPushButton::clicked, this, &ip_and_port::onJoinClicked);
    connect(nicknameEdit, &QLineEdit::returnPressed, this, &ip_and_port::onJoinClicked);

    layout = new QVBoxLayout(this);

    QSpacerItem* verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    layout->addWidget(nicknameLabel, 0, Qt::AlignHCenter);

    layout->addSpacerItem(verticalSpacer);

    QHBoxLayout* nicknameLayout = new QHBoxLayout();

    nicknameLayout->addWidget(nicknameEdit);
    nicknameLayout->addWidget(joinButton);

    layout->addLayout(nicknameLayout);

    layout->setAlignment(nicknameLayout, Qt::AlignHCenter);

    layout->addSpacerItem(verticalSpacer);
}



void ip_and_port::onJoinClicked()
{
    emit connectionEstablished();
}

QString ip_and_port::getPort()
{
    return "8080";
}


QString ip_and_port::getIP()
{/*
    std::string ifconfigOutput = executeCommand("ifconfig");
    std::regex ipRegex(R"(inet (\d+\.\d+\.\d+\.\d+))");

    std::smatch match;
    std::sregex_iterator next(ifconfigOutput.begin(), ifconfigOutput.end(), ipRegex);
    std::sregex_iterator end;

    while (next != end)
    {
        match = *next;
        std::string ipAddress = match[1].str();

        if (ipAddress != "127.0.0.1")
        {
            return QString::fromStdString(ipAddress);
        }

        ++next;
    }

    return "";*/
    return "192.168.10.253";
}


std::string ip_and_port::executeCommand(const char *cmd)
{
    char buffer[128];
    std::string result = "";
    FILE *pipe = popen(cmd, "r");
    if (!pipe)
    {
        return "";
    }

    while (!feof(pipe))
    {
        if (fgets(buffer, sizeof(buffer), pipe) != nullptr)
        {
            result += buffer;
        }
    }

    pclose(pipe);
    return result;
}

QString ip_and_port::getNickname()
{
    return nicknameEdit -> text();
}
