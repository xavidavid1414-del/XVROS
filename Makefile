# XVROS Nintendo 3DS homebrew build
ifeq ($(strip $(DEVKITARM)),)
$(error "DEVKITARM is not set. Install devkitPro/devkitARM.")
endif

include $(DEVKITARM)/3ds_rules

TARGET      := XVROS
BUILD       := build
SOURCES     := source source/wifi
INCLUDES    := include

ARCH        := -march=armv6k -mtune=mpcore -mfloat-abi=hard
CFLAGS      := -g -Wall -Wextra -O2 -mword-relocations -ffunction-sections $(ARCH) -mtp=soft
CFLAGS      += $(INCLUDE) -D__3DS__
CXXFLAGS    := $(CFLAGS) -fno-rtti -fno-exceptions
ASFLAGS     := -g $(ARCH)
# Keep compiler-only CPU options out of LDFLAGS: the linker interprets
# -mfloat-abi=hard as an unsupported emulation mode when passed directly.
LDFLAGS     := -specs=3dsx.specs -g -Wl,-Map,$(notdir $*).map -Wl,--gc-sections
LIBS        := -lctru

.PHONY: all clean
all: $(TARGET).3dsx

clean:
	@rm -rf $(BUILD) $(TARGET).3dsx $(TARGET).elf
