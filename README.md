# RC4 Encryption/Decryption

Dự án này cài đặt thuật toán mã hóa dòng RC4 (Rivest Cipher 4) để mã hóa và giải mã chuỗi văn bản.

## Yêu cầu hệ thống

- GCC compiler (hoặc bất kỳ C compiler nào hỗ trợ C99)
- Make (tùy chọn, để build tự động)
- Linux/Unix/MacOS hoặc Windows với MinGW/Cygwin

## Hướng dẫn biên dịch và chạy

### Cách 1: Sử dụng Makefile (Khuyến nghị)

```bash
# Biên dịch cả hai chương trình
make all

# Chạy test tự động (mã hóa và giải mã)
make test

# Xóa các file build
make clean
```

### Cách 2: Biên dịch thủ công

**Biên dịch chương trình mã hóa:**
```bash
gcc -Wall -Wextra -std=c99 -I. main_encrypt.c -o encrypt
```

**Biên dịch chương trình giải mã:**
```bash
gcc -Wall -Wextra -std=c99 -I. main_decrypt.c -o decrypt
```

### Cách 3: Chạy từng bước

**Bước 1: Mã hóa**
```bash
./encrypt
```
Output:
- In ra ciphertext dưới dạng hex
- Lưu ciphertext vào file `ciphertext.bin`

**Bước 2: Giải mã**
```bash
./decrypt
```
Output:
- Đọc ciphertext từ file `ciphertext.bin`
- In ra plaintext đã giải mã

## Test Vectors

### Test 1: Văn bản mặc định
**Input:**
- Plaintext: `"Hanoi University of Science and Technology"`
- Key: `"MySecretKey"`

**Expected Output:**
```
Ciphertext (Hex): [Kết quả sẽ hiển thị khi chạy]
Decrypted Text: Hanoi University of Science and Technology
```

### Test 2: Test Vector chuẩn RC4

**Test 2.1:**
- Key: `"Key"` (0x4B 0x65 0x79)
- Plaintext: `"Plaintext"` (0x50 0x6C 0x61 0x69 0x6E 0x74 0x65 0x78 0x74)
- Expected Ciphertext (Hex): `BB F3 16 E8 D9 40 AF 0A D3`

**Test 2.2:**
- Key: `"Wiki"` (0x57 0x69 0x6B 0x69)
- Plaintext: `"pedia"` (0x70 0x65 0x64 0x69 0x61)
- Expected Ciphertext (Hex): `10 21 BF 04 20`

**Test 2.3:**
- Key: `"Secret"` (0x53 0x65 0x63 0x72 0x65 0x74)
- Plaintext: `"Attack at dawn"` (0x41 0x74 0x74 0x61 0x63 0x6B 0x20 0x61 0x74 0x20 0x64 0x61 0x77 0x6E)
- Expected Ciphertext (Hex): `45 A0 1F 64 5F C3 5B 38 35 52 54 4B 9B F5`

### Hướng dẫn test thủ công

Để test với các test vector trên, bạn cần sửa giá trị `plaintext_str` và `key_str` trong file `main_encrypt.c` và `main_decrypt.c`, sau đó biên dịch lại.

**Ví dụ:**
```c
const char *plaintext_str = "Plaintext";
const char *key_str = "Key";
```

## 📚 Mô tả thuật toán RC4

RC4 là thuật toán mã hóa dòng (stream cipher) gồm 2 giai đoạn chính:

### 1. Key Scheduling Algorithm (KSA)
- Khởi tạo mảng hoán vị S với các giá trị từ 0-255
- Xáo trộn mảng S dựa trên khóa

### 2. Pseudo-Random Generation Algorithm (PRGA)
- Sinh keystream từ mảng S
- XOR keystream với plaintext để tạo ciphertext
- Hoặc XOR keystream với ciphertext để giải mã

**Đặc điểm quan trọng:**
- RC4 là thuật toán đối xứng: mã hóa và giải mã sử dụng cùng một quy trình
- Kích thước khóa linh hoạt: 40-2048 bits (thường dùng 128 bits)

## 🔐 Cấu trúc module

### rc4.h
- `RC4_State`: Cấu trúc lưu trạng thái RC4
- `rc4_ksa()`: Key Scheduling Algorithm
- `rc4_prga()`: Pseudo-Random Generation Algorithm
- `rc4_init()`: Khởi tạo trạng thái RC4

### rc4_encrypt.h
- `rc4_encrypt()`: Hàm mã hóa
- `print_encrypted_hex()`: In ciphertext dạng hex
- `print_encrypted_chars()`: In ciphertext dạng ký tự

### rc4_decrypt.h
- `rc4_decrypt()`: Hàm giải mã
- `print_decrypted_text()`: In plaintext
- `print_decrypted_hex()`: In plaintext dạng hex
