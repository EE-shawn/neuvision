/* * Z3D - A structured light 3D scanner
 * Copyright (C) 2013-2016 Nicolas Ulrich <nikolaseu@gmail.com>
 *
 * This file is part of Z3D.
 *
 * Z3D is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Z3D is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Z3D.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <QObject>

#include "zstructuredlight_global.h"
#include "zcameraimage.h"
#include "zcamerainterface.h"

namespace Z3D {

class Z3D_STRUCTUREDLIGHT_SHARED_EXPORT ZCameraAcquisitionManager : public QObject
{
    Q_OBJECT

public:
    explicit ZCameraAcquisitionManager(std::vector<Z3D::ZCameraInterface::Ptr> cameras, QObject *parent = nullptr);

signals:
    void acquisitionReady(QString acquisitionId);
    void imagesAcquired(std::vector<Z3D::ZImageGrayscale::Ptr> &images, QString id);
    void acquisitionFinished(std::vector< std::vector<Z3D::ZImageGrayscale::Ptr> > &acquiredImages, QString acquisitionId);

public slots:
    void prepareAcquisition(QString acquisitionId);
    void acquireSingle(QString id);
    void finishAcquisition();

private:
    std::vector<Z3D::ZCameraInterface::Ptr> m_cameras;

    // 1st index: image number / order
    // 2nd index: camera index
    std::vector< std::vector<Z3D::ZImageGrayscale::Ptr> > m_images;

    QString m_acquisitionId;

    bool m_debugMode;
};

} // namespace Z3D
