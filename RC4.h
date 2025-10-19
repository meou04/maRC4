#ifndef RC4_H
#define RC4_H

#include <stdint.h>
#include <string.h>

// Cấu trúc lưu trữ trạng thái RC4
typedef struct {
    uint8_t S[256];
    uint8_t i;
    uint8_t j;
} RC4_State;

/**
 * Key Scheduling Algorithm (KSA)
 * Khởi tạo bảng hoán vị S dựa trên khóa
 */
void rc4_ksa(RC4_State *state, const uint8_t *key, size_t key_len) {
    // Bước 1: Khởi tạo mảng S với giá trị từ 0 đến 255
    for (int i = 0; i < 256; i++) {
        state->S[i] = i;
    }
    
    // Bước 2: Xáo trộn mảng S dựa trên khóa
    uint8_t j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + state->S[i] + key[i % key_len]) % 256;
        
        // Hoán đổi S[i] và S[j]
        uint8_t temp = state->S[i];
        state->S[i] = state->S[j];
        state->S[j] = temp;
    }
    
    // Khởi tạo các biến trạng thái
    state->i = 0;
    state->j = 0;
}

/**
 * Pseudo-Random Generation Algorithm (PRGA)
 * Sinh keystream và thực hiện XOR với dữ liệu
 */
void rc4_prga(RC4_State *state, const uint8_t *input, uint8_t *output, size_t len) {
    for (size_t k = 0; k < len; k++) {
        // Bước 1: Tăng i
        state->i = (state->i + 1) % 256;
        
        // Bước 2: Tính j
        state->j = (state->j + state->S[state->i]) % 256;
        
        // Bước 3: Hoán đổi S[i] và S[j]
        uint8_t temp = state->S[state->i];
        state->S[state->i] = state->S[state->j];
        state->S[state->j] = temp;
        
        // Bước 4: Tính keystream byte
        uint8_t t = (state->S[state->i] + state->S[state->j]) % 256;
        uint8_t keystream_byte = state->S[t];
        
        // Bước 5: XOR với input để tạo output
        output[k] = input[k] ^ keystream_byte;
    }
}

/**
 * Khởi tạo trạng thái RC4 với khóa
 */
void rc4_init(RC4_State *state, const uint8_t *key, size_t key_len) {
    rc4_ksa(state, key, key_len);
}

#endif // RC4_H