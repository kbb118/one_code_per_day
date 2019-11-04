
HEADERS = ./app/widget.h \
          ./model_view/sampledata.h \
          ./model_view/mymodel.h \
          ./model_view/myview.h \
          ./model_view/testview.h
SOURCES = ./app/widget.cpp \
          ./app/main.cpp \
          ./model_view/testview.cpp \
          ./model_view/sampledata.cpp \
          ./model_view/myview.cpp \
          ./model_view/mymodel.cpp
FORMS   = ./app/widget.ui

INCLUDEPATH += ./app ./model_view

QT += widgets
