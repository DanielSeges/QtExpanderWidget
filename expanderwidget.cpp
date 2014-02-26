/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

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
}

QSize ExpanderWidget::sizeHint() const
{
    return QSize(200, 150);
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
