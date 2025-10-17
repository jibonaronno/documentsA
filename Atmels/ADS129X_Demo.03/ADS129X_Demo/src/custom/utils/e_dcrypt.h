#ifndef E_DCRYPT_H
#define E_DCRYPT_H

#ifdef __cplusplus
extern "C" {
#endif

char* Crypt_Encode(char *key, char *plainMessage);

char* Crypt_Decode(char *key, char *encodedMessage);

#ifdef __cplusplus
}
#endif

#endif /* E_DCRYPT_H */
