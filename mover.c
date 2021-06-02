#include "c2logic/builtins.h"
#include "c2logic/io.h"
#include "helpers/consts.h"
#include "helpers/setup.c"
#include "helpers/utils.c"
extern struct MindustryObject cell1;
extern struct MindustryObject vault1;
extern struct MindustryObject unit;
extern struct MindustryObject message1;
void main() {
	setup();
	int this_vault_id = read(cell1, 0);
	ubind(UNIT);
	int flag = sensor(unit, "flag");
	double ident = get_flag(flag, F_IDENT);
	double vx = sensor(vault1, "x");
	double vy = sensor(vault1, "y");
	if (ident != IDENT) {
		return;
	}
	int flag = sensor(unit, "flag");
	double mode = get_flag(flag, F_MODE);
	if ((mode == LOADING) | (mode == CLAIMED)) {
		return;
	}
	if (mode != IDLE) {
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
