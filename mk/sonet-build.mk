# net build

-include $(SONET_DEP)

# build target
$(SONET_TARGET): $(SONET_OBJ_CPP) $(SONET_OBJ_C) $(LIBMODULE_TARGET)
	@echo ' '
	@echo 'Building executable => $@'
	@$(DIR_GUARD)
	@$(SONET_CC) $(SONET_LIB_PATH) -fPIC -shared -o "$(SONET_TARGET)" $(SONET_OBJ_CPP) $(SONET_OBJ_C) $(SONET_LIBS)
	@echo 'Done!'
	@echo ' '
	
# build objects
$(SONET_OBJ_CPP): $(SONET_BUILD_DIR)/%.o: $(SONET_SRC_DIR)/%.cpp
	@echo "Compiling => $<"
	@$(DIR_GUARD)
	@$(SONET_CC) $(SONET_INC_PATH) $(SONET_CFLAGS) -fPIC -c -MMD -MP -MF"$(@:%.o=%.d)" -o "$@" "$<"

$(SONET_OBJ_C): $(SONET_BUILD_DIR)/%.o: $(SONET_SRC_DIR)/%.c
	@echo "Compiling => $<"
	@$(DIR_GUARD)
	@$(SONET_CC) $(SONET_INC_PATH) $(SONET_CFLAGS) -fPIC -c -MMD -MP -MF"$(@:%.o=%.d)" -o "$@" "$<"
