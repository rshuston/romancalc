#ifndef strutils_h
#define strutils_h

extern char *strutils_name(void);

extern char *trim(char *s);
extern char *lowercase(char *s);
extern char *uppercase(char *s);

extern int strConsistsOfCharSet(char *s, char *charSet);

#endif
