#ifndef EXPANDERWIDGETPLUGIN_H
#define EXPANDERWIDGETPLUGIN_H

#include <QtDesigner/QDesignerCustomWidgetInterface>

class QIcon;
class QWidget;

class ExpanderWidgetPlugin: public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QDesignerCustomWidget")
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    explicit ExpanderWidgetPlugin(QObject *parent = 0);
    virtual ~ExpanderWidgetPlugin(){};

    QString name() const;
    QString group() const;
    QString toolTip() const;
    QString whatsThis() const;
    QString includeFile() const;
    QIcon icon() const;
    bool isContainer() const;
    QWidget *createWidget(QWidget *parent);
    bool isInitialized() const;
    void initialize(QDesignerFormEditorInterface *formEditor);
    QString domXml() const;

private slots:
    void expanderChanged(bool flag);

private:
    bool initialized;
};

#endif
