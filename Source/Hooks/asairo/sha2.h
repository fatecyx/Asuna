#ifndef SHA2_H
#define SHA2_H

#include "my_common.h"

_MY_C_HEAD_

Void WINAPI sha256(const unsigned char *message, unsigned int len, unsigned char *digest);

_MY_C_TAIL_

#endif /* !SHA2_H */

