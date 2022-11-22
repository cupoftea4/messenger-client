QT += quick
QT += quickcontrols2

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        actionhandler.cpp \
        connectionprovider.cpp \
        jsonfactory.cpp \
        loginactionhandler.cpp \
        mailslotconnection.cpp \
        main.cpp \
        messageactionhandler.cpp \
        messengerconfiguration.cpp \
        pipeconnection.cpp \
        quickviewwrapper.cpp \
        registeractionhandler.cpp \
        servereventservice.cpp \
        signalsconnector.cpp \
        socketconnection.cpp \
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
    qtquickcontrols2.conf

HEADERS += \
    actionhandler.h \
    connection.h \
    connectionprovider.h \
    jsonconstants.h \
    jsonfactory.h \
    loginactionhandler.h \
    mailslotconnection.h \
    messageactionhandler.h \
    messengerconfiguration.h \
    pipeconnection.h \
    quickviewwrapper.h \
    registeractionhandler.h \
    servereventservice.h \
    signalsconnector.h \
    socketconnection.h \
    uieventprocessor.h
