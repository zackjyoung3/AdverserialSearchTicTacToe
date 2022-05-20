cmake_minimum_required(VERSION 3.21)
project(AdverserialSearchTicTacToe)

set(CMAKE_CXX_STANDARD 14)

add_executable(AdverserialSearchTicTacToe main.cpp Game.cpp Game.h TicTacToe.cpp TicTacToe.h State.cpp State.h TicTacToeState.cpp TicTacToeState.h Action.cpp Action.h TicTacToeAction.cpp TicTacToeAction.h Search.cpp Search.h)
