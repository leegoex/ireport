
IF( NOT WIN32 )
    #MESSAGE( WARNING "Only support packaging on WIN32" )
    RETURN()
ENDIF( NOT WIN32 )

# --------------------------------------------------------------------
# Install
# --------------------------------------------------------------------
FIND_PATH(QT_LIBRARY_DIR Qt5Core.dll)
FIND_PATH(QT_PLUGINS_DIR imageformats/qjpeg.dll)
FIND_PATH(ICU_LIBRARY_DIR icuin52.dll)
FIND_PATH(SSL_LIBRARY_DIR libeay32.dll)
IF( NOT QT_IS_STATIC )
    ### FIXME Using QT_IS_STATIC to determine static system library is INCORRECT ###
    SET( CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION . )
    INCLUDE( InstallRequiredSystemLibraries )
    ### FIXME ###

    INSTALL(
        FILES "${SSL_LIBRARY_DIR}/libeay32.dll" "${SSL_LIBRARY_DIR}/ssleay32.dll"
        DESTINATION .
        CONFIGURATIONS Release MinSizeRel RelWithDebInfo
        COMPONENT RUNTIME
    )
	INSTALL(
        FILES "${ICU_LIBRARY_DIR}/icuin52.dll" "${ICU_LIBRARY_DIR}/icuuc52.dll" "${ICU_LIBRARY_DIR}/icudt52.dll"
        DESTINATION .
        CONFIGURATIONS Release MinSizeRel RelWithDebInfo
        COMPONENT RUNTIME
    )
	INSTALL(
        FILES "${QT_LIBRARY_DIR}/Qt5Core.dll" "${QT_LIBRARY_DIR}/Qt5Gui.dll" "${QT_LIBRARY_DIR}/Qt5Widgets.dll" "${QT_LIBRARY_DIR}/Qt5Multimedia.dll" "${QT_LIBRARY_DIR}/Qt5Network.dll" "${QT_LIBRARY_DIR}/Qt5WebKit.dll" "${QT_LIBRARY_DIR}/Qt5Quick.dll" "${QT_LIBRARY_DIR}/Qt5Qml.dll" "${QT_LIBRARY_DIR}/Qt5OpenGL.dll" "${QT_LIBRARY_DIR}/Qt5Sensors.dll" "${QT_LIBRARY_DIR}/Qt5WebKitWidgets.dll" "${QT_LIBRARY_DIR}/Qt5MultimediaWidgets.dll" "${QT_LIBRARY_DIR}/Qt5PrintSupport.dll" "${QT_LIBRARY_DIR}/Qt5V8.dll" "${QT_LIBRARY_DIR}/Qt5Sql.dll"
        DESTINATION .
        CONFIGURATIONS Release MinSizeRel RelWithDebInfo
        COMPONENT RUNTIME
    )
	INSTALL(
        FILES "${QT_PLUGINS_DIR}/platforms/qwindows.dll"
        DESTINATION platforms
        CONFIGURATIONS Release MinSizeRel RelWithDebInfo
        COMPONENT RUNTIME
    )
	
ENDIF( NOT QT_IS_STATIC )

# --------------------------------------------------------------------
# Package
# --------------------------------------------------------------------
SET( IREPORT_EXE_NAME IReport )

#SET( CPACK_INSTALL_CMAKE_PROJECTS "${IReport_BINARY_DIR};IReport;RUNTIME;/" )
SET( CPACK_PACKAGE_NAME ${IREPORT_PRODUCT_NAME} )
SET( CPACK_PACKAGE_VENDOR ${IREPORT_VENDOR_NAME} )
SET( CPACK_PACKAGE_VERSION_MAJOR ${IREPORT_VERSION_MAJOR} )
SET( CPACK_PACKAGE_VERSION_MINOR ${IREPORT_VERSION_MINOR} )
SET( CPACK_PACKAGE_VERSION_PATCH ${IREPORT_VERSION_PATCH} )
SET( CPACK_PACKAGE_INSTALL_DIRECTORY ${IREPORT_PRODUCT_NAME} )
SET( CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE" )
SET( CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README" )
SET( CPACK_STRIP_FILES TRUE )
SET( CPACK_MONOLITHIC_INSTALL TRUE )

SET( CPACK_NSIS_EXECUTABLES_DIRECTORY . )
SET( CPACK_PACKAGE_EXECUTABLES "${IREPORT_EXE_NAME};${IREPORT_PRODUCT_NAME}" )
SET( CPACK_NSIS_INSTALLED_ICON_NAME "${IREPORT_EXE_NAME}.exe" )
#SET( CPACK_NSIS_COMPRESSOR "/SOLID lzma" )
SET( CPACK_NSIS_COMPRESSOR lzma )

INCLUDE( CPack )
