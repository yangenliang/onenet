# game build

-include $(NETSO_DEP)

# build target
$(NETSO_TARGET): $(NETSO_OBJ_CPP) $(NETSO_OBJ_C)
	@echo ' '
	@echo 'Building executable => $@'
	@$(DIR_GUARD)
	@$(NETSO_CC) $(NETSO_LIB_PATH) -fPIC -shared -o "$(NETSO_TARGET)" $(NETSO_OBJ_CPP) $(NETSO_OBJ_C) $(NETSO_LIBS)
	@echo 'Done!'
	@echo ' '
	
# build objects
$(NETSO_OBJ_CPP): $(NETSO_BUILD_DIR)/%.o: $(NETSO_SRC_DIR)/%.cpp
	@echo "Compiling => $<"
	@$(DIR_GUARD)
	@$(NETSO_CC) $(NETSO_INC_PATH) $(NETSO_CFLAGS) -fPIC -c -MMD -MP -MF"$(@:%.o=%.d)" -o "$@" "$<"

$(NETSO_OBJ_C): $(NETSO_BUILD_DIR)/%.o: $(NETSO_SRC_DIR)/%.c
	@echo "Compiling => $<"
	@$(DIR_GUARD)
	@$(NETSO_CC) $(NETSO_INC_PATH) $(NETSO_CFLAGS) -fPIC -c -MMD -MP -MF"$(@:%.o=%.d)" -o "$@" "$<"
