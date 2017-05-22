// aes_keygen.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


static const unsigned long seed_origin[4] = { 123456789, 362436069, 521288629, 88675123 };
static unsigned long seed[4];

void init_xor128(unsigned long s) {
	for (unsigned long i = 0; i<4; ++i) seed[i] = s = 1812433253U * (s ^ (s >> 30)) + i;
}

unsigned long xor128() {
	unsigned long *a = seed;
	unsigned long t = (a[0] ^ (a[0] << 11));
	a[0] = a[1]; a[1] = a[2]; a[2] = a[3];
	return (a[3] = (a[3] ^ (a[3] >> 19)) ^ (t ^ (t >> 8)));
}

void key_gen(char *key1,size_t key1_len,char* key2,size_t key2_len)
{
	int i, j;
	unsigned char c1, c2;
	char s[3] = { 0,0 };
	union {
		unsigned char data8[4];
		unsigned long data32;
	}data;
	strncat(key2, "static const unsigned char key[] = {", key2_len);
	for (i = 0; i < 4; i++) {
		data.data32 = xor128();
		for (j = 3; j >= 0; j--) {
			c1 = (data.data8[j] >> 4);
			c2 = (data.data8[j] & 0x0F);
			s[0] = c1 < 10 ? '0' + c1 : 'a' + c1 - 10;
			s[1] = c2 < 10 ? '0' + c2 : 'a' + c2 - 10;
			strncat(key1, s, key1_len);
			strncat(key2, "0x", key1_len);
			strncat(key2, s, key2_len);
			strncat(key2, ",", key2_len);
		}
	}
	key2[strlen(key2) - 1] = NULL;
	strncat(key2, "};", sizeof(key2));
	printf("Seeds for Lazurite Pi Gateway::\r\n");
	printf("%s\r\n\r\n", key1);
	printf("Seeds for Lazurite SubGHz::\r\n");
	printf("%s\r\n", key2);
	printf("\r\n\r\n");
}

int main(int argc, char *argv[])
{
	unsigned long base;
	char key1[33];
	char key2[128];
	char *ctx;

	if (argc == 2) {
		memcpy(key2, argv[1], sizeof(key2));
		base = strtol(key2, NULL, 0);

		if (base == 0) {
			printf("seeds is invalid number..\n");
			return 0;
		}

		memcpy(seed, seed_origin, sizeof(seed));

		init_xor128(base);
		memset(key1, 0, sizeof(key1));
		memset(key2, 0, sizeof(key2));

		memcpy(seed, seed_origin, sizeof(seed));

		key_gen(key1, sizeof(key1), key2, sizeof(key2));

	} else {
		while (1) {

			memset(key2, 0, sizeof(key2));
			printf("Please input seeds of key[1-2147483647] or [0x00000001-0xFFFFFFFF]\r\n\t  or q(exit)::");
			fgets(key2, sizeof(key2), stdin);
			strtok(key2, "\r\n");

			if (strncmp(key2, "q", sizeof(key2)) == 0) return 0;
			base = strtol(key2, NULL, 0);

			if (base == 0) {
				printf("seeds is invalid number..\n");
				continue;
			}

			printf("seeds = %d \r\n", base);

			memset(key1, 0, sizeof(key1));
			memset(key2, 0, sizeof(key2));

			memcpy(seed, seed_origin, sizeof(seed));

			init_xor128(base);
			key_gen(key1, sizeof(key1), key2, sizeof(key2));
		}
	}

	return 0;
}

