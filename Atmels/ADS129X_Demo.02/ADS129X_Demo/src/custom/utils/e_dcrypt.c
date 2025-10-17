#include "e_dcrypt.h"
#include <stddef.h>

#define MSGLEN  64

char* Crypt_Encode(char *key, char *plainMessage) {
    char i, *keyptr, *msgptr;

    msgptr = plainMessage;
    keyptr = key;
    if (!*keyptr || !*msgptr)
        return NULL;

    for (i = 0; i < 5; i++) {
        keyptr++;
        if (!*keyptr)
            keyptr = key;
    }

    for (i = 0; i < MSGLEN; i++) {
        *msgptr ^= *keyptr;
        *msgptr += ~MSGLEN;
        keyptr++;
        if (!*keyptr)
            keyptr = key;
        msgptr++;
    }
    return plainMessage;
}

char* Crypt_Decode(char *key, char *encodedMessage) {
    char i, *keyptr, *msgptr;

    msgptr = encodedMessage;
    keyptr = key;
    if (!*keyptr || !*msgptr)
        return NULL;

    for (i = 0; i < 5; i++) {
        keyptr++;
        if (!*keyptr)
            keyptr = key;
    }

    for (i = 0; i < MSGLEN; i++) {
        *msgptr += (MSGLEN + 1);
        *msgptr ^= *keyptr;
        keyptr++;
        if (!*keyptr)
            keyptr = key;
        msgptr++;
    }
    return encodedMessage;
}
