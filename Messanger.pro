
QT += core gui quick quickcontrols2
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        action_handles/actionhandler.cpp \
        action_handles/loginactionhandler.cpp \
        action_handles/messageactionhandler.cpp \
        action_handles/registeractionhandler.cpp \
        connectins/mailslotconnection.cpp \
        connectins/socketconnection.cpp \
        connectionprovider.cpp \
        jsonfactory.cpp \
        main.cpp \
        messengerconfiguration.cpp \
        quickviewwrapper.cpp \
        servereventservice.cpp \
        signalsconnector.cpp \
        uieventprocessor.cpp

RESOURCES += \
        $$files(qml/*)

LIBS += -lws2_32

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = qml/imports

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH = qml/content

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    qml/content/icons/open.png \
    qml/content/images/i1669877641.png \
    qtquickcontrols2.conf

HEADERS += \
    action_handles/actionhandler.h \
    action_handles/loginactionhandler.h \
    action_handles/messageactionhandler.h \
    action_handles/registeractionhandler.h \
    connectins/connection.h \
    connectins/mailslotconnection.h \
    connectins/socketconnection.h \
    connectionprovider.h \
    jsonconstants.h \
    jsonfactory.h \
    messengerconfiguration.h \
    quickviewwrapper.h \
    servereventservice.h \
    signalsconnector.h \
    uieventprocessor.h

INCLUDEPATH += $$PWD/connectins
INCLUDEPATH += $$PWD/action_handles
