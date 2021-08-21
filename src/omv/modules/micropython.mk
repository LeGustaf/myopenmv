OMV_MOD_DIR := $(USERMOD_DIR)
OMV_PORT_MOD_DIR := $(OMV_MOD_DIR)/../ports/$(PORT)/modules

# Add OpenMV common modules.
SRC_USERMOD += $(wildcard $(OMV_MOD_DIR)/*.c)

# Add OpenMV port-specific modules.
SRC_USERMOD += $(wildcard $(OMV_PORT_MOD_DIR)/*.c)

# Extra module flags.
CFLAGS_USERMOD += -I$(OMV_MOD_DIR) -I$(OMV_PORT_MOD_DIR) -Wno-float-conversion

###########
#bitcoin files
BITCOIN_MOD_DIR := $(USERMOD_DIR)

# Add all C files to SRC_USERMOD.
SRC_USERMOD += $(BITCOIN_MOD_DIR)/secp256k1/src/utility/secp256k1.c
SRC_USERMOD += $(BITCOIN_MOD_DIR)/libsecp256k1.c

# We can add our module folder to include paths if needed
CFLAGS_USERMOD += -I$(BITCOIN_MOD_DIR)/secp256k1/src
###########

BITCOIN_MOD_DIR := $(USERMOD_DIR)

# Add all C files to SRC_USERMOD.
SRC_USERMOD += $(BITCOIN_MOD_DIR)/crypto/memzero.c
SRC_USERMOD += $(BITCOIN_MOD_DIR)/crypto/rand.c
SRC_USERMOD += $(BITCOIN_MOD_DIR)/crypto/ripemd160.c
SRC_USERMOD += $(BITCOIN_MOD_DIR)/crypto/sha2.c
SRC_USERMOD += $(BITCOIN_MOD_DIR)/crypto/bignum.c
SRC_USERMOD += $(BITCOIN_MOD_DIR)/crypto/ecdsa.c
SRC_USERMOD += $(BITCOIN_MOD_DIR)/crypto/secp256k1.c
SRC_USERMOD += $(BITCOIN_MOD_DIR)/crypto/hmac.c
SRC_USERMOD += $(BITCOIN_MOD_DIR)/crypto/pbkdf2.c
SRC_USERMOD += $(BITCOIN_MOD_DIR)/hashlib.c
SRC_USERMOD += $(BITCOIN_MOD_DIR)/ecc.c

# We can add our module folder to include paths if needed
CFLAGS_USERMOD += -I$(BITCOIN_MOD_DIR)/crypto

###########
# Add CubeAI module if enabled.
ifeq ($(MICROPY_PY_CUBEAI), 1)
SRC_USERMOD += $(OMV_MOD_DIR)/../../stm32cubeai/py_st_nn.c
endif

ifeq ($(MICROPY_PY_ULAB), 1)
# NOTE: overrides USERMOD_DIR
# Workaround to build and link ulab.
USERMOD_DIR := $(USERMOD_DIR)/ulab/code
include $(USERMOD_DIR)/micropython.mk
endif
