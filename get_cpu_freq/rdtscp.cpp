#include <stdio.h>
#include <unistd.h>

unsigned long long get_cycles() {
    long long out;
    asm volatile(
        "RDTSCP;"  /* outputs to EDX:EAX and the (unused) cpuid to ECX*/
        "SHLQ $32,%%rdx;"
        "ORQ %%rdx,%%rax;"
        "MOVQ %%rax,%0;"
        :"=r"(out)
        : /*no input*/
        :"rdx","rax", "rcx"
    );
    return out;
}

int main() {
    unsigned long long start, end = 0;
    start = get_cycles();
    sleep(4);
    end = get_cycles();
    printf("%lld cycles/s\n", (end - start)/4);
    return 0;
}
