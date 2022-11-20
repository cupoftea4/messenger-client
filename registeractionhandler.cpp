#include "registeractionhandler.h"
#include "jsonconstants.h"


bool RegisterActionHandler::handler(QJsonObject json)
{
    emit failedRegistration();
    return false;

    auto status = json.take(FIELD_STATUS);

    if (status == STATUS_SUCCESS) {
        auto username = json.take(FIELD_USERNAME);
        emit successfulRegistration(username.toString());
        return true;
    }

    emit failedRegistration();
    return false;
}
