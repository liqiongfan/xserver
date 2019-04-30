/**
 * File: ${FILE} for project Xserver
 * Email: xeapplee@gmail.com
 * website: https://www.supjos.cn
 * Author: Josin 
 */

#include "md5.h"

#define ROTATELEFT(value, bits) (((value) << (bits)) | ((value) >> (32 - (bits))))

#define TO_HEX_FMT_L "%02x"
#define TO_HEX_FMT_U "%02X"

/**
 * @desc: convert message and mes_bkp string into integer array and store them in w
 */
static void md5_process_part1(uint32_t *w, const char *message, uint32_t *pos, uint32_t mes_len, const unsigned char *mes_bkp)
{
	uint32_t i; // used in for loop

	for(i = 0; i <= 15; i++)
	{
		int32_t count = 0;
		while(*pos < mes_len && count <= 24)
		{
			w[i] += (((uint32_t)message[*pos]) << count);
			(*pos)++;
			count += 8;
		}
		while(count <= 24)
		{
			w[i] += (((uint32_t)mes_bkp[*pos - mes_len]) << count);
			(*pos)++;
			count += 8;
		}
	}
}

/**
 * @desc: start encryption based on w
 */
static void md5_process_part2(uint32_t abcd[4], uint32_t *w, const uint32_t k[64], const uint32_t s[64])
{
	uint32_t i; // used in for loop

	uint32_t a = abcd[0];
	uint32_t b = abcd[1];
	uint32_t c = abcd[2];
	uint32_t d = abcd[3];
	uint32_t f = 0;
	uint32_t g = 0;

	for(i = 0; i < 64; i++)
	{
		if(i >= 0 && i <= 15)
		{
			f = (b & c) | ((~b) & d);
			g = i;
		}else if(i >= 16 && i <= 31)
		{
			f = (d & b) | ((~d) & c);
			g = (5 * i + 1) % 16;
		}else if(i >= 32 && i <= 47)
		{
			f = b ^ c ^ d;
			g = (3 * i + 5) % 16;
		}else if(i >= 48 && i <= 63)
		{
			f = c ^ (b | (~d));
			g = (7 * i) % 16;
		}
		uint32_t temp = d;
		d = c;
		c = b;
		b = ROTATELEFT((a + f + k[i] + w[g]), s[i]) + b;
		a = temp;
	}

	abcd[0] += a;
	abcd[1] += b;
	abcd[2] += c;
	abcd[3] += d;
}

/**
 * @desc: format the output, convert numbers to hexdecimal string and store them in result
 */
static void format_output(char *result, size_t size, const uint32_t *abcd, uint32_t flag)
{
	uint32_t i; // used in for loop
	memset(result, 0, size);
	uint32_t ptr = 0;
	for(i = 0; i < 4; i++)
	{
		ptr += snprintf(result + ptr, size - ptr, (flag == 0)?TO_HEX_FMT_U:TO_HEX_FMT_L, (abcd[i] & 0x000000FF));
		ptr += snprintf(result + ptr, size - ptr, (flag == 0)?TO_HEX_FMT_U:TO_HEX_FMT_L, (abcd[i] & 0x0000FF00) >> 8 );
		ptr += snprintf(result + ptr, size - ptr, (flag == 0)?TO_HEX_FMT_U:TO_HEX_FMT_L, (abcd[i] & 0x00FF0000) >> 16);
		ptr += snprintf(result + ptr, size - ptr, (flag == 0)?TO_HEX_FMT_U:TO_HEX_FMT_L, (abcd[i] & 0xFF000000) >> 24);
	}
}


/**
 * @input: result -- store the calculation result
 *         size   -- size of result. Make sure it's at least 33
 *                   since the result is a 32-byte hexdecimal string.
 *         message-- string to be encrypted
 *         flag   -- 0 means upper case output, 1 means lower case output
 * @return: 0 -- success
 *          1 -- result size less than 33
 *          2 -- calloc failed
 */
int32_t md5(char *result, size_t size, const char *message, uint32_t flag){
	if (result == NULL || size < 33)
	{
		return 1;
	}

	uint32_t *w = (uint32_t *)calloc(16, sizeof(uint32_t));
	if(w == NULL)
	{
		return 2;
	}

	uint32_t i; // used in for loop

	uint32_t mes_len = (uint32_t) strlen(message);
	uint32_t looptimes = (mes_len + 8) / 64 + 1;
	uint32_t abcd[] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};

	const uint32_t k[]={
			0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,
			0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,0x698098d8,
			0x8b44f7af,0xffff5bb1,0x895cd7be,0x6b901122,0xfd987193,
			0xa679438e,0x49b40821,0xf61e2562,0xc040b340,0x265e5a51,
			0xe9b6c7aa,0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
			0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,0xa9e3e905,
			0xfcefa3f8,0x676f02d9,0x8d2a4c8a,0xfffa3942,0x8771f681,
			0x6d9d6122,0xfde5380c,0xa4beea44,0x4bdecfa9,0xf6bb4b60,
			0xbebfbc70,0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,
			0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,0xf4292244,
			0x432aff97,0xab9423a7,0xfc93a039,0x655b59c3,0x8f0ccc92,
			0xffeff47d,0x85845dd1,0x6fa87e4f,0xfe2ce6e0,0xa3014314,
			0x4e0811a1,0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391
	};

	const uint32_t s[]={
			7,12,17,22,7,12,17,22,7,12,17,22,7,
			12,17,22,5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
			4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,6,10,
			15,21,6,10,15,21,6,10,15,21,6,10,15,21
	};

	uint32_t pos = 0; // position pointer for message string
	uint32_t bkp_len = 64 * looptimes - mes_len;
	unsigned char *bkp_mes = (unsigned char *)calloc(1, bkp_len);
	if(bkp_mes == NULL)
	{
		free(w);
		return 2;
	}

	bkp_mes[0] = (unsigned char)(0x80);
	uint64_t mes_bit_len = ((uint64_t)mes_len) * 8;
	for(i = 0; i < 8; i++)
	{
		bkp_mes[bkp_len-i-1] = (unsigned char)((mes_bit_len & (0x00000000000000FF << (8 * (7 - i)))) >> (8 * (7 - i)));
	}

	for(i = 0; i < looptimes; i++)
	{
		memset(w, 0, 16 * sizeof(uint32_t));
		md5_process_part1(w, message, &pos, mes_len, bkp_mes); // compute w
		md5_process_part2(abcd, w, k, s); // calculate md5 and store the result in abcd
	}
	free(w);
	free(bkp_mes);

	format_output(result, size, abcd, flag);
	return 0;
}