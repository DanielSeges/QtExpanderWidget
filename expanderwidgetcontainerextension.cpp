#include "expanderwidgetcontainerextension.h"
#include "expanderwidget.h"

ExpanderWidgetContainerExtension::ExpanderWidgetContainerExtension(ExpanderWidget *widget,
                                                                     QObject *parent)
    :QObject(parent)
{
    myWidget = widget;
}

void ExpanderWidgetContainerExtension::addWidget(QWidget *widget)
{
    myWidget->addPage(widget);
}

int ExpanderWidgetContainerExtension::count() const
{
    return myWidget->count();
}

int ExpanderWidgetContainerExtension::currentIndex() const
{
    return myWidget->currentIndex();
}

void ExpanderWidgetContainerExtension::insertWidget(int index, QWidget *widget)
{
    myWidget->insertPage(index, widget);
}

void ExpanderWidgetContainerExtension::remove(int index)
{
    myWidget->removePage(index);
}

void ExpanderWidgetContainerExtension::setCurrentIndex(int index)
{
    myWidget->setCurrentIndex(index);
}

QWidget* ExpanderWidgetContainerExtension::widget(int index) const
{
    return myWidget->widget(index);
}
