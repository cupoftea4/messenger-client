#include "loginactionhandler.h"

LoginActionHandler::LoginActionHandler()
{

}

bool LoginActionHandler::handler(QJsonObject json)
{
    emit failedLogin();
    return false;

    auto status = json.take(FIELD_STATUS);

    if (status == STATUS_SUCCESS) {
        auto username = json.take(FIELD_USERNAME);
        emit successfulLogin(username.toString());
        return true;
    }

    emit failedLogin();
    return false;
}
