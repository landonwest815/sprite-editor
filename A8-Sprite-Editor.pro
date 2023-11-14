QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Tool.cpp \
    filemanager.cpp \
    frame.cpp \
    framelabel.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp

HEADERS += \
    Tool.h \
    filemanager.h \
    framelabel.h \
    mainwindow.h \
    model.h \
    frame.h \

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Assets.qrc

#macx: LIBS += -F$$PWD/../../../Qt/6.6.0/macos/lib/QtTextToSpeech.framework/ -lQTTextToSpeech

#unix|win32: LIBS += -L$$PWD/../../../../../../Qt/6.6.0/mingw_64/lib/ -lQt6TextToSpeech

#INCLUDEPATH += $$PWD/../../../../../../Qt/6.6.0/mingw_64/include
#DEPENDPATH += $$PWD/../../../../../../Qt/6.6.0/mingw_64/include
#INCLUDEPATH += $$PWD/../../../../../../Qt/6.6.0/macos/include
#DEPENDPATH += $$PWD/../../../../../../Qt/6.6.0/macos/include

macx {
    LIBS += -F$$PWD/../../../Qt/6.6.0/macos/lib/ -framework QtTextToSpeech
    INCLUDEPATH += $$PWD/../../../Qt/6.6.0/macos/include
    DEPENDPATH += $$PWD/../../../Qt/6.6.0/macos/include
}

unix|win32 {
    LIBS += -L$$PWD/../../../../../../Qt/6.6.0/mingw_64/lib/ -lQt6TextToSpeech
    INCLUDEPATH += $$PWD/../../../../../../Qt/6.6.0/mingw_64/include
    DEPENDPATH += $$PWD/../../../../../../Qt/6.6.0/mingw_64/include
}

