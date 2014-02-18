
IF( NOT WIN32 )
    #MESSAGE( WARNING "Only support packaging on WIN32" )
    RETURN()
ENDIF( NOT WIN32 )

# --------------------------------------------------------------------
# Install
# --------------------------------------------------------------------
IF( NOT QT_IS_STATIC )
    ### FIXME Using QT_IS_STATIC to determine static system library is INCORRECT ###
    SET( CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION . )
    INCLUDE( InstallRequiredSystemLibraries )
    ### FIXME ###

    INSTALL(
        FILES "${QT_LIBRARY_DIR}/icuin51.dll" "${QT_LIBRARY_DIR}/icuuc51.dll" "${QT_LIBRARY_DIR}/icudt51.dll" "${QT_LIBRARY_DIR}/Qt5Core.dll" "${QT_LIBRARY_DIR}/Qt5Gui.dll" "${QT_LIBRARY_DIR}/Qt5Widgets.dll" "${QT_LIBRARY_DIR}/Qt5Multimedia.dll" "${QT_LIBRARY_DIR}/Qt5Network.dll" "${QT_LIBRARY_DIR}/Qt5WebKit.dll" "${QT_LIBRARY_DIR}/Qt5Quick.dll" "${QT_LIBRARY_DIR}/Qt5Qml.dll" "${QT_LIBRARY_DIR}/Qt5V8.dll" "${QT_LIBRARY_DIR}/Qt5Sensors.dll" "${QT_LIBRARY_DIR}/Qt5WebKitWidgets.dll" "${QT_LIBRARY_DIR}/Qt5MultimediaWidgets.dll" "${QT_LIBRARY_DIR}/Qt5PrintSupport.dll"
        DESTINATION "${BIN_INSTALL_DIR}"
        CONFIGURATIONS Release MinSizeRel RelWithDebInfo
        COMPONENT RUNTIME
    )
    INSTALL(
        FILES "${QT_PLUGINS_DIR}/imageformats/qjpeg.dll" "${QT_PLUGINS_DIR}/imageformats/qgif.dll"
        DESTINATION "${BIN_INSTALL_DIR}/imageformats"
        CONFIGURATIONS Release MinSizeRel RelWithDebInfo
        COMPONENT RUNTIME
    )
	INSTALL(
        FILES "${QT_PLUGINS_DIR}/platforms/qwindows.dll"
        DESTINATION "${BIN_INSTALL_DIR}/platforms"
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
