/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtDesigner/QExtensionFactory>
#include <QtDesigner/QExtensionManager>
#include <QtDesigner/QDesignerFormEditorInterface>
#include <QtDesigner/QDesignerFormWindowInterface>
#include <QtDesigner/QDesignerContainerExtension>
#include <QtDesigner/QDesignerPropertySheetExtension>

#include <QIcon>
#include <QtPlugin>

#include "expanderwidget.h"
#include "expanderwidgetplugin.h"
#include "expanderwidgetextensionfactory.h"

ExpanderWidgetPlugin::ExpanderWidgetPlugin(QObject *parent)
    :QObject(parent)
{
    initialized = false;
}

QString ExpanderWidgetPlugin::name() const
{
    return QLatin1String("ExpanderWidget");
}

QString ExpanderWidgetPlugin::group() const
{
    return QLatin1String("Display Widgets [Examples]");
}

QString ExpanderWidgetPlugin::toolTip() const
{
    return QString();
}

QString ExpanderWidgetPlugin::whatsThis() const
{
    return QString();
}

QString ExpanderWidgetPlugin::includeFile() const
{
    return QLatin1String("expanderwidget.h");
}

QIcon ExpanderWidgetPlugin::icon() const
{
    return QIcon();
}

bool ExpanderWidgetPlugin::isContainer() const
{
    return true;
}

QWidget *ExpanderWidgetPlugin::createWidget(QWidget *parent)
{
    ExpanderWidget *widget = new ExpanderWidget(parent);
    connect(widget, SIGNAL(expanderChanged(bool)),this, SLOT(expanderChanged(bool)));
    return widget;
}

bool ExpanderWidgetPlugin::isInitialized() const
{
    return initialized;
}

void ExpanderWidgetPlugin::initialize(QDesignerFormEditorInterface *formEditor)
{
    if (initialized)
        return;

    QExtensionManager *manager = formEditor->extensionManager();
    QExtensionFactory *factory = new ExpanderWidgetExtensionFactory(manager);

    Q_ASSERT(manager != 0);
    manager->registerExtensions(factory, Q_TYPEID(QDesignerContainerExtension));

    initialized = true;
}

QString ExpanderWidgetPlugin::domXml() const
{
    return QLatin1String("\
<ui language=\"c++\">\
    <widget class=\"ExpanderWidget\" name=\"expanderwidget\">\
        <widget class=\"QWidget\" name=\"page\" />\
    </widget>\
    <customwidgets>\
        <customwidget>\
            <class>ExpanderWidget</class>\
            <extends>QWidget</extends>\
            <addpagemethod>addPage</addpagemethod>\
        </customwidget>\
    </customwidgets>\
</ui>");
}

void ExpanderWidgetPlugin::expanderChanged(bool flag)
{

    ExpanderWidget *widget = qobject_cast<ExpanderWidget*>(sender());
    if (widget) {

        QDesignerFormWindowInterface *form;
        form = QDesignerFormWindowInterface::findFormWindow(widget);
        if (form) {
            QDesignerFormEditorInterface *editor = form->core();
            QExtensionManager *manager = editor->extensionManager();
            QDesignerPropertySheetExtension *sheet;
            sheet = qt_extension<QDesignerPropertySheetExtension*>(manager, widget);
            const int propertyIndex = sheet->indexOf(QLatin1String("isExpanded"));

            //QVariant value = sheet->property(propertyIndex);
            //bool v = value.toBool();

            //QString res = QString::number(propertyIndex);

            //sheet->setProperty(propertyIndex, v);
            sheet->setChanged(propertyIndex, true);

//            QMessageBox msgBox;
//            msgBox.setText(res);
//            msgBox.exec();
        }
    }


}
