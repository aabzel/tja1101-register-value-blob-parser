#include "parse_tja1101_regs.h"

#include "convert.h"
#include "str_ops.h"
#include "tja1101_bits_offsets.h"
#include "utils.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern regTJA1101_t tja1101RegMap[TJA1101_REG_NUM];

bool parse_tja1101_regs_file (char *inFileName, char *outFileName) {
    printf ("\n%s()\n", __FUNCTION__);
    char curFileStr[500];
    bool res = false;
    FILE *inFilePrt = NULL;
    FILE *out_file_prt = NULL;
    inFilePrt = fopen (inFileName, "r");
    out_file_prt = fopen (outFileName, "w");
    uint16_t reg_cnt = 0;
    if (inFilePrt && out_file_prt) {

        int line = 0;
        while (NULL != fgets (curFileStr, sizeof (curFileStr), inFilePrt)) {
            uint8_t reg_addr;
            uint16_t reg16b_val;
            // printf ("\nFile line :<%s>", curFileStr);

            res = parse_8bit_reg_addr (curFileStr, strlen (curFileStr) - 1, &reg_addr);
            if (true == res) {
                res = parse_16bit_val (curFileStr, strlen (curFileStr) - 1, &reg16b_val);
                if (true == res) {
                    res = parse_tja1101_reg (reg_addr, reg16b_val, out_file_prt);
                    if (true == res) {
                        reg_cnt++;
                    } else {
                        printf ("\n%s(): parse phy reg [%u] error", __FUNCTION__, reg_addr);
                    }
                } else {
                    printf ("\n%s(): parse reg 16bit value from [%s] error", __FUNCTION__, curFileStr);
                }
            } else {
                printf ("\n%s(): Unable to parse reg 8bit address from [%s]", __FUNCTION__, curFileStr);
            }
            // printf ("\n[%x] [%x]", reg_addr, reg16b_val);
            line++;
        }
        fprintf (out_file_prt, "\n\n Support: aabzele@gmail.com");
        fclose (inFilePrt);
        fclose (out_file_prt);
        res = true;
    }
    printf ("\n%s(): processed registers %u/32 \n", __FUNCTION__, reg_cnt);
    return res;
}



static bool parse_basic_control_register (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    if (reg16b_val & RESET_BIT_15) {
        fprintf (out_file_prt, "\n  reg %02u bit15: RW PHY reset", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit15: RW normal operation", reg_addr);
    }
    if (reg16b_val & LOOPBACK_14) {
        fprintf (out_file_prt, "\n  reg %02u bit14: RW PHY reset", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit14: RW normal operation", reg_addr);
    }

    if (reg16b_val & SPEED_SELECT_13) {
        fprintf (out_file_prt, "\n  reg %02u bit13: RW 100 Mbit/s if SPEED_SELECT (MSB) = 0 reserved if SPEED_SELECT (MSB) = 1", reg_addr);
    } else {
        fprintf (out_file_prt,
                 "\n  reg %02u bit 13: RW 10 Mbit/s if SPEED_SELECT (MSB) = 0 1000 Mbit/s if SPEED_SELECT (MSB) = 1", reg_addr);
    }

    if (reg16b_val & AUTONEG_EN_12) {
        fprintf (out_file_prt, "\n  reg %02u bit12: RW Error", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit12: RW Auto negotiation not supported; always 0; a write access is ignored ", reg_addr);
    }

    if (reg16b_val & POWER_DOWN_11) {
        fprintf (out_file_prt, "\n  reg %02u bit11: RW power down and switch to Standby mode (provided ISOLATE = 0; ignored if "
                             "ISOLATE = 1 and CONTROL_ERR interrupt generated) ", reg_addr);
    } else {
        fprintf (out_file_prt,
                 "\n  reg %02u bit 11:RW  normal operation (clearing this bit automatically triggers a transition to Normal "
                 "mode, provided control bits POWER_MODE are set to 0011 Normal mode, see Table 18) ", reg_addr);
    }

    if (reg16b_val & ISOLATE_10) {
        fprintf (out_file_prt, "\n  reg %02u bit10: RW isolate PHY from MII/RMII (provided POWER_DOWN = 0; ignored if POWER_DOWN "
                             "= 1 and CONTROL_ERR interrupt generated) ", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit10: RW normal operation ", reg_addr);
    }

    if (reg16b_val & RE_AUTONEG_9) {
        fprintf (out_file_prt, "\n  reg %02u bit9: RW Error ", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit9:  RW Auto negotiation not supported; always 0; a write access is ignored.", reg_addr);
    }

    if (reg16b_val & DUPLEX_MODE_8) {
        fprintf (out_file_prt, "\n  reg %02u bit8: RW  only full duplex supported; always 1; a write access is ignored ", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit8: RW  Error ", reg_addr);
    }

    if (reg16b_val & COLLISION_TEST_7) {
        fprintf (out_file_prt, "\n  reg %02u bit7: RW  error! ", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit7: RW  COL signal test not supported; always 0; a write access is ignored ", reg_addr);
    }

    if (reg16b_val & SPEED_SELECT_6) {
        fprintf (out_file_prt, "\n  reg %02u bit6: RW 1000 Mbit/s if SPEED_SELECT (LSB) = 0 reserved if SPEED_SELECT (LSB) = 1", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit6: RW 10 Mbit/s if SPEED_SELECT (LSB) = 0 100 Mbit/s if SPEED_SELECT (LSB) = 1 ", reg_addr);
    }
    if (reg16b_val & UNIDIRECT_EN_5) {
        fprintf (out_file_prt, "\n  reg %02u bit5: RW enable transmit from MII regardless of whether the PHY has determined that "
                             "a valid link has been established", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit5: RW enable transmit from MII only when the PHY has determined that a valid "
                             "link has been established ", reg_addr);
    }
    fprintf (out_file_prt, "\n");
    return res;
}

static bool parse_basic_status_register (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr)  {
    bool res = false;
    if (reg16b_val & S100BASE_T4_15) {
        fprintf (out_file_prt, "\n  reg %02u bit 15: PHY able to perform 100BASE-T4 ",reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit15: PHY not able to perform 100BASE-T4 ", reg_addr);
    }
    if (reg16b_val & S100BASE_X_FD_14) {
        fprintf (out_file_prt, "\n  reg %02u bit14: PHY able to perform 100BASE-X full-duplex ", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit14: PHY not able to perform 100BASE-X full-duplex", reg_addr);
    }
    if (reg16b_val & S100BASE_X_HD_13) {
        fprintf (out_file_prt, "\n  reg %02u bit13: PHY able to perform 100BASE-X half-duplex ", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit13: PHY not able to perform 100BASE-X half-duplex ", reg_addr);
    }
    if (reg16b_val & S10Mbps_FD_12) {
        fprintf (out_file_prt, "\n  reg %02u bit12: PHY able to perform 10 Mbit/s full-duplex ", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit12: PHY not able to perform 10 Mbit/s full-duplex ", reg_addr);
    }
    if (reg16b_val & S10Mbps_HD_11) {
        fprintf (out_file_prt, "\n  reg %02u bit11: PHY able to perform 10 Mbit/s half-duplex ", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit11: PHY not able to perform 10 Mbit/s half-duplex ", reg_addr);
    }
    if (reg16b_val & S100BASE_T2_FD_10) {
        fprintf (out_file_prt, "\n  reg %02u bit10: PHY able to perform 100BASE-T2 full-duplex", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit10: PHY not able to perform 100BASE-T2 full-duplex", reg_addr);
    }
    if (reg16b_val & S100BASE_T2_HD_9) {
        fprintf (out_file_prt, "\n  reg %02u bit9: PHY able to perform 100BASE-T2 half-duplex", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit9: PHY not able to perform 100BASE-T2 half-duplex", reg_addr);
    }
    if (reg16b_val & EXTENDED_STATUS_8) {
        fprintf (out_file_prt, "\n  reg %02u bit8: extended status information in register 15h", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit8: no extended status information in register 15h", reg_addr);
    }
    if (reg16b_val & UNIDIRECT_ABILITY_7) {
        fprintf (out_file_prt, "\n  reg %02u bit7: PHY able to transmit from MII regardless of whether the PHY has determined "
                             "that a valid link has been established", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit7: PHY able to transmit from MII only when the PHY has determined that a valid "
                             "link has been established", reg_addr);
    }
    if (reg16b_val & MF_PREAMBLE_SUPPRESSION_6) {
        fprintf (out_file_prt, "\n  reg %02u bit6: PHY will accept management frames with preamble suppressed", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit6: PHY will not accept management frames with preamble suppressed", reg_addr);
    }
    if (reg16b_val & AUTONEG_COMPLETE_5) {
        fprintf (out_file_prt, "\n  reg %02u bit5: Autonegotiation process completed", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit5: Autonegotiation process not completed", reg_addr);
    }
    if (reg16b_val & REMOTE_FAULT_4) {
        fprintf (out_file_prt, "\n  reg %02u bit4: remote fault condition detected", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit4: no remote fault condition detected", reg_addr);
    }
    if (reg16b_val & AUTONEG_ABILITY_3) {
        fprintf (out_file_prt, "\n  reg %02u bit3: PHY able to perform Autonegotiation", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit3: PHY not able to perform Autonegotiation", reg_addr);
    }
    if (reg16b_val & LINK_STATUS_2) {
        fprintf (out_file_prt, "\n  reg %02u bit2: link is up", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit2: link is down", reg_addr);
    }
    if (reg16b_val & JABBER_DETECT_1) {
        fprintf (out_file_prt, "\n  reg %02u bit1: jabber condition detected", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit1: no jabber condition detected", reg_addr);
    }
    if (reg16b_val & EXTENDED_CAPABILITY_0) {
        fprintf (out_file_prt, "\n  reg %02u bit0: extended register capabilities", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit0: basic register set capabilities only", reg_addr);
    }
    fprintf (out_file_prt, "\n");
    return res;
}

static bool parse_phy_identifier_1_register (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr)  {
    bool res = false;
    fprintf (out_file_prt, "\n  reg %02u bit15..0: Organizationally Unique Identifier 0x%04x",reg_addr, reg16b_val);
    fprintf (out_file_prt, "\n");
    return res;
}

static bool parse_phy_identifier_2_register (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr)  {
    bool res = false;
    uint8_t phyId = extract_subval_from_16bit (reg16b_val, 15, 10);
    fprintf (out_file_prt, "\n  reg %02u bit15..10: phyId 0x%02x (19 to 24 of the OUI)",reg_addr, phyId);
    uint8_t typeNo = extract_subval_from_16bit (reg16b_val, 9, 4);
    fprintf (out_file_prt, "\n  reg %02u bit9..4: manufacturer type number 0x%02x",reg_addr, typeNo);
    uint8_t revNo = extract_subval_from_16bit (reg16b_val, 3, 0);
    fprintf (out_file_prt, "\n  reg %02u bit3..0: manufacturer  revision number 0x%02x",reg_addr, revNo);
    fprintf (out_file_prt, "\n");
    return res;
}

static bool parse_extended_status_register (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr)  {
    bool res = false;
    if (reg16b_val & S1000BASE_X_FD_15) {
        fprintf (out_file_prt, "\n  reg %02u bit15: PHY able to perform 1000BASE-X full-duplex", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit15: PHY not able to perform 1000BASE-X full-duplex", reg_addr);
    }
    if (reg16b_val & S1000BASE_X_HD_14) {
        fprintf (out_file_prt, "\n  reg %02u bit14: PHY able to perform 1000BASE-X half-duplex", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit14: PHY not able to perform 1000BASE-X half-duplex ", reg_addr);
    }
    if (reg16b_val & S1000BASE_T_FD_13) {
        fprintf (out_file_prt, "\n  reg %02u bit13: PHY able to perform 1000BASE-T full-duplex", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit13: PHY not able to perform 1000BASE-T full-duplex", reg_addr);
    }
    if (reg16b_val & S1000BASE_T_HD_12) {
        fprintf (out_file_prt, "\n  reg %02u bit12: PHY able to perform 1000BASE-T half-duplex", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit12: PHY not able to perform 1000BASE-T half-duplex", reg_addr);
    }
    if (reg16b_val & S100BASE_T1_7) {
        fprintf (out_file_prt, "\n  reg %02u bit7: PHY able to 1-pair 100BASE-T1 100 Mbit/s", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit7: PHY not able to 1-pair 100BASE-T1 100 Mbit/s", reg_addr);
    }
    if (reg16b_val & S1000BASE_RTPGE_6) {
        fprintf (out_file_prt, "\n  reg %02u bit6: PHY supports RTPGE", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit6: PHY not able to support RTPGE", reg_addr);
    }
    fprintf (out_file_prt, "\n");

    return res;
}

static bool parse_power_mode (uint8_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    switch (reg16b_val) {
    case 0:
        fprintf (out_file_prt, "\n  reg %02u bit14..11: operating mode: no change", reg_addr);
        break;
    case 3:
        fprintf (out_file_prt, "\n  reg %02u bit14..11: operating mode: Normal mode (command)", reg_addr);
        break;
    case 9:
        fprintf (out_file_prt, "\n  reg %02u bit14..11: Silent mode (read only)", reg_addr);
        break;
    case 10:
        fprintf (out_file_prt, "\n  reg %02u bit14..11: Sleep mode (read only)", reg_addr);
        break;
    case 11:
        fprintf (out_file_prt, "\n  reg %02u bit14..11: Sleep Request mode (command)", reg_addr);
        break;
    case 12:
        fprintf (out_file_prt, "\n  reg %02u bit14..11: Standby mode (command)", reg_addr);
        break;
    default:
        fprintf (out_file_prt, "\n  reg %02u bit14..11: Error", reg_addr);
        break;
    }
    return res;
}

static bool parse_test_mode (uint8_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    switch (reg16b_val) {
    case 0:
        fprintf (out_file_prt, "\n  reg %02u bit8..6: R/W test mode selection: no test mode", reg_addr);
        break;
    case 1:
        fprintf (out_file_prt, "\n  reg %02u bit8..6: R/W test mode selection 100BASE-T1 test mode 1", reg_addr);
        break;
    case 2:
        fprintf (out_file_prt, "\n  reg %02u bit8..6: R/W test mode selection 100BASE-T1 test mode 2 ", reg_addr);
        break;
    case 3:
        fprintf (out_file_prt, "\n  reg %02u bit8..6: R/W test mode selection test mode 3", reg_addr);
        break;
    case 4:
        fprintf (out_file_prt, "\n  reg %02u bit8..6: R/W test mode selection 100BASE-T1 test mode 4", reg_addr);
        break;
    case 5:
        fprintf (out_file_prt, "\n  reg %02u bit8..6: R/W test mode selection 100BASE-T1 test mode 5", reg_addr);
        break;
    case 6:
        fprintf (out_file_prt, "\n  reg %02u bit8..6: R/W test mode selection scrambler and descrambler bypassed", reg_addr);
        break;
    case 7:
        fprintf (out_file_prt, "\n  reg %02u bit8..6: R/W test mode selection reserved", reg_addr);
        break;
    default:
        fprintf (out_file_prt, "\n  reg %02u bit8..6: R/W Error", reg_addr);
        break;
    }
    return res;
}

static bool parse_loopback_mode (uint8_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    switch (reg16b_val) {
    case 0:
        fprintf (out_file_prt, "\n  reg %02u bit4..3: R/W internal loopback", reg_addr);
        break;
    case 1:
        fprintf (out_file_prt, "\n  reg %02u bit4..3: R/W external loopback", reg_addr);
        break;
    case 2:
        fprintf (out_file_prt, "\n  reg %02u bit4..3: R/W external loopback", reg_addr);
        break;
    case 3:
        fprintf (out_file_prt, "\n  reg %02u bit4..3: R/W remote loopback", reg_addr);
        break;

    default:
        fprintf (out_file_prt, "\n  reg %02u bit4..3: R/W Error", reg_addr);
        break;
    }
    return res;
}

static bool parse_extended_control_register (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr)  {
    bool res = false;
    if (reg16b_val & LINK_CONTROL_15) {
        fprintf (out_file_prt, "\n  reg %02u bit15: link control enabled", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit15: link control disabled", reg_addr);
    }
    uint16_t powerMode = extract_subval_from_16bit (reg16b_val, 14, 11);
    res = parse_power_mode (powerMode, out_file_prt, reg_addr);
    if (reg16b_val & SLAVE_JITTER_TEST_10) {
        fprintf (out_file_prt, "\n  reg %02u bit10: enable Slave jittet test", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit10: disable Slave jitter test", reg_addr);
    }
    if (reg16b_val & TRAINING_RESTART_9) {
        fprintf (out_file_prt, "\n  reg %02u bit9: forces a restart of the training phase", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit9: halts the training phase", reg_addr);
    }
    uint16_t testMode = extract_subval_from_16bit (reg16b_val, 8, 6);
    res = parse_test_mode (testMode, out_file_prt, reg_addr);

    if (reg16b_val & CABLE_TEST_5) {
        fprintf (out_file_prt, "\n  reg %02u bit5: forces TDR-based cable test", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit5: stops TDR-based cable test", reg_addr);
    }
    uint16_t loopbackMode = extract_subval_from_16bit (reg16b_val, 4, 3);
    res = parse_loopback_mode (loopbackMode, out_file_prt, reg_addr);
    if (reg16b_val & CONFIG_EN_2) {
        fprintf (out_file_prt, "\n  reg %02u bit2: configuration register access enabled", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit2: configuration register access disabled", reg_addr);
    }
    fprintf (out_file_prt, "\n");

    return res;
}



bool parse_phy_state (uint8_t phyState, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    switch (phyState) {
    case 0:
        fprintf (out_file_prt, "\n  reg %02u bit2..0: r PHY Idle", reg_addr);
        break;
    case 1:
        fprintf (out_file_prt, "\n  reg %02u bit2..0: r PHY Initializing", reg_addr);
        break;
    case 2:
        fprintf (out_file_prt, "\n  reg %02u bit2..0: r PHY Configured", reg_addr);
        break;
    case 3:
        fprintf (out_file_prt, "\n  reg %02u bit2..0: r PHY Offline", reg_addr);
        break;
    case 4:
        fprintf (out_file_prt, "\n  reg %02u bit2..0: r PHY Active", reg_addr);
        break;
    case 5:
        fprintf (out_file_prt, "\n  reg %02u bit2..0: r PHY Isolate", reg_addr);
        break;
    case 6:
        fprintf (out_file_prt, "\n  reg %02u bit2..0: r PHY Cable test", reg_addr);
        break;
    case 7:
        fprintf (out_file_prt, "\n  reg %02u bit2..0: r PHY Test mode", reg_addr);
        break;
    default:
        fprintf (out_file_prt, "\n  reg %02u bit2..0: r PHY Test mode", reg_addr);
        break;
    }
    return res;
}


static bool parse_configuration_register_2 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr)  {
    bool res = false;
    uint16_t phyAddr = extract_subval_from_16bit (reg16b_val, 15, 11);
    fprintf (out_file_prt, "\n  reg %02u bit15..11: r 5bit PHY address: [%d]", reg_addr,phyAddr);
    if (reg16b_val & JUMBO_ENABLE_2) {
        fprintf (out_file_prt, "\n  reg %02u bit2: rw packets up to 16 kB supported", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit2: rw packets up to 4 kB supported", reg_addr);
    }
    fprintf (out_file_prt, "\n");
    return res;
}

static bool parse_communication_status_register (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr)  {
    bool res;
    if (reg16b_val & LINK_UP_15) {
        fprintf (out_file_prt, "\n  reg %02u bit15: r link OK", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit15: r link failure", reg_addr);
    }
    if (reg16b_val & LOC_RCVR_STATUS_12) {
        fprintf (out_file_prt, "\n  reg %02u bit12: r local receiver OK", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit12: r local receiver not OK", reg_addr);
    }
    if (reg16b_val & REM_RCVR_STATUS_11) {
        fprintf (out_file_prt, "\n  reg %02u bit11: r remote receiver OK", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit11: r remote receiver not OK", reg_addr);
    }
    if (reg16b_val & SCR_LOCKED_10) {
        fprintf (out_file_prt, "\n  reg %02u bit10: r descrambler locked", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit10: r descrambler unlocked", reg_addr);
    }
    if (reg16b_val & SSD_ERR_9) {
        fprintf (out_file_prt, "\n  reg %02u bit9: r SSD error detected", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit9: r no SSD error detected", reg_addr);
    }
    if (reg16b_val & ESD_ERR_8) {
        fprintf (out_file_prt, "\n  reg %02u bit8: r ESD error detected", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit8: r no ESD error detected", reg_addr);
    }
    uint16_t sqi = extract_subval_from_16bit (reg16b_val, 7, 5);
    res = parse_sqi (sqi, out_file_prt ,reg_addr);
    if (reg16b_val & RECEIVE_ERR_4) {
        fprintf (out_file_prt, "\n  reg %02u bit4: r receive error detected since register last read", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit4: r no receive error detected", reg_addr);
    }
    if (reg16b_val & TRANSMIT_ERR_3) {
        fprintf (out_file_prt, "\n  reg %02u bit3: r transmit error detected since register last read", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit3: r no transmit error detected", reg_addr);
    }
    uint16_t phyState = extract_subval_from_16bit (reg16b_val, 2, 0);
    res = parse_phy_state (phyState, out_file_prt , reg_addr);
    fprintf (out_file_prt, "\n");
    return res;
}

static bool parse_configuration_register_3 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr)  {
    fprintf (out_file_prt, "\n  reg %02u bit15:2: RW reserved", reg_addr);
    if (reg16b_val & FORCE_SLEEP_1) {
        fprintf (out_file_prt, "\n  reg %02u bit1: RW force PHY to Sleep mode", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit1: RW forced sleep inactive", reg_addr);
    }
    fprintf (out_file_prt, "\n  reg %02u bit0: RW write 1; ignore on read", reg_addr);

    fprintf (out_file_prt, "\n");
    return true;
}
static bool parse_phy_identifier_3_register (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr)  {
    (void)reg16b_val;
    (void)out_file_prt;
    fprintf (out_file_prt, "\n  reg %02u Lack of detalisation in datasheet", reg_addr);
    fprintf (out_file_prt, "\n");
    return true;
}
static bool parse_configuration_register_1 (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr)  {
    bool res = false;
    (void)out_file_prt;
    if (reg16b_val & MASTER_SLAVE_15) {
        fprintf (out_file_prt, "\n  reg %02u bit15: rw PHY configured as Master", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit15: rw PHY configured as Slave", reg_addr);
    }
    if (reg16b_val & FWDPHYLOC_14) {
        fprintf (out_file_prt, "\n  reg %02u bit14: rw wake-up event forwarded locally", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit14: rw wake-up event not forwarded locally", reg_addr);
    }
    if (reg16b_val & REMWUPHY_11) {
        fprintf (out_file_prt, "\n  reg %02u bit11: rw PHY reacts to a remote wake-up", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit11: rw PHY does not react to a remote wake-up", reg_addr);
    }
    if (reg16b_val & LOCWUPHY_10) {
        fprintf (out_file_prt, "\n  reg %02u bit14: rw PHY reacts to a local wake-up", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit14: rw PHY does not react to a local wake-up", reg_addr);
    }
    uint16_t mii_mode = extract_subval_from_16bit (reg16b_val, 9, 8);
    res = parse_mii_mode (mii_mode, out_file_prt,reg_addr );
    if (reg16b_val & MII_DRIVER_7) {
        fprintf (out_file_prt, "\n  reg %02u bit7: rw MII output driver reduced strength", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit7: MII output driver standard strength", reg_addr);
    }
    if (reg16b_val & SLEEP_CONFIRM_6) {
        fprintf (out_file_prt, "\n  reg %02u bit6: confirmation needed from another PHY before going to sleep", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit6: no confirmation needed from another PHY before going to sleep", reg_addr);
    }

    if (reg16b_val & LPS_WUR_DIS_5) {
        fprintf (out_file_prt, "\n  reg %02u bit5: LPS/WUR disabled", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit5: LPS/WUR enabled", reg_addr);
    }

    if (reg16b_val & SLEEP_ACK_4) {
        fprintf (out_file_prt, "\n  reg %02u bit4: sleep acknowledge timer enabled; auto-transition back from Sleep Request mode "
                             "to Normal mode disabled during data transmission on MII or MDI", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit4: sleep acknowledge timer disabled; auto-transition back from Sleep Request "
                             "mode to Normal mode enabled during data transmission on MII or MDI", reg_addr);
    }

    if (reg16b_val & FWDPHYREM_2) {
        fprintf (out_file_prt, "\n  reg %02u bit2: wake-up event forwarded remotely ", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit2: wake-up event not forwarded remotely  ", reg_addr);
    }
    if (reg16b_val & AUTO_PWD_1) {
        fprintf (out_file_prt, "\n  reg %02u bit1: autonomous power-down enabled ", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit1: autonomous power-down disabled ", reg_addr);
    }
    if (reg16b_val & LPS_ACTIVE_0) {
        fprintf (out_file_prt,
                 "\n  reg %02u bit 0: automatic transition from Normal to Sleep Request when LPS code group received enabled ", reg_addr);
    } else {
        fprintf (out_file_prt,
                 "\n  reg %02u bit 0: automatic transition from Normal to Sleep Request when LPS code group received disabled ", reg_addr);
    }

    fprintf (out_file_prt, "\n");
    return res;
}
static bool parse_symbol_error_counter_register (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr)  {
    (void)reg16b_val;
    (void)out_file_prt;
    uint16_t sym_err_cnt = reg16b_val;
    fprintf (out_file_prt,
             "\n  reg %02u bit 15-0: [%u] R The symbol error counter is incremented when an invalid code symbol is received (including idle "
             "symbols). The counter is incremented only once per packet, even when the received packet contains more "
             "than one symbol error. This counter increments up to 216. When the counter overflows, the value FFFFh is "
             "retained. The counter is reset when the register is read.",reg_addr, sym_err_cnt);
    fprintf (out_file_prt, "\n");
    return true;
}

static bool parse_interrupt_status_register (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr)  {
    if (reg16b_val & PWON_15) {
        fprintf (out_file_prt, "\n  reg %02u bit15: R power-on detected", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit15: R power-on not detected", reg_addr);
    }
    if (reg16b_val & WAKEUP_14) {
        fprintf (out_file_prt, "\n  reg %02u bit14: R local or remote wake-up detected", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit14: R no local or remote wake-up detected", reg_addr);
    }
    if (reg16b_val & WUR_RECEIVED_13) {
        fprintf (out_file_prt, "\n  reg %02u bit13: R dedicated wake-up request detected", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit13: R no dedicated wake-up request detected", reg_addr);
    }
    if (reg16b_val & LPS_RECEIVED_12) {
        fprintf (out_file_prt, "\n  reg %02u bit12: R LPS code groups received", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit12: R no LPS code groups received", reg_addr);
    }
    if (reg16b_val & PHY_INIT_FAIL_11) {
        fprintf (out_file_prt, "\n  reg %02u bit11: R PHY initialization error detected", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit11: R no PHY initialization error detected", reg_addr);
    }
    if (reg16b_val & LINK_STATUS_FAIL_10) {
        fprintf (out_file_prt, "\n  reg %02u bit10: R link status bit LINK_UP changed from вЂ�link OKвЂ™ to вЂ�link failвЂ™", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit10: R link status not changed", reg_addr);
    }
    if (reg16b_val & LINK_STATUS_UP_9) {
        fprintf (out_file_prt, "\n  reg %02u bit9: R link status bit LINK_UP changed from вЂ�link failвЂ™ to вЂ�link OKвЂ™", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit9: R link status not changed", reg_addr);
    }
    if (reg16b_val & SYM_ERR_8) {
        fprintf (out_file_prt, "\n  reg %02u bit8: R symbol error detected", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit8: R no symbol error detected", reg_addr);
    }
    if (reg16b_val & TRAINING_FAILED_7) {
        fprintf (out_file_prt, "\n  reg %02u bit7: R training phase failure detected", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit7: R no training phase failure detected", reg_addr);
    }
    if (reg16b_val & SQI_WARNING_6) {
        fprintf (out_file_prt, "\n  reg %02u bit6: R SQI value below warning limit and bit LINK_UP set", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit6: R SQI value above warning limit", reg_addr);
    }
    if (reg16b_val & CONTROL_ERR_5) {
        fprintf (out_file_prt, "\n  reg %02u bit5: R SMI control error detected", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit5: R no SMI control error detected", reg_addr);
    }
    if (reg16b_val & UV_ERR_3) {
        fprintf (out_file_prt, "\n  reg %02u bit3: R undervoltage detected on VDD(IO), VDDD(3V3), VDDD(1V8) or VDDA(3V3);", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit3: R no undervoltage detected", reg_addr);
    }
    if (reg16b_val & UV_RECOVERY_2) {
        fprintf (out_file_prt, "\n  reg %02u bit2: R undervoltage recovery detected", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit2: R no undervoltage recovery detected", reg_addr);
    }
    if (reg16b_val & TEMP_ERR_1) {
        fprintf (out_file_prt, "\n  reg %02u bit1: R overtemperature error detected", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit1: R no overtemperature error detected", reg_addr);
    }
    if (reg16b_val & SLEEP_ABORT_0) {
        fprintf (out_file_prt, "\n  reg %02u bit0: R transition from Sleep Request back to Normal as a result of the Sleep "
                             "Request timer expiring", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit0: R no transition from Sleep Request back to Normal as a result of the Sleep "
                             "Request timer expiring", reg_addr);
    }
    fprintf (out_file_prt, "\n");
    return true;
}

static bool parse_interrupt_enable_register (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr)  {
    (void)reg16b_val;
    (void)out_file_prt;
    if (reg16b_val & PWON_EN_15) {
        fprintf (out_file_prt, "\n  reg %02u bit15: RW PWON interrupt enabled", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit15: RW PWON interrupt disabled", reg_addr);
    }
    if (reg16b_val & WAKEUP_EN_14) {
        fprintf (out_file_prt, "\n  reg %02u bit14: RW WAKEUP interrupt enabled", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit14: RW WAKEUP interrupt disabled", reg_addr);
    }
    if (reg16b_val & WUR_RECEIVED_EN_13) {
        fprintf (out_file_prt, "\n  reg %02u bit13: RW WUR_RECEIVED interrupt enabled", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit13: RW WUR_RECEIVED interrupt disabled", reg_addr);
    }
    if (reg16b_val & LPS_RECEIVED_EN_12) {
        fprintf (out_file_prt, "\n  reg %02u bit12: RW LPS_RECEIVED interrupt enabled", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit12: RW LPS_RECEIVED interrupt disabled", reg_addr);
    }
    if (reg16b_val & PHY_INIT_FAIL_EN_11) {
        fprintf (out_file_prt, "\n  reg %02u bit11: RW PHY_INIT_FAIL interrupt enabled", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit11: RW LINK_STATUS_FAIL interrupt disabled", reg_addr);
    }
    if (reg16b_val & LINK_STATUS_FAIL_EN_10) {
        fprintf (out_file_prt, "\n  reg %02u bit10: RW LINK_STATUS_FAIL interrupt enabled", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit10: RW LINK_STATUS_FAIL interrupt disabled", reg_addr);
    }
    if (reg16b_val & LINK_STATUS_UP_EN_9) {
        fprintf (out_file_prt, "\n  reg %02u bit 9: RW LINK_STATUS_UP interrupt enabled", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit 9: RW LINK_STATUS_UP interrupt disabled", reg_addr);
    }
    if (reg16b_val & SYM_ERR_EN_8) {
        fprintf (out_file_prt, "\n  reg %02u bit 8: RW SYM_ERR interrupt enabled", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit 8: RW SYM_ERR interrupt disabled", reg_addr);
    }
    if (reg16b_val & TRAINING_FAILED_EN_7) {
        fprintf (out_file_prt, "\n  reg %02u bit 7: RW TRAINING_FAILED interrupt enabled", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit 7: RW TRAINING_FAILED interrupt disabled", reg_addr);
    }
    if (reg16b_val & SQI_WARNING_EN_6) {
        fprintf (out_file_prt, "\n  reg %02u bit 6: RW SQI_WARNING interrupt enabled", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit 6: RW SQI_WARNING interrupt disabled", reg_addr);
    }
    if (reg16b_val & CONTROL_ERR_EN_5) {
        fprintf (out_file_prt, "\n  reg %02u bit 5: RW CONTROL_ERR interrupt enabled", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit 5: RW CONTROL_ERR interrupt disabled", reg_addr);
    }
    if (reg16b_val & UV_ERR_EN_3) {
        fprintf (out_file_prt, "\n  reg %02u bit 3: RW UV_ERR interrupt enabled", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit 3: RW UV_ERR interrupt disabled", reg_addr);
    }
    if (reg16b_val & UV_RECOVERY_EN_2) {
        fprintf (out_file_prt, "\n  reg %02u bit 2: RW UV_RECOVERY interrupt enabled", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit 2: RW UV_RECOVERY interrupt disabled", reg_addr);
    }
    if (reg16b_val & TEMP_ERR_EN_1) {
        fprintf (out_file_prt, "\n  reg %02u bit 1: RW TEMP_ERR interrupt enabled", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit 1: RW TEMP_ERR interrupt disabled", reg_addr);
    }
    if (reg16b_val & SLEEP_ABORT_EN_0) {
        fprintf (out_file_prt, "\n  reg %02u bit 0: RW SLEEP_ABORT interrupt enabled", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit 0: RW SLEEP_ABORT interrupt disabled", reg_addr);
    }

    fprintf (out_file_prt, "\n");
    return true;
}
static bool parse_general_status_register (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr)  {

    if (reg16b_val & INT_STATUS_15) {
        fprintf (out_file_prt, "\n  reg %02u bit15  R unmasked interrupt pending", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit15 R all interrupts cleared", reg_addr);
    }
    if (reg16b_val & PLL_LOCKED_14) {
        fprintf (out_file_prt, "\n  reg %02u bit14 R PLL stable and locked", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit14 R PLL unstable and not locked", reg_addr);
    }
    if (reg16b_val & LOCAL_WU_13) {
        fprintf (out_file_prt, "\n  reg %02u bit13 R local wake-up detected", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit13 R no local wake-up detected", reg_addr);
    }
    if (reg16b_val & REMOTE_WU_12) {
        fprintf (out_file_prt, "\n  reg %02u bit12 R remote wake-up detected", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit12 R no remote wake-up detected", reg_addr);
    }
    if (reg16b_val & DATA_DET_WU_11) {
        fprintf (out_file_prt, "\n  reg %02u bit11  R 100BASE-T1 data detected at MDI (pcs_rx_dv = TRUE; see Ref. 1) or MII "
                             "(TXEN = 1) in Sleep Request mode", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit11 R no 100BASE-T1 data detected at MDI or MII in Sleep Request mode", reg_addr);
    }
    if (reg16b_val & EN_STATUS_10) {
        fprintf (out_file_prt, "\n  reg %02u bit10 R EN switched LOW since register last read", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit10 R EN HIGH", reg_addr);
    }
    if (reg16b_val & RESET_STATUS_9) {
        fprintf (out_file_prt, "\n  reg %02u bit9 R hardware reset detected since register last read", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit9 R no hardware reset detected", reg_addr);
    }
    fprintf (out_file_prt, "\n  reg %02u bit8 R reserved", reg_addr);
    uint16_t linkFailCnt = extract_subval_from_16bit (reg16b_val, 7, 3);
    fprintf (out_file_prt, "\n  reg %02u bit7:3 R linkFailCnt: [%u]", reg_addr, linkFailCnt);
    fprintf (out_file_prt, "\n  reg %02u bit2:0 R reserved", reg_addr);
    fprintf (out_file_prt, "\n");
    return true;
}
static bool parse_external_status_register (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr)  {
    if (reg16b_val & UV_VDDD_3V3_15) {
        fprintf (out_file_prt, "\n  reg %02u bit15: R undervoltage detected on pin VDDD(3V3)", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit15: R no undervoltage detected on pin VDDD(3V3)", reg_addr);
    }
    if (reg16b_val & UV_VDDA_3V3_14) {
        fprintf (out_file_prt, "\n  reg %02u bit14: R undervoltage detected on pin VDDA(3V3)", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit14: R no undervoltage detected on pin VDDA(3V3)", reg_addr);
    }
    if (reg16b_val & UV_VDDD_1V8_13) {
        fprintf (out_file_prt, "\n  reg %02u bit13: R undervoltage detected on pin VDDD(1V8)", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit13: R no undervoltage detected on pin VDDD(1V8)", reg_addr);
    }
    if (reg16b_val & UD_VDDIO_11) {
        fprintf (out_file_prt, "\n  reg %02u bit11: R undervoltage detected on pin VDD(IO)", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit11: R no undervoltage detected on pin VDD(IO)", reg_addr);
    }
    if (reg16b_val & TEMP_HIGH_10) {
        fprintf (out_file_prt, "\n  reg %02u bit10: R temperature above high level", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit10: R temperature below high level", reg_addr);
    }
    if (reg16b_val & TEMP_WARN_9) {
        fprintf (out_file_prt, "\n  reg %02u bit9: R temperature above warning level", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit9: R temperature below warning level", reg_addr);
    }
    if (reg16b_val & SHORT_DETECT_8) {
        fprintf (out_file_prt, "\n  reg %02u bit8: R short circuit detected since register last read", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit8: R no short circuit detected", reg_addr);
    }
    if (reg16b_val & OPEN_DETECT_7) {
        fprintf (out_file_prt, "\n  reg %02u bit7: R open circuit detected since register last read", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit7: R no open circuit detected", reg_addr);
    }
    if (reg16b_val & POLARITY_DETECT_6) {
        fprintf (out_file_prt, "\n  reg %02u bit6: R polarity inversion detected at MDI", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit6: R no polarity inversion detected at MDI", reg_addr);
    }
    if (reg16b_val & INTERLEAVE_DETECT_5) {
        fprintf (out_file_prt, "\n  reg %02u bit5: R interleave order of detected ternary symbols: TBn, TAn", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit5: R interleave order of detected ternary symbols: TAn, TBn", reg_addr);
    }
    fprintf (out_file_prt, "\n");
    return true;
}

static bool parse_link_fail_counter_register (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr)  {
    uint16_t loc_rcvr_cnt = extract_subval_from_16bit (reg16b_val, 15, 8);
    fprintf (out_file_prt,
             "\n  reg %02u bit 15:8 R [%u] The counter is incremented when local receiver is NOT_OK; when the counter "
             "overflows, the value FFh is retained. The counter is reset when the register is read.",reg_addr,
             loc_rcvr_cnt);
    uint16_t rem_rcvr_cnt = extract_subval_from_16bit (reg16b_val, 7, 0);
    fprintf (out_file_prt,
             "\n  reg %02u bit 7:0  R [%u] The counter is incremented when remote receiver is NOT_OK; when the counter "
             "overflows, the value FFh is retained. The counter is reset when the register is read.",reg_addr,
             rem_rcvr_cnt);
    fprintf (out_file_prt, "\n");
    return true;
}
static bool parse_common_configuration_register (uint16_t reg16b_val, FILE *out_file_prt, uint8_t reg_addr)  {
    bool res = false;
    if (reg16b_val & AUTO_OP_15) {
        fprintf (out_file_prt, "\n  reg %02u bit15: R/W autonomous operation", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit15: R/W managed operation", reg_addr);
    }
    uint16_t clkMode = extract_subval_from_16bit (reg16b_val, 13, 12);
    res = parse_clk_mode (clkMode, out_file_prt, reg_addr);
    if (reg16b_val & LDO_MODE_11) {
        fprintf (out_file_prt, "\n  reg %02u bit11: R/W external 1.8 V supply", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit11: R/W internal 1.8 V LDO enabled", reg_addr);
    }
    if (reg16b_val & CLK_DRIVER_10) {
        fprintf (out_file_prt, "\n  reg %02u bit10:  R/W reduced output driver strength at output of CLK_IN_OUT ", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit10:  R/W standard output driver strength at output of CLK_IN_OUT", reg_addr);
    }
    if (reg16b_val & CLK_HOLD_9) {
        fprintf (out_file_prt,
                 "\n  reg %02u bit 9: R/W XTAL and CLK_IN_OUT output remain active until device switched to Sleep mode via SMI", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit9: R/W XTAL and CLK_IN_OUT output switched off in Sleep mode", reg_addr);
    }
    uint16_t loc_wu_tim = extract_subval_from_16bit (reg16b_val, 8, 7);
    res = parse_loc_wu_tim (loc_wu_tim, out_file_prt, reg_addr);

    if (reg16b_val & CONFIG_WAKE_6) {
        fprintf (out_file_prt, "\n  reg %02u bit6: R/W ratiometric input threshold (VDD(IO))", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit6: R/W absolute input threshold", reg_addr);
    }
    if (reg16b_val & CONFIG_INH_5) {
        fprintf (out_file_prt, "\n  reg %02u bit5:  R/W INH switched on in Disable mode", reg_addr);
    } else {
        fprintf (out_file_prt, "\n  reg %02u bit5:  R/W INH switched off in Disable mode", reg_addr);
    }
    fprintf (out_file_prt, "\n  reg %02u bit4:0:  R/W reserved", reg_addr);
    fprintf (out_file_prt, "\n");
    return res;
}

bool parse_sqi (uint8_t sqi, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    switch (sqi) {
    case 0:
        fprintf (out_file_prt, "\n  reg %02u bit7..5: r worse than class A SQI (unstable link)", reg_addr);
        break;
    case 1:
        fprintf (out_file_prt, "\n  reg %02u bit7..5: r class A SQI (unstable link)", reg_addr);
        break;
    case 2:
        fprintf (out_file_prt, "\n  reg %02u bit7..5: r class B SQI (unstable link)", reg_addr);
        break;
    case 3:
        fprintf (out_file_prt, "\n  reg %02u bit7..5: r class C SQI (good link)", reg_addr);
        break;
    case 4:
        fprintf (out_file_prt, "\n  reg %02u bit7..5: r class D SQI (good link; bit error rate < 1e-10)", reg_addr);
        break;
    case 5:
        fprintf (out_file_prt, "\n  reg %02u bit7..5: r class E SQI (good link)", reg_addr);
        break;
    case 6:
        fprintf (out_file_prt, "\n  reg %02u bit7..5: r class F SQI (very good link)", reg_addr);
        break;
    case 7:
        fprintf (out_file_prt, "\n  reg %02u bit7..5: r class G SQI (very good link)", reg_addr);
        break;
    default:
        fprintf (out_file_prt, "\n  reg %02u bit2..0: r Error", reg_addr);
        break;
    }
    return res;
}

bool parse_mii_mode (uint8_t mii_mode, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    switch (mii_mode) {
    case 0:
        fprintf (out_file_prt, "\n  reg %02u bit9:8: RW MII mode enabled", reg_addr);
        break;
    case 1:
        fprintf (out_file_prt, "\n  reg %02u bit9:8: RW RMII mode enabled (50 MHz input on REF_CLK)", reg_addr);
        break;
    case 2:
        fprintf (out_file_prt, "\n  reg %02u bit9:8: RW RMII mode enabled (50 MHz output on REF_CLK)", reg_addr);
        break;
    case 3:
        fprintf (out_file_prt, "\n  reg %02u bit9:8: RW Reverse MII mode", reg_addr);
        break;
    default:
        fprintf (out_file_prt, "\n  reg %02u bit9:8: RW Error", reg_addr);
        break;
    }
    return res;
}

bool parse_clk_mode (uint8_t clk_mode, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    switch (clk_mode) {
    case 0:
        fprintf (out_file_prt, "\n  reg %02u bit13:12 RW 25 MHz XTAL; no clock at CLK_IN_OUT", reg_addr);
        break;
    case 1:
        fprintf (out_file_prt, "\n  reg %02u bit13:12 RW 25 MHz XTAL; 25 MHz output at CLK_IN_OUT", reg_addr);
        break;
    case 2:
        fprintf (out_file_prt, "\n  reg %02u bit13:12 RW 25 MHz external clock at CLK_IN_OUT", reg_addr);
        break;
    case 3:
        fprintf (out_file_prt,
                 "\n  reg %02u bit 13:12 RW 50 MHz input at REF_CLK; RMII mode only; no XTAL; no clock at CLK_IN_OUT", reg_addr);
        break;
    default:
        fprintf (out_file_prt, "\n  reg %02u bit13:12 RW ", reg_addr);
        break;
    }
    return res;
}

bool parse_loc_wu_tim (uint8_t loc_wu_tim, FILE *out_file_prt, uint8_t reg_addr) {
    bool res = false;
    switch (loc_wu_tim) {
    case 0:
        fprintf (out_file_prt, "\n  reg %02u bit8:7 RW local wake-up timer: longest (10 ms to 20 ms)", reg_addr);
        break;
    case 1:
        fprintf (out_file_prt, "\n  reg %02u bit8:7 RW local wake-up timer: long (250 us to 500 s)", reg_addr);
        break;
    case 2:
        fprintf (out_file_prt, "\n  reg %02u bit8:7 RW local wake-up timer: short (100 us to 200 s)", reg_addr);
        break;
    case 3:
        fprintf (out_file_prt, "\n  reg %02u bit8:7 RW local wake-up timer: shortest (10 us to 40 s)", reg_addr);
        break;
    }
    return res;
}

const char *reg_name (uint8_t reg_addr) {
    const char *reg_name = UNDEF_REG_NAME;
    switch (reg_addr) {
    case 0:
        reg_name = "Basic control register";
        break;
    case 1:
        reg_name = "Basic status register";
        break;
    case 2:
        reg_name = "PHY identifier register 1";
        break;
    case 3:
        reg_name = "PHY identifier register 2";
        break;
    case 15:
        reg_name = "Extended status register";
        break;
    case 16:
        reg_name = "PHY identifier register 3";
        break;
    case 17:
        reg_name = "Extended control register";
        break;
    case 18:
        reg_name = "Configuration register 1";
        break;
    case 19:
        reg_name = "Configuration register 2";
        break;
    case 20:
        reg_name = "Symbol error counter register";
        break;
    case 21:
        reg_name = "Interrupt source register";
        break;
    case 22:
        reg_name = "Interrupt enable register";
        break;
    case 23:
        reg_name = "Communication status register";
        break;
    case 24:
        reg_name = "General status register";
        break;
    case 25:
        reg_name = "External status register";
        break;
    case 26:
        reg_name = "Link-fail counter register";
        break;
    case 27:
        reg_name = "Common configuration register";
        break;
    case 28:
        reg_name = "Configuration register 3";
        break;
    default:
        reg_name = UNDEF_REG_NAME;
        break;
    }
    return reg_name;
}

bool parse_16bit_val (char *in_str_val, uint32_t len, uint16_t *reg_addr) {
    bool res;
    int cnt = 0;
    char *in_str = in_str_val;
    if (len < 4) {
        return false;
    }
    if (NULL == in_str) {
        return false;
    }

    in_str = strstr (in_str, "0x");
    while (NULL != in_str) {
        if (4 < cnt) {
            return false;
        }
        // printf("\n %s",istr);
        res = try_strl2uint16 (in_str, 6, reg_addr);
        if (true == res) {
            return true;
        }
        cnt++;
        in_str = strstr (in_str + 1, "0x");
    }

    return false;
}


bool parse_tja1101_reg (uint8_t reg_addr, uint16_t reg16b_val, FILE *out_file_prt) {
    bool res = false;
    char curRegName[100] = "";
    strncpy (curRegName, reg_name (reg_addr), sizeof (curRegName));
    // printf ("\nReg name: %s \t\t reg addr: %u reg16b_val: [0x%04x] or [0b_%s]", reg_name (reg_addr),reg_addr,
    // reg16b_val, utoa_bin16 (reg16b_val));
    if (0 != strcmp (UNDEF_REG_NAME, curRegName)) {
        fprintf (out_file_prt, "\n Register name: [%30s] register addr: [%02u] register value: [0x%04x] or [0b_%s]",
                 reg_name (reg_addr), reg_addr, reg16b_val, utoa_bin16 (reg16b_val));
        switch (reg_addr) {
        case 0:
            res = parse_basic_control_register (reg16b_val, out_file_prt, reg_addr);
            break;
        case 1:
            res = parse_basic_status_register (reg16b_val, out_file_prt, reg_addr);
            break;
        case 2:
            res = parse_phy_identifier_1_register (reg16b_val, out_file_prt, reg_addr);
            break;
        case 3:
            res = parse_phy_identifier_2_register (reg16b_val, out_file_prt, reg_addr);
            break;
        case 15:
            res = parse_extended_status_register (reg16b_val, out_file_prt, reg_addr);
            break;
        case 16:
            res = parse_phy_identifier_3_register (reg16b_val, out_file_prt, reg_addr);
            break;
        case 17:
            res = parse_extended_control_register (reg16b_val, out_file_prt, reg_addr);
            break;
        case 18:
            res = parse_configuration_register_1 (reg16b_val, out_file_prt, reg_addr);
            break;

        case 19:
            res = parse_configuration_register_2 (reg16b_val, out_file_prt, reg_addr);
            break;
        case 20:
            res = parse_symbol_error_counter_register (reg16b_val, out_file_prt, reg_addr);
            break;
        case 21:
        	res = parse_interrupt_status_register (reg16b_val, out_file_prt, reg_addr);
            break;
        case 22:
            res = parse_interrupt_enable_register (reg16b_val, out_file_prt, reg_addr);
            break;
        case 23:
            res = parse_communication_status_register (reg16b_val, out_file_prt, reg_addr);
            break;
        case 24:
            res = parse_general_status_register (reg16b_val, out_file_prt, reg_addr);
            break;
        case 25:
            res = parse_external_status_register (reg16b_val, out_file_prt, reg_addr);
            break;
        case 26:
            res = parse_link_fail_counter_register (reg16b_val, out_file_prt, reg_addr);
            break;
        case 27:
            res = parse_common_configuration_register (reg16b_val, out_file_prt, reg_addr);
            break;
        case 28:
            res = parse_configuration_register_3 (reg16b_val, out_file_prt, reg_addr);
            break;
        default:
            res = false;
            break;
        }
    }
    return res;
}
