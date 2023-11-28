QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++20

QT += network

CONFIG += link_pkgconfig
PKGCONFIG += openssl


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aes.cpp \
    create_password.cpp \
    file.cpp \
    main.cpp \
    mainwindow.cpp \
    password.cpp \
    sha256.cpp

HEADERS += \
    aes.h \
    create_password.h \
    file.h \
    mainwindow.h \
    password.h \
    sha256.h

FORMS += \
    create_password.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
