###################
# List of sources #
###################
# Define the UI source files
SET(ireport_UIs
    mainframe.ui
)

# Define the C++ source files
SET(ireport_Srcs
    main.cpp
    mainframe.cpp
)


################
# Qt settings #
################
# This scripts run the user interface compiler uic.
QT5_WRAP_UI(ireport_UIC_Srcs ${ireport_UIs})


#####################
# Compiler settings #
#####################
# This needs to be added in order for #include to work inside .cpp files
INCLUDE_DIRECTORIES(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5WebKit_INCLUDE_DIRS}
    ${Qt5WebKitWidgets_INCLUDE_DIRS}
)

INCLUDE_DIRECTORIES(
	${IREPORT_SRC_DIR}/locale
)

# This line tells cmake to create the Test program.
ADD_EXECUTABLE(${PROJECT_NAME} WIN32 ${ireport_UIC_Srcs} ${ireport_Srcs})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} intl )


# Link the required libraries
QT5_USE_MODULES(${PROJECT_NAME} Widgets WebKit WebKitWidgets)

################
# Installation #
################
INSTALL(TARGETS ${PROJECT_NAME} ${INSTALL_TARGETS_DEFAULT_ARGS})
