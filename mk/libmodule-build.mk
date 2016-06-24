# module build

-include $(LIBMODULE_DEP)

# build target
$(LIBMODULE_TARGET): $(LIBMODULE_OBJ_CPP) $(LIBMODULE_OBJ_C)
	@echo ' '
	@echo 'Building executable => $@'
	@$(DIR_GUARD)
	@$(LIBMODULE_AR) -r "$(LIBMODULE_TARGET)" $(LIBMODULE_OBJ_CPP) $(LIBMODULE_OBJ_C)
	@echo 'Done!'
	@echo ' '
	
# build objects
$(LIBMODULE_OBJ_CPP): $(LIBMODULE_BUILD_DIR)/%.o: $(LIBMODULE_SRC_DIR)/%.cpp
	@echo "Compiling => $<"
	@$(DIR_GUARD)
	@$(LIBMODULE_CC) $(LIBMODULE_INC_PATH) $(LIBMODULE_CFLAGS) -c -MMD -MP -MF"$(@:%.o=%.d)" -o "$@" "$<"

$(LIBMODULE_OBJ_C): $(LIBMODULE_BUILD_DIR)/%.o: $(LIBMODULE_SRC_DIR)/%.c
	@echo "Compiling => $<"
	@$(DIR_GUARD)
	@$(LIBMODULE_CC) $(LIBMODULE_INC_PATH) $(LIBMODULE_CFLAGS)  -c -MMD -MP -MF"$(@:%.o=%.d)" -o "$@" "$<"
