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

            sheet->setChanged(propertyIndex, true);

        }
    }


}
