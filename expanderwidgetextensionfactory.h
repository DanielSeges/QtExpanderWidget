#ifndef EXPANDERWIDGETEXTENSIONFACTORY_H
#define EXPANDERWIDGETEXTENSIONFACTORY_H

#include <QtDesigner/QExtensionFactory>

class QExtensionManager;

class ExpanderWidgetExtensionFactory: public QExtensionFactory
{
    Q_OBJECT

public:
    explicit ExpanderWidgetExtensionFactory(QExtensionManager *parent = 0);
    virtual ~ExpanderWidgetExtensionFactory(){};

protected:
    QObject *createExtension(QObject *object, const QString &iid, QObject *parent) const;
};

#endif
