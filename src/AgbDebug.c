// ����gba������
// by laqieer
// 2017/8/26

#include "AgbDebug.h"

// NO$GBA Debug Message

// originally for auto no$gba support, the string "no$gba" should be at this address,
// the user needs to read this string out as the memory viewer won't show it.
#define NOCASHGBAIDADDR 0x4FFFA00
#define NOCASHGBAPRINTADDR1 0x4FFFA10 // automatically adds a newline after the string has finished
#define NOCASHGBAPRINTADDR2 0x4FFFA14 // does not automatically add the newline. by default, NOCASHGBAPRINTADDR2 is used. this is used to keep strings consistent between no$gba and VBA-RR, but a user can choose to forgo this.

// Write to EZ Omega Flashcard S71GL064A08 SRAM

void EZO_SetRampage(unsigned short page)
{
	*(volatile unsigned short *)0x9fe0000 = 0xd200;
	*(volatile unsigned short *)0x8000000 = 0x1500;
	*(volatile unsigned short *)0x8020000 = 0xd200;
	*(volatile unsigned short *)0x8040000 = 0x1500;
	*(volatile unsigned short *)0x9c00000 = page;//E0
	*(volatile unsigned short *)0x9fc0000 = 0x1500;
}

void EZO_WriteSram(unsigned int address, char * data , int size )
{
	for(int i = 0; i < size; i++)
		*(volatile char*)(address + i) = data[i];
}

// debug print log length

#define debug_print_length (*(unsigned int *)(0x0203FE00 - 4))

int strlen_new(const char* src)
{
    int len = 0;
    while(*src++ != '\0')
        len ++;
    return len;
}

// mGBA AGBPrint functions

#define AGB_PRINT_BUFFER ((volatile unsigned short *) (0x09FD0000))
#define AGB_PRINT_CONTEXT (( AGBPrintContext volatile *) (0x09FE20F8))
#define AGB_PRINT_PROTECT (*(volatile unsigned short *)(0x09FE2FFE))

typedef struct
{
    unsigned short request;
    unsigned short bank;
    unsigned short get;
    unsigned short put;
} AGBPrintContext;

void AGBPrintFlush()
{
  asm volatile("swi 0xfa");
}

void AGBPrintInit(void)
{
	AGB_PRINT_PROTECT = (unsigned short) 0x20;
	AGB_PRINT_CONTEXT->request = (unsigned short) 0x00;
    AGB_PRINT_CONTEXT->get = (unsigned short) 0x00;
    AGB_PRINT_CONTEXT->put = (unsigned short) 0x00;
    AGB_PRINT_CONTEXT->bank = (unsigned short) 0xFD;
    AGB_PRINT_PROTECT = (unsigned short) 0x00;
}

static void AGBPutChar(const char c)
{
    unsigned short data = AGB_PRINT_BUFFER[AGB_PRINT_CONTEXT->put >> 1];

    AGB_PRINT_PROTECT = (unsigned short) 0x20;
    data = (AGB_PRINT_CONTEXT->put & 1) ? (c << 8) | (data & 0xFF) : (data & 0xFF00) | c;
    AGB_PRINT_BUFFER[AGB_PRINT_CONTEXT->put >> 1] = data;
    AGB_PRINT_CONTEXT->put++;
    AGB_PRINT_PROTECT = (unsigned short) 0x00;
}

// Emulator / Flashcard
void _print(char *s)
{
#ifdef __DEBUG_VBA_THUMB
  asm volatile("mov r0, %0;"
               "swi 0xff;"
               : // no ouput
               : "r" (s)
               : "r0");
	return;
#endif
#ifdef __DEBUG_VBA_ARM
  asm volatile("mov r0, %0;"
               "swi 0xff0000;"
               : // no ouput
               : "r" (s)
               : "r0");
	return;
#endif
#ifdef __DEBUG_MGBA
	AGBPrintInit();
	while (*s)
    {
        AGBPutChar(*s);
        s++;
    }
	AGBPrintFlush();
	return;
#endif
#ifdef __DEBUG_NOCASH
	*(volatile unsigned int*)NOCASHGBAPRINTADDR2 = s;
	return;
#endif
#ifdef __DEBUG_EZ_OMEGA
	EZO_SetRampage(0xB0);
	EZO_WriteSram(0x0E000000 + debug_print_length, s, strlen_new(s) + 1);
	debug_print_length += strlen_new(s) + 1;
	EZO_SetRampage(0);
	return;
#endif
}

// ��ͣ
void _pause()
{
	while(1);
}

/*���ܣ����ַ��� ��ʽ����ӡһ���ַ���
*��������ʽ�����ַ���
*ע�⣺����Ǽ��װ汾 (%02x ���)
* %-3s���У� %fҲ���У� %X����
*/
int sprintf(char * str, const char *fmt, ...)
{
    int count = 0;
    char c;
    char *s;
    int n;
    
    int index = 0;
    int ret = 2;
    
    char buf[65];
    char digit[16];
    int num = 0;
    int len = 0;
    
    memset(buf, 0, sizeof(buf));
    memset(digit, 0, sizeof(digit));

    va_list ap;
    
    va_start(ap, fmt);
    
    while(*fmt != '\0')
    {
//        printf("*fmt=[%c]\n", *fmt);
        if(*fmt == '%')
        {
            fmt++;
            switch(*fmt)
         {
                case 'd': /*����*/
                {
                        n = va_arg(ap, int);
                        if(n < 0)
                        {
                            *str = '-';
                            str++;
                            n = -n;
                        }
//                        printf("case d n=[%d]\n", n);
                        itoa(n, buf);
//                        printf("case d buf=[%s]\n", buf);
                        memcpy(str, buf, strlen(buf));
                        str += strlen(buf);
                        break;
                }    
                case 'c': /*�ַ���*/
                {
                        c = va_arg(ap, int);
                        *str = c;
                        str++;
                        
                        break;
                }
                case 'x': /*16����*/
                {
                        n = va_arg(ap, int);
                        xtoa(n, buf);
                        memcpy(str, buf, strlen(buf));
                        str += strlen(buf);
                        break;
                }
                case 's': /*�ַ���*/
                {
                        s = va_arg(ap, char *);
                        memcpy(str, s, strlen(s));
                        str += strlen(s);
                        break;
                }
                case '%': /*���%*/
                {
                    *str = '%';
                    str++;
                    
                    break;
                }
                case '0': /*λ�������0*/
                {
                        index = 0;
                        num = 0;
                        memset(digit, 0, sizeof(digit));
                        
                        while(1)
                        {
                                fmt++;
                                ret = isDigit(*fmt);
                                if(ret == 1) //������
                                {
                                        digit[index] = *fmt;
                                        index++;
                                }
                                else
                                {
                                        num = atoi(digit);
                                        break;
                                }
                        }
                        switch(*fmt)
                     {
                                case 'd': /*����*/
                                {
                                        n = va_arg(ap, int);
                                        if(n < 0)
                                        {
                                            *str = '-';
                                            str++;
                                            n = -n;
                                        }    
                                        itoa(n, buf);
                                        len = strlen(buf);
                                        if(len >= num)
                                        {
                                                memcpy(str, buf, strlen(buf));
                                                str += strlen(buf);
                                        }
                                        else
                                        {
                                                memset(str, '0', num-len);
                                                str += num-len;
                                                memcpy(str, buf, strlen(buf));
                                                str += strlen(buf);
                                        }
                                        break;
                                }    
                                case 'x': /*16����*/
                                {
                                        n = va_arg(ap, int);
                                        xtoa(n, buf);
                                        len = strlen(buf);
                                        if(len >= num)
                                        {
                                                memcpy(str, buf, len);
                                                str += len;
                                        }            
                                        else
                                        {
                                                memset(str, '0', num-len);
                                                str += num-len;
                                                memcpy(str, buf, len);
                                                str += len;
                                        }
                                        break;
                                }
                                case 's': /*�ַ���*/
                                {
                                        s = va_arg(ap, char *);
                                        len = strlen(s);
                                        if(len >= num)
                                        {
                                                memcpy(str, s, strlen(s));
                                                str += strlen(s);
                                        }
                                        else
                                        {
                                                memset(str, '0', num-len);
                                                str += num-len;
                                                memcpy(str, s, strlen(s));
                                                str += strlen(s);
                                        }
                                        break;
                                }
                                default:
                                        break;
                        }
                }
                default:
                        break;
            }
        }
        else
        {
            *str = *fmt;
            str++;
            
            if(*fmt == '\n')
            {
                    
            }
        }
        fmt++;
    }

    va_end(ap);

    return count;
}

/*
*���ܣ�����(int) ת���� �ַ���(char)
*ע�⣺���� % / ���ŵĻ���ֻ����ȷ��ӡ:0...9�����ֶ�Ӧ���ַ�'0'...'9'
*/
void itoa(unsigned int n, char * buf)
{
        int i;
        
        if(n < 10)
        {
                buf[0] = n + '0';
                buf[1] = '\0';
                return;
        }
//      itoa(n / 10, buf);
//		undefined reference to `__aeabi_uidiv'
		itoa(FE7JDiv(n,10), buf);

        for(i=0; buf[i]!='\0'; i++);
        
//      buf[i] = (n % 10) + '0';
//		undefined reference to `__aeabi_uidivmod'		
        buf[i] = FE7JMod(n,10) + '0';

        buf[i+1] = '\0';
}

/*
*���ܣ��ַ���(char) ת���� ����(int)
*/
int atoi(char* pstr) 
{
        int int_ret = 0; 
        int int_sign = 1; //�����ű�ʾ 1:���� -1:����
        
        if(pstr == '\0') //�ж�ָ���Ƿ�Ϊ��
        {
                return -1;
        }
        while(((*pstr) == ' ') || ((*pstr) == '\n') || ((*pstr) == '\t') || ((*pstr) == '\b')) 
        {
                pstr++; //����ǰ��Ŀո��ַ� 
        }
        
        /* 
        * �ж������� 
        * ��������ţ�ָ��ָ����һ���ַ� 
        * ����Ƿ��ţ��ѷ��ű��ΪInteger_sign��-1��Ȼ���ٰ�ָ��ָ����һ���ַ� 
        */ 
        if(*pstr == '-') 
        { 
                int_sign = -1; 
        } 
        if(*pstr == '-' || *pstr == '+') 
        { 
                pstr++; 
        } 
        
        while(*pstr >= '0' && *pstr <= '9') //�������ַ������ת�����������������ת���õ���������Ret_Integer 
        {
                int_ret = int_ret * 10 + *pstr - '0'; 
                pstr++; 
        }
        int_ret = int_sign * int_ret; 
        
        return int_ret;
} 

/*
*���ܣ�16������(0x) ת���� �ַ���(char)
*ע�⣺���� % / ���ŵĻ���ֻ����ȷ��ӡ��0...9..15������,��Ӧ��'0'...'9''A'...'F'
*ע�⣺���ڱ������⣬�����������ʱ��uart_sendByte_hex()�������
*/
void xtoa(unsigned int n, char * buf)
{
        int i;
        
        if(n < 16)
        {
                if(n < 10)
                {
                        buf[0] = n + '0';
                }
                else
                {
                        buf[0] = n - 10 + 'a';
                }
                buf[1] = '\0';
                return;
        }
        xtoa(n / 16, buf);
        
        for(i = 0; buf[i] != '\0'; i++);
        
        if((n % 16) < 10)
        {
                buf[i] = (n % 16) + '0';
        }
        else
        {
                buf[i] = (n % 16) - 10 + 'a';
        }
        buf[i + 1] = '\0';
}

/*
 * �ж�һ���ַ��Ƿ�����
 */
int isDigit(unsigned char c)
{
    if (c >= '0' && c <= '9')
        return 1;
    else
        return 0; 
}

/*
 * �ж�һ���ַ��Ƿ�Ӣ����ĸ
 */
int isLetter(unsigned char c)
{
    if (c >= 'a' && c <= 'z')
        return 1;
    else if (c >= 'A' && c <= 'Z')
        return 1; 
    else
        return 0;
}

/**
 * memset - Fill a region of memory with the given value
 * @s: Pointer to the start of the area.
 * @c: The byte to fill the area with
 * @count: The size of the area.
 *
 * Do not use memset() to access IO space, use memset_io() instead.
 */
/*
void * memset(void * s,int c,unsigned int count)
{
    char *xs = (char *) s;

    while (count--)
        *xs++ = c;

    return s;
}
*/

/**
 * strcpy - Copy a %NUL terminated string
 * @dest: Where to copy the string to
 * @src: Where to copy the string from
 */
char * strcpy(char * dest,const char *src)
{
    char *tmp = dest;

    while ((*dest++ = *src++) != '\0')
        /* nothing */;
    return tmp;
}


/**
 * strlen - Find the length of a string
 * @s: The string to be sized
 */
unsigned int strlen(const char * s)
{
    const char *sc;

    for (sc = s; *sc != '\0'; ++sc)
        /* nothing */;
    return sc - s;
}

/**
 * strcat - Append one %NUL-terminated string to another
 * @dest: The string to be appended to
 * @src: The string to append to it
 */
char * strcat(char * dest, const char * src)
{
    char *tmp = dest;

    while (*dest)
        dest++;
    while ((*dest++ = *src++) != '\0')
        ;

    return tmp;
}

/*
int printf (const char * szFormat, ...)
{
	char szBuffer[BufferMaxLength];
	int strLen = -1;
	strLen = sprintf(szBuffer,szFormat,...);	// ����������
	_print(szBuffer);
}
*/

void * memcpy(void * dest,const void *src,unsigned int count)
{
	if(count & (32 - 1) == 0)
		FE7JCPUFastSet(src,dest,count>>2);
	else
		if(count & (4 - 1) == 0)
			FE7JCPUSet(src,dest,(count>>2)|(1<<26));
		else
			if(count & (2 - 1) == 0)
				FE7JCPUSet(src,dest,count>>1);
			else
				while(count--)
					((char *)dest)[count] = ((char *)src)[count];
}

void * memset(void * s,int c,unsigned int count)
{
	if(count & (32 - 1) == 0)
		FE7JCPUFastSet(&c,s,(count>>2)|(1<<24));
	else
		if(count & (4 - 1) == 0)
			FE7JCPUSet(&c,s,(count>>2)|(1<<24)|(1<<26));
		else
			if(count & (2 - 1) == 0)
				FE7JCPUSet(&c,s,(count>>1)|(1<<24));
			else
				while(count--)
					((char *)s)[count] = c;
}

