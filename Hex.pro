TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        hex_ai_player.cpp \
        hex_board.cpp \
        hex_game.cpp \
        hex_node.cpp \
        hex_winner.cpp \
        main.cpp

HEADERS += \
    hex_ai_player.h \
    hex_board.h \
    hex_game.h \
    hex_node.h \
    hex_winner.h
