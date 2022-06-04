#include <string.h>
#include <sodium.h>

void create_hash_from_password(char* password, char hash[crypto_pwhash_STRBYTES]){
    if (crypto_pwhash_str(hash, password, strlen(password), crypto_pwhash_OPSLIMIT_SENSITIVE, crypto_pwhash_MEMLIMIT_SENSITIVE) != 0){
        printf("Can't create hash\n");
        exit(1);
    }
}


void encrypt_str(char* str, char* encrypted_str, char hash[crypto_pwhash_STRBYTES], int isLastLine){
    uint8_t tag;
    if (isLastLine == 1){
        tag = crypto_secretstream_xchacha20poly1305_TAG_FINAL;
    } else { 
        tag = crypto_secretstream_xchacha20poly1305_TAG_PUSH;
    }
    crypto_secretstream_xchacha20poly1305_state *state;
    uint8_t header[crypto_secretstream_xchacha20poly1305_HEADERBYTES];
    crypto_secretstream_xchacha20poly1305_init_push(state, header, hash);
    printf("test\n");
    crypto_secretstream_xchacha20poly1305_push(state, encrypted_str, NULL, str, strlen(str), NULL, 0, crypto_secretstream_xchacha20poly1305_TAG_PUSH);
    printf("encrypted string : %s", encrypted_str);

}

