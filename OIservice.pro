#-------------------------------------------------
#
# Project created by QtCreator 2017-01-09T15:39:06
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OIservice
TEMPLATE = app

TRANSLATIONS += lang_oi_ko.ts

RC_FILE = myapp.rc


SOURCES += main.cpp\
        mainwindow.cpp \
    oistystemsoap/oisystemC.cpp \
    oistystemsoap/oisystemOIWebServiceSoapProxy.cpp \
    oistystemsoap/stdsoap2.cpp \
    operatingratio/operating_ratio_action.cpp \
    login_form.cpp \
    machine_list_item.cpp \
    machine_statue_data.cpp \
    th_monitering.cpp \
    b_label.cpp

HEADERS  += mainwindow.h \
    oistystemsoap/oisystem.nsmap \
    oistystemsoap/oisystemH.h \
    oistystemsoap/oisystemOIWebServiceSoapProxy.h \
    oistystemsoap/oisystemStub.h \
    oistystemsoap/stdsoap2.h \
    operatingratio/operating_ratio_action.h \
    login_form.h \
    machine_list_item.h \
    machine_statue_data.h \
    th_monitering.h \
    b_label.h

FORMS    += mainwindow.ui \
    operatingratio/operating_ratio_action.ui \
    login_form.ui \
    machine_list_item.ui

RESOURCES += \
    resource.qrc
