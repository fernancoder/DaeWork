noinst_PROGRAMS = test

test_SOURCES = \
    test.cpp \
    TestAction.cpp \
    TestAction.h \
    TestDispatcher.cpp \
    TestDispatcher.h \
    TestServer.cpp \
    TestServer.h \
    TestThread.cpp \
    TestThread.h

test_CXXFLAGS = -I$(top_srcdir)/src

test_LDADD = ../src/libdaework.a \
    -lpthread

AM_LDFLAGS = -lpthread

