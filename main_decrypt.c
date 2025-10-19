#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rc4_decrypt.h"

int main() {
    // Ciphertext từ kết quả mã hóa (hoặc đọc từ file)
    // Đây là ví dụ, trong thực tế bạn sẽ đọc từ file hoặc nhập vào
    
    // Khóa giải mã (phải giống khóa mã hóa)
    const char *key_str = "MySecretKey";
    const uint8_t *key = (const uint8_t *)key_str;
    size_t key_len = strlen(key_str);
    
    // Đọc ciphertext từ file
    FILE *fp = fopen("ciphertext.bin", "rb");
    if (fp == NULL) {
        fprintf(stderr, "Error: Cannot open ciphertext.bin\n");
        fprintf(stderr, "Please run encryption program first!\n");
        return 1;
    }
    
    // Lấy kích thước file
    fseek(fp, 0, SEEK_END);
    size_t ciphertext_len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    // Đọc dữ liệu
    uint8_t *ciphertext = (uint8_t *)malloc(ciphertext_len);
    uint8_t *plaintext = (uint8_t *)malloc(ciphertext_len + 1);
    
    if (ciphertext == NULL || plaintext == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(fp);
        return 1;
    }
    
    fread(ciphertext, 1, ciphertext_len, fp);
    fclose(fp);
    
    // Hiển thị thông tin
    printf("=== RC4 DECRYPTION ===\n");
    printf("Key: %s\n", key_str);
    printf("Ciphertext Length: %zu bytes\n", ciphertext_len);
    printf("Key Length: %zu bytes\n\n", key_len);
    
    printf("Ciphertext (Hex): ");
    for (size_t i = 0; i < ciphertext_len; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n\n");
    
    // Thực hiện giải mã
    rc4_decrypt(ciphertext, ciphertext_len, key, key_len, plaintext);
    
    // Thêm null terminator để in chuỗi
    plaintext[ciphertext_len] = '\0';
    
    // Hiển thị kết quả
    print_decrypted_text(plaintext, ciphertext_len);
    print_decrypted_hex(plaintext, ciphertext_len);
    
    // Giải phóng bộ nhớ
    free(ciphertext);
    free(plaintext);
    
    return 0;
}