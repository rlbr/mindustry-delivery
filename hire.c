#include "c2logic/builtins.h"
#include "c2logic/io.h"
#include "helpers/consts.h"
#include "helpers/setup.c"
#include "helpers/utils.c"
extern struct MindustryObject cell1;
extern struct MindustryObject unit;
void main() {
	setup();
	ubind(UNIT);
	int flag = sensor(unit, "flag");
	int ident = get_flag(flag, F_IDENT);
	if (ident != IDENT) {
		flag = mod_flag(flag, F_IDENT, IDENT);
		flag = mod_flag(flag, F_MODE, IDLE);
		unit_flag(flag);
	}
}
