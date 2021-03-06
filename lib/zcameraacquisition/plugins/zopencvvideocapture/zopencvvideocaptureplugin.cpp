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

#include "zopencvvideocaptureplugin.h"
#include "zopencvvideocapturecamera.h"

#include <QDebug>

namespace Z3D
{

ZOpenCVVideoCapturePlugin::ZOpenCVVideoCapturePlugin()
{

}

ZOpenCVVideoCapturePlugin::~ZOpenCVVideoCapturePlugin()
{

}

QString ZOpenCVVideoCapturePlugin::id() const
{
    return QString("ZOpenCV");
}

QString ZOpenCVVideoCapturePlugin::name() const
{
    return QString("OpenCV VideoCapture");
}

QString ZOpenCVVideoCapturePlugin::version() const
{
    return QString(Z3D_VERSION_STR);
}

QList<ZCameraInfo *> ZOpenCVVideoCapturePlugin::getConnectedCameras()
{
    QList<ZCameraInfo*> camerasList;

    int cameraDeviceID = 0;
    while (true) {
        cv::VideoCapture *capture = new cv::VideoCapture(cameraDeviceID);
        if (capture->isOpened()) {
            delete capture;
            capture = nullptr;

            QVariantMap extraData;
            extraData["DeviceID"] = cameraDeviceID;

            camerasList << new ZCameraInfo(this, QString("Camera %1").arg(cameraDeviceID), extraData);
        } else {
            delete capture;
            capture = nullptr;

            /// if capture device didn't open, assume there is no more
            break;
        }

        cameraDeviceID++;
    }

    return camerasList;
}

ZCameraInterface::Ptr ZOpenCVVideoCapturePlugin::getCamera(QVariantMap options)
{
    int cameraDeviceID = options.value("DeviceID").toInt();

    OpenCVVideoCaptureCamera *camera = nullptr;

    cv::VideoCapture *capture = new cv::VideoCapture(cameraDeviceID);
    if (capture->isOpened()) {
        delete capture;
        capture = nullptr;
        camera = new OpenCVVideoCaptureCamera(cameraDeviceID);
    } else {
        delete capture;
        capture = nullptr;
    }

    if (camera) {
        return ZCameraInterface::Ptr(camera);
    }

    qDebug() << "opencv camera not found:" << options;

    return ZCameraInterface::Ptr(nullptr);
}

} // namespace Z3D
