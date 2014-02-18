
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

#    INSTALL(
#        FILES "${QT_LIBRARY_DIR}/QtCored4.dll" "${QT_LIBRARY_DIR}/QtGuid4.dll" "${QT_LIBRARY_DIR}/QtXml4.dll" "${QT_LIBRARY_DIR}/QtMultimediad4.dll" "${QT_LIBRARY_DIR}/QtNetworkd4.dll" "${QT_LIBRARY_DIR}/QtOpenGLd4.dll" "${QT_LIBRARY_DIR}/QtSqld4.dll" "${QT_LIBRARY_DIR}/QtSvgd4.dll" "${QT_LIBRARY_DIR}/QtWebKitd4.dll" "${QTMOBILITY_LIBRARY_DIR}/QtMultimediaKitd1.dll"
#        DESTINATION "${BIN_INSTALL_DIR}"
#        CONFIGURATIONS Debug
#        COMPONENT RUNTIME
#    )
#    INSTALL(
#        FILES "${QT_LIBRARY_DIR}/QtCore4.dll" "${QT_LIBRARY_DIR}/QtGui4.dll" "${QT_LIBRARY_DIR}/QtXml4.dll" "${QT_LIBRARY_DIR}/QtMultimedia4.dll" "${QT_LIBRARY_DIR}/QtNetwork4.dll" "${QT_LIBRARY_DIR}/QtOpenGL4.dll" "${QT_LIBRARY_DIR}/QtSql4.dll" "${QT_LIBRARY_DIR}/QtSvg4.dll" "${QT_LIBRARY_DIR}/QtWebKit4.dll" "${QTMOBILITY_LIBRARY_DIR}/QtMultimediaKit1.dll"
#        DESTINATION "${BIN_INSTALL_DIR}"
#        CONFIGURATIONS Release MinSizeRel RelWithDebInfo
#        COMPONENT RUNTIME
#    )
#    INSTALL(
#        FILES "${QT_PLUGINS_DIR}/imageformats/qjpeg4.dll" "${QT_PLUGINS_DIR}/imageformats/qgif4.dll"
#        DESTINATION "${BIN_INSTALL_DIR}/imageformats"
#        CONFIGURATIONS Release MinSizeRel RelWithDebInfo
#        COMPONENT RUNTIME
#    )
#    INSTALL(
#        FILES "${QTMOBILITY_PLUGINS_DIR}/mediaservice/dsengine.dll" "${QTMOBILITY_PLUGINS_DIR}/mediaservice/qtmedia_audioengine.dll"
#        DESTINATION "${BIN_INSTALL_DIR}/mediaservice"
#        CONFIGURATIONS Release MinSizeRel RelWithDebInfo
#        COMPONENT RUNTIME
#    )
	
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
