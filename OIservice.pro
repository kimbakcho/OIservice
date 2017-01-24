#-------------------------------------------------
#
# Project created by QtCreator 2017-01-09T15:39:06
#
#-------------------------------------------------

QT       += core gui network charts sql

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
    b_label.cpp \
    manager_login.cpp \
    add_machine_dialog.cpp \
    modify_machine_dialog.cpp \
    oi_data.cpp \
    rest_time_widget.cpp \
    oi_total_ratio_chart.cpp \
    oi_total_ratio_chartview.cpp \
    oi_total_ratio_view.cpp \
    oi_select_ratio_chart.cpp \
    b_table_view.cpp \
    b_table_widget2.cpp \
    simplecrypt/simplecrypt.cpp \
    join_popup.cpp \
    oi_select_ratio_chartview.cpp \
    oi_select_ratio_view.cpp

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
    b_label.h \
    manager_login.h \
    add_machine_dialog.h \
    modify_machine_dialog.h \
    oi_data.h \
    rest_time_widget.h \
    oi_total_ratio_chart.h \
    oi_total_ratio_chartview.h \
    oi_total_ratio_view.h \
    oi_select_ratio_chart.h \
    b_table_view.h \
    b_table_widget2.h \
    simplecrypt/simplecrypt.h \
    join_popup.h \
    oi_select_ratio_chartview.h \
    oi_select_ratio_view.h

FORMS    += mainwindow.ui \
    operatingratio/operating_ratio_action.ui \
    login_form.ui \
    machine_list_item.ui \
    manager_login.ui \
    add_machine_dialog.ui \
    modify_machine_dialog.ui \
    rest_time_widget.ui \
    oi_total_ratio_view.ui \
    join_popup.ui \
    oi_select_ratio_view.ui

RESOURCES += \
    resource.qrc
