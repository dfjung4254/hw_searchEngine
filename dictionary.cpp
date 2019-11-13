#include <dictionary.h>

bool isAlpha(int c){
    return c>='a' && c<='z' || c>='A' && c<='Z';
}

bool isDigit(int c){
    return c>='0' && c<='9';
}

bool isBlank(int c){
    return c==' ' || c=='\t' || c=='\n';
}

/* 한글, 한문 등 */
bool isOtherCode(int c){
    /* ascii 나 eof 는 아님 */
    return c<-1 || c>127;
}