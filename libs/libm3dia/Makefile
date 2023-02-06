#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif
.PHONY: install

#---------------------------------------------------------------------------------
ifeq ($(OS),Windows_NT)
install:
	@cp -rf lib/* $(DEVKITPRO)/portlibs/3ds/lib/
	@cp -rf includes/* $(DEVKITPRO)/portlibs/3ds/include/
else
install:
	@sudo cp -rf lib/* $(DEVKITPRO)/portlibs/3ds/lib/
	@sudo cp -rf includes/* $(DEVKITPRO)/portlibs/3ds/include/
endif
