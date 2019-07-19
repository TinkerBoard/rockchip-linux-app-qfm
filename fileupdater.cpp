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
#include "fileupdater.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QMimeDatabase>
#include <QStandardPaths>



FileUpdater::FileUpdater() : QThread()
{
    m_videoSuffixList<<"*.mp4"<<"*.m4v"<<"*.avi"<<"*.wmv"<<"*.mkv"<<"*.asf"<<"*.mov"<<"*.ts"<<"*.mpg"<<"*.mpeg"<<"*.vob"<<"*.m2ts"<<"*.trp"<<"*.flv"<<"*.webm"<<"*.3gp"<<"*.flv";
    m_musicSuffixList<<"*.mp3"<<"*.wave"<<"*.wma"<<"*.ogg"<<"*.midi"<<"*.mod"<<"*.mp1"<<"*.mp2"<<"*.wav"<<"*.flac"<<"*.aac"<<"*.m4a"<<"*.aac";
    m_picSuffixList<<"*.jpg"<<"*.png"<<"*.bmp"<<"*.jpeg"<<"*.svg"<<"*.titf"<<"*.gif";
    m_Filter = FileAll;
    qRegisterMetaType<QFileInfoList>("QFileInfoList");
}

void FileUpdater::waitForThreadFinished()
{
    requestInterruption();
    quit();
    wait();
}

QStringList FileUpdater::getFiles(const QString &path)
{
    QDir *dir = new QDir(path);
    QFileInfoList files;
    QStringList filelist;
    switch (m_Filter) {
    case FileAll:
        files = dir->entryInfoList(QDir::AllDirs|QDir::Files|QDir::NoDotAndDotDot);
        break;
    case FileVideo:
        files = dir->entryInfoList(m_videoSuffixList, QDir::AllDirs|QDir::Files|QDir::NoDotAndDotDot);
        break;
    case FileMusic:
        files = dir->entryInfoList(m_musicSuffixList, QDir::AllDirs|QDir::Files|QDir::NoDotAndDotDot);
        break;
    case FilePic:
        files = dir->entryInfoList(m_picSuffixList, QDir::AllDirs|QDir::Files|QDir::NoDotAndDotDot);
        break;
    }


    for(int i=0;i<files.count();i++){
        filelist << files[i].fileName();
        QString type = getMimeType(files[i].fileName());
        qDebug() << files[i].fileName() << "mime type: " << type;
    }

    return filelist;
}

QString FileUpdater::getMimeType(const QString &path)
{
    QMimeDatabase db;
    QMimeType type = db.mimeTypeForFile(path);

    return type.name();
}

void FileUpdater::run()
{
//    QFileInfoList fileList = getFiles(SEARCH_PATH_HOME);
//    if (!isInterruptionRequested())
//        emit m_mainWindow->searchResultAvailable(fileList);


}
