// Copyright (c) Christopher D. Dickson <cdd@matoya.group>
//
// This Source Code Form is subject to the terms of the MIT License.
// If a copy of the MIT License was not distributed with this file,
// You can obtain one at https://spdx.org/licenses/MIT.html.

#include "matoya.h"

#include <CommonCrypto/CommonCryptor.h>
#include <CommonCrypto/CommonRandom.h>
#include <CommonCrypto/CommonHMAC.h>


// Hash

void MTY_CryptoHash(MTY_Algorithm algo, const void *input, size_t inputSize, const void *key,
	size_t keySize, void *output, size_t outputSize)
{
	switch (algo) {
		case MTY_ALGORITHM_SHA1:
			if (key) {
				CCHmac(kCCHmacAlgSHA1, key, keySize, input, inputSize, output);
			} else {
				CC_SHA1(input, inputSize, output);
			}
			break;
		case MTY_ALGORITHM_SHA1_HEX: {
			uint8_t bytes[MTY_SHA1_SIZE];
			MTY_CryptoHash(MTY_ALGORITHM_SHA1, input, inputSize, NULL, 0, bytes, MTY_SHA1_SIZE);
			MTY_BytesToHex(bytes, sizeof(bytes), output, outputSize);
			break;
		}
		case MTY_ALGORITHM_SHA256:
			if (key) {
				CCHmac(kCCHmacAlgSHA256, key, keySize, input, inputSize, output);
			} else {
				CC_SHA256(input, inputSize, output);
			}
			break;
		case MTY_ALGORITHM_SHA256_HEX: {
			uint8_t bytes[MTY_SHA256_SIZE];
			MTY_CryptoHash(MTY_ALGORITHM_SHA256, input, inputSize, NULL, 0, bytes, MTY_SHA256_SIZE);
			MTY_BytesToHex(bytes, sizeof(bytes), output, outputSize);
			break;
		}
	}
}


// Random

void MTY_GetRandomBytes(void *output, size_t size)
{
	CCRNGStatus e = CCRandomGenerateBytes(output, size);
	if (e != kCCSuccess)
		MTY_Log("'CCRandomGenerateBytes' failed with error %d\n", e);
}
