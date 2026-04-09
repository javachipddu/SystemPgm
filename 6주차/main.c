#include <stdio.h>

extern void helloA();
extern void helloB();

int main() {
    helloA();
    helloB();
    return 0;
}