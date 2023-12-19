#ifndef IP_AND_PORT_H
#define IP_AND_PORT_H

#include <QPushButton>
#include<QWidget>
#include <QLineEdit>
#include <QVBoxLayout>


class ip_and_port : public QWidget
{
    Q_OBJECT
public:
    ip_and_port(QWidget* parent = nullptr);
    QString getPort();
    QString getIP();
    QString getNickname();
signals:
    void connectionEstablished();

private slots:
    void onJoinClicked();
private:
    std::string executeCommand(const char *cmd);



    QLineEdit* portLineEdit;
    QLineEdit* ipLineEdit;
    QLineEdit* nicknameEdit;
    QPushButton* joinButton;
    QVBoxLayout* layout;

};

#endif // IP_AND_PORT_H
