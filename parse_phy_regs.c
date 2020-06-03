#include "parse_phy_regs.h"

#include "str_ops.h"
#include "tja1101_bits_offsets.h"
#include "utils.h"

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
        case 0:
            printf ("\nBasic control register \t\t [0h] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            fprintf (outFilePrt, "\nBasic control register [0h] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_basic_control_register (regVal, outFilePrt);
            break;
        case 1:
            printf ("\nBasic status register \t\t [1h] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            fprintf (outFilePrt, "\nBasic status register [1h] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_basic_status_register (regVal, outFilePrt);
            break;
        case 2:
            printf ("\nPHY identifier register 1 \t [2h] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            fprintf (outFilePrt, "\nPHY identifier register 1 [2h] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_phy_identifier_1_register (regVal, outFilePrt);
            break;
        case 3:
            printf ("\nPHY identifier register 2 \t [3h] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            fprintf (outFilePrt, "\nPHY identifier register 2 [3h] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_phy_identifier_2_register (regVal, outFilePrt);
            break;
        case 15:
            printf ("\nExtended status register \t [15] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            fprintf (outFilePrt, "\nExtended status register [15] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_extended_status_register (regVal, outFilePrt);
            break;
        case 16:
            printf ("\nPHY identifier register 3 \t [16] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            fprintf (outFilePrt, "\nPHY identifier register 3 [16] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_phy_identifier_3_register (regVal, outFilePrt);
            break;
        case 17:
            printf ("\nExtended control register \t [17] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            fprintf (outFilePrt, "\nExtended control register [17] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_extended_control_register (regVal, outFilePrt);
            break;
        case 18:
            printf ("\nConfiguration register 1 \t [18] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            fprintf (outFilePrt, "\nConfiguration register 1 [18] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_configuration_register_1 (regVal, outFilePrt);
            break;

        case 19:
            printf ("\nConfiguration register 2 \t [19] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            fprintf (outFilePrt, "\nConfiguration register 2 [19] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_configuration_register_2 (regVal, outFilePrt);
            break;
        case 20:
            printf ("\nSymbol error counter register \t [20] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            fprintf (outFilePrt, "\nSymbol error counter register [20] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_symbol_error_counter_register (regVal, outFilePrt);
            break;
        case 21:
            printf ("\nInterrupt status register \t [21] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            fprintf (outFilePrt, "\nInterrupt source register [21] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_interrupt_status_register (regVal, outFilePrt);
            break;
        case 22:
            printf ("\nInterrupt enable register \t [22] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            fprintf (outFilePrt, "\nInterrupt enable register [22] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_interrupt_enable_register (regVal, outFilePrt);
            break;
        case 23:
            printf ("\nCommunication status register \t [23] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            fprintf (outFilePrt, "\nCommunication status register [23] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_communication_status_register (regVal, outFilePrt);
            break;
        case 24:
            printf ("\nGeneral status register \t [24] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            fprintf (outFilePrt, "\nGeneral status register [24] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_general_status_register (regVal, outFilePrt);
            break;
        case 25:
            printf ("\nExternal status register \t [25] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            fprintf (outFilePrt, "\nExternal status register [25] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_external_status_register (regVal, outFilePrt);
            break;
        case 26:
            printf ("\nLink-fail counter register \t [26] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            fprintf (outFilePrt, "\nLink-fail counter register [26] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_link_fail_counter_register (regVal, outFilePrt);
            break;
        case 27:
            printf ("\nCommon configuration register \t [27] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            fprintf (outFilePrt, "\nCommon configuration register [27] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_common_configuration_register (regVal, outFilePrt);
            break;
        case 28:
            printf ("\nConfiguration register 3 \t [28] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            fprintf (outFilePrt, "\nConfiguration register 3 [28] regVal: [0x%04x] [0b_%s]", regVal, utoa_bin16 (regVal));
            res = parse_configuration_register_3 (regVal, outFilePrt);
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
        fprintf (outFilePrt, "\n  bit 15: RW PHY reset");
    } else {
        fprintf (outFilePrt, "\n  bit 15: RW normal operation");
    }
    if (regVal & LOOPBACK_14) {
        fprintf (outFilePrt, "\n  bit 14: RW PHY reset");
    } else {
        fprintf (outFilePrt, "\n  bit 14: RW normal operation");
    }

    if (regVal & SPEED_SELECT_13) {
        fprintf (outFilePrt, "\n  bit 13: RW 100 Mbit/s if SPEED_SELECT (MSB) = 0 reserved if SPEED_SELECT (MSB) = 1");
    } else {
        fprintf (outFilePrt, "\n  bit 13: RW 10 Mbit/s if SPEED_SELECT (MSB) = 0 1000 Mbit/s if SPEED_SELECT (MSB) = 1");
    }

    if (regVal & AUTONEG_EN_12) {
        fprintf (outFilePrt, "\n  bit 12: RW Error");
    } else {
        fprintf (outFilePrt, "\n  bit 12: RW Auto negotiation not supported; always 0; a write access is ignored ");
    }

    if (regVal & POWER_DOWN_11) {
        fprintf (
            outFilePrt,
            "\n  bit 11: RW power down and switch to Standby mode (provided ISOLATE = 0; ignored if ISOLATE = 1 and CONTROL_ERR interrupt generated) ");
    } else {
        fprintf (
            outFilePrt,
            "\n  bit 11:RW  normal operation (clearing this bit automatically triggers a transition to Normal mode, provided control bits POWER_MODE are set to 0011 Normal mode, see Table 18) ");
    }

    if (regVal & ISOLATE_10) {
        fprintf (
            outFilePrt,
            "\n  bit 10: RW isolate PHY from MII/RMII (provided POWER_DOWN = 0; ignored if POWER_DOWN = 1 and CONTROL_ERR interrupt generated) ");
    } else {
        fprintf (outFilePrt, "\n  bit 10: RW normal operation ");
    }

    if (regVal & RE_AUTONEG_9) {
        fprintf (outFilePrt, "\n  bit 9: RW Error ");
    } else {
        fprintf (outFilePrt, "\n  bit 9:  RW Auto negotiation not supported; always 0; a write access is ignored.");
    }

    if (regVal & DUPLEX_MODE_8) {
        fprintf (outFilePrt, "\n  bit 8: RW  only full duplex supported; always 1; a write access is ignored ");
    } else {
        fprintf (outFilePrt, "\n  bit 8: RW  Error ");
    }

    if (regVal & COLLISION_TEST_7) {
        fprintf (outFilePrt, "\n  bit 7: RW  error! ");
    } else {
        fprintf (outFilePrt, "\n  bit 7: RW  COL signal test not supported; always 0; a write access is ignored ");
    }

    if (regVal & SPEED_SELECT_6) {
        fprintf (outFilePrt, "\n  bit 6: RW 1000 Mbit/s if SPEED_SELECT (LSB) = 0 reserved if SPEED_SELECT (LSB) = 1");
    } else {
        fprintf (outFilePrt, "\n  bit 6: RW 10 Mbit/s if SPEED_SELECT (LSB) = 0 100 Mbit/s if SPEED_SELECT (LSB) = 1 ");
    }
    if (regVal & UNIDIRECT_EN_5) {
        fprintf (
            outFilePrt,
            "\n  bit 5: RW enable transmit from MII regardless of whether the PHY has determined that a valid link has been established");
    } else {
        fprintf (outFilePrt, "\n  bit 5: RW enable transmit from MII only when the PHY has determined that a valid link has been established ");
    }
    fprintf (outFilePrt, "\n");
    return res;

}

bool parse_basic_status_register (uint16_t regVal, FILE *outFilePrt) {
    bool res = false;
    if (regVal & S100BASE_T4_15) {
        fprintf (outFilePrt, "\n  bit 15: PHY able to perform 100BASE-T4 ");
    } else {
        fprintf (outFilePrt, "\n  bit 15: PHY not able to perform 100BASE-T4 ");
    }
    if (regVal & S100BASE_X_FD_14) {
        fprintf (outFilePrt, "\n  bit 14: PHY able to perform 100BASE-X full-duplex ");
    } else {
        fprintf (outFilePrt, "\n  bit 14: PHY not able to perform 100BASE-X full-duplex");
    }
    if (regVal & S100BASE_X_HD_13) {
        fprintf (outFilePrt, "\n  bit 13: PHY able to perform 100BASE-X half-duplex ");
    } else {
        fprintf (outFilePrt, "\n  bit 13: PHY not able to perform 100BASE-X half-duplex ");
    }
    if (regVal & S10Mbps_FD_12) {
        fprintf (outFilePrt, "\n  bit 12: PHY able to perform 10 Mbit/s full-duplex ");
    } else {
        fprintf (outFilePrt, "\n  bit 12: PHY not able to perform 10 Mbit/s full-duplex ");
    }
    if (regVal & S10Mbps_HD_11) {
        fprintf (outFilePrt, "\n  bit 11: PHY able to perform 10 Mbit/s half-duplex ");
    } else {
        fprintf (outFilePrt, "\n  bit 11: PHY not able to perform 10 Mbit/s half-duplex ");
    }
    if (regVal & S100BASE_T2_FD_10) {
        fprintf (outFilePrt, "\n  bit 10: PHY able to perform 100BASE-T2 full-duplex");
    } else {
        fprintf (outFilePrt, "\n  bit 10: PHY not able to perform 100BASE-T2 full-duplex");
    }
    if (regVal & S100BASE_T2_HD_9) {
        fprintf (outFilePrt, "\n  bit 9: PHY able to perform 100BASE-T2 half-duplex");
    } else {
        fprintf (outFilePrt, "\n  bit 9: PHY not able to perform 100BASE-T2 half-duplex");
    }
    if (regVal & EXTENDED_STATUS_8) {
        fprintf (outFilePrt, "\n  bit 8: extended status information in register 15h");
    } else {
        fprintf (outFilePrt, "\n  bit 8: no extended status information in register 15h");
    }
    if (regVal & UNIDIRECT_ABILITY_7) {
        fprintf (
            outFilePrt,
            "\n  bit 7: PHY able to transmit from MII regardless of whether the PHY has determined that a valid link has been established");
    } else {
        fprintf (outFilePrt, "\n  bit 7: PHY able to transmit from MII only when the PHY has determined that a valid link has been established");
    }
    if (regVal & MF_PREAMBLE_SUPPRESSION_6) {
        fprintf (outFilePrt, "\n  bit 6: PHY will accept management frames with preamble suppressed");
    } else {
        fprintf (outFilePrt, "\n  bit 6: PHY will not accept management frames with preamble suppressed");
    }
    if (regVal & AUTONEG_COMPLETE_5) {
        fprintf (outFilePrt, "\n  bit 5: Autonegotiation process completed");
    } else {
        fprintf (outFilePrt, "\n  bit 5: Autonegotiation process not completed");
    }
    if (regVal & REMOTE_FAULT_4) {
        fprintf (outFilePrt, "\n  bit 4: remote fault condition detected");
    } else {
        fprintf (outFilePrt, "\n  bit 4: no remote fault condition detected");
    }
    if (regVal & AUTONEG_ABILITY_3) {
        fprintf (outFilePrt, "\n  bit 3: PHY able to perform Autonegotiation");
    } else {
        fprintf (outFilePrt, "\n  bit 3: PHY not able to perform Autonegotiation");
    }
    if (regVal & LINK_STATUS_2) {
        fprintf (outFilePrt, "\n  bit 2: link is up");
    } else {
        fprintf (outFilePrt, "\n  bit 2: link is down");
    }
    if (regVal & JABBER_DETECT_1) {
        fprintf (outFilePrt, "\n  bit 1: jabber condition detected");
    } else {
        fprintf (outFilePrt, "\n  bit 1: no jabber condition detected");
    }
    if (regVal & EXTENDED_CAPABILITY_0) {
        fprintf (outFilePrt, "\n  bit 0: extended register capabilities");
    } else {
        fprintf (outFilePrt, "\n  bit 0: basic register set capabilities only");
    }
    fprintf (outFilePrt, "\n");
    return res;
}

bool parse_phy_identifier_1_register (uint16_t regVal, FILE *outFilePrt) {
    bool res = false;
    fprintf (outFilePrt, "\n  bit 15..0: Organizationally Unique Identifier 0x%04x", regVal);
    fprintf (outFilePrt, "\n");
    return res;
}

bool parse_phy_identifier_2_register (uint16_t regVal, FILE *outFilePrt) {
    bool res = false;
    uint8_t phyId = extract_subval_from_16bit (regVal, 15, 10);
    fprintf (outFilePrt, "\n  bit 15..10: phyId 0x%02x (19 to 24 of the OUI)", phyId);
    uint8_t typeNo = extract_subval_from_16bit (regVal, 9, 4);
    fprintf (outFilePrt, "\n  bit 9..4: manufacturer type number 0x%02x", typeNo);
    uint8_t revNo = extract_subval_from_16bit (regVal, 3, 0);
    fprintf (outFilePrt, "\n  bit 3..0: manufacturer  revision number 0x%02x", revNo);
    fprintf (outFilePrt, "\n");
    return res;
}

bool parse_extended_status_register (uint16_t regVal, FILE *outFilePrt) {
    bool res = false;
    if (regVal & S1000BASE_X_FD_15) {
        fprintf (outFilePrt, "\n  bit 15: PHY able to perform 1000BASE-X full-duplex");
    } else {
        fprintf (outFilePrt, "\n  bit 15: PHY not able to perform 1000BASE-X full-duplex");
    }
    if (regVal & S1000BASE_X_HD_14) {
        fprintf (outFilePrt, "\n  bit 14: PHY able to perform 1000BASE-X half-duplex");
    } else {
        fprintf (outFilePrt, "\n  bit 14: PHY not able to perform 1000BASE-X half-duplex ");
    }
    if (regVal & S1000BASE_T_FD_13) {
        fprintf (outFilePrt, "\n  bit 13: PHY able to perform 1000BASE-T full-duplex");
    } else {
        fprintf (outFilePrt, "\n  bit 13: PHY not able to perform 1000BASE-T full-duplex");
    }
    if (regVal & S1000BASE_T_HD_12) {
        fprintf (outFilePrt, "\n  bit 12: PHY able to perform 1000BASE-T half-duplex");
    } else {
        fprintf (outFilePrt, "\n  bit 12: PHY not able to perform 1000BASE-T half-duplex");
    }
    if (regVal & S100BASE_T1_7) {
        fprintf (outFilePrt, "\n  bit 7: PHY able to 1-pair 100BASE-T1 100 Mbit/s");
    } else {
        fprintf (outFilePrt, "\n  bit 7: PHY not able to 1-pair 100BASE-T1 100 Mbit/s");
    }
    if (regVal & S1000BASE_RTPGE_6) {
        fprintf (outFilePrt, "\n  bit 6: PHY supports RTPGE");
    } else {
        fprintf (outFilePrt, "\n  bit 6: PHY not able to support RTPGE");
    }
    fprintf (outFilePrt, "\n");

    return res;
}

bool parse_extended_control_register (uint16_t regVal, FILE *outFilePrt) {
    bool res = false;
    if (regVal & LINK_CONTROL_15) {
        fprintf (outFilePrt, "\n  bit 15: link control enabled");
    } else {
        fprintf (outFilePrt, "\n  bit 15: link control disabled");
    }
    uint16_t powerMode = extract_subval_from_16bit (regVal, 14, 11);
    res = parse_power_mode (powerMode, outFilePrt);
    if (regVal & SLAVE_JITTER_TEST_10) {
        fprintf (outFilePrt, "\n  bit 10: enable Slave jittet test");
    } else {
        fprintf (outFilePrt, "\n  bit 10: disable Slave jitter test");
    }
    if (regVal & TRAINING_RESTART_9) {
        fprintf (outFilePrt, "\n  bit 9: forces a restart of the training phase");
    } else {
        fprintf (outFilePrt, "\n  bit 9: halts the training phase");
    }
    uint16_t testMode = extract_subval_from_16bit (regVal, 8, 6);
    res = parse_test_mode (testMode, outFilePrt);

    if (regVal & CABLE_TEST_5) {
        fprintf (outFilePrt, "\n  bit 5: forces TDR-based cable test");
    } else {
        fprintf (outFilePrt, "\n  bit 5: stops TDR-based cable test");
    }
    uint16_t loopbackMode = extract_subval_from_16bit (regVal, 4, 3);
    res = parse_loopback_mode (loopbackMode, outFilePrt);
    if (regVal & CONFIG_EN_2) {
        fprintf (outFilePrt, "\n  bit 2: configuration register access enabled");
    } else {
        fprintf (outFilePrt, "\n  bit 2: configuration register access disabled");
    }
    fprintf (outFilePrt, "\n");

    return res;
}

bool parse_power_mode (uint8_t regVal, FILE *outFilePrt) {
    bool res = false;
    switch (regVal) {
        case 0:
            fprintf (outFilePrt, "\n  bit 14..11: operating mode: no change");
            break;
        case 3:
            fprintf (outFilePrt, "\n  bit 14..11: operating mode: Normal mode (command)");
            break;
        case 9:
            fprintf (outFilePrt, "\n  bit 14..11: Silent mode (read only)");
            break;
        case 10:
            fprintf (outFilePrt, "\n  bit 14..11: Sleep mode (read only)");
            break;
        case 11:
            fprintf (outFilePrt, "\n  bit 14..11: Sleep Request mode (command)");
            break;
        case 12:
            fprintf (outFilePrt, "\n  bit 14..11: Standby mode (command)");
            break;
        default:
            fprintf (outFilePrt, "\n  bit 14..11: Error");
            break;
    }
    return res;
}

bool parse_test_mode (uint8_t regVal, FILE *outFilePrt) {
    bool res = false;
    switch (regVal) {
        case 0:
            fprintf (outFilePrt, "\n  bit 8..6: R/W test mode selection: no test mode");
            break;
        case 1:
            fprintf (outFilePrt, "\n  bit 8..6: R/W test mode selection 100BASE-T1 test mode 1");
            break;
        case 2:
            fprintf (outFilePrt, "\n  bit 8..6: R/W test mode selection 100BASE-T1 test mode 2 ");
            break;
        case 3:
            fprintf (outFilePrt, "\n  bit 8..6: R/W test mode selection test mode 3");
            break;
        case 4:
            fprintf (outFilePrt, "\n  bit 8..6: R/W test mode selection 100BASE-T1 test mode 4");
            break;
        case 5:
            fprintf (outFilePrt, "\n  bit 8..6: R/W test mode selection 100BASE-T1 test mode 5");
            break;
        case 6:
            fprintf (outFilePrt, "\n  bit 8..6: R/W test mode selection scrambler and descrambler bypassed");
            break;
        case 7:
            fprintf (outFilePrt, "\n  bit 8..6: R/W test mode selection reserved");
            break;
        default:
            fprintf (outFilePrt, "\n  bit 8..6: R/W Error");
            break;
    }
    return res;
}

bool parse_loopback_mode (uint8_t regVal, FILE *outFilePrt) {
    bool res = false;
    switch (regVal) {
        case 0:
            fprintf (outFilePrt, "\n  bit 4..3: R/W internal loopback");
            break;
        case 1:
            fprintf (outFilePrt, "\n  bit 4..3: R/W external loopback");
            break;
        case 2:
            fprintf (outFilePrt, "\n  bit 4..3: R/W external loopback");
            break;
        case 3:
            fprintf (outFilePrt, "\n  bit 4..3: R/W remote loopback");
            break;

        default:
            fprintf (outFilePrt, "\n  bit 4..3: R/W Error");
            break;
    }
    return res;
}

bool parse_configuration_register_2 (uint16_t regVal, FILE *outFilePrt) {
    bool res = false;
    uint16_t phyAddr = extract_subval_from_16bit (regVal, 15, 11);
    fprintf (outFilePrt, "\n  bit 15..11: r 5bit PHY address: [%d]", phyAddr);
    if (regVal & JUMBO_ENABLE_2) {
        fprintf (outFilePrt, "\n  bit 2: rw packets up to 16 kB supported");
    } else {
        fprintf (outFilePrt, "\n  bit 2: rw packets up to 4 kB supported");
    }
    fprintf (outFilePrt, "\n");
    return res;
}

bool parse_communication_status_register (uint16_t regVal, FILE *outFilePrt) {
    bool res;
    if (regVal & LINK_UP_15) {
        fprintf (outFilePrt, "\n  bit 15: r link OK");
    } else {
        fprintf (outFilePrt, "\n  bit 15: r link failure");
    }
    if (regVal & LOC_RCVR_STATUS_12) {
        fprintf (outFilePrt, "\n  bit 12: r local receiver OK");
    } else {
        fprintf (outFilePrt, "\n  bit 12: r local receiver not OK");
    }
    if (regVal & REM_RCVR_STATUS_11) {
        fprintf (outFilePrt, "\n  bit 11: r remote receiver OK");
    } else {
        fprintf (outFilePrt, "\n  bit 11: r remote receiver not OK");
    }
    if (regVal & SCR_LOCKED_10) {
        fprintf (outFilePrt, "\n  bit 10: r descrambler locked");
    } else {
        fprintf (outFilePrt, "\n  bit 10: r descrambler unlocked");
    }
    if (regVal & SSD_ERR_9) {
        fprintf (outFilePrt, "\n  bit 9: r SSD error detected");
    } else {
        fprintf (outFilePrt, "\n  bit 9: r no SSD error detected");
    }
    if (regVal & ESD_ERR_8) {
        fprintf (outFilePrt, "\n  bit 8: r ESD error detected");
    } else {
        fprintf (outFilePrt, "\n  bit 8: r no ESD error detected");
    }
    uint16_t sqi = extract_subval_from_16bit (regVal, 7, 5);
    res = parse_sqi (sqi, outFilePrt);
    if (regVal & RECEIVE_ERR_4) {
        fprintf (outFilePrt, "\n  bit 4: r receive error detected since register last read");
    } else {
        fprintf (outFilePrt, "\n  bit 4: r no receive error detected");
    }
    if (regVal & TRANSMIT_ERR_3) {
        fprintf (outFilePrt, "\n  bit 3: r transmit error detected since register last read");
    } else {
        fprintf (outFilePrt, "\n  bit 3: r no transmit error detected");
    }
    uint16_t phyState = extract_subval_from_16bit (regVal, 2, 0);
    res = parse_phy_state (phyState, outFilePrt);
    fprintf (outFilePrt, "\n");
    return res;
}

bool parse_configuration_register_3 (uint16_t regVal, FILE *outFilePrt) {
    fprintf (outFilePrt, "\n  bit 15:2: RW reserved");
    if (regVal & FORCE_SLEEP_1) {
        fprintf (outFilePrt, "\n  bit 1: RW force PHY to Sleep mode");
    } else {
        fprintf (outFilePrt, "\n  bit 1: RW forced sleep inactive");
    }
    fprintf (outFilePrt, "\n  bit 0: RW write 1; ignore on read");

    fprintf (outFilePrt, "\n");
    return true;
}
bool parse_phy_identifier_3_register (uint16_t regVal, FILE *outFilePrt) {
    (void) regVal;
    (void) outFilePrt;
    fprintf (outFilePrt, "\nLack of detalisation in datasheet");
    fprintf (outFilePrt, "\n");
    return true;
}
bool parse_configuration_register_1 (uint16_t regVal, FILE *outFilePrt) {
    bool res = false;
    (void) outFilePrt;
    if (regVal & MASTER_SLAVE_15) {
        fprintf (outFilePrt, "\n  bit 15: rw PHY configured as Master");
    } else {
        fprintf (outFilePrt, "\n  bit 15: rw PHY configured as Slave");
    }
    if (regVal & FWDPHYLOC_14) {
        fprintf (outFilePrt, "\n  bit 14: rw wake-up event forwarded locally");
    } else {
        fprintf (outFilePrt, "\n  bit 14: rw wake-up event not forwarded locally");
    }
    if (regVal & REMWUPHY_11) {
        fprintf (outFilePrt, "\n  bit 11: rw PHY reacts to a remote wake-up");
    } else {
        fprintf (outFilePrt, "\n  bit 11: rw PHY does not react to a remote wake-up");
    }
    if (regVal & LOCWUPHY_10) {
        fprintf (outFilePrt, "\n  bit 14: rw PHY reacts to a local wake-up");
    } else {
        fprintf (outFilePrt, "\n  bit 14: rw PHY does not react to a local wake-up");
    }
    uint16_t mii_mode = extract_subval_from_16bit (regVal, 9, 8);
    res = parse_mii_mode (mii_mode, outFilePrt);
    if (regVal & MII_DRIVER_7) {
        fprintf (outFilePrt, "\n  bit 7: rw MII output driver reduced strength");
    } else {
        fprintf (outFilePrt, "\n  bit 7: MII output driver standard strength");
    }
    if (regVal & SLEEP_CONFIRM_6) {
        fprintf (outFilePrt, "\n  bit 6: confirmation needed from another PHY before going to sleep");
    } else {
        fprintf (outFilePrt, "\n  bit 6: no confirmation needed from another PHY before going to sleep");
    }

    if (regVal & LPS_WUR_DIS_5) {
        fprintf (outFilePrt, "\n  bit 5: LPS/WUR disabled");
    } else {
        fprintf (outFilePrt, "\n  bit 5: LPS/WUR enabled");
    }

    if (regVal & SLEEP_ACK_4) {
        fprintf (
            outFilePrt,
            "\n  bit 4: sleep acknowledge timer enabled; auto-transition back from Sleep Request mode to Normal mode disabled during data transmission on MII or MDI");
    } else {
        fprintf (
            outFilePrt,
            "\n  bit 4: sleep acknowledge timer disabled; auto-transition back from Sleep Request mode to Normal mode enabled during data transmission on MII or MDI");
    }

    if (regVal & FWDPHYREM_2) {
        fprintf (outFilePrt, "\n  bit 2: wake-up event forwarded remotely ");
    } else {
        fprintf (outFilePrt, "\n  bit 2: wake-up event not forwarded remotely  ");
    }
    if (regVal & AUTO_PWD_1) {
        fprintf (outFilePrt, "\n  bit 1: autonomous power-down enabled ");
    } else {
        fprintf (outFilePrt, "\n  bit 1: autonomous power-down disabled ");
    }
    if (regVal & LPS_ACTIVE_0) {
        fprintf (outFilePrt, "\n  bit 0: automatic transition from Normal to Sleep Request when LPS code group received enabled ");
    } else {
        fprintf (outFilePrt, "\n  bit 0: automatic transition from Normal to Sleep Request when LPS code group received disabled ");
    }

    fprintf (outFilePrt, "\n");
    return res;
}
bool parse_symbol_error_counter_register (uint16_t regVal, FILE *outFilePrt) {
    (void) regVal;
    (void) outFilePrt;
    uint16_t sym_err_cnt = regVal;
    fprintf (outFilePrt, "\n The symbol error counter is incremented when an invalid code symbol is received (including idle symbols). The counter is incremented only once per packet, even when the received packet contains more than one symbol error. This counter increments up to 216. When the counter overflows, the value FFFFh is retained. The counter is reset when the register is read.");
    fprintf (outFilePrt, "\n bit 15:0 R sym_err_cnt [%u]",sym_err_cnt);
    fprintf (outFilePrt, "\n");
    return true;
}

bool parse_interrupt_status_register (uint16_t regVal, FILE *outFilePrt) {
    if (regVal & PWON_15) {
        fprintf (outFilePrt, "\n  bit 15: R power-on detected");
    } else {
        fprintf (outFilePrt, "\n  bit 15: R power-on not detected");
    }
    if (regVal & WAKEUP_14) {
        fprintf (outFilePrt, "\n  bit 14: R local or remote wake-up detected");
    } else {
        fprintf (outFilePrt, "\n  bit 14: R no local or remote wake-up detected");
    }
    if (regVal & WUR_RECEIVED_13) {
        fprintf (outFilePrt, "\n  bit 13: R dedicated wake-up request detected");
    } else {
        fprintf (outFilePrt, "\n  bit 13: R no dedicated wake-up request detected");
    }
    if (regVal & LPS_RECEIVED_12) {
        fprintf (outFilePrt, "\n  bit 12: R LPS code groups received");
    } else {
        fprintf (outFilePrt, "\n  bit 12: R no LPS code groups received");
    }
    if (regVal & PHY_INIT_FAIL_11) {
        fprintf (outFilePrt, "\n  bit 11: R PHY initialization error detected");
    } else {
        fprintf (outFilePrt, "\n  bit 11: R no PHY initialization error detected");
    }
    if (regVal & LINK_STATUS_FAIL_10) {
        fprintf (outFilePrt, "\n  bit 10: R link status bit LINK_UP changed from ‘link OK’ to ‘link fail’");
    } else {
        fprintf (outFilePrt, "\n  bit 10: R link status not changed");
    }
    if (regVal & LINK_STATUS_UP_9) {
        fprintf (outFilePrt, "\n  bit 9: R link status bit LINK_UP changed from ‘link fail’ to ‘link OK’");
    } else {
        fprintf (outFilePrt, "\n  bit 9: R link status not changed");
    }
    if (regVal & SYM_ERR_8) {
        fprintf (outFilePrt, "\n  bit 8: R symbol error detected");
    } else {
        fprintf (outFilePrt, "\n  bit 8: R no symbol error detected");
    }
    if (regVal & TRAINING_FAILED_7) {
        fprintf (outFilePrt, "\n  bit 7: R training phase failure detected");
    } else {
        fprintf (outFilePrt, "\n  bit 7: R no training phase failure detected");
    }
    if (regVal & SQI_WARNING_6) {
        fprintf (outFilePrt, "\n  bit 6: R SQI value below warning limit and bit LINK_UP set");
    } else {
        fprintf (outFilePrt, "\n  bit 6: R SQI value above warning limit");
    }
    if (regVal & CONTROL_ERR_5) {
        fprintf (outFilePrt, "\n  bit 5: R SMI control error detected");
    } else {
        fprintf (outFilePrt, "\n  bit 5: R no SMI control error detected");
    }
    if (regVal & UV_ERR_3) {
        fprintf (outFilePrt, "\n  bit 3: R undervoltage detected on VDD(IO), VDDD(3V3), VDDD(1V8) or VDDA(3V3);" );
    } else {
        fprintf (outFilePrt, "\n  bit 3: R no undervoltage detected");
    }
    if (regVal & UV_RECOVERY_2) {
        fprintf (outFilePrt, "\n  bit 2: R undervoltage recovery detected");
    } else {
        fprintf (outFilePrt, "\n  bit 2: R no undervoltage recovery detected");
    }
    if (regVal & TEMP_ERR_1) {
        fprintf (outFilePrt, "\n  bit 1: R overtemperature error detected");
    } else {
        fprintf (outFilePrt, "\n  bit 1: R no overtemperature error detected");
    }
    if (regVal & SLEEP_ABORT_0) {
        fprintf (outFilePrt, "\n  bit 0: R transition from Sleep Request back to Normal as a result of the Sleep Request timer expiring");
    } else {
        fprintf (outFilePrt, "\n  bit 0: R no transition from Sleep Request back to Normal as a result of the Sleep Request timer expiring");
    }
    fprintf (outFilePrt, "\n");
    return true;
}

bool parse_interrupt_source_register (uint16_t regVal, FILE *outFilePrt) {
    (void) regVal;
    (void) outFilePrt;
    fprintf (outFilePrt, "\nLack of detalisation ");
    fprintf (outFilePrt, "\n");
    return true;
}

bool parse_interrupt_enable_register (uint16_t regVal, FILE *outFilePrt) {
    (void) regVal;
    (void) outFilePrt;
    if (regVal & PWON_EN_15) {
        fprintf (outFilePrt, "\n  bit 15: RW PWON interrupt enabled");
    } else {
        fprintf (outFilePrt, "\n  bit 15: RW PWON interrupt disabled");
    }
    if (regVal & WAKEUP_EN_14) {
        fprintf (outFilePrt, "\n  bit 14: RW WAKEUP interrupt enabled");
    } else {
        fprintf (outFilePrt, "\n  bit 14: RW WAKEUP interrupt disabled");
    }
    if (regVal & WUR_RECEIVED_EN_13) {
        fprintf (outFilePrt, "\n  bit 13: RW WUR_RECEIVED interrupt enabled");
    } else {
        fprintf (outFilePrt, "\n  bit 13: RW WUR_RECEIVED interrupt disabled");
    }
    if (regVal & LPS_RECEIVED_EN_12) {
        fprintf (outFilePrt, "\n  bit 12: RW LPS_RECEIVED interrupt enabled");
    } else {
        fprintf (outFilePrt, "\n  bit 12: RW LPS_RECEIVED interrupt disabled");
    }
    if (regVal & PHY_INIT_FAIL_EN_11) {
        fprintf (outFilePrt, "\n  bit 11: RW PHY_INIT_FAIL interrupt enabled");
    } else {
        fprintf (outFilePrt, "\n  bit 11: RW LINK_STATUS_FAIL interrupt disabled");
    }
    if (regVal & LINK_STATUS_FAIL_EN_10) {
        fprintf (outFilePrt, "\n  bit 10: RW LINK_STATUS_FAIL interrupt enabled");
    } else {
        fprintf (outFilePrt, "\n  bit 10: RW LINK_STATUS_FAIL interrupt disabled");
    }
    if (regVal & LINK_STATUS_UP_EN_9) {
        fprintf (outFilePrt, "\n  bit  9: RW LINK_STATUS_UP interrupt enabled");
    } else {
        fprintf (outFilePrt, "\n  bit  9: RW LINK_STATUS_UP interrupt disabled");
    }
    if (regVal & SYM_ERR_EN_8) {
        fprintf (outFilePrt, "\n  bit  8: RW SYM_ERR interrupt enabled");
    } else {
        fprintf (outFilePrt, "\n  bit  8: RW SYM_ERR interrupt disabled");
    }
    if (regVal & TRAINING_FAILED_EN_7) {
        fprintf (outFilePrt, "\n  bit  7: RW TRAINING_FAILED interrupt enabled");
    } else {
        fprintf (outFilePrt, "\n  bit  7: RW TRAINING_FAILED interrupt disabled");
    }
    if (regVal & SQI_WARNING_EN_6) {
        fprintf (outFilePrt, "\n  bit  6: RW SQI_WARNING interrupt enabled");
    } else {
        fprintf (outFilePrt, "\n  bit  6: RW SQI_WARNING interrupt disabled");
    }
    if (regVal & CONTROL_ERR_EN_5) {
        fprintf (outFilePrt, "\n  bit  5: RW CONTROL_ERR interrupt enabled");
    } else {
        fprintf (outFilePrt, "\n  bit  5: RW CONTROL_ERR interrupt disabled");
    }
    if (regVal & UV_ERR_EN_3) {
        fprintf (outFilePrt, "\n  bit  3: RW UV_ERR interrupt enabled");
    } else {
        fprintf (outFilePrt, "\n  bit  3: RW UV_ERR interrupt disabled");
    }
    if (regVal & UV_RECOVERY_EN_2) {
        fprintf (outFilePrt, "\n  bit  2: RW UV_RECOVERY interrupt enabled");
    } else {
        fprintf (outFilePrt, "\n  bit  2: RW UV_RECOVERY interrupt disabled");
    }
    if (regVal & TEMP_ERR_EN_1) {
        fprintf (outFilePrt, "\n  bit  1: RW TEMP_ERR interrupt enabled");
    } else {
        fprintf (outFilePrt, "\n  bit  1: RW TEMP_ERR interrupt disabled");
    }
    if (regVal & SLEEP_ABORT_EN_0) {
        fprintf (outFilePrt, "\n  bit  0: RW SLEEP_ABORT interrupt enabled");
    } else {
        fprintf (outFilePrt, "\n  bit  0: RW SLEEP_ABORT interrupt disabled");
    }

    fprintf (outFilePrt, "\n");
    return true;
}
bool parse_general_status_register (uint16_t regVal, FILE *outFilePrt) {

    if (regVal & INT_STATUS_15) {
        fprintf (outFilePrt, "\n  bit 15  R unmasked interrupt pending");
    } else {
        fprintf (outFilePrt, "\n  bit 15 R all interrupts cleared");
    }
    if (regVal & PLL_LOCKED_14) {
        fprintf (outFilePrt, "\n  bit 14 R PLL stable and locked");
    } else {
        fprintf (outFilePrt, "\n  bit 14 R PLL unstable and not locked");
    }
    if (regVal & LOCAL_WU_13) {
        fprintf (outFilePrt, "\n  bit 13 R local wake-up detected");
    } else {
        fprintf (outFilePrt, "\n  bit 13 R no local wake-up detected");
    }
    if (regVal & REMOTE_WU_12) {
        fprintf (outFilePrt, "\n  bit 12 R remote wake-up detected");
    } else {
        fprintf (outFilePrt, "\n  bit 12 R no remote wake-up detected");
    }
    if (regVal & DATA_DET_WU_11) {
        fprintf (outFilePrt, "\n  bit 11  R 100BASE-T1 data detected at MDI (pcs_rx_dv = TRUE; see Ref. 1) or MII (TXEN = 1) in Sleep Request mode");
    } else {
        fprintf (outFilePrt, "\n  bit 11 R no 100BASE-T1 data detected at MDI or MII in Sleep Request mode");
    }
    if (regVal & EN_STATUS_10) {
        fprintf (outFilePrt, "\n  bit 10 R EN switched LOW since register last read");
    } else {
        fprintf (outFilePrt, "\n  bit 10 R EN HIGH");
    }
    if (regVal & RESET_STATUS_9) {
        fprintf (outFilePrt, "\n  bit 9 R hardware reset detected since register last read");
    } else {
        fprintf (outFilePrt, "\n  bit 9 R no hardware reset detected");
    }
    fprintf (outFilePrt, "\n  bit 8 R reserved");
    uint16_t linkFailCnt = extract_subval_from_16bit (regVal, 7, 3);
    fprintf (outFilePrt, "\n  bit 7:3 R linkFailCnt: [%u]", linkFailCnt);
    fprintf (outFilePrt, "\n  bit 2:0 R reserved");
    fprintf (outFilePrt, "\n");
    return true;
}
bool parse_external_status_register (uint16_t regVal, FILE *outFilePrt) {
    if (regVal & UV_VDDD_3V3_15) {
        fprintf (outFilePrt, "\n  bit 15: R undervoltage detected on pin VDDD(3V3)");
    } else {
        fprintf (outFilePrt, "\n  bit 15: R no undervoltage detected on pin VDDD(3V3)");
    }
    if (regVal & UV_VDDA_3V3_14) {
        fprintf (outFilePrt, "\n  bit 14: R undervoltage detected on pin VDDA(3V3)");
    } else {
        fprintf (outFilePrt, "\n  bit 14: R no undervoltage detected on pin VDDA(3V3)");
    }
    if (regVal & UV_VDDD_1V8_13) {
        fprintf (outFilePrt, "\n  bit 13: R undervoltage detected on pin VDDD(1V8)");
    } else {
        fprintf (outFilePrt, "\n  bit 13: R no undervoltage detected on pin VDDD(1V8)");
    }
    if (regVal & UD_VDDIO_11) {
        fprintf (outFilePrt, "\n  bit 11: R undervoltage detected on pin VDD(IO)");
    } else {
        fprintf (outFilePrt, "\n  bit 11: R no undervoltage detected on pin VDD(IO)");
    }
    if (regVal & TEMP_HIGH_10) {
        fprintf (outFilePrt, "\n  bit 10: R temperature above high level");
    } else {
        fprintf (outFilePrt, "\n  bit 10: R temperature below high level");
    }
    if (regVal & TEMP_WARN_9) {
        fprintf (outFilePrt, "\n  bit 9: R temperature above warning level");
    } else {
        fprintf (outFilePrt, "\n  bit 9: R temperature below warning level");
    }
    if (regVal & SHORT_DETECT_8) {
        fprintf (outFilePrt, "\n  bit 8: R short circuit detected since register last read");
    } else {
        fprintf (outFilePrt, "\n  bit 8: R no short circuit detected");
    }
    if (regVal & OPEN_DETECT_7) {
        fprintf (outFilePrt, "\n  bit 7: R open circuit detected since register last read");
    } else {
        fprintf (outFilePrt, "\n  bit 7: R no open circuit detected");
    }
    if (regVal & POLARITY_DETECT_6) {
        fprintf (outFilePrt, "\n  bit 6: R polarity inversion detected at MDI");
    } else {
        fprintf (outFilePrt, "\n  bit 6: R no polarity inversion detected at MDI");
    }
    if (regVal & INTERLEAVE_DETECT_5) {
        fprintf (outFilePrt, "\n  bit 5: R interleave order of detected ternary symbols: TBn, TAn");
    } else {
        fprintf (outFilePrt, "\n  bit 5: R interleave order of detected ternary symbols: TAn, TBn");
    }
    fprintf (outFilePrt, "\n");
    return true;
}

bool parse_link_fail_counter_register (uint16_t regVal, FILE *outFilePrt) {
    uint16_t loc_rcvr_cnt = extract_subval_from_16bit (regVal, 15, 8);
    fprintf (
        outFilePrt,
        "\n  bit 15:8 R [%u] The counter is incremented when local receiver is NOT_OK; when the counter overflows, the value FFh is retained. The counter is reset when the register is read.",
        loc_rcvr_cnt);
    uint16_t rem_rcvr_cnt = extract_subval_from_16bit (regVal, 7, 0);
    fprintf (
        outFilePrt,
        "\n  bit 7:0  R [%u] The counter is incremented when remote receiver is NOT_OK; when the counter overflows, the value FFh is retained. The counter is reset when the register is read.",
        rem_rcvr_cnt);
    fprintf (outFilePrt, "\n");
    return true;
}
bool parse_common_configuration_register (uint16_t regVal, FILE *outFilePrt) {
    bool res = false;
    if (regVal & AUTO_OP_15) {
        fprintf (outFilePrt, "\n  bit 15: R/W autonomous operation");
    } else {
        fprintf (outFilePrt, "\n  bit 15: R/W managed operation");
    }
    uint16_t clkMode = extract_subval_from_16bit (regVal, 13, 12);
    res = parse_clk_mode (clkMode, outFilePrt);
    if (regVal & LDO_MODE_11) {
        fprintf (outFilePrt, "\n  bit 11: R/W external 1.8 V supply");
    } else {
        fprintf (outFilePrt, "\n  bit 11: R/W internal 1.8 V LDO enabled");
    }
    if (regVal & CLK_DRIVER_10) {
        fprintf (outFilePrt, "\n  bit 10:  R/W reduced output driver strength at output of CLK_IN_OUT ");
    } else {
        fprintf (outFilePrt, "\n  bit 10:  R/W standard output driver strength at output of CLK_IN_OUT");
    }
    if (regVal & CLK_HOLD_9) {
        fprintf (outFilePrt, "\n  bit 9: R/W XTAL and CLK_IN_OUT output remain active until device switched to Sleep mode via SMI");
    } else {
        fprintf (outFilePrt, "\n  bit 9: R/W XTAL and CLK_IN_OUT output switched off in Sleep mode");
    }
    uint16_t loc_wu_tim = extract_subval_from_16bit (regVal, 8, 7);
    res = parse_loc_wu_tim (loc_wu_tim, outFilePrt);

    if (regVal & CONFIG_WAKE_6) {
        fprintf (outFilePrt, "\n  bit 6: R/W ratiometric input threshold (VDD(IO))");
    } else {
        fprintf (outFilePrt, "\n  bit 6: R/W absolute input threshold");
    }
    if (regVal & CONFIG_INH_5) {
        fprintf (outFilePrt, "\n  bit 5:  R/W INH switched on in Disable mode");
    } else {
        fprintf (outFilePrt, "\n  bit 5:  R/W INH switched off in Disable mode");
    }
    fprintf (outFilePrt, "\n  bit 4:0:  R/W reserved");
    fprintf (outFilePrt, "\n");
    return res;
}

bool parse_phy_state (uint8_t phyState, FILE *outFilePrt) {
    bool res = false;
    switch (phyState) {
        case 0:
            fprintf (outFilePrt, "\n  bit 2..0: r PHY Idle");
            break;
        case 1:
            fprintf (outFilePrt, "\n  bit 2..0: r PHY Initializing");
            break;
        case 2:
            fprintf (outFilePrt, "\n  bit 2..0: r PHY Configured");
            break;
        case 3:
            fprintf (outFilePrt, "\n  bit 2..0: r PHY Offline");
            break;
        case 4:
            fprintf (outFilePrt, "\n  bit 2..0: r PHY Active");
            break;
        case 5:
            fprintf (outFilePrt, "\n  bit 2..0: r PHY Isolate");
            break;
        case 6:
            fprintf (outFilePrt, "\n  bit 2..0: r PHY Cable test");
            break;
        case 7:
            fprintf (outFilePrt, "\n  bit 2..0: r PHY Test mode");
            break;
        default:
            fprintf (outFilePrt, "\n  bit 2..0: r PHY Test mode");
            break;
    }
    return res;
}

bool parse_sqi (uint8_t sqi, FILE *outFilePrt) {
    bool res = false;
    switch (sqi) {
        case 0:
            fprintf (outFilePrt, "\n  bit 7..5: r worse than class A SQI (unstable link)");
            break;
        case 1:
            fprintf (outFilePrt, "\n  bit 7..5: r class A SQI (unstable link)");
            break;
        case 2:
            fprintf (outFilePrt, "\n  bit 7..5: r class B SQI (unstable link)");
            break;
        case 3:
            fprintf (outFilePrt, "\n  bit 7..5: r class C SQI (good link)");
            break;
        case 4:
            fprintf (outFilePrt, "\n  bit 7..5: r class D SQI (good link; bit error rate < 1e-10)");
            break;
        case 5:
            fprintf (outFilePrt, "\n  bit 7..5: r class E SQI (good link)");
            break;
        case 6:
            fprintf (outFilePrt, "\n  bit 7..5: r class F SQI (very good link)");
            break;
        case 7:
            fprintf (outFilePrt, "\n  bit 7..5: r class G SQI (very good link)");
            break;
        default:
            fprintf (outFilePrt, "\n  bit 2..0: r Error");
            break;
    }
    return res;
}

bool parse_mii_mode (uint8_t mii_mode, FILE *outFilePrt) {
    bool res = false;
    switch (mii_mode) {
        case 0:
            fprintf (outFilePrt, "\n  bit 9:8: RW MII mode enabled");
            break;
        case 1:
            fprintf (outFilePrt, "\n  bit 9:8: RW RMII mode enabled (50 MHz input on REF_CLK)");
            break;
        case 2:
            fprintf (outFilePrt, "\n  bit 9:8: RW RMII mode enabled (50 MHz output on REF_CLK)");
            break;
        case 3:
            fprintf (outFilePrt, "\n  bit 9:8: RW Reverse MII mode");
            break;
        default:
            fprintf (outFilePrt, "\n  bit 9:8: RW Error");
            break;
    }
    return res;
}

bool parse_clk_mode (uint8_t clk_mode, FILE *outFilePrt) {
    bool res = false;
    switch (clk_mode) {
        case 0:
            fprintf (outFilePrt, "\n  bit 13:12 RW 25 MHz XTAL; no clock at CLK_IN_OUT");
            break;
        case 1:
            fprintf (outFilePrt, "\n  bit 13:12 RW 25 MHz XTAL; 25 MHz output at CLK_IN_OUT");
            break;
        case 2:
            fprintf (outFilePrt, "\n  bit 13:12 RW 25 MHz external clock at CLK_IN_OUT");
            break;
        case 3:
            fprintf (outFilePrt, "\n  bit 13:12 RW 50 MHz input at REF_CLK; RMII mode only; no XTAL; no clock at CLK_IN_OUT");
            break;
        default:
            fprintf (outFilePrt, "\n  bit 13:12 RW ");
            break;
    }
    return res;
}

bool parse_loc_wu_tim (uint8_t loc_wu_tim, FILE *outFilePrt) {
    bool res = false;
    switch (loc_wu_tim) {
        case 0:
            fprintf (outFilePrt, "\n  bit 8:7 RW local wake-up timer: longest (10 ms to 20 ms)");
            break;
        case 1:
            fprintf (outFilePrt, "\n  bit 8:7 RW local wake-up timer: long (250 us to 500 s)");
            break;
        case 2:
            fprintf (outFilePrt, "\n  bit 8:7 RW local wake-up timer: short (100 us to 200 s)");
            break;
        case 3:
            fprintf (outFilePrt, "\n  bit 8:7 RW local wake-up timer: shortest (10 us to 40 s)");
            break;
    }
    return res;
}
