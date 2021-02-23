## Source directory

#
# Makefile for the GNU g++ compiler. There are three make targets.
#
# 1) java_adevs
#
# This target builds the java language bindings to the adevs simulator.
# Point this at your java installation if you want to build the Java bindings.
#JAVA_HOME = /usr/local/jdk1.8.0_60
#java_adevs: CFLAGS += -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux
#java_adevs: CFLAGS += -I${JAVA_HOME}/include -I${JAVA_HOME}/include/darwin 

JAVA_HOME = /Library/Java/Home

#
# 2) adevs
#
# This builds the vanilla adevs library against which to link your c++ 
# simulations.
#

#
# 3) adevs_qemu
# 
# This builds the vanilla library and the extensions for using qemu
# to insert a simulated computer into your model.
# 

# These are generic options for the GNU C++ compiler.

# Use OpenMP? 
#OMP = 
# Compiler flags
#CFLAGS += ${OMP} -fPIC -Wall -I../include -I./ -I./qemu
# Best bet for GNU compiler
#CXX = g++
#CC = gcc
#OPTFLAG = -O3

#
# SHOULD NOT NEED TO EDIT BELOW THIS LINE
#

adevs_inc_dir=../include

libadevs_la_include_HEADERS = $(adevs_inc_dir)/adevs.h
libadevs_la_include_HEADERS += $(adevs_inc_dir)/adevs_abstract_simulator.h
libadevs_la_include_HEADERS += $(adevs_inc_dir)/adevs_bag.h
libadevs_la_include_HEADERS += $(adevs_inc_dir)/adevs_cereal.hpp
libadevs_la_include_HEADERS += $(adevs_inc_dir)/adevs_cellspace.h
libadevs_la_include_HEADERS += $(adevs_inc_dir)/adevs_corrected_euler.h
libadevs_la_include_HEADERS += $(adevs_inc_dir)/adevs_digraph.h
libadevs_la_include_HEADERS += $(adevs_inc_dir)/adevs_event_listener.h
libadevs_la_include_HEADERS += $(adevs_inc_dir)/adevs_event_locators.h
libadevs_la_include_HEADERS += $(adevs_inc_dir)/adevs_exception.h
libadevs_la_include_HEADERS += $(adevs_inc_dir)/adevs_fmi.h
libadevs_la_include_HEADERS += $(adevs_inc_dir)/adevs_hybrid.h
libadevs_la_include_HEADERS += $(adevs_inc_dir)/adevs_models.h
libadevs_la_include_HEADERS += $(adevs_inc_dir)/adevs_msg_manager.h
libadevs_la_include_HEADERS += $(adevs_inc_dir)/adevs_poly.h
libadevs_la_include_HEADERS += $(adevs_inc_dir)/adevs_qemu.h
libadevs_la_include_HEADERS += $(adevs_inc_dir)/adevs_rand.h
libadevs_la_include_HEADERS += $(adevs_inc_dir)/adevs_rk_45.h
libadevs_la_include_HEADERS += $(adevs_inc_dir)/adevs_sched.h
libadevs_la_include_HEADERS += $(adevs_inc_dir)/adevs_serialization.hpp
libadevs_la_include_HEADERS += $(adevs_inc_dir)/adevs_set.h
libadevs_la_include_HEADERS += $(adevs_inc_dir)/adevs_simpledigraph.h
libadevs_la_include_HEADERS += $(adevs_inc_dir)/adevs_simulator.h
libadevs_la_include_HEADERS += $(adevs_inc_dir)/adevs_time.h
libadevs_la_include_HEADERS += $(adevs_inc_dir)/adevs_wrapper.h
libadevs_la_include_HEADERS += $(adevs_inc_dir)/object_pool.h

ADEVS_OBJS = rv.cpp
ADEVS_OBJS += poly.cpp

# need to enable sub-dir object
AUTOMAKE_OPTIONS = subdir-objects

JAVA_OBJS = adevs_jni/JavaAtomic.cpp
JAVA_OBJS += adevs_jni/JavaDevs.cpp
JAVA_OBJS += adevs_jni/JavaEventListenerManager.cpp
JAVA_OBJS += adevs_jni/JavaNetwork.cpp
JAVA_OBJS += adevs_jni/JavaSimulator.cpp

QEMU_OBJS = \
	qemu/computer.cpp \
	qemu/device_model.cpp \
	qemu/nic.cpp \
	qemu/serial_port.cpp \
	qemu/ucsim_serial_port.cpp \
	qemu/qqq_rpc.cpp \
	qemu/ucsim_rpc.cpp

AM_CPPFLAGS = -I$(adevs_inc_dir)
AM_CPPFLAGS += -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/darwin

# shared libraries
lib_LTLIBRARIES = libadevs.la
lib_LTLIBRARIES += libjava_adevs.la

libadevs_la_SOURCES= $(libadevs_la_include_HEADERS) $(ADEVS_OBJS)
# This builds the library with QEMU extensions
#libadevs_la_SOURCES= $(libadevs_la_include_HEADERS) $(ADEVS_OBJS)

libadevs_la_includedir=$(includedir)/adevs

libjava_adevs_la_SOURCES= $(JAVA_OBJS)

MAJOR_VERSION = 3
MINOR_VERSION = 3
SUB_VERSION = 0

VERSION = $(MAJOR_VERSION).$(MINOR_VERSION).$(SUB_VERSION)

libadevs_la_LDFLAGS= -release $(VERSION)
libjava_adevs_la_LDFLAGS= -release $(VERSION)

jar:
	javac adevs_jni/adevs/*.java
	cd adevs_jni ; jar cfv ../adevs.jar adevs/*.class

clean-generic:
	rm -f adevs_jni/adevs/*.class *.jar
