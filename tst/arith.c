int i0(int x) { return x * 0; }
int i1(int x) { return 0 * x; }
int i2(int x) { return x * 1; }
int i3(int x) { return 1 * x; }
int i4(int *x) { return *x * 0; }
int i5(int *x) { return 0 * *x; }
int i6(int *x) { return *x * 1; }
int i7(int *x) { return 1 * *x; }
int i8(volatile int *x) { return *x * 0; }
int i9(volatile int *x) { return 0 * *x; }
int ia(volatile int *x) { return *x * 1; }
int ib(volatile int *x) { return 1 * *x; }
int ic(int (*x)(void)) { return x() * 0; }
int id(int (*x)(void)) { return 0 * x(); }

unsigned u0(unsigned x) { return x * 0; }
unsigned u1(unsigned x) { return 0 * x; }
unsigned u2(unsigned x) { return x * 1; }
unsigned u3(unsigned x) { return 1 * x; }
unsigned u4(unsigned *x) { return *x * 0; }
unsigned u5(unsigned *x) { return 0 * *x; }
unsigned u6(unsigned *x) { return *x * 1; }
unsigned u7(unsigned *x) { return 1 * *x; }
unsigned u8(volatile unsigned *x) { return *x * 0; }
unsigned u9(volatile unsigned *x) { return 0 * *x; }
unsigned ua(volatile unsigned *x) { return *x * 1; }
unsigned ub(volatile unsigned *x) { return 1 * *x; }
unsigned uc(unsigned (*x)(void)) { return x() * 0; }
unsigned ud(unsigned (*x)(void)) { return 0 * x(); }
