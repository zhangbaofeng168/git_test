#ifndef __STRING_H__
#define __STRING_H__

char *mystrcpy(char *dest, const char *src)
{
	int i = 0;
	const char *ptr = src;
	
	while(ptr[i]) {
		dest[i] = ptr[i];
		i++;
	}
	
	return dest;
}

int strlen(char *str)
{
	int len = 0;

	while(str[len++]); 
	
	return len;	
}

#endif /*__STRING_H__*/
