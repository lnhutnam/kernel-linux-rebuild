#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

#if defined(__x86_64__)
#define pnametoid 436
#define pidtoname 437
#elif defined(__i386__)
#define pnametoid 436
#define pidtoname 437
#else
#define pnametoid 436
#define pidtoname 437
#endif

int main() {
    printf("[DEBUG] Call pnametoid (%d)\n", pnametoid);
    printf("[DEBUG] Pnametoid return %d\n", (int)syscall(pnametoid, (char *)"firefox"));
    printf("[DEBUG] Call pidtoname (%d)\n", pidtoname);
    char buf[256];
    buf[0] = '\0';
    printf("[DEBUG] Pidtoname return %d\n", (int)syscall(pidtoname, (int)getpid(), (char *)buf, (int)256));
    printf("[DEBUG] Process name: %s\n", buf);
    return 0;
}
