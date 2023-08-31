default: main

include common.mk
include map/Makefile

$(BIN_DIR)/main: main.c $(MAPLIB_FILE) | $(BIN_DIR)
	$(CC) -o $@ $< -I$(INCLUDE) -I$(MAPLIB_INCLUDE) -lm -l$(MAPLIB) -L$(MAPLIB_DIR) $(CFLAGS)

main: $(BIN_DIR)/main

clean: libmap_clean
	rm -rf $(BUILD_DIR)/*

.PHONY: clean main
