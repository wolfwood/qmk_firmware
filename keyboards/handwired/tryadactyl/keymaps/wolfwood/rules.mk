MH_AUTO_BUTTONS = yes

ifeq ($(strip $(MH_AUTO_BUTTONS)), yes)
  OPT_DEFS += -DMH_AUTO_BUTTONS
endif
