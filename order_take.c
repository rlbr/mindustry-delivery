#include "c2logic/builtins.h"
#include "consts.h"
#include "setup.c"
#include "utils.c"
extern struct MindustryObject cell1;
extern struct MindustryObject vault1;
extern struct MindustryObject unit;

double get_low_resource_int() {
	double low_resource_int = 0;
	double low_resource_count = 90000000;
	double res_count;
	double res_int;
	for (int i = 0; i < LEN_RESOURCE_NEEDED; i++) {
		res_int = read(cell1, OFFSET_RESOURCE_NEEDED + i);
		res_count = count_from_resource_int(vault1, res_int);
		if (res_count < low_resource_count) {
			low_resource_count = res_count;
			low_resource_int = res_int;
		}
	}
	return low_resource_int;
}

void main() {
	setup();
	ubind("flare");
	int flag = carrier_state();
	double ident = get_flag(flag, F_IDENT);
	if (ident != IDENT)
		return;
	double mode = get_flag(flag, F_MODE);
	if (mode != FULL)
		return;
	double vx = sensor(vault1, "x");
	double vy = sensor(vault1, "y");
	double resource_int = get_low_resource_int();
	double count = count_from_resource_int(vault1, resource_int);
	double storage = sensor(vault1, "itemCapacity");
	if (count / storage > THRESHOLD_FULL)
		return;
	if (unit_within(vx, vy, 4)) {
		count = count_from_resource_int(unit, resource_int);
		while (count > 0) {
			unit_item_drop(vault1, INCR_DROP);
		}
		flag = mod_flag(flag, F_MODE, EMPTY);
		flag = mod_flag(flag, F_RESOURCE, get_low_resource_int());
		flag = mod_flag(flag, F_MOVING, false);
		unit_flag(flag);
	} else {
		if (get_flag(flag, F_MOVING))
			return;
		flag = mod_flag(flag, F_MOVING, true);
		unit_flag(flag);
		unit_approach(vx, vy, 2);
	}
}
