#   Copyright (C) 2009 Zii Labs Pte Ltd
#   All Rights Reserved.
#
#  Platform-independent CMake input file (build rules)
#  for [ZiiWakeBreaker]
#

cmake_minimum_required(VERSION 2.6)

include($ENV{PLASZMAHOME}/cmake/CMakeAppInc.txt.in)

set(TARGET_NAME ZiiWakeBreaker)

set(TARGET_SRCS
	wakebreaker/Base.h
	wakebreaker/boat1.h
	wakebreaker/boat2.h
	wakebreaker/Camera.cpp
	wakebreaker/Camera.h
	wakebreaker/checkpoint.h
	wakebreaker/Chest.cpp
	wakebreaker/chesttex.h
	wakebreaker/Color4.h
	wakebreaker/Game.cpp
	wakebreaker/Game.h
	wakebreaker/Info.h
	wakebreaker/island1.h
	wakebreaker/island2.h
	wakebreaker/island3.h
	wakebreaker/main.cpp
	wakebreaker/Math.cpp
	wakebreaker/Math.h
	wakebreaker/ModelManager.cpp
	wakebreaker/ModelManager.h
	wakebreaker/ParticleSystem.cpp
	wakebreaker/ParticleSystem.h
	wakebreaker/RaceCourse.cpp
	wakebreaker/RaceCourse.h
	wakebreaker/Racer.cpp
	wakebreaker/Racer.h
	wakebreaker/RenderData.h
	wakebreaker/RenderDataManager.h
	wakebreaker/Renderer.cpp
	wakebreaker/Renderer.h
	wakebreaker/RenderInstance.h
	wakebreaker/Seascape.cpp
	wakebreaker/Seascape.h
	wakebreaker/Texture.cpp
	wakebreaker/Texture.h
	wakebreaker/Vector3.h
	ZiiWakeBreakerApp.cpp
	ZiiWakeBreakerApp.h
	mainwindow.cpp
	mainwindow.h
	HUDWindow.cpp
	HUDWindow.h
)

include_directories(
	./
	wakebreaker/
)

link_directories ($ENV{PLASZMAHOME}/lib)

# executable built from the source files
add_executable(${TARGET_NAME} ${TARGET_SRCS})

include($ENV{PLASZMAHOME}/cmake/CMakeAppLib.txt.in)


