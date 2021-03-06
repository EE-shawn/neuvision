//
// Z3D - A structured light 3D scanner
// Copyright (C) 2013-2016 Nicolas Ulrich <nikolaseu@gmail.com>
//
// This file is part of Z3D.
//
// Z3D is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Z3D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Z3D.  If not, see <http://www.gnu.org/licenses/>.
//

#include "zcamerapreviewer.h"
#include "ui_zcamerapreviewer.h"

#include <opencv2/core/core.hpp>

#include <QDebug>

namespace Z3D
{

ZCameraPreviewer::ZCameraPreviewer(QWidget *parent)
    : ZWidget(parent)
    , ui(new Ui::ZCameraPreviewer)
{
    qDebug() << Q_FUNC_INFO;

    ui->setupUi(this);

    setCamera(Z3D::ZCameraInterface::Ptr(nullptr));
}

ZCameraPreviewer::ZCameraPreviewer(ZCameraInterface::Ptr camera, QWidget *parent)
    : ZCameraPreviewer(parent)
{
    setCamera(camera);
}

ZCameraPreviewer::~ZCameraPreviewer()
{
    qDebug() << Q_FUNC_INFO;

    delete ui;
}

void ZCameraPreviewer::setCamera(ZCameraInterface::Ptr camera)
{
    if (m_camera) {
        /// need to disconect previous camera
        QObject::disconnect(m_camera.data(), SIGNAL(runningChanged()),
                            this, SLOT(onCameraRunningChanged()));

        QObject::disconnect(m_camera.data(), SIGNAL(newImageReceived(Z3D::ZImageGrayscale::Ptr)),
                            ui->imageView, SLOT(updateImage(Z3D::ZImageGrayscale::Ptr)));

        QObject::disconnect(ui->settingsButton, SIGNAL(clicked()),
                            m_camera.data(), SLOT(showSettingsDialog()));
    }

    m_camera = camera;

    bool cameraIsValid = bool(m_camera);

    if (cameraIsValid) {
//        setWindowTitle(QString("%1 - Preview").arg(m_camera->uuid()));

        /// updates acquisition button
        onCameraRunningChanged();

        QObject::connect(m_camera.data(), SIGNAL(runningChanged()),
                         this, SLOT(onCameraRunningChanged()));

        QObject::connect(m_camera.data(), SIGNAL(newImageReceived(Z3D::ZImageGrayscale::Ptr)),
                         ui->imageView, SLOT(updateImage(Z3D::ZImageGrayscale::Ptr)));

        QObject::connect(ui->settingsButton, SIGNAL(clicked()),
                         m_camera.data(), SLOT(showSettingsDialog()),
                         Qt::DirectConnection); /// we don't want this to be executed from the camera thread...
    } else {
//        setWindowTitle("NO CAMERA");
        ui->imageView->updateImage(Z3D::ZImageGrayscale::Ptr(nullptr));
    }

    ui->settingsButton->setEnabled(cameraIsValid);
    ui->playButton->setEnabled(cameraIsValid);
    ui->snapshotButton->setEnabled(cameraIsValid);
}

void ZCameraPreviewer::closeEvent(QCloseEvent *)
{
    qDebug() << Q_FUNC_INFO;

    /// and delete dialog
    deleteLater();
}

void ZCameraPreviewer::onCameraRunningChanged()
{
    if (!m_camera)
        return;

    ui->playButton->setChecked(m_camera->isRunning());
}

void ZCameraPreviewer::on_playButton_clicked()
{
    if (!m_camera)
        return;

    if (m_camera->isRunning())
        m_camera->stopAcquisition();
    else
        m_camera->startAcquisition();
}

void ZCameraPreviewer::on_snapshotButton_clicked()
{
    if (!m_camera)
        return;

    if (!m_camera->isRunning())
        ui->imageView->updateImage(m_camera->getSnapshot());
}

} // namespace Z3D
