// SPDX-License-Identifier: GPL-2.0
//
// SentraOS OTA Update — Crypto bridge helpers.
//
// Provides SHA-256 hashing and PKCS#7 signature verification
// using the kernel's native crypto API.  Called from Rust
// via extern "C".

#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/verification.h>
#include <keys/system_keyring.h>
#include <crypto/hash.h>

/*
 * sentraos_ota_hash_sha256  -  Compute SHA-256 digest.
 * @data:      input data buffer
 * @len:       length of input
 * @out_hash:  32-byte output buffer
 *
 * Returns 0 on success, negative errno on failure.
 */
int sentraos_ota_hash_sha256(const void *data, size_t len, u8 *out_hash)
{
	struct crypto_shash *tfm;
	int ret;

	tfm = crypto_alloc_shash("sha256", 0, 0);
	if (IS_ERR(tfm))
		return PTR_ERR(tfm);

	ret = crypto_shash_tfm_digest(tfm, data, len, out_hash);

	crypto_free_shash(tfm);
	return ret;
}
EXPORT_SYMBOL_GPL(sentraos_ota_hash_sha256);

/*
 * sentraos_ota_verify_pkcs7  -  Verify PKCS#7 signature over data.
 * @data:      data that was signed
 * @data_len:  length of data
 * @sig:       raw PKCS#7 signature blob
 * @sig_len:   length of signature
 *
 * Uses the built-in (primary + secondary) trusted keyring.
 * Returns 0 on valid signature, negative errno on failure.
 */
int sentraos_ota_verify_pkcs7(const void *data, size_t data_len,
			      const void *sig, size_t sig_len)
{
	if (!data || !sig || !data_len || !sig_len)
		return -EINVAL;

	return verify_pkcs7_signature(data, data_len, sig, sig_len,
				      VERIFY_USE_SECONDARY_KEYRING,
				      VERIFYING_UNSPECIFIED_SIGNATURE,
				      NULL, NULL);
}
EXPORT_SYMBOL_GPL(sentraos_ota_verify_pkcs7);

/*
 * sentraos_ota_is_strict  -  Report whether strict signing is required.
 *
 * Reflects CONFIG_SENTRAOS_OTA_STRICT_SIGN from Kconfig so that
 * Rust code can enforce the policy.
 */
int sentraos_ota_is_strict(void)
{
	if (IS_ENABLED(CONFIG_SENTRAOS_OTA_STRICT_SIGN))
		return 1;
	return 0;
}
EXPORT_SYMBOL_GPL(sentraos_ota_is_strict);
