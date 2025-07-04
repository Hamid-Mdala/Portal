include("/home/hamidmdala/Desktop/CLionProjects/Portal/build/.qt/QtDeploySupport.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/MainWindow-plugins.cmake" OPTIONAL)
set(__QT_DEPLOY_I18N_CATALOGS "qtbase")

qt6_deploy_runtime_dependencies(
    EXECUTABLE /home/hamidmdala/Desktop/CLionProjects/Portal/build/MainWindow/MainWindow
    GENERATE_QT_CONF
)
