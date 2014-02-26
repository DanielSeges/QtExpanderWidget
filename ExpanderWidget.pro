QTDIR_build {
# This is only for the Qt build. Do not use externally. We mean it.
PLUGIN_TYPE = designer
PLUGIN_CLASS_NAME = ExpanderWidgetPlugin
load(qt_plugin)
} else {
# Public example:

TEMPLATE = lib
CONFIG  += plugin

TARGET   = $$qtLibraryTarget($$TARGET)

target.path = $$[QT_INSTALL_PLUGINS]/designer
INSTALLS += target

}

QT      += widgets designer

CONFIG += c++11

HEADERS += \
    expanderwidgetplugin.h \
    expanderwidget.h \
    expanderwidgetcontainerextension.h \
    expanderwidgetextensionfactory.h

SOURCES += \
    expanderwidget.cpp \
    expanderwidgetcontainerextension.cpp \
    expanderwidgetextensionfactory.cpp \
    expanderwidgetplugin.cpp

RESOURCES += \
    res.qrc


