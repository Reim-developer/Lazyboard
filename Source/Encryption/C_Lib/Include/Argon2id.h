#ifndef CORE_ARGON_2ID_H
#define CORE_ARGON_2ID_H
#if defined(__cplusplus)
extern "C" {
#endif

// clang-format off
typedef enum {
    ENCRYPT_OK,
    MEMORY_ERROR
} EncryptStatus;

typedef enum {
    HASH_MATCHES,
    HASH_MISMATCH
} IS_HASH_MATCHES;

// clang-format on

EncryptStatus hash_password(const char *password, char hashed_output[256]);
IS_HASH_MATCHES is_hash_matches(const char *hashed, const char *password);

#if defined(__cplusplus)
}
#endif

#endif  // CORE_ARGON_2ID_H