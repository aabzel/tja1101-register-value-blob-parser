#ifndef PARSE_PHY_REGS_H
#define PARSE_PHY_REGS_H

#include "custom_type.h"
#include "tja1101_bits_offsets.h"

#include <stdio.h>

#define UNDEF_REG_NAME "Undef_REG_NAME"

#define TJA1101_REG_NUM 18U

typedef struct xRegTJA1101_t {
    uint8_t regAddr;
    uint16_t regVal;
    char regname[100];
} regTJA1101_t;

extern regTJA1101_t tja1101RegMap[TJA1101_REG_NUM];

const char *reg_name (uint8_t regAddr);
bool parse_tja1101_regs_file (char *inFileName, char *outFileName);
bool parse_tja1101_reg (uint8_t regAddr, uint16_t regVal, FILE *outFilePrt);

bool parse_8bit_reg_addr(char *in_str, uint32_t len, uint8_t *reg_addr);
bool parse_16bit_val(char *in_str_val, uint32_t len, uint16_t *reg_addr);

bool parse_basic_control_register (uint16_t regVal, FILE *outFilePrt);
bool parse_basic_status_register (uint16_t regVal, FILE *outFilePrt);
bool parse_phy_identifier_1_register (uint16_t regVal, FILE *outFilePrt);
bool parse_phy_identifier_2_register (uint16_t regVal, FILE *outFilePrt);
bool parse_extended_status_register (uint16_t regVal, FILE *outFilePrt);
bool parse_phy_identifier_3_register (uint16_t regVal, FILE *outFilePrt);
bool parse_extended_control_register (uint16_t regVal, FILE *outFilePrt);
bool parse_configuration_register_1 (uint16_t regVal, FILE *outFilePrt);
bool parse_configuration_register_2 (uint16_t regVal, FILE *outFilePrt);
bool parse_symbol_error_counter_register (uint16_t regVal, FILE *outFilePrt);
bool parse_interrupt_status_register (uint16_t regVal, FILE *outFilePrt);
bool parse_interrupt_source_register (uint16_t regVal, FILE *outFilePrt);
bool parse_interrupt_enable_register (uint16_t regVal, FILE *outFilePrt);
bool parse_communication_status_register (uint16_t regVal, FILE *outFilePrt);
bool parse_general_status_register (uint16_t regVal, FILE *outFilePrt);
bool parse_external_status_register (uint16_t regVal, FILE *outFilePrt);
bool parse_link_fail_counter_register (uint16_t regVal, FILE *outFilePrt);
bool parse_common_configuration_register (uint16_t regVal, FILE *outFilePrt);
bool parse_configuration_register_3 (uint16_t regVal, FILE *outFilePrt);

bool parse_power_mode (uint8_t regVal, FILE *outFilePrt);
bool parse_loopback_mode (uint8_t regVal, FILE *outFilePrt);
bool parse_test_mode (uint8_t regVal, FILE *outFilePrt);
bool parse_phy_state (uint8_t phyState, FILE *outFilePrt);
bool parse_sqi (uint8_t sqi, FILE *outFilePrt);
bool parse_mii_mode (uint8_t mii_mode, FILE *outFilePrt);
bool parse_clk_mode (uint8_t clk_mode, FILE *outFilePrt);
bool parse_loc_wu_tim (uint8_t loc_wu_tim, FILE *outFilePrt);

#endif /* PARSE_PHY_REGS_H */
