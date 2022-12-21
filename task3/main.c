#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

const char* FORMATS[] = {
    "%s",
    "%d",
    "%ld",
    "%f"    
};

const int FORMATS_C = 4;

int count(const char* str, const char* substr) {
    int count = 0;
    const char *tmp = str;
    while((tmp = strstr(tmp, substr)))
    {
        count++;
        tmp++;
    }
    return count;
}

void print_string_f(const char* s) {
    int p = 0;
    while(s[p]) {
        putchar(s[p]);
        p++;
    }
}

void print_string(va_list* args) {
    const char* s = va_arg(*args, char*);
    print_string_f(s);
}


void print_long(va_list* args) {
    long int a = va_arg(*args, long int);
    if (a == 0) {
        putchar('0');
        return;
    }

    int negative = 0;
    if (a < 0) {
        negative = 1;
        a = -a;
    }
    long int inverted = 1;
    while (a) {
        inverted = inverted * 10 + a % 10;
        a /= 10;
    }
    if (negative) putchar('-');
    while (inverted-1) {
        int v = inverted % 10;
        putchar(v + '1' - 1);
        inverted /= 10;
    }
}

void print_digit(va_list* args) {
    print_long(args);
}


void print_float(va_list* args) {
    const double a = va_arg(*args, double);
    char buf[10];
    gcvt(a, 7, buf);
    gcvt(a, 8, buf);
    buf[9] = '\0';
    print_string_f(buf);
}

void (*PRINT_FUNCS[])(va_list* args) = {
    print_string,
    print_digit,
    print_long,
    print_float
};

char* check_format(const char* fmt, int* i, const int fi, va_list* vlist) {
    const char* format = FORMATS[fi];
    int len = strlen(format);
    if (strncmp(format, fmt+*i, len) != 0) return "";
    *i += len-1;
    // printf("\nCALLING %d\n", fi);
    PRINT_FUNCS[fi](vlist);
    return "";
}

void my_printf(const char * fmt, ...) {
    // count format occurances
    int tCount = 0;
    for (int i = 0; i < FORMATS_C; i++) {
        int c = count(fmt, FORMATS[i]);
        tCount += c;
    }
    // initiate variadic vars
    va_list args;
    va_start(args, tCount);
    // print the string
    for (int i = 0; i < strlen(fmt); i++) {
        if (fmt[i] != '%') {
            putchar(fmt[i]);
            continue;
        }
        for (int fi = 0; fi < FORMATS_C; fi++) {
            const char* fs = check_format(fmt, &i, fi, &args);
            if (!strlen(fs)) continue;
            break;
        }
    }
    // end variadic vargs
    va_end(args);
}

int main() {
    printf("Hello, %s\n", "world");
    printf("%d + %d = %d\n", 2, 3, 5);
    printf("%s %d\n", "aa", 23);
    printf("%f %f %f\n", .1, 22.2, 9011.11111);
    
    printf("%d %s\n", "aa", 23); // segfaults
}