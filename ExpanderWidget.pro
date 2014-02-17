QTDIR_build {
# This is only for the Qt build. Do not use externally. We mean it.
PLUGIN_TYPE = designer
PLUGIN_CLASS_NAME = ExpanderWidgetPlugin
load(qt_plugin)
} else {
# Public example:

TEMPLATE = lib
CONFIG  += plugin

CONFIG += c++11

TARGET   = $$qtLibraryTarget($$TARGET)

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target

}

QT      += widgets designer

HEADERS += expanderwidget.h \
           expanderwidgetplugin.h \
           expanderwidgetcontainerextension.h \
           expanderwidgetextensionfactory.h

SOURCES += expanderwidget.cpp \
           expanderwidgetplugin.cpp \
           expanderwidgetcontainerextension.cpp \
           expanderwidgetextensionfactory.cpp

RESOURCES += \
    res.qrc
