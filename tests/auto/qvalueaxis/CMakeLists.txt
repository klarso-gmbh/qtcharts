# Generated from qvalueaxis.pro.

#####################################################################
## qvalueaxis Test:
#####################################################################

qt_internal_add_test(qvalueaxis
    SOURCES
        ../inc/tst_definitions.h
        ../qabstractaxis/tst_qabstractaxis.cpp ../qabstractaxis/tst_qabstractaxis.h
        tst_qvalueaxis.cpp
    INCLUDE_DIRECTORIES
        ../inc
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::OpenGL
        Qt::OpenGLWidgets
        Qt::Widgets
)
