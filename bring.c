#include "c2logic/builtins.h"
#include "helpers/consts.h"
#include "helpers/setup.c"
#include "helpers/utils.c"
extern struct MindustryObject cell1;
extern struct MindustryObject nucleus1;
extern struct MindustryObject unit;

void main() {
	setup();
	ubind("flare");
	int flag = carrier_state(unit);
	double ident = get_flag(flag, F_IDENT);
	if (ident != IDENT) {
		return;
	}
	double mode = get_flag(flag, F_MODE);
	if (mode != EMPTY) {
		return;
	}
	double nx = sensor(nucleus1, "x");
	double ny = sensor(nucleus1, "y");
	double resource_int = get_flag(flag, F_RESOURCE);
	double in_core = count_from_resource_int(nucleus1, resource_int);
	if (in_core < THRESHOLD_FULL) {
		return;
	}
	if (unit_within(nx, ny, 4)) {
		double count = count_from_resource_int(unit, resource_int);
		take_from_resource_int(nucleus1, resource_int);
		count = count_from_resource_int(unit, resource_int);
		flag = mod_flag(flag, F_MODE, FULL);
		flag = mod_flag(flag, F_MOVING, false);
		unit_flag(flag);
	} else {
		if (get_flag(flag, F_MOVING)) {
			return;
		}
		flag = mod_flag(flag, F_MOVING, true);
		unit_flag(flag);
		unit_approach(nx, ny, 2);
	}
}
