#ifndef EXPANDERWIDGET_H
#define EXPANDERWIDGET_H

#include <QWidget>
#include <QIcon>

class QPushButton;
class QStackedWidget;
class QVBoxLayout;

#ifdef _WIN32
#ifdef QTEXPANDERWIDGET_EXPORT
#define QTEXPANDERWIDGET_DLLIMPEXP __declspec(dllexport)
#else
#define QTEXPANDERWIDGET_DLLIMPEXP __declspec(dllexport)
#endif
#else
#define QTEXPANDERWIDGET_DLLIMPEXP __attribute__ ((visibility ("default")))
#endif

class QTEXPANDERWIDGET_DLLIMPEXP ExpanderWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QString expanderTitle READ expanderTitle WRITE setExpanderTitle STORED true)
    Q_PROPERTY(bool isExpanded READ isExpanded WRITE setExpanded STORED true)
    Q_PROPERTY(QIcon collapsedIcon READ collapsedIcon WRITE setCollapsedIcon STORED true)
    Q_PROPERTY(QIcon expandedIcon READ expandedIcon WRITE setExpandedIcon STORED true)
	Q_PROPERTY(QString settingsKey READ settingsKey WRITE setSettingsKey STORED true)
	
public:
    explicit ExpanderWidget(QWidget *parent = 0, bool in_designer=false);
    virtual ~ExpanderWidget(){};

    QSize sizeHint() const;

    int count() const;
    int currentIndex() const;
    QWidget *widget(int index);

    QString expanderTitle() const;
    bool isExpanded() const;

	QIcon collapsedIcon() const;
	QIcon expandedIcon() const;
	
	QString settingsKey() const;
	
public slots:

    void buttonPressed();
    void setExpanderTitle(const QString &title);
    void setExpanded(bool flag);
	
	void setCollapsedIcon(const QIcon & icon);
	void setExpandedIcon(const QIcon & icon);
	
	void setSettingsKey(QString key);
	
    void addPage(QWidget *page);
    void insertPage(int index, QWidget *page);
    void removePage(int index);
    void setCurrentIndex(int index);

signals:
    void currentIndexChanged(int index);
    void expanderChanged(bool flag);

private:
    bool m_expanded;
	bool m_in_designer;
	
    QPushButton *m_button;
    QStackedWidget *m_stackWidget;
    QVBoxLayout *m_layout;
	
	QIcon m_collapsedIcon;
	QIcon m_expandedIcon;
	
	QString m_settingsKey;
};

#endif
