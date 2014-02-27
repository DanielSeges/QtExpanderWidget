#include "expanderwidgetextensionfactory.h"
#include "expanderwidgetcontainerextension.h"
#include "expanderwidget.h"

ExpanderWidgetExtensionFactory::ExpanderWidgetExtensionFactory(QExtensionManager *parent)
    : QExtensionFactory(parent)
{}

QObject *ExpanderWidgetExtensionFactory::createExtension(QObject *object,
                                                          const QString &iid,
                                                          QObject *parent) const
{
    ExpanderWidget *widget = qobject_cast<ExpanderWidget*>(object);

    if (widget && (iid == Q_TYPEID(QDesignerContainerExtension))) {
        return new ExpanderWidgetContainerExtension(widget, parent);
    } else {
        return 0;
    }
}
