QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    main.cpp \
    message.cpp \
    mode_selection.cpp \
    send_read_data.cpp \
    server.cpp

HEADERS += \
    client.h \
    message.h \
    mode_selection.h \
    send_read_data.h \
    server.h \
    settings.h

FORMS += \
    client.ui \
    message.ui \
    mode_selection.ui \
    server.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
