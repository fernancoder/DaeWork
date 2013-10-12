lib_LIBRARIES = libdaework.a


include_HEADERS = \
        daework-include.h \
        daework-kernel.h \
        daework-support.h 

libdaework_a_SOURCES = \
        daework-include.h \
        daework-kernel.h \
        daework-support.h \
        kernel/Action.cpp \
        kernel/Daemonizer.cpp \
        kernel/Dispatcher.cpp \
        kernel/Server.cpp \
        kernel/Thread.cpp \
        support/IniParser.cpp \
        support/LogManager.cpp \
        support/Comm.cpp \
        support/CommHttp.cpp \
        support/CommTelnet.cpp \
        support/MeterAction.cpp \
        support/Meter.cpp \
        support/Util.cpp \
	support/ModulePool.cpp \
	support/ModuleHelper.cpp 

#libdaework_a_CXXFLAGS = -pg -g
#libdaework_a_LIBS = -pg -g

libdaework_a_CXXFLAGS = -O3
#libdaework_a_LDFLAGS = -version-info 0:1:0
