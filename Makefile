# onenet Makefile

# ----------- DO NOT MODIFY BELOW THIS LINE -------------

CONF ?= r

CFLAGS = -Wall -Wno-deprecated -std=c++0x

ifeq ($(CONF), d)
    CFLAGS += -O0 -g3 -D_DEBUG
else ifeq ($(CONF), r.di)
    CFLAGS += -O3 -g3
else
    CFLAGS += -O3
endif

# --------------------------------------------------------

MK_DIR      = mk
SUB_DEFS    = $(wildcard $(MK_DIR)/*-def.mk)
SUB_BUILDS  = $(wildcard $(MK_DIR)/*-build.mk)

# --------------------------------------------------------

TARGETS     =

SRC_DIR     = src
BUILD_DIR   = build
BIN_DIR     = bin

DIR_GUARD = test -d $(@D) || mkdir -p $(@D)

include $(SUB_DEFS)

# --------------------------------------------------------

# targets
all: $(TARGETS)

include $(SUB_BUILDS)

# clean
clean:
	@rm -rf $(BUILD_DIR)

.PHONY: clean $(TARGETS)
