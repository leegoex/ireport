# $Id: CMakeLists.txt 4 2012-07-27 12:29:39Z twu $
#
# Copyright (C) 2011 China Science & Intelligence Information Technology Co.,Ltd.
# All rights reserved.
#
# Contact: Development Department <devel@cnsiit.com>
# Author: Joseph Wu <twu@cnsiit.com>
#

# --------------------------------------------------------------------
# lupdate
# --------------------------------------------------------------------
IF( IREPORT_ENABLE_CREATE_TRANSLATIONS )
    SET( TS_FILES )
    SET( TS_QM_FILES )

    SET( TS_CREATE_OPTIONS )
    IF( IREPORT_NO_OBSOLETE_TRANSLATIONS )
        SET( TS_CREATE_OPTIONS ${TS_CREATE_OPTIONS} -no-obsolete )
    ENDIF( IREPORT_NO_OBSOLETE_TRANSLATIONS )

    FOREACH( TS_LANGUAGE ${IREPORT_TRANSLATIONS_LANGUAGES} )
        LIST( APPEND TS_FILES "${IREPORT_PRODUCT_DOMAIN}_${TS_LANGUAGE}.ts" )
    ENDFOREACH( TS_LANGUAGE ${IREPORT_TRANSLATIONS_LANGUAGES} )

    FILE( GLOB_RECURSE TS_CPP_FILES "${IREPORT_SRC_DIR}/*.cpp" )
    FILE( GLOB_RECURSE TS_H_FILES "${IREPORT_SRC_DIR}/*.h" )
    FILE( GLOB_RECURSE TS_UI_FILES "${IREPORT_SRC_DIR}/*.ui" )
    FILE( GLOB_RECURSE TS_QML_FILES "${IREPORT_SRC_DIR}/*.qml" )
    SET( TS_SOURCE_FILES ${TS_CPP_FILES} ${TS_H_FILES} ${TS_UI_FILES} ${TS_QML_FILES} )

    QT5_CREATE_TRANSLATION( TS_QM_FILES ${TS_SOURCE_FILES} ${TS_FILES} OPTIONS ${TS_CREATE_OPTIONS} )
    ADD_CUSTOM_TARGET( lupdate DEPENDS ${TS_QM_FILES} )
ENDIF( IREPORT_ENABLE_CREATE_TRANSLATIONS )

# --------------------------------------------------------------------
# lrelease
# --------------------------------------------------------------------
SET( TS_REL_FILES )
SET( TS_REL_QM_FILES )

FOREACH( TS_LANGUAGE ${IREPORT_TRANSLATIONS_LANGUAGES} )
    LIST( APPEND TS_REL_FILES "${IREPORT_PRODUCT_DOMAIN}_${TS_LANGUAGE}.ts" )
ENDFOREACH( TS_LANGUAGE ${IREPORT_TRANSLATIONS_LANGUAGES} )

IF( IREPORT_TRANSLATIONS_INCLUDE_QT )
    FOREACH( TS_LANGUAGE ${IREPORT_TRANSLATIONS_LANGUAGES_QT} )
        SET( TS_QT_QM_FILENAME "qt_${TS_LANGUAGE}" )
        SET( TS_QT_QM_FILE "${_qt5Core_install_prefix}/translations/${TS_QT_QM_FILENAME}.qm" )
        IF( EXISTS ${TS_QT_QM_FILE} )
            ADD_CUSTOM_COMMAND(
                OUTPUT "${TS_QT_QM_FILENAME}.qm"
                COMMAND ${CMAKE_COMMAND} -E copy_if_different ${TS_QT_QM_FILE} "${TS_QT_QM_FILENAME}.qm"
                VERBATIM
            )
            LIST( APPEND TS_REL_QM_FILES "${TS_QT_QM_FILENAME}.qm" )
        ELSE( EXISTS ${TS_QT_QM_FILE} )
            LIST( APPEND TS_REL_FILES "${_qt5Core_install_prefix}/translations/${TS_QT_QM_FILENAME}.ts" )
        ENDIF( EXISTS ${TS_QT_QM_FILE} )
    ENDFOREACH( TS_LANGUAGE ${IREPORT_TRANSLATIONS_LANGUAGES_QT} )
ENDIF( IREPORT_TRANSLATIONS_INCLUDE_QT )

QT5_ADD_TRANSLATION( TS_REL_QM_FILES ${TS_REL_FILES} )
ADD_CUSTOM_TARGET( lrelease DEPENDS ${TS_REL_QM_FILES} )
