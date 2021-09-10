#ifndef RUN_LENGTH_ENCODING_H
#define RUN_LENGTH_ENCODING_H


int encode_len(const char  *str);
char *encode(const char *text);

int decode_len(const char  *str);
char *decode(const char *data);

#endif

#include "br-common.h"
