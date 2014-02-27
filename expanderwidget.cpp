#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedWidget>

#include "expanderwidget.h"

ExpanderWidget::ExpanderWidget(QWidget *parent)
    : QWidget(parent)
{
    button = new QPushButton();
    button->setObjectName("__qt__passive_button");
    button->setText("Expander");
    button->setIcon(QIcon(":/arrow-expanded.png"));
    button->setFlat(true);
    button->setStyleSheet("text-align: left; font-weight: bold; border: none;");

    connect(button, SIGNAL(clicked()), this, SLOT(buttonPressed()));

    stackWidget = new QStackedWidget();

    layout = new QVBoxLayout();
    layout->addWidget(button, 0, Qt::AlignTop);
    layout->addWidget(stackWidget);
    setLayout(layout);
}

void ExpanderWidget::buttonPressed(){

    if(expanded)
    {

        expanded = false;
        button->setIcon(QIcon(":/arrow.png"));

        QSize size = layout->sizeHint();
        int width = size.width();
        int height = size.height();

        setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

        stackWidget->hide();
        resize(width, 20);

        updateGeometry();
    }
    else
    {
        expanded = true;
        button->setIcon(QIcon(":/arrow-expanded.png"));

        setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        stackWidget->show();

        updateGeometry();
    }

    emit expanderChanged(expanded);
}

QSize ExpanderWidget::sizeHint() const
{
    return QSize(200, 20);
}

void ExpanderWidget::addPage(QWidget *page)
{
    insertPage(count(), page);
}

void ExpanderWidget::removePage(int index)
{

}

int ExpanderWidget::count() const
{
    return stackWidget->count();
}

int ExpanderWidget::currentIndex() const
{
    return stackWidget->currentIndex();
}

void ExpanderWidget::insertPage(int index, QWidget *page)
{
    page->setParent(stackWidget);
    stackWidget->insertWidget(index, page);
}

void ExpanderWidget::setCurrentIndex(int index)
{
    if (index != currentIndex()) {
        stackWidget->setCurrentIndex(index);
        emit currentIndexChanged(index);
    }
}

QWidget* ExpanderWidget::widget(int index)
{
    return stackWidget->widget(index);
}

void ExpanderWidget::setExpanderTitle(QString const &newTitle)
{
    button->setText(newTitle);
}

QString ExpanderWidget::expanderTitle() const
{
    return button->text();
}

void ExpanderWidget::setExpanded(bool flag)
{
    if(flag != expanded) buttonPressed();
    else expanded = flag;
}

bool ExpanderWidget::isExpanded() const
{
    return expanded;
}
