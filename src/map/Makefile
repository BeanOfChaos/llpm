ifndef COMMON_INCLUDED
	include ../common.mk
endif

MAPLIB_DIR=$(ROOT_DIR)/map/lib
MAPLIB=map
MAPLIB_INCLUDE=$(ROOT_DIR)/map/include
MAPLIB_FILE=$(MAPLIB_DIR)/lib$(MAPLIB).a

MAPLIB_BUILD=$(BUILD_DIR)/map

$(MAPLIB_BUILD): $(BUILD_DIR)
	mkdir $(MAPLIB_BUILD)

$(MAPLIB_DIR):
	mkdir $(MAPLIB_DIR)

$(MAPLIB_BUILD)/map.o: $(ROOT_DIR)/map/src/map.c | $(MAPLIB_BUILD)
	$(CC) -c -o $@ $< -I$(MAPLIB_INCLUDE) $(CFLAGS)

$(MAPLIB_FILE): $(MAPLIB_BUILD)/map.o | $(MAPLIB_DIR)
	ar rcs $@ $^


libmap_clean:
	rm $(MAPLIB_DIR)/*

.PHONY: libmap_clean
