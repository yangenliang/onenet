# game define

GAME_NAME		= game
	
GAME_CC			= g++
GAME_CFLAGS		= $(CFLAGS)

GAME_INC_PATH	= 
GAME_LIB_PATH	= 
GAME_LIBS		= 

# --------------------------------------------------------

GAME_SRC_DIR	= $(SRC_DIR)
GAME_BUILD_DIR	= $(BUILD_DIR)/$(GAME_NAME)

GAME_TARGET		= $(BIN_DIR)/$(GAME_NAME)

# --------------------------------------------------------

GAME_SRC_DIR	:= $(GAME_SRC_DIR:%/=%)
GAME_BUILD_DIR	:= $(GAME_BUILD_DIR:%/=%)

GAME_SRC_CPP	:= $(shell find $(GAME_SRC_DIR) -name '*.cpp')
GAME_SRC_C		:= $(shell find $(GAME_SRC_DIR) -name '*.c')
	
GAME_OBJ_CPP	:= $(GAME_SRC_CPP:$(GAME_SRC_DIR)/%.cpp=$(GAME_BUILD_DIR)/%.o)
GAME_OBJ_C		:= $(GAME_SRC_C:$(GAME_SRC_DIR)/%.c=$(GAME_BUILD_DIR)/%.o)

GAME_DEP		:= $(GAME_SRC_CPP:$(GAME_SRC_DIR)/%.cpp=$(GAME_BUILD_DIR)/%.d)
GAME_DEP		+= $(GAME_SRC_C:$(GAME_SRC_DIR)/%.c=$(GAME_BUILD_DIR)/%.d)

TARGETS			+= $(GAME_TARGET)
