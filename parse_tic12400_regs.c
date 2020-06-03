#include "parse_phy_regs.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

bool parse_phy_regs_file (char *inFileName, char *outFileName) {
    (void) *outFileName;
    char curFileStr [500];
    bool res = false;
    FILE *inFilePrt = NULL;
    FILE *outFilePrt = NULL;
    inFilePrt = fopen (inFileName, "r");
    outFilePrt = fopen (outFileName, "w");
    if (inFilePrt && outFilePrt) {
        int line = 0;
        while (NULL != fgets (curFileStr, sizeof(curFileStr), inFilePrt)) {
            unsigned int regAddr;
            unsigned int regVal;
            //printf ("\n>[%s]", curFileStr);
            sscanf (curFileStr, "%x %x", (unsigned int *) &regAddr, (unsigned int *) &regVal);
            parse_reg (regAddr, regVal, outFilePrt);
            //printf ("\n[%x] [%x]", regAddr, regVal);
            line++;
        }
        fclose (inFilePrt);
        fclose (outFilePrt);
        res = true;
    }
    return res;

}

bool parse_reg (uint8_t regAddr, uint16_t regVal, FILE *outFilePrt) {
    bool res = false;
    switch (regAddr) {
        case 0: {
            fprintf (outFilePrt, "\nBasic control register 0h");
            res = parse_basic_control_register (regVal, outFilePrt);
        }
            break;
        case 1: {
            fprintf (outFilePrt, "\nBasic status register 1h");
            res = parse_basic_status_register (regVal, outFilePrt);
        }
            break;
        default:
            break;
    }
    return res;
}

#define LOOPBACK (1<<14)

bool parse_basic_control_register (uint16_t regVal, FILE *outFilePrt) {
    bool res = false;
    if (regVal & RESET_BIT_15) {
        fprintf (outFilePrt, "\n bit 15: PHY reset");
    } else {
        printf ("\n bit 15: normal operation");
    }
    if (regVal & LOOPBACK_14) {
        fprintf (outFilePrt, "\n bit 14: PHY reset");
    } else {
        fprintf (outFilePrt, "\n bit 14: normal operation");
    }

    if (regVal & SPEED_SELECT_13) {
        fprintf (outFilePrt, "\n bit 13: 100 Mbit/s if SPEED_SELECT (MSB) = 0 reserved if SPEED_SELECT (MSB) = 1");
    } else {
        fprintf (outFilePrt, "\n bit 13: 10 Mbit/s if SPEED_SELECT (MSB) = 0 1000 Mbit/s if SPEED_SELECT (MSB) = 1");
    }

    if (regVal & AUTONEG_EN_12) {
        fprintf (outFilePrt, "\n bit 12: Error");
    } else {
        fprintf (outFilePrt, "\n bit 12: Auto negotiation not supported; always 0; a write access is ignored ");
    }

    if (regVal & POWER_DOWN_11) {
        fprintf (
            outFilePrt,
            "\n bit 11: power down and switch to Standby mode (provided ISOLATE = 0; ignored if ISOLATE = 1 and CONTROL_ERR interrupt generated) ");
    } else {
        fprintf (
            outFilePrt,
            "\n bit 11: normal operation (clearing this bit automatically triggers a transition to Normal mode, provided control bits POWER_MODE are set to 0011 Normal mode, see Table 18) ");
    }

    if (regVal & ISOLATE_10) {
        fprintf (
            outFilePrt,
            "\n bit 10: isolate PHY from MII/RMII (provided POWER_DOWN = 0; ignored if POWER_DOWN = 1 and CONTROL_ERR interrupt generated) ");
    } else {
        fprintf (outFilePrt, "\n bit 10: normal operation ");
    }

    if (regVal & RE_AUTONEG_9) {
        fprintf (outFilePrt, "\n bit 9: Error ");
    } else {
        fprintf (outFilePrt, "\n bit 9:  Auto negotiation not supported; always 0; a write access is ignored.");
    }

    if (regVal & DUPLEX_MODE_8) {
        fprintf (outFilePrt, "\n bit 8: only full duplex supported; always 1; a write access is ignored ");
    } else {
        fprintf (outFilePrt, "\n bit 8: Error ");
    }

    if (regVal & COLLISION_TEST_7) {
        fprintf (outFilePrt, "\n bit 7: error! ");
    } else {
        fprintf (outFilePrt, "\n bit 7: COL signal test not supported; always 0; a write access is ignored ");
    }

    if (regVal & SPEED_SELECT_6) {
        fprintf (outFilePrt, "\n bit 6: 1000 Mbit/s if SPEED_SELECT (LSB) = 0 reserved if SPEED_SELECT (LSB) = 1");
    } else {
        fprintf (outFilePrt, "\n bit 6: 10 Mbit/s if SPEED_SELECT (LSB) = 0 100 Mbit/s if SPEED_SELECT (LSB) = 1 ");
    }
    if (regVal & UNIDIRECT_EN_5) {
        fprintf (outFilePrt, "\n bit 5: enable transmit from MII regardless of whether the PHY has determined that a valid link has been established");
    } else {
        fprintf (outFilePrt, "\n bit 5: enable transmit from MII only when the PHY has determined that a valid link has been established ");
    }
    fprintf (outFilePrt, "\n");
    return res;

}

bool parse_basic_status_register (uint16_t regVal, FILE *outFilePrt) {
    bool res = false;
    if (regVal & S100BASE_T4_15) {
        fprintf (outFilePrt, "\n bit 15: PHY able to perform 100BASE-T4 ");
    } else {
        fprintf (outFilePrt, "\n bit 15: PHY not able to perform 100BASE-T4 ");
    }
    if (regVal & S100BASE_X_FD_14) {
        fprintf (outFilePrt, "\n bit 14: PHY able to perform 100BASE-X full-duplex ");
    } else {
        fprintf (outFilePrt, "\n bit 14: PHY not able to perform 100BASE-X full-duplex");
    }
    if (regVal & S100BASE_X_HD_13) {
        fprintf (outFilePrt, "\n bit 13: PHY able to perform 100BASE-X half-duplex ");
    } else {
        fprintf (outFilePrt, "\n bit 13: PHY not able to perform 100BASE-X half-duplex ");
    }
    if (regVal & S10Mbps_FD_12) {
        fprintf (outFilePrt, "\n bit 12: PHY able to perform 10 Mbit/s full-duplex ");
    } else {
        fprintf (outFilePrt, "\n bit 12: PHY not able to perform 10 Mbit/s full-duplex ");
    }
    if (regVal & S10Mbps_HD_11) {
        fprintf (outFilePrt, "\n bit 11: PHY able to perform 10 Mbit/s half-duplex ");
    } else {
        fprintf (outFilePrt, "\n bit 11: PHY not able to perform 10 Mbit/s half-duplex ");
    }
    if (regVal & S100BASE_T2_FD_10) {
        fprintf (outFilePrt, "\n bit 10: PHY able to perform 100BASE-T2 full-duplex");
    } else {
        fprintf (outFilePrt, "\n bit 10: PHY not able to perform 100BASE-T2 full-duplex");
    }
    if (regVal & S100BASE_T2_HD_9) {
        fprintf (outFilePrt, "\n bit 9: PHY able to perform 100BASE-T2 half-duplex");
    } else {
        fprintf (outFilePrt, "\n bit 9: PHY not able to perform 100BASE-T2 half-duplex");
    }
    if (regVal & EXTENDED_STATUS_8) {
        fprintf (outFilePrt, "\n bit 8: extended status information in register 15h");
    } else {
        fprintf (outFilePrt, "\n bit 8: no extended status information in register 15h");
    }
    if (regVal & UNIDIRECT_ABILITY_7) {
        fprintf (outFilePrt, "\n bit 7: PHY able to transmit from MII regardless of whether the PHY has determined that a valid link has been established");
    } else {
        fprintf (outFilePrt, "\n bit 7: PHY able to transmit from MII only when the PHY has determined that a valid link has been established");
    }
    if (regVal & MF_PREAMBLE_SUPPRESSION_6) {
        fprintf (outFilePrt, "\n bit 6: PHY will accept management frames with preamble suppressed");
    } else {
        fprintf (outFilePrt, "\n bit 6: PHY will not accept management frames with preamble suppressed");
    }
    if (regVal & AUTONEG_COMPLETE_5) {
        fprintf (outFilePrt, "\n bit 5: Autonegotiation process completed");
    } else {
        fprintf (outFilePrt, "\n bit 5: Autonegotiation process not completed");
    }
    if (regVal & REMOTE_FAULT_4) {
        fprintf (outFilePrt, "\n bit 4: remote fault condition detected");
    } else {
        fprintf (outFilePrt, "\n bit 4: no remote fault condition detected");
    }
    if (regVal & AUTONEG_ABILITY_3) {
        fprintf (outFilePrt, "\n bit 3: PHY able to perform Autonegotiation");
    } else {
        fprintf (outFilePrt, "\n bit 3: PHY not able to perform Autonegotiation");
    }
    if (regVal & LINK_STATUS_2) {
        fprintf (outFilePrt, "\n bit 2: link is up");
    } else {
        fprintf (outFilePrt, "\n bit 2: link is down");
    }
    if (regVal & JABBER_DETECT_1) {
        fprintf (outFilePrt, "\n bit 1: jabber condition detected");
    } else {
        fprintf (outFilePrt, "\n bit 1: no jabber condition detected");
    }
    if (regVal & EXTENDED_CAPABILITY_0) {
        fprintf (outFilePrt, "\n bit 0: extended register capabilities");
    } else {
        fprintf (outFilePrt, "\n bit 0: basic register set capabilities only");
    }
    fprintf (outFilePrt, "\n");
    return res;
}

