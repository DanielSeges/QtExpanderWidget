#ifndef EXPANDERWIDGETEXTENSIONFACTORY_H
#define EXPANDERWIDGETEXTENSIONFACTORY_H

#include <QtDesigner/QExtensionFactory>

class QExtensionManager;

class ExpanderWidgetExtensionFactory: public QExtensionFactory
{
    Q_OBJECT

public:
    ExpanderWidgetExtensionFactory(QExtensionManager *parent = 0);

protected:
    QObject *createExtension(QObject *object, const QString &iid, QObject *parent) const;
};

#endif
