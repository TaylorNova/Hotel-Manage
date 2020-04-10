#-------------------------------------------------
#
# Project created by QtCreator 2018-07-17T10:55:23
#
#-------------------------------------------------

QT       += core gui
QT       += sql widgets
CONFIG   += resources_big

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Hotelmanage
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    object.cpp \
    people.cpp \
    order.cpp \
    room.cpp \
    customer.cpp \
    manager.cpp \
    hotel.cpp \
    data.cpp \
    register.cpp \
    customer_run.cpp \
    manager_run.cpp \
    hotel_run.cpp \
    addroom.cpp \
    changeroom.cpp \
    platform.cpp \
    hotelapply.cpp \
    confirmpass.cpp \
    setstarlevel.cpp \
    findroom.cpp \
    cus_record.cpp \
    seeroom.cpp \
    orderroom.cpp \
    pay.cpp \
    checkorder.cpp \
    match.cpp \
    managecheck.cpp \
    backmoncheck.cpp \
    backmonapp.cpp \
    evaluate.cpp \
    evalue.cpp

HEADERS  += mainwindow.h \
    all_headers_nedded.h \
    object.h \
    people.h \
    order.h \
    room.h \
    customer.h \
    manager.h \
    hotel.h \
    data.h \
    register.h \
    customer_run.h \
    manager_run.h \
    hotel_run.h \
    addroom.h \
    changeroom.h \
    platform.h \
    hotelapply.h \
    confirmpass.h \
    setstarlevel.h \
    findroom.h \
    cus_record.h \
    seeroom.h \
    orderroom.h \
    pay.h \
    checkorder.h \
    match.h \
    managecheck.h \
    backmoncheck.h \
    backmonapp.h \
    evaluate.h \
    evalue.h

FORMS    += mainwindow.ui \
    register.ui \
    customer_run.ui \
    manager_run.ui \
    hotel_run.ui \
    addroom.ui \
    changeroom.ui \
    platform.ui \
    hotelapply.ui \
    confirmpass.ui \
    setstarlevel.ui \
    findroom.ui \
    seeroom.ui \
    orderroom.ui \
    pay.ui \
    checkorder.ui \
    managecheck.ui \
    backmoncheck.ui \
    backmonapp.ui \
    evaluate.ui

RESOURCES += \
    resource.qrc
