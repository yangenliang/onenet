# module define

LIBMODULE_NAME		= module
	
LIBMODULE_CC		= g++
LIBMODULE_AR		= ar
LIBMODULE_CFLAGS	= $(CFLAGS)

LIBMODULE_INC_PATH	= 

# --------------------------------------------------------

LIBMODULE_SRC_DIR	= $(LIB_DIR)/$(LIBMODULE_NAME)
LIBMODULE_BUILD_DIR	= $(BUILD_DIR)/$(LIBMODULE_NAME)

LIBMODULE_TARGET	= $(BIN_DIR)/lib$(LIBMODULE_NAME).a

# --------------------------------------------------------

LIBMODULE_SRC_DIR	:= $(LIBMODULE_SRC_DIR:%/=%)
LIBMODULE_BUILD_DIR	:= $(LIBMODULE_BUILD_DIR:%/=%)

LIBMODULE_SRC_CPP	:= $(shell find $(LIBMODULE_SRC_DIR) -name '*.cpp')
LIBMODULE_SRC_C		:= $(shell find $(LIBMODULE_SRC_DIR) -name '*.c')
	
LIBMODULE_OBJ_CPP	:= $(LIBMODULE_SRC_CPP:$(LIBMODULE_SRC_DIR)/%.cpp=$(LIBMODULE_BUILD_DIR)/%.o)
LIBMODULE_OBJ_C		:= $(LIBMODULE_SRC_C:$(LIBMODULE_SRC_DIR)/%.c=$(LIBMODULE_BUILD_DIR)/%.o)

LIBMODULE_DEP		:= $(LIBMODULE_SRC_CPP:$(LIBMODULE_SRC_DIR)/%.cpp=$(LIBMODULE_BUILD_DIR)/%.d)
LIBMODULE_DEP		+= $(LIBMODULE_SRC_C:$(LIBMODULE_SRC_DIR)/%.c=$(LIBMODULE_BUILD_DIR)/%.d)

TARGETS				+= $(LIBMODULE_TARGET)
