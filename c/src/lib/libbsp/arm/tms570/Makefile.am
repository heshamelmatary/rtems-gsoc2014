##
#
# @file makefile.am
#
# @brief Makefile of LibBSP for the TMS570 boards.
#

ACLOCAL_AMFLAGS = -I ../../../../aclocal

include $(top_srcdir)/../../../../automake/compile.am

include_bspdir = $(includedir)/bsp

dist_project_lib_DATA = bsp_specs

# ----------------------------
# ------  Headers
# ----------------------------

include_HEADERS = include/bsp.h

nodist_include_HEADERS = ../../shared/include/coverhd.h
nodist_include_HEADERS += include/bspopts.h

nodist_include_bsp_HEADERS = ../../shared/include/bootcard.h

include_bsp_HEADERS =
include_bsp_HEADERS += ../../shared/include/utility.h
include_bsp_HEADERS += ../../shared/include/irq-generic.h
include_bsp_HEADERS += ../../shared/include/irq-info.h
include_bsp_HEADERS += ../../shared/include/stackalloc.h
include_bsp_HEADERS += ../../shared/include/uart-output-char.h
include_bsp_HEADERS += ../../shared/tod.h
include_bsp_HEADERS += ../shared/include/start.h
include_bsp_HEADERS += include/tms570.h
include_bsp_HEADERS += include/tms570-sci.h
include_bsp_HEADERS += include/irq.h
include_bsp_HEADERS += include/tms570-rti.h
include_bsp_HEADERS += include/tms570-vim.h
include_bsp_HEADERS += include/tms570-pom.h
include_bsp_HEADERS += include/tms570-sci-driver.h
include_bsp_HEADERS += include/system-clocks.h

include_HEADERS += ../../shared/include/tm27.h

# ----------------------------
# ------  Data
# ----------------------------

noinst_LIBRARIES = libbspstart.a

libbspstart_a_SOURCES = ../shared/start/start.S

project_lib_DATA = start.$(OBJEXT)
project_lib_DATA += startup/linkcmds

EXTRA_DIST =
EXTRA_DIST += startup/linkcmds.tms570ls3137_hdk
EXTRA_DIST += startup/linkcmds.tms570ls3137_hdk_sdram
EXTRA_DIST += startup/linkcmds.tms570ls3137_hdk_intram

# ----------------------------
# ------  LibBSP
# ----------------------------

noinst_LIBRARIES += libbsp.a

libbsp_a_SOURCES =
libbsp_a_CPPFLAGS =
libbsp_a_LIBADD =

# Shared
libbsp_a_SOURCES += ../../shared/bootcard.c
libbsp_a_SOURCES += ../../shared/bspclean.c
libbsp_a_SOURCES += ../../shared/bspgetworkarea.c
libbsp_a_SOURCES += ../../shared/bsplibc.c
libbsp_a_SOURCES += ../../shared/bsppost.c
libbsp_a_SOURCES += ../../shared/bsppredriverhook.c
libbsp_a_SOURCES += ../../shared/gnatinstallhandler.c
libbsp_a_SOURCES += ../../shared/sbrk.c
libbsp_a_SOURCES += ../../shared/src/stackalloc.c
libbsp_a_SOURCES += ../../shared/cpucounterdiff.c

# Startup
libbsp_a_SOURCES += ../shared/startup/bsp-start-memcpy.S
libbsp_a_SOURCES += ../../shared/bsppretaskinghook.c
libbsp_a_SOURCES += startup/bspreset.c
libbsp_a_SOURCES += startup/bspstart.c

# POM
libbsp_a_SOURCES += pom/tms570-pom.c

# IRQ
libbsp_a_SOURCES += ../../shared/src/irq-default-handler.c
libbsp_a_SOURCES += ../../shared/src/irq-generic.c
libbsp_a_SOURCES += ../../shared/src/irq-info.c
libbsp_a_SOURCES += ../../shared/src/irq-legacy.c
libbsp_a_SOURCES += ../../shared/src/irq-server.c
libbsp_a_SOURCES += ../../shared/src/irq-shell.c
libbsp_a_SOURCES += irq/irq.c

# Console
libbsp_a_SOURCES += ../../shared/console-termios.c
libbsp_a_SOURCES += console/printk-support.c
libbsp_a_SOURCES += console/tms570-sci.c

# Clock
libbsp_a_SOURCES += ../../shared/clockdrv_shell.h
libbsp_a_SOURCES += clock/clock.c
libbsp_a_SOURCES += clock/benchmark_timer.c

# RTC

# GPIO

# Timer

# Benchmark Timer

# Misc
libbsp_a_SOURCES += misc/cpucounterread.c

# Watchdog

# Cache
libbsp_a_SOURCES += ../../../libcpu/shared/src/cache_manager.c
libbsp_a_SOURCES += ../../../libcpu/arm/shared/include/cache_.h
libbsp_a_CPPFLAGS += -I$(srcdir)/../../../libcpu/arm/shared/include

# Start hooks
libbsp_a_SOURCES += startup/bspstarthooks.c

# Network

if HAS_NETWORKING

noinst_PROGRAMS = network.rel

network_rel_CPPFLAGS = $(AM_CPPFLAGS)
network_rel_CPPFLAGS += -D__INSIDE_RTEMS_BSD_TCPIP_STACK__ -D__BSD_VISIBLE
network_rel_LDFLAGS = $(RTEMS_RELLDFLAGS)

libbsp_a_LIBADD += network.rel

endif

# ----------------------------
# ------  Special Rules
# ----------------------------

DISTCLEANFILES = include/bspopts.h

include $(srcdir)/preinstall.am
include $(top_srcdir)/../../../../automake/local.am
