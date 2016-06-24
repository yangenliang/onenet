# net define

SONET_NAME		= net
	
SONET_CC		= g++
SONET_CFLAGS	= $(CFLAGS)

SONET_INC_PATH	= 
SONET_LIB_PATH	= 
SONET_LIBS		= 

# --------------------------------------------------------

SONET_SRC_DIR	= $(LIB_DIR)/$(SONET_NAME)
SONET_BUILD_DIR	= $(BUILD_DIR)/$(SONET_NAME)

SONET_TARGET	= $(BIN_DIR)/lib$(SONET_NAME).so

# --------------------------------------------------------

SONET_SRC_DIR	:= $(SONET_SRC_DIR:%/=%)
SONET_BUILD_DIR	:= $(SONET_BUILD_DIR:%/=%)

SONET_SRC_CPP	:= $(shell find $(SONET_SRC_DIR) -name '*.cpp')
SONET_SRC_C		:= $(shell find $(SONET_SRC_DIR) -name '*.c')
	
SONET_OBJ_CPP	:= $(SONET_SRC_CPP:$(SONET_SRC_DIR)/%.cpp=$(SONET_BUILD_DIR)/%.o)
SONET_OBJ_C		:= $(SONET_SRC_C:$(SONET_SRC_DIR)/%.c=$(SONET_BUILD_DIR)/%.o)

SONET_DEP		:= $(SONET_SRC_CPP:$(SONET_SRC_DIR)/%.cpp=$(SONET_BUILD_DIR)/%.d)
SONET_DEP		+= $(SONET_SRC_C:$(SONET_SRC_DIR)/%.c=$(SONET_BUILD_DIR)/%.d)

TARGETS			+= $(SONET_TARGET)
