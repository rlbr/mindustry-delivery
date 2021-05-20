#include "c2logic/builtins.h"
#include "c2logic/io.h"
#include "helpers/consts.h"
#include "helpers/setup.c"
#include "helpers/utils.c"
extern struct MindustryObject cell1;
extern struct MindustryObject unit;
extern struct MindustryObject message2;
void main() {
	setup();
	ubind("flare");
	int flag = sensor(unit, "flag");
	int ident = get_flag(flag, F_IDENT);
	if (ident != IDENT) {
		flag = mod_flag(flag, F_IDENT, IDENT);
		printdln(flag);
		flag = mod_flag(flag, F_MODE, FULL);
		printdln(flag);
		printflush(message2);
		unit_flag(flag);
	}
}
