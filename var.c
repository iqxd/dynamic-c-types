#include "var.h"

var_t VAR_NULL = ((var_t)T_NULL) << TAG_SHIFT_BITS;
var_t VAR_END = ((var_t)T_END) << TAG_SHIFT_BITS;