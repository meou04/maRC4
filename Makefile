# Makefile cho RC4 Encryption/Decryption

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I.

# Targets
all: encrypt decrypt

encrypt: main_encrypt.c rc4.h rc4_encrypt.h
	$(CC) $(CFLAGS) main_encrypt.c -o encrypt

decrypt: main_decrypt.c rc4.h rc4_decrypt.h
	$(CC) $(CFLAGS) main_decrypt.c -o decrypt

clean:
	rm -f encrypt decrypt ciphertext.bin *.o

test: all
	@echo "=== Running Encryption ==="
	./encrypt
	@echo ""
	@echo "=== Running Decryption ==="
	./decrypt

.PHONY: all clean test