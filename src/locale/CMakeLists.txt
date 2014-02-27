# --------------------------------------------------------------------
# Configurations
# --------------------------------------------------------------------
SET( IREPORT_TRANSLATIONS_LANGUAGES en zh_CN )
SET( IREPORT_TRANSLATIONS_LANGUAGES_QT zh_CN )

IF( WIN32 OR APPLE )
    SET( IREPORT_TRANSLATIONS_INCLUDE_QT TRUE )
ENDIF( WIN32 OR APPLE )

IF( IREPORT_TRANSLATIONS_INCLUDE_QT )
    CONFIGURE_FILE( intl_qt.qrc.in intl.qrc )
ELSE( IREPORT_TRANSLATIONS_INCLUDE_QT )
    CONFIGURE_FILE( intl.qrc.in intl.qrc )
ENDIF( IREPORT_TRANSLATIONS_INCLUDE_QT )

# --------------------------------------------------------------------
# translations
# --------------------------------------------------------------------
ADD_SUBDIRECTORY( translations )

# --------------------------------------------------------------------
# Qt
# --------------------------------------------------------------------
SET( QT_DONT_USE_QTGUI TRUE )
INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
)

###################
# List of sources #
###################
# Define the C++ source files
SET(intl_Srcs
    intl.cpp
    
)
QT5_ADD_RESOURCES( intl_Qrcs ${CMAKE_CURRENT_BINARY_DIR}/intl.qrc )

ADD_LIBRARY( intl ${intl_Qrcs} ${intl_Srcs} )
ADD_DEPENDENCIES( intl lrelease )
QT5_USE_MODULES(intl Core)
SET_TARGET_PROPERTIES( intl PROPERTIES OUTPUT_NAME intl DEFINE_SYMBOL FEI_INTL_SOURCE )

IF(BUILD_SHARED_LIBS)
	INSTALL( TARGETS intl ${INSTALL_TARGETS_DEFAULT_ARGS} )
ENDIF(BUILD_SHARED_LIBS)
