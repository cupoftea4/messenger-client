#include "registeractionhandler.h"
#include "jsonconstants.h"

//RegisterActionHandler::RegisterActionHandler(QObject *obj)
//{

////    QObject::connect(obj, SIGNAL(failedRegistration()),
////                        this, SLOT(onRegisterFail()));
//    QObject::connect(this, SIGNAL(failedRegistration()),
//                        obj, SLOT(onServerResponse("sffdsf")), Qt::QueuedConnection);
//}

bool RegisterActionHandler::handler(QJsonObject json)
{
    emit failedRegistration();
//    auto status = json.take(FIELD_STATUS);

//    if (status == STATUS_SUCCESS) {
//        auto username = json.take(FIELD_USERNAME);
//        emit successfulRegistration(username.toString());
//        return true;
//    }

//    emit failedRegistration();
    return false;
}
