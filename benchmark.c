#include "c2logic/builtins.h"
#include "c2logic/io.h"
#include "helpers/consts.h"
#include "helpers/setup.c"
#include "helpers/utils.c"
extern struct MindustryObject message1;
extern struct MindustryObject time;
void main() {
	setup();
	int s = time;
	int result1 = get_flag(0, 0);
	int e = time;
	print("Read ");
	printdln(e - s);
	int s = time;
	int result2 = mod_flag(0, 0, 0);
	int e = time;
	print("Write ");
	printdln(e - s);
	printflush(message1);
}
