/**
 * File: ${FILE} for project Xserver
 * Email: xeapplee@gmail.com
 * website: https://www.supjos.cn
 * Author: Josin 
 */

#include "base64.h"

/* Encode the given str to the base64 code
 * RETURN:
 * The encoding string with the form of the base64
 * NOTE: free the return value after used. */
unsigned char *base64_encode(unsigned char *str)
{
	long len;
	long str_len;
	unsigned char *res;
	int i,j;

	unsigned char *base64_table= (unsigned char *) "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	str_len=strlen(str);
	if(str_len % 3 == 0)
		len=str_len/3*4;
	else
		len=(str_len/3+1)*4;

	res=malloc(sizeof(unsigned char)*len+1);
	res[len]='\0';

	for(i=0,j=0;i<len-2;j+=3,i+=4)
	{
		res[i]=base64_table[str[j]>>2];
		res[i+1]=base64_table[(str[j]&0x3)<<4 | (str[j+1]>>4)];
		res[i+2]=base64_table[(str[j+1]&0xf)<<2 | (str[j+2]>>6)];
		res[i+3]=base64_table[str[j+2]&0x3f];
	}

	switch(str_len % 3)
	{
		case 1:
			res[i-2]='=';
			res[i-1]='=';
			break;
		case 2:
			res[i-1]='=';
			break;
	}

	return res;
}

/* Base64 decode the encoding string to the raw string
 * Return value should be freed after used. */
unsigned char *base64_decode(unsigned char *code)
{
	int table[]={
		0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,62,0,0,0,
		63,52,53,54,55,56,57,58,
		59,60,61,0,0,0,0,0,0,0,0,
		1,2,3,4,5,6,7,8,9,10,11,12,
		13,14,15,16,17,18,19,20,21,
		22,23,24,25,0,0,0,0,0,0,26,
		27,28,29,30,31,32,33,34,35,
		36,37,38,39,40,41,42,43,44,
		45,46,47,48,49,50,51
	};
	long len;
	long str_len;
	unsigned char *res;
	int i,j;

	len=strlen(code);
	if(strstr(code,"=="))
		str_len=len/4*3-2;
	else if(strstr(code,"="))
		str_len=len/4*3-1;
	else
		str_len=len/4*3;

	res=malloc(sizeof(unsigned char)*str_len+1);
	res[str_len]='\0';

	for(i=0,j=0;i < len-2;j+=3,i+=4)
	{
		res[j] = ((unsigned char)table[code[i]])<<2 | (((unsigned char)table[code[i+1]])>>4);
		res[j+1] = (((unsigned char)table[code[i+1]])<<4) | (((unsigned char)table[code[i+2]])>>2);
		res[j+2] = (((unsigned char)table[code[i+2]])<<6) | ((unsigned char)table[code[i+3]]);
	}

	return res;

}