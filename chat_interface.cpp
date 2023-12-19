#include "chat_interface.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollBar>
#include <QDebug>

chat_interface::chat_interface(QWidget* parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);

    scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);




    messageWidget = new QWidget(this);
    QVBoxLayout *messageLayout = new QVBoxLayout(messageWidget);
    messageLayout->setAlignment(Qt::AlignTop);


    scrollArea->setWidget(messageWidget);


    messageWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    messageLayout->setSizeConstraint(QLayout::SetMinimumSize);

    layout->addWidget(scrollArea);

    messageEdit = new QLineEdit();
    sendButton = new QPushButton("Send");
    connect(sendButton, &QPushButton::clicked, this, &chat_interface::onSendButtonCliced);
    connect(messageEdit, &QLineEdit::returnPressed, this, &chat_interface::onSendButtonCliced);

    QHBoxLayout *blueGreenLayout = new QHBoxLayout();

    QWidget *blueWidget = new QWidget(this);
    blueWidget->setStyleSheet("background-color: #3498DB;");
    blueWidget->setFixedWidth(width() / 4);
    blueGreenLayout->addWidget(blueWidget);

    QWidget *greenWidget = new QWidget(this);
    greenWidget->setStyleSheet("background-color: #4CAF50;");
    blueGreenLayout->addWidget(greenWidget);

    layout->addLayout(blueGreenLayout);
    layout->addWidget(messageEdit);
    layout->addWidget(sendButton);

    setFixedSize(800, 1000);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
}


void chat_interface::onSendButtonCliced()
{
    QString message = messageEdit->text();

    if (!message.isEmpty())
    {
        addMessage(message, true);
        messageEdit->clear();
        emit sendMessage(message);
    }
}

void chat_interface::printReceivedMessage(const QString &message)
{
    addMessage(message, false);
}





void chat_interface::addMessage(const QString &text, bool isUser)
{
    QFontMetrics metrics(messageWidget->font());
    int maxWidth = scrollArea->viewport()->width();
    int maxCharsPerLine = maxWidth / metrics.averageCharWidth();

    QStringList lines;
    QStringList words = text.split(" ", Qt::SkipEmptyParts);
    QString currentLine;

    for (const QString &word : words)
    {
        if (currentLine.length() + word.length() + 1 <= maxCharsPerLine / 2)
        {
            if (!currentLine.isEmpty())
                currentLine += " ";
            currentLine += word;
        }
        else
        {
            lines.append(currentLine);
            currentLine = word;
        }
    }

    lines.append(currentLine);

    QLabel *messageLabel = new QLabel();
    messageLabel->setText(lines.join("\n"));

    if (isUser)
    {
        messageLabel->setStyleSheet("background-color: #4CAF50; color: white; border-radius: 10px; padding: 8px; margin-left: 400px;");
        messageLabel->setAlignment(Qt::AlignRight);
    }
    else
    {
        messageLabel->setStyleSheet("background-color: #3498DB; color: white; border-radius: 10px; padding: 8px; margin-right: 400px;");
        messageLabel->setAlignment(Qt::AlignLeft);
    }

    QVBoxLayout *messageLayout = qobject_cast<QVBoxLayout *>(messageWidget->layout());

    messageLayout->addWidget(messageLabel);
    messageLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    scrollArea->verticalScrollBar()->setValue(scrollArea->verticalScrollBar()->maximum());
}

