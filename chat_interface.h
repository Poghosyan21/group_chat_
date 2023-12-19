#ifndef CHAT_INTERFACE_H
#define CHAT_INTERFACE_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QScrollArea>
#include <QVBoxLayout>

class chat_interface : public QWidget
{
    Q_OBJECT
public:
    chat_interface(QWidget* parent = nullptr);

public slots:
    void printReceivedMessage(const QString& message);

private slots:
    void onSendButtonCliced();

signals:
    void sendMessage(const QString& message);

private:
    QLineEdit* messageEdit;
    QPushButton* sendButton;
    QWidget* messageWidget;
    QScrollArea* scrollArea;
    QVBoxLayout* layout;


private:
    void addMessage(const QString& text, bool isUser);
};

#endif // CHAT_INTERFACE_H
