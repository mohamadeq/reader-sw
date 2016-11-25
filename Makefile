##############################################################################
# Build global options
# NOTE: Can be overridden externally.
#

# Compiler options here.
ifeq ($(USE_OPT),)
  USE_OPT = -O0 -ggdb -fomit-frame-pointer -falign-functions=16
endif

# C specific options here (added to USE_OPT).
ifeq ($(USE_COPT),)
  USE_COPT =
endif

# C++ specific options here (added to USE_OPT).
ifeq ($(USE_CPPOPT),)
  USE_CPPOPT = -fno-rtti
endif

# Enable this if you want the linker to remove unused code and data
ifeq ($(USE_LINK_GC),)
  USE_LINK_GC = yes
endif

# Linker extra options here.
ifeq ($(USE_LDOPT),)
  USE_LDOPT =
endif

# Enable this if you want link time optimizations (LTO)
ifeq ($(USE_LTO),)
  # This is turned off as a workaround of a gcc 5.3.0 bug (https://gcc.gnu.org/bugzilla/show_bug.cgi?id=65380)
  # The bug is still present in gcc 6.1.1
  USE_LTO = no
endif

# If enabled, this option allows to compile the application in THUMB mode.
ifeq ($(USE_THUMB),)
  USE_THUMB = yes
endif

# Enable this if you want to see the full log while compiling.
ifeq ($(USE_VERBOSE_COMPILE),)
  USE_VERBOSE_COMPILE = no
endif

# If enabled, this option makes the build process faster by not compiling
# modules not used in the current configuration.
ifeq ($(USE_SMART_BUILD),)
  USE_SMART_BUILD = yes
endif

#
# Build global options
##############################################################################

##############################################################################
# Architecture or project specific options
#

# Stack size to be allocated to the Cortex-M process stack. This stack is
# the stack used by the main() thread.
ifeq ($(USE_PROCESS_STACKSIZE),)
  USE_PROCESS_STACKSIZE = 0x200
endif

# Stack size to the allocated to the Cortex-M main/exceptions stack. This
# stack is used for processing interrupts and exceptions.
ifeq ($(USE_EXCEPTIONS_STACKSIZE),)
  USE_EXCEPTIONS_STACKSIZE = 0x400
endif

#
# Architecture or project specific options
##############################################################################

##############################################################################
# Project, sources and paths
#

# Define project name here
PROJECT = deadlock-reader
BOARD   = reader-revA

ifeq ($(BOARD),reader-revA)
    BOARD_FOLDER = hal/boards/reader-revA
    # TODO
    # reader-revA board actually shoud have STM32F052 MCU, this is for development and
    # not final!
    LDSCRIPT= $(STARTUPLD)/STM32F072xB.ld
    FW_FLASH_ADDRESS= 0x08000000
endif

ifeq ($(BOARD),reader-plus-revA)
    BOARD_FOLDER =
    $(error Reader Plus revA board is not yes supported!)
    LDSCRIPT= $(STARTUPLD)/STM32F072xB.ld
    FW_FLASH_ADDRESS= 0x08000000
endif

ifndef BOARD_FOLDER
    $(error Incorrect board specified, fix the BOARD value!)
endif


# Imported source files and paths
# Warning: order is important!
CHIBIOS = deps/ChibiOS
UNITY = deps/Unity/src/
FFF   = deps/fff/
CUSTOM_HAL = hal/
TEST_PATH = test/
TEST_BUILD = build/test/out/
TEST_RUNNERS = build/test/runners/
TEST_OBJS = build/test/objs/
TEST_RESULTS = build/test/results/
TEST_BUILD_PATHS = $(TEST_BUILD) $(TEST_OBJS) $(TEST_RESULTS) $(TEST_RUNNERS)
# So that we can test both src/ and hal/
TEST_ROOOT = ./
SOURCE = src/
# Startup files.
include $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC/mk/startup_stm32f0xx.mk
# HAL-OSAL files (optional).
include $(CHIBIOS)/os/hal/hal.mk
include $(CUSTOM_HAL)/hal.mk
include $(CHIBIOS)/os/hal/ports/STM32/STM32F0xx/platform.mk
include $(BOARD_FOLDER)/board.mk
include $(CHIBIOS)/os/hal/osal/rt/osal.mk
# RTOS files (optional).
include $(CHIBIOS)/os/rt/rt.mk
include $(CHIBIOS)/os/rt/ports/ARMCMx/compilers/GCC/mk/port_v6m.mk
# Other files (optional).
include $(CHIBIOS)/test/rt/test.mk

# C sources that can be compiled in ARM or THUMB mode depending on the global
# setting.
CSRC = $(STARTUPSRC) \
       $(KERNSRC) \
       $(PORTSRC) \
       $(OSALSRC) \
       $(HALSRC) \
       $(PLATFORMSRC) \
       $(BOARDSRC) \
       $(TESTSRC) \
       $(shell find $(SOURCE) -type f -name '*.c')

# C test sources.
TEST_CSRC = $(shell find $(TEST_PATH) -type f -name '*-test.c')

# C++ sources that can be compiled in ARM or THUMB mode depending on the global
# setting.
CPPSRC =

# C sources to be compiled in ARM mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
ACSRC =

# C++ sources to be compiled in ARM mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
ACPPSRC =

# C sources to be compiled in THUMB mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
TCSRC =

# C sources to be compiled in THUMB mode regardless of the global setting.
# NOTE: Mixing ARM and THUMB mode enables the -mthumb-interwork compiler
#       option that results in lower performance and larger code size.
TCPPSRC =

# List ASM source files here
ASMSRC = $(STARTUPASM) $(PORTASM) $(OSALASM)

INCDIR = $(STARTUPINC) $(KERNINC) $(PORTINC) $(OSALINC) \
         $(HALINC) $(PLATFORMINC) $(BOARDINC) $(TESTINC) \
         $(CHIBIOS)/os/various \

#
# Project, sources and paths
##############################################################################

##############################################################################
# Compiler settings
#

MCU  = cortex-m0

#TRGT = arm-elf-
TRGT = arm-none-eabi-
CC   = $(TRGT)gcc
CPPC = $(TRGT)g++
# Enable loading with g++ only if you need C++ runtime support.
# NOTE: You can use C++ even without C++ support if you are careful. C++
#       runtime support makes code size explode.
LD   = $(TRGT)gcc
#LD   = $(TRGT)g++
CP   = $(TRGT)objcopy
AS   = $(TRGT)gcc -x assembler-with-cpp
AR   = $(TRGT)ar
OD   = $(TRGT)objdump
SZ   = $(TRGT)size
HEX  = $(CP) -O ihex
BIN  = $(CP) -O binary

TEST_TRGT   =
TEST_CC     = $(TEST_TRGT)gcc
TEST_LD     = $(TEST_TRGT)gcc
TEST_INCDIR = $(INCDIR) src/ $(FFF)
TEST_INCPARAMS = $(foreach d, $(TEST_INCDIR), -I$d)
TEST_CFLAGS = -I. -I$(UNITY) $(TEST_INCPARAMS) -DTEST

# ARM-specific options here
AOPT =

# THUMB-specific options here
TOPT = -mthumb -DTHUMB

# Define C warning options here
CWARN = -Wall -Wextra -Wundef -Wstrict-prototypes

# Define C++ warning options here
CPPWARN = -Wall -Wextra -Wundef

#
# Compiler settings
##############################################################################

##############################################################################
# Start of user section
#

# List all user C define here, like -D_DEBUG=1
UDEFS =

# Define ASM defines here
UADEFS =

# List all user directories here
UINCDIR =

# List the user directory to look for the libraries here
ULIBDIR =

# List all user libraries here
ULIBS =

#
# End of user defines
##############################################################################

RULESPATH = $(CHIBIOS)/os/common/ports/ARMCMx/compilers/GCC
include $(RULESPATH)/rules.mk

##############################################################################
# Start of helper flash and debug commands
#

flash: build/deadlock-reader.bin
	st-flash erase
	st-flash write build/deadlock-reader.bin $(FW_FLASH_ADDRESS)

debug: build/deadlock-reader.elf
	if [ -z "`pgrep st-util`"]; then st-util 2> /dev/null & fi
	arm-none-eabi-gdb build/deadlock-reader.elf -ex "target extended :4242"
	pkill st-util

#
#
##############################################################################

##############################################################################
# Start of Unit Testing with Unity rules
#

$(TEST_BUILD):
	@mkdir -p $(TEST_BUILD)

$(TEST_OBJS):
	@mkdir -p $(TEST_OBJS)

$(TEST_RESULTS):
	@mkdir -p $(TEST_RESULTS)

$(TEST_RUNNERS):
	@mkdir -p $(TEST_RUNNERS)

$(TEST_RUNNERS)%-test-runner.c:: $(TEST_PATH)%-test.c
	@echo 'Generating runner for $@'
	@mkdir -p `dirname $@`
	@ruby $(UNITY)../auto/generate_test_runner.rb $< $@

$(TEST_OBJS)unity.o:: $(UNITY)unity.c $(UNITY)unity.h
	@echo 'Compiling Unity'
	@$(TEST_CC) $(TEST_CFLAGS) -c $< -o $@

$(TEST_OBJS)%-test.o:: $(TEST_PATH)%-test.c
	@echo 'Compiling test $<'
	@mkdir -p `dirname $@`
	@$(TEST_CC) $(TEST_CFLAGS) -c $< -o $@

$(TEST_OBJS)%-test-runner.o: $(TEST_RUNNERS)%-test-runner.c
	@echo 'Compiling test runner $<'
	@mkdir -p `dirname $@`
	@$(TEST_CC) $(TEST_CFLAGS) -c $< -o $@

$(TEST_OBJS)%.o:: $(TEST_ROOT)%.c
	@echo 'Compiling $<'
	@mkdir -p `dirname $@`
	@$(TEST_CC) $(TEST_CFLAGS) -c $< -o $@

$(TEST_BUILD)%-test.out: $(TEST_OBJS)%-test.o $(TEST_OBJS)%.o $(TEST_OBJS)unity.o $(TEST_OBJS)%-test-runner.o
	@echo 'Linking test $@'
	@mkdir -p `dirname $@`
	@$(TEST_LD) -o $@ $^

$(TEST_RESULTS)%.result: $(TEST_BUILD)%-test.out
	@echo
	@echo '----- Running test $<:'
	@mkdir -p `dirname $@`
	@-./$< > $@ 2>&1
	@cat $@

RESULTS = $(patsubst $(TEST_PATH)%-test.c,$(TEST_RESULTS)%.result,$(TEST_CSRC))
TEST_EXECS = $(patsubst $(TEST_RESULTS)%.result,$(TEST_BUILD)%-test.out,$(RESULTS))

.PHONY: test run-tests clean-tests

run-tests: $(TEST_BUILD_PATHS) $(TEST_EXECS) $(RESULTS)
	@echo
	@echo "----- SUMMARY -----"
	@echo "PASS:   `for i in $(RESULTS); do grep -s PASS $$i; done | wc -l`"
	@echo "IGNORE: `for i in $(RESULTS); do grep -s IGNORE $$i; done | wc -l`"
	@echo "FAIL:   `for i in $(RESULTS); do grep -s FAIL $$i; done | wc -l`"
	@echo
	@echo "DONE"
	@if [ "`for i in $(RESULTS); do grep -s FAIL $$i; done | wc -l`" != 0 ]; then \
	exit 1; \
	fi

clean-tests:
	@rm -rf $(TEST_BUILD) $(TEST_OBJS) $(TEST_RESULTS) $(TEST_RUNNERS)

test: run-tests clean-tests

#
#
##############################################################################
