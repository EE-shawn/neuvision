################################################################################
## PCL
unix:!macx:include(pcl_lin_1.7.pri)
macx:include(pcl_osx_1.8.pri)
win32:include(pcl_win_1.8.pri)

################################################################################
## VTK
unix:!macx:include(vtk_lin_6.pri)
macx:include(vtk_osx_8.pri)
win32:include(vtk_win_8.pri)
