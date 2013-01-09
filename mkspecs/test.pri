include(features/qtx_testcase.prf)


INCLUDEPATH += \
    ../../../src/xrd \
    ../../../../qtxxml/include

LIBS += \
    -L../../../lib \
    -L../../../../qtxxml/lib

LIBS += -lQtxXrd -lQtxXml
