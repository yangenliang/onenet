# game build

-include $(GAME_DEP)

# build target
$(GAME_TARGET): $(GAME_OBJ_CPP) $(GAME_OBJ_C) $(SONET_TARGET)
	@echo ' '
	@echo 'Building executable => $@'
	@$(DIR_GUARD)
	@$(GAME_CC) $(GAME_LIB_PATH) -o "$(GAME_TARGET)" $(GAME_OBJ_CPP) $(GAME_OBJ_C) $(GAME_LIBS)
	@echo 'Done!'
	@echo ' '
	
# build objects
$(GAME_OBJ_CPP): $(GAME_BUILD_DIR)/%.o: $(GAME_SRC_DIR)/%.cpp
	@echo "Compiling => $<"
	@$(DIR_GUARD)
	@$(GAME_CC) $(GAME_INC_PATH) $(GAME_CFLAGS) -c -MMD -MP -MF"$(@:%.o=%.d)" -o "$@" "$<"

$(GAME_OBJ_C): $(GAME_BUILD_DIR)/%.o: $(GAME_SRC_DIR)/%.c
	@echo "Compiling => $<"
	@$(DIR_GUARD)
	@$(GAME_CC) $(GAME_INC_PATH) $(GAME_CFLAGS) -c -MMD -MP -MF"$(@:%.o=%.d)" -o "$@" "$<"
