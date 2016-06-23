# net define

NETSO_NAME		= net
	
NETSO_CC		= g++
NETSO_CFLAGS	= $(CFLAGS)

NETSO_INC_PATH	= 
NETSO_LIB_PATH	= 
NETSO_LIBS		= 

# --------------------------------------------------------

NETSO_SRC_DIR	= $(LIB_DIR)/$(NETSO_NAME)
NETSO_BUILD_DIR	= $(BUILD_DIR)/$(NETSO_NAME)

NETSO_TARGET	= $(BIN_DIR)/lib$(NETSO_NAME).so

# --------------------------------------------------------

NETSO_SRC_DIR	:= $(NETSO_SRC_DIR:%/=%)
NETSO_BUILD_DIR	:= $(NETSO_BUILD_DIR:%/=%)

NETSO_SRC_CPP	:= $(shell find $(NETSO_SRC_DIR) -name '*.cpp')
NETSO_SRC_C		:= $(shell find $(NETSO_SRC_DIR) -name '*.c')
	
NETSO_OBJ_CPP	:= $(NETSO_SRC_CPP:$(NETSO_SRC_DIR)/%.cpp=$(NETSO_BUILD_DIR)/%.o)
NETSO_OBJ_C		:= $(NETSO_SRC_C:$(NETSO_SRC_DIR)/%.c=$(NETSO_BUILD_DIR)/%.o)

NETSO_DEP		:= $(NETSO_SRC_CPP:$(NETSO_SRC_DIR)/%.cpp=$(NETSO_BUILD_DIR)/%.d)
NETSO_DEP		+= $(NETSO_SRC_C:$(NETSO_SRC_DIR)/%.c=$(NETSO_BUILD_DIR)/%.d)

TARGETS			+= $(NETSO_TARGET)
