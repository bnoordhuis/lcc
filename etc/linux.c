/* x86s running Linux */

#include <string.h>

static char rcsid[] = "$Id$";

#ifndef LCCDIR
#define LCCDIR "/usr/local/lib/lcc/"
#endif

char *suffixes[] = { ".c", ".i", ".s", ".o", ".out", 0 };
char inputs[256] = "";
char *cpp[] = { LCCDIR "lib/lcc/cpp",
	"-U__GNUC__", "-D_POSIX_SOURCE", "-D__STDC__=1", "-D__STRICT_ANSI__",
	"-Dunix", "-Di386", "-Dlinux",
	"-D__unix__", "-D__i386__", "-D__linux__", "-D__signed__=signed",
	"$1", "$2", "$3", 0 };
char *include[] = {
	/*  0 */ "-I" LCCDIR "include/x86/linux",
	/*  1 */ "-I/usr/include",
	0 };
char *com[] = {LCCDIR "lib/lcc/rcc", "-target=x86/linux", "$1", "$2", "$3", 0 };
char *as[] = { "/usr/bin/as", "--32", "-o", "$3", "$1", "$2", 0 };
char *ld[] = {
	/*  0 */ "/usr/bin/ld", "-m", "elf_i386", "-dynamic-linker",
	/*  4 */ "/lib32/ld-linux.so.2", "-o", "$3",
	/*  7 */ "/usr/lib32/crt1.o", "/usr/lib32/crti.o", "$1", "$2",
	/* 11 */ "-L" LCCDIR "lib/lcc",
	/* 12 */ "-lc", "-lm",
	/* 14 */ "",
	/* 15 */ "/usr/lib32/crtn.o",
	0 };

extern char *concat(char *, char *);

int option(char *arg) {
  	if (strncmp(arg, "-lccdir=", 8) == 0) {
		if (strcmp(cpp[0], LCCDIR "lib/lcc/cpp") == 0)
			cpp[0] = concat(&arg[8], "/lib/lcc/cpp");
		include[0] = concat("-I", concat(&arg[8], "/include/x86/linux"));
		ld[11] = concat("-L", concat(&arg[8], "/lib/lcc"));
		com[0] = concat(&arg[8], "/lib/lcc/rcc");
	} else if (strcmp(arg, "-p") == 0 || strcmp(arg, "-pg") == 0) {
		ld[7] = "/usr/lib32/gcrt1.o";
		ld[14] = "-lgmon";
	} else if (strcmp(arg, "-b") == 0) 
		;
	else if (strcmp(arg, "-g") == 0)
		;
	else if (strncmp(arg, "-ld=", 4) == 0)
		ld[0] = &arg[4];
	else if (strcmp(arg, "-static") == 0) {
		ld[3] = "-static";
		ld[4] = "";
	} else
		return 0;
	return 1;
}
