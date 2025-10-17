#ifndef MD5_H
#define MD5_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void md5(char *initial_msg, size_t initial_len, int32_t *out /* array of 4 int32_t */);

#ifdef __cplusplus
}
#endif

#endif /* MD5_H */