#ifndef JSONCONSTANTS_H
#define JSONCONSTANTS_H

// json fields
const char *const FIELD_ACTION = "action";
const char *const FIELD_PAYLOAD = "payload";
const char *const FIELD_USERNAME = "username";
const char *const FIELD_PASSWORD = "password";
const char *const FIELD_STATUS = "status";

// json actions
const char *const ACTION_PING = "PING";
const char *const ACTION_LOGIN = "LOGIN";
const char *const ACTION_REGISTER = "REGISTER";
const char *const ACTION_MESSAGE = "MESSAGE";

// json status
const char *const STATUS_SUCCESS = "SUCCESS";
const char *const STATUS_FAIL = "FAIL";

#endif // JSONCONSTANTS_H
