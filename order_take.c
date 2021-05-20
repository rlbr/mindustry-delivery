#include "c2logic/builtins.h"
#include "helpers/consts.h"
#include "helpers/setup.c"
#include "helpers/utils.c"
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
	int this_vault_id = read(cell1, 0);
	ubind("flare");
	int flag = sensor(unit, "flag");
	double ident = get_flag(flag, F_IDENT);
	double vx = sensor(vault1, "x");
	double vy = sensor(vault1, "y");
	if (ident != IDENT)
		return;
	double mode = get_flag(flag, F_MODE);
    if ((mode == LOADING) | (mode == CLAIMED))
        return;
	if (mode == IDLE) {
		double resource_int = get_low_resource_int();
		double count = count_from_resource_int(vault1, resource_int);
		double storage = sensor(vault1, "itemCapacity");
		// don't be greedy
		if (count / storage > THRESHOLD_FULL) {
			return;
		}

		// claim any idle units immediately
        flag = mod_flag(flag, F_MODE, CLAIMED);
        unit_flag(flag);
        // set relevant parameters
        flag = mod_flag(flag, F_RESOURCE, resource_int);
		flag = mod_flag(flag, F_VAULT_ID, this_vault_id);
        flag = mod_flag(flag, F_MODE, LOADING);
		unit_flag(flag);

	} else {
		int unit_vault_id = get_flag(flag, F_VAULT_ID);
		// check if we own this unit
		if (this_vault_id != unit_vault_id)
			return;
		// better throughput if we can move units we own at the same time
		if (!unit_within(vx, vy, 2)) {
			unit_move(vx, vy);
			unit_item_drop(vault1, INCR_DROP);
			return;
		}
		// unit has arrived
		unit_item_drop(vault1, INCR_DROP);
		// mark as idle
		flag = mod_flag(flag, F_MODE, IDLE);
		unit_flag(flag);
	}
}
