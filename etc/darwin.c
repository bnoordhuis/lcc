#include <string.h>

static char rcsid[] = "$Id$";

#ifndef LCCDIR
#define LCCDIR "/usr/local/lib/lcc/"
#endif

char *suffixes[] = { ".c", ".i", ".s", ".o", ".out", 0 };
char inputs[256] = "";
char *cpp[] = {
	LCCDIR "lib/lcc/cpp",
	"-D__STDC__=1",
	"-D__i386__=1",
	"$1", "$2", "$3",
	0 };
char *include[] = {
	"-I" LCCDIR "include/x86/darwin",
	"-I/usr/include",
	"-I/Applications/Xcode.app/Contents/Developer/Platforms/" /* no comma */
	"MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include",
	0 };
char *com[] = {
	LCCDIR "lib/lcc/rcc",
	"-target=x86/darwin",
	"$1", "$2", "$3",
	0 };
char *as[] = {
	"/usr/bin/as", "-mmacosx-version-min=10.8", "-arch", "i386",
	"-o", "$3", "$1", "$2",
	0 };
char *ld[] = {
	"/usr/bin/ld", "-macosx_version_min", "10.8", "-arch", "i386",
	"-no_pie", "-read_only_relocs", "suppress",
	"-o", "$3", "$1", "$2", "-lSystem",
	0 };

int option(char *arg) {
	return 1;
}
