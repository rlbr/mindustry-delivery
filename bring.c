#include "c2logic/builtins.h"
#include "helpers/consts.h"
#include "helpers/setup.c"
#include "helpers/utils.c"
extern struct MindustryObject cell1;
extern struct MindustryObject nucleus1;
extern struct MindustryObject unit;

void main() {
	setup();
	ubind(UNIT);
	int flag = sensor(unit, "flag");
	double ident = get_flag(flag, F_IDENT);
	if (ident != IDENT) {
		return;
	}
	double nx = sensor(nucleus1, "x");
	double ny = sensor(nucleus1, "y");
	int flag = sensor(unit, "flag");
	double mode = get_flag(flag, F_MODE);
	if (mode == IDLE) {
		unit_move(nx, ny);
		return;
	} else if (mode == LOADING) {
		double resource_int = get_flag(flag, F_RESOURCE);
		double in_core = count_from_resource_int(nucleus1, resource_int);
		if (in_core < THRESHOLD_CORE_FULL) {
			flag = mod_flag(flag, F_MODE, IDLE);
			return;
		}
		if (!unit_within(nx, ny, 2)) {
			unit_move(nx, ny);
			return;
		}
		take_from_resource_int(nucleus1, resource_int);
		flag = mod_flag(flag, F_MODE, FULL);
		unit_flag(flag);
	}
}
