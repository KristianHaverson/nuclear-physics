#!/bin/bash

rm -f moc_MenuWindow.cpp menu
moc MenuWindow.h -o moc_MenuWindow.cpp
QT_CFLAGS=$(pkg-config --cflags Qt5Widgets)
QT_LIBS=$(pkg-config --libs Qt5Widgets)
g++ -std=c++14 -fPIC $QT_CFLAGS main.cpp MenuWindow.cpp moc_MenuWindow.cpp -o menu $QT_LIBS

