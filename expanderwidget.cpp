#include <QPushButton>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QSettings>

#include "expanderwidget.h"

ExpanderWidget::ExpanderWidget(QWidget *parent, bool in_designer)
    : QWidget(parent)
{
	m_in_designer = in_designer;
	m_expanded = true;

	m_collapsedIcon=QIcon(":/arrow.png");
	m_expandedIcon=QIcon(":/arrow-expanded.png");

    m_button = new QPushButton();
    m_button->setObjectName("__qt__passive_button");
    m_button->setText("Expander");
    m_button->setFlat(true);
	m_button->setCheckable(true);
	m_button->setChecked(true);
	m_button->setIcon(m_expandedIcon);
    m_button->setStyleSheet("text-align: left; font-weight: bold; border: none;");
	
    connect(m_button, SIGNAL(clicked()), this, SLOT(buttonPressed()));

    m_stackWidget = new QStackedWidget();

    m_layout = new QVBoxLayout();
    m_layout->addWidget(m_button, 0, Qt::AlignTop);
    m_layout->addWidget(m_stackWidget);
    setLayout(m_layout);
}

void ExpanderWidget::buttonPressed()
{
    if(m_expanded)
    {
        m_expanded = false;
		m_button->setIcon(m_collapsedIcon);
        m_stackWidget->hide();
	}
    else
    {
        m_expanded = true;
		m_button->setIcon(m_expandedIcon);
        m_stackWidget->show();
	}

	if(!m_in_designer && !m_settingsKey.isEmpty())
	{
		QSettings settings;
		settings.setValue(m_settingsKey,m_expanded);
	}
	
	QSize size = m_layout->sizeHint();
	int width = size.width();
	int height = size.height();

	resize(width, height);

	updateGeometry();

    emit expanderChanged(m_expanded);
}

QSize ExpanderWidget::sizeHint() const
{
	return m_layout->sizeHint();
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
    return m_stackWidget->count();
}

int ExpanderWidget::currentIndex() const
{
    return m_stackWidget->currentIndex();
}

void ExpanderWidget::insertPage(int index, QWidget *page)
{
    page->setParent(m_stackWidget);
    m_stackWidget->insertWidget(index, page);
}

void ExpanderWidget::setCurrentIndex(int index)
{
    if (index != currentIndex()) {
        m_stackWidget->setCurrentIndex(index);
        emit currentIndexChanged(index);
    }
}

QWidget* ExpanderWidget::widget(int index)
{
    return m_stackWidget->widget(index);
}

void ExpanderWidget::setExpanderTitle(QString const &newTitle)
{
    m_button->setText(newTitle);
}

QString ExpanderWidget::expanderTitle() const
{
    return m_button->text();
}

void ExpanderWidget::setExpanded(bool flag)
{
    if(flag != m_expanded)
		buttonPressed();	
}

bool ExpanderWidget::isExpanded() const
{
    return m_expanded;
}

QIcon ExpanderWidget::collapsedIcon() const
{
	return m_collapsedIcon;
}

QIcon ExpanderWidget::expandedIcon() const
{
	return m_expandedIcon;
}
	
void ExpanderWidget::setCollapsedIcon(const QIcon & icon)
{
	m_collapsedIcon=icon;
	if(!m_expanded)
	{
		m_button->setIcon(m_collapsedIcon);
	}
}

void ExpanderWidget::setExpandedIcon(const QIcon & icon)
{
	m_expandedIcon=icon;
	if(m_expanded)
	{
		m_button->setIcon(m_expandedIcon);
	}
}

QString ExpanderWidget::settingsKey() const
{
	return m_settingsKey;
}

void ExpanderWidget::setSettingsKey(QString key)
{
	m_settingsKey=key;
	
	if(!m_in_designer && !m_settingsKey.isEmpty())
	{
		QSettings settings;
		bool flag = settings.value(m_settingsKey,m_expanded).toBool();
		if(flag != m_expanded) 
			buttonPressed();
	}
}
