#ifndef LUAT_CRYPTO_H
#define LUAT_CRYPTO_H
#include "luat_base.h"
#include "mbedtls/md.h"

#define LUAT_CRYPTO_AES_ECB 1
#define LUAT_CRYPTO_AES_CBC 2
#define LUAT_CRYPTO_AES_CTR 3
#define LUAT_CRYPTO_AES_CFB 4
#define LUAT_CRYPTO_AES_OFB 5

#define LUAT_CRYPTO_AES_PAD_ZERO 1
#define LUAT_CRYPTO_AES_PAD_5 2
#define LUAT_CRYPTO_AES_PAD_7 3

typedef struct
{
    char tp[16];
    size_t key_len;
	mbedtls_md_context_t *ctx;
}luat_crypt_stream_t;
/**
 * @defgroup luatos_crypto crypto数据加密
 * @{
 */
int luat_crypto_trng(char* buff, size_t len);
/// @brief 计算md5值
/// @param str 需要计算的字符串
/// @param str_size  需要计算的字符串的长度
/// @param out_ptr 输出
/// @return 成功0，失败-1
int luat_crypto_md5_simple(const char* str, size_t str_size, void* out_ptr);
/// @brief 计算hmac_md5值
/// @param str 需要计算的字符串
/// @param str_size 字符串长度
/// @param mac 密钥
/// @param mac_size 密钥的长度
/// @param out_ptr 输出
/// @return 成功0，失败-1
int luat_crypto_hmac_md5_simple(const char* str, size_t str_size, const char* mac, size_t mac_size, void* out_ptr);

/// @brief 计算sha1值
/// @param str  需要计算的字符串
/// @param str_size 需要计算的字符串的长度
/// @param out_ptr 输出
/// @return  成功0，失败-1
int luat_crypto_sha1_simple(const char* str, size_t str_size, void* out_ptr);
/// @brief 计算hmac_sha1值
/// @param str 需要计算的字符串
/// @param str_size 字符串长度
/// @param mac 密钥
/// @param mac_size 密钥的长度
/// @param out_ptr 输出
/// @return 成功0，失败-1
int luat_crypto_hmac_sha1_simple(const char* str, size_t str_size, const char* mac, size_t mac_size, void* out_ptr);
/// @brief 计算sha256值
/// @param str  需要计算的字符串
/// @param str_size 需要计算的字符串的长度
/// @param out_ptr 输出
/// @return  成功0，失败-1
int luat_crypto_sha256_simple(const char* str, size_t str_size, void* out_ptr);
/// @brief 计算hmac_sha256值
/// @param str 需要计算的字符串
/// @param str_size 字符串长度
/// @param mac 密钥
/// @param mac_size 密钥的长度
/// @param out_ptr 输出
/// @return 成功0，失败-1
int luat_crypto_hmac_sha256_simple(const char* str, size_t str_size, const char* mac, size_t mac_size, void* out_ptr) ;
/// @brief 计算sha512值
/// @param str  需要计算的字符串
/// @param str_size 需要计算的字符串的长度
/// @param out_ptr 输出
/// @return  成功0，失败-1
int luat_crypto_sha512_simple(const char* str, size_t str_size, void* out_ptr) ;
/// @brief 计算hmac_sha512值
/// @param str 需要计算的字符串
/// @param str_size 字符串长度
/// @param mac 密钥
/// @param mac_size 密钥的长度
/// @param out_ptr 输出
/// @return 成功0，失败-1
int luat_crypto_hmac_sha512_simple(const char* str, size_t str_size, const char* mac, size_t mac_size, void* out_ptr) ;
/**
 * @brief BASE64加密
 * @param dst buffer
 * @param dlen buffer长度
 * @param olen 写入的字节数
 * @param src 加密密钥
 * @param slen 加密密钥长度
 * @return 0成功
 */
int luat_crypto_base64_encode( unsigned char *dst, size_t dlen, size_t *olen, const unsigned char *src, size_t slen ) ;
/**
 * @brief BASE64解密
 * @param dst buffer
 * @param dlen buffer长度
 * @param olen 写入的字节数
 * @param src 密钥
 * @param slen 密钥长度
 * @return 0成功
 */
int luat_crypto_base64_decode( unsigned char *dst, size_t dlen, size_t *olen, const unsigned char *src, size_t slen ) ;
/**@}*/ 
int luat_crypto_cipher_list(const char** list, size_t* len);
int luat_crypto_cipher_suites(const char** list, size_t* len);

int luat_crypto_md(const char* md, const char* str, size_t str_size, void* out_ptr, const char* key, size_t key_len);
int luat_crypto_md_file(const char* md, void* out_ptr, const char* key, size_t key_len, const char* path);

int luat_crypto_md_init(const char* md, const char* key, luat_crypt_stream_t *stream);
int luat_crypto_md_update(const char* md, const char* str, size_t str_size, luat_crypt_stream_t *stream);
int luat_crypto_md_finish(const char* md, void* out_ptr, luat_crypt_stream_t *stream);
#endif
