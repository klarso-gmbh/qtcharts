# Generated from qcandlestickset.pro.

#####################################################################
## qcandlestickset Test:
#####################################################################

qt_internal_add_test(qcandlestickset
    SOURCES
        ../inc/tst_definitions.h
        tst_qcandlestickset.cpp
    INCLUDE_DIRECTORIES
        ../inc
    PUBLIC_LIBRARIES
        Qt::Charts
        Qt::Gui
        Qt::OpenGL
        Qt::OpenGLWidgets
        Qt::Widgets
)
