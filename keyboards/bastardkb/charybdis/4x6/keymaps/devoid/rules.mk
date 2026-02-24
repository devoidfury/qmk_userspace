# not using via, disable for security
VIA_ENABLE = no

# leader key, QK_LEAD
LEADER_ENABLE = yes

# unused features turned off to save space
SPACE_CADET_ENABLE = no
COMBO_ENABLE = no
GRAVE_ESC_ENABLE = no

ifdef LEADER_ENABLE
SEND_STRING_ENABLE = yes
else
SEND_STRING_ENABLE = no
endif

# link time optimization to save space
LTO_ENABLE = yes
