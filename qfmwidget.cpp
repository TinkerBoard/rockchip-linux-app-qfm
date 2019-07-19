/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
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
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
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

#include "qfmwidget.h"
#include <QColor>
#include <QDir>
#include <QDirIterator>
#include <QStandardPaths>
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>


#define FILEMANAGER "File Manager"
QfmWidget::QfmWidget(QWidget *parent) : QWidget(parent)
{
    initLayout();
    connect(m_btnreturn, SIGNAL(clicked(bool)), this, SLOT(on_returnClicked()));
    connect(m_listWid, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(on_itemClicked(QListWidgetItem *)));
    connect(m_listWid, SIGNAL(itemEntered(QListWidgetItem *)), this, SLOT(on_itemEntered(QListWidgetItem *)));
}

void QfmWidget::initLayout()
{
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *hlayout = new QHBoxLayout;
    QColor c(Qt::black);

    m_curDir= "top";
    m_topDirList<<"Root"<<"Home"<<"Oem"<<"User data"<<"sdcard";
    m_topPathList<<"/"<<QStandardPaths::standardLocations(QStandardPaths::HomeLocation)<<"/oem"<<"/userdata"<<"/sdcard";

    m_btnreturn = new QPushButton(this);
    m_btnreturn->setStyleSheet(tr("border-image: url(:/image/return.png);"));
    QPixmap pixmap(":/image/return.png");
    m_btnreturn->setFixedSize(pixmap.width(), pixmap.height());

    m_titleLabel = new QLabel(tr(FILEMANAGER), this);
    QFont font = m_titleLabel->font();
    font.setBold(true);
    m_titleLabel->setFont(font);
    m_titleLabel->setAlignment(Qt::AlignCenter);

    hlayout->addWidget(m_btnreturn, 1);
    hlayout->addWidget(m_titleLabel, 1);
    hlayout->addStretch(1);
    hlayout->setMargin(0);
    hlayout->setSpacing(0);

    m_listWid = new QListWidget(this);
    m_listWid->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_listWid->setStyleSheet("background-color:rgb(204,228,247)");
    setStyleSheet("background-color:rgb(204,228,247)");
    getlist(m_listWid, &m_topDirList);
    m_listWid->setObjectName(tr("filelist"));
    mainLayout->addLayout(hlayout);
    mainLayout->addWidget(m_listWid);
    setLayout(mainLayout);
}

void QfmWidget::getlist(QListWidget *listWid, QStringList *list)
{
    listWid->clear();

    for(int i = 0; i < list->size(); ++i)
    {
        QListWidgetItem *item = new QListWidgetItem();
        item->setText(list->at(i));
        item->setTextColor(QColor(Qt::black));
        listWid->addItem(item);
    }

    if(m_curDir.compare("top")){
        m_titleLabel->setText(m_curDir);
     }else {
        m_titleLabel->setText(tr(FILEMANAGER));
    }
}

void QfmWidget::getItems(QListWidgetItem *item)
{
    QString path;
    QStringList files;

    if(m_curDir.compare("top")){
        path = item->text();
        if(m_curDir.compare("/")){
            files = m_fileUpdater.getFiles(m_curDir + '/' + path);
        }else{
            files = m_fileUpdater.getFiles('/' + path);
        }

    }else {
        path = m_topPathList.at(m_listWid->row(item));
        files = m_fileUpdater.getFiles(path);
    }

    if(files.empty()){
        ;
    }else{
        if(m_curDir.compare("top")){
            if(m_curDir.compare("/")){
                m_curDir = m_curDir + '/' + path;
            }else {
                m_curDir = '/' + path;
            }
        }else {
            m_curDir = path;
        }
        getlist(m_listWid, &files);
    }
}

bool QfmWidget::isTop(QString path)
{

    for(int i = 0; i < m_topPathList.count(); i++){
        if(!m_topPathList.at(i).compare(path)){
            return true;
        }
    }
    return false;
}

void QfmWidget::on_returnClicked()
{
    if(m_curDir.compare("top")){
        if(isTop(m_curDir)){
            m_curDir = "top";
            getlist(m_listWid, &m_topDirList);
        }else {
            QStringList files;
            int index = m_curDir.lastIndexOf('/');

            if(index == 0){
                m_curDir = "/";
            }else {
                m_curDir = m_curDir.mid(0, index);
            }
            files = m_fileUpdater.getFiles(m_curDir);
            getlist(m_listWid, &files);
        }
    }else {
        qApp->exit(0);
    }

}

void QfmWidget::on_itemEntered(QListWidgetItem *item)
{
//    getItems(item);
}

void QfmWidget::on_itemClicked(QListWidgetItem *item)
{
    if(m_curDir.compare("top")){
        QString path = m_curDir + "/" + item->text();
        QFileInfo file = QFileInfo(path);
        if(! file.isDir()){
            m_mimeUtils.openInApp(path, "");
            return;
        }
    }
    getItems(item);
}


