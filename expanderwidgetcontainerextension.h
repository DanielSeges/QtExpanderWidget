#ifndef EXPANDERWIDGETCONTAINEREXTENSION_H
#define EXPANDERWIDGETCONTAINEREXTENSION_H

#include <QtDesigner/QDesignerContainerExtension>

class QExtensionManager;

class ExpanderWidget;

class ExpanderWidgetContainerExtension: public QObject,
                                         public QDesignerContainerExtension
{
    Q_OBJECT
    Q_INTERFACES(QDesignerContainerExtension)

public:
    ExpanderWidgetContainerExtension(ExpanderWidget *widget, QObject *parent);

    void addWidget(QWidget *widget);
    int count() const;
    int currentIndex() const;
    void insertWidget(int index, QWidget *widget);
    void remove(int index);
    void setCurrentIndex(int index);
    QWidget *widget(int index) const;

private:
    ExpanderWidget *myWidget;
};

#endif
