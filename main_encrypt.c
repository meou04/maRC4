#ifndef RC4_DECRYPT_H
#define RC4_DECRYPT_H

#include "rc4.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Giải mã dữ liệu sử dụng RC4
 * @param ciphertext: Văn bản đã mã hóa
 * @param ciphertext_len: Độ dài văn bản đã mã hóa
 * @param key: Khóa giải mã
 * @param key_len: Độ dài khóa
 * @param plaintext: Buffer chứa kết quả giải mã (phải được cấp phát trước)
 * 
 * Lưu ý: RC4 là thuật toán đối xứng, nên giải mã = mã hóa
 */
void rc4_decrypt(const uint8_t *ciphertext, size_t ciphertext_len,
                 const uint8_t *key, size_t key_len,
                 uint8_t *plaintext) {
    // Khởi tạo trạng thái RC4
    RC4_State state;
    rc4_init(&state, key, key_len);
    
    // Thực hiện giải mã (giống mã hóa)
    rc4_prga(&state, ciphertext, plaintext, ciphertext_len);
}

/**
 * In kết quả giải mã dưới dạng chuỗi văn bản
 */
void print_decrypted_text(const uint8_t *plaintext, size_t len) {
    printf("Plaintext: ");
    for (size_t i = 0; i < len; i++) {
        printf("%c", plaintext[i]);
    }
    printf("\n");
}

/**
 * In kết quả giải mã dưới dạng hex
 */
void print_decrypted_hex(const uint8_t *plaintext, size_t len) {
    printf("Plaintext (Hex): ");
    for (size_t i = 0; i < len; i++) {
        printf("%02X ", plaintext[i]);
    }
    printf("\n");
}

#endif // RC4_DECRYPT_H