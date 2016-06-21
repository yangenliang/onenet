# onenet Makefile

CONF 		?= d
CC			= g++
CFLAGS 		= -Wall -Wno-deprecated -std=c++11

ifeq ($(CONF), d)
    CFLAGS	+= -O0 -g3 -D_DEBUG
else ifeq ($(CONF), r.di)
    CFLAGS	+= -O3 -g3
else
    CFLAGS	+= -O3
endif

# --------------------------------------------------

SRC_DIR     = src
BUILD_DIR   = tmp
BIN_DIR     = bin

DIR_GUARD 	= test -d $(@D) || mkdir -p $(@D)

# --------------------------------------------------

# --------------------------------------------------

LIB_PATH	= 
INC_PATH	= 
LIBS		= 

SRC_DIR		:= $(SRC_DIR:%/=%)
BUILD_DIR	:= $(BUILD_DIR:%/=%)

SRC_CPP 	:= $(shell find $(SRC_DIR) -name '*.cpp')
SRC_C   	:= $(shell find $(SRC_DIR) -name '*.c')

OBJ_CPP 	:= $(SRC_CPP:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
OBJ_C   	:= $(SRC_C:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

GAME_DEP 	:= $(SRC_CPP:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.d)
GAME_DEP 	+= $(SRC_C:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.d)

TARGET		= $(BIN_DIR)/game

# --------------------------------------------------

# build target
$(TARGET): $(OBJ_CPP) $(OBJ_C)
	@echo ' '
	@echo 'Building executable => $@'
	@$(DIR_GUARD)
	@$(CC) $(LIB_PATH) -o "$(TARGET)" $(OBJ_CPP) $(OBJ_C) $(LIBS)
	@echo 'Done!'
	@echo ' '
	
# build objects
$(OBJ_CPP): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling => $<"
	@$(DIR_GUARD)
	@$(CC) $(INC_PATH) $(CFLAGS) -c -MMD -MP -MF"$(@:%.o=%.d)" -o "$@" "$<"

$(OBJ_C): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling => $<"
	@$(DIR_GUARD)
	@$(CC) $(INC_PATH) $(CFLAGS) -c -MMD -MP -MF"$(@:%.o=%.d)" -o "$@" "$<"

# --------------------------------------------------

# targets
all: $(TARGET)

# clean
clean:
	@rm -rf $(BUILD_DIR)

.PHONY: all clean $(TARGET)
	