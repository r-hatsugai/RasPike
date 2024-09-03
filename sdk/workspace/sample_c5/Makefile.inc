mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS +=\
LineTracer.o\
EdgeExchange.o\
SceneStraight.o\
SceneCorner.o\
SceneLap.o\
SceneExit.o\
SceneBlue.o\
rgbtohsv.o\
distance.o\
run.o\
Scene1.o\
Scene2.o\
Scene3.o\
Scene4.o\
Scene5.o\
Scene6.o\
Scene7.o\

APPL_LIBS += -lm

APPL_DIRS += $(mkfile_path)LineTracer
APPL_DIRS += $(mkfile_path)EdgeExchange
APPL_DIRS += $(mkfile_path)SceneStraight
APPL_DIRS += $(mkfile_path)SceneCorner
APPL_DIRS += $(mkfile_path)SceneLap
APPL_DIRS += $(mkfile_path)SceneExit
APPL_DIRS += $(mkfile_path)SceneBlue
APPL_DIRS += $(mkfile_path)rgbtohsv
APPL_DIRS += $(mkfile_path)distance
APPL_DIRS += $(mkfile_path)run
APPL_DIRS += $(mkfile_path)Scene1
APPL_DIRS += $(mkfile_path)Scene2
APPL_DIRS += $(mkfile_path)Scene3
APPL_DIRS += $(mkfile_path)Scene4
APPL_DIRS += $(mkfile_path)Scene5
APPL_DIRS += $(mkfile_path)Scene6
APPL_DIRS += $(mkfile_path)Scene7

INCLUDES += \
	-I$(mkfile_path)LineTracer\
	-I$(mkfile_path)EdgeExchange\
	-I$(mkfile_path)SceneStraight\
	-I$(mkfile_path)SceneCorner\
	-I$(mkfile_path)SceneLap\
	-I$(mkfile_path)SceneExit\
	-I$(mkfile_path)SceneBlue\
	-I$(mkfile_path)rgbtohsv\
	-I$(mkfile_path)distance\
	-I$(mkfile_path)run\
	-I$(mkfile_path)Scene1\
	-I$(mkfile_path)Scene2\
	-I$(mkfile_path)Scene3\
	-I$(mkfile_path)Scene4\
	-I$(mkfile_path)Scene5\
	-I$(mkfile_path)Scene6\
	-I$(mkfile_path)Scene7\

	