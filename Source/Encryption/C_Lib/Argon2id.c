#include "Include/Argon2id.h"
#include <sodium.h>
#include <sodium/crypto_pwhash.h>
#include <string.h>

EncryptStatus hash_password(const char *password, char *hashed_output) {
    const int PASSWORD_LENGTH = strlen(password);

    // clang-format off
    const int HASH_STATUS = crypto_pwhash_str(
            hashed_output, password, PASSWORD_LENGTH,
       crypto_pwhash_OPSLIMIT_INTERACTIVE, 
       crypto_pwhash_MEMLIMIT_INTERACTIVE);
    // clang-format on

    if (HASH_STATUS != 0) {
        return MEMORY_ERROR;
    }

    return ENCRYPT_OK;
}

IS_HASH_MATCHES is_hash_matches(const char *hashed, const char *password) {
    // clang-format off
    const int PASSWORD_LENGTH = strlen(password);
    const int IS_HASH_MATCHES = crypto_pwhash_str_verify(
        hashed, password,
  PASSWORD_LENGTH
    );
    // clang-format on

    if (IS_HASH_MATCHES != 0) {
        return HASH_MISMATCH;
    }

    return HASH_MATCHES;
}