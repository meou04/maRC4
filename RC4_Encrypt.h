#ifndef RC4_ENCRYPT_H
#define RC4_ENCRYPT_H

#include "rc4.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Mã hóa dữ liệu sử dụng RC4
 * @param plaintext: Văn bản gốc
 * @param plaintext_len: Độ dài văn bản gốc
 * @param key: Khóa mã hóa
 * @param key_len: Độ dài khóa
 * @param ciphertext: Buffer chứa kết quả mã hóa (phải được cấp phát trước)
 */
void rc4_encrypt(const uint8_t *plaintext, size_t plaintext_len,
                 const uint8_t *key, size_t key_len,
                 uint8_t *ciphertext) {
    // Khởi tạo trạng thái RC4
    RC4_State state;
    rc4_init(&state, key, key_len);
    
    // Thực hiện mã hóa
    rc4_prga(&state, plaintext, ciphertext, plaintext_len);
}

/**
 * In kết quả mã hóa dưới dạng hex
 */
void print_encrypted_hex(const uint8_t *ciphertext, size_t len) {
    printf("Ciphertext (Hex): ");
    for (size_t i = 0; i < len; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");
}

/**
 * In kết quả mã hóa dưới dạng chuỗi ký tự (nếu có thể hiển thị)
 */
void print_encrypted_chars(const uint8_t *ciphertext, size_t len) {
    printf("Ciphertext (Chars): ");
    for (size_t i = 0; i < len; i++) {
        if (ciphertext[i] >= 32 && ciphertext[i] <= 126) {
            printf("%c", ciphertext[i]);
        } else {
            printf(".");
        }
    }
    printf("\n");
}

#endif // RC4_ENCRYPT_H