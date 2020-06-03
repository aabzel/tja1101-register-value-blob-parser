#ifndef PARSE_TIC12400_REGS_H
#define PARSE_TIC12400_REGS_H

#include "custom_type.h"

#include <stdio.h>

bool parse_tic12400_regs_file (char *inFileName,char *outFileName);
bool parse_reg (uint8_t regAddr, uint16_t regVal, FILE *outFilePrt);

#endif /* PARSE_TIC12400_REGS_H */
