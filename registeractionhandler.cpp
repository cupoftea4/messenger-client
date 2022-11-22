#include "registeractionhandler.h"


bool RegisterActionHandler::handle(QJsonObject json)
{
    auto status = json.take(FIELD_STATUS);
    if (status == STATUS_SUCCESS) {
        auto username = json.take(FIELD_USERNAME).toString();
        emit successfulRegistration(username);
        return true;
    }

    emit failedRegistration();
    return false;
}
