#ifndef roman_h
#define roman_h


#define ROMAN_MAX_NUMBER_YEAR   3999

#define ROMAN_MAX_STRING_LENGTH 9       /* 3999 = MMMCMXCIX */


extern char *roman_name(void);

extern int number2roman(unsigned number, char *roman);
extern int roman2number(char *roman, unsigned *number);

#endif
