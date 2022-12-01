#include "uieventprocessor.h"
//#include <QApplication>
#include <QBuffer>

UiEventProcessor::UiEventProcessor(ConnectionProvider *provider, QObject *parent)
    : QObject{parent}
{
    this->connectionProvider = provider;
}

UiEventProcessor::~UiEventProcessor()
{
    connectionProvider->setActiveConnection(NONE);
    delete connectionProvider;
}

void UiEventProcessor::onSocketsConnectionClicked()
{
    qDebug() << "Sockets button clicked";
    if (connectionProvider->setActiveConnection(SOCKETS)) {
        emit socketsConnected();
    } else {
        emit connectionFailed();
    }
}


void UiEventProcessor::onMailslotsConnectionClicked()
{
    qDebug() << "Mailslots button clicked";
    if (connectionProvider->setActiveConnection(MAILSLOTS)) {
        emit mailslotsConnected(QString::number(GetCurrentProcessId()));
    } else {
        emit connectionFailed();
    }
}

void UiEventProcessor::onMessageSend(QString message)
{
    connectionProvider->sendChatMessage(message, "TEXT");
}

void UiEventProcessor::onOpenImageClicked(QString path)
{
   qDebug() << "Open image" << path;
   QUrl url(path);
   QFile file(url.path().mid(1));
   if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        qCritical() << "Can't open file: " + file.errorString();
        return;
   }

   file.close();

   QImage imageObject;
   imageObject.load(url.path().mid(1));
   QPixmap image = QPixmap::fromImage(imageObject);

   QByteArray ba;              // Construct a QByteArray object
   QBuffer buffer(&ba);        // Construct a QBuffer object using the QbyteArray
   image.save(&buffer, "JPG"); // Save the QImage data into the QBuffer

   connectionProvider->sendChatMessage(QString::fromLatin1(ba.toBase64()), "IMAGE");
//   qjo.insert("request_type", PHOTO_REQUEST);
//   qjo.insert("photo", QString::fromLatin1(ba.toBase64()));

//   qDebug() << "Size of QString::fromLatin1(ba.toBase64())): " << QString::fromLatin1(ba.toBase64()).size();	// 470184

//   QJsonDocument doc(qjo);
//   QString strJson(doc.toJson(QJsonDocument::Compact));
//   info.append(strJson);
//   ds << info;

}

void UiEventProcessor::onLoginClicked(const QString &name, const QString &password)
{
    connectionProvider->sendLoginMessage(name, password);
}

void UiEventProcessor::onRegisterClicked(const QString &name, const QString &password)
{
    connectionProvider->sendRegisterMessage(name, password);
}
