#include "c2logic/builtins.h"
#include "c2logic/io.h"
#include "helpers/consts.h"
#include "helpers/setup.c"
#include "helpers/utils.c"
extern struct MindustryObject cell1;
extern struct MindustryObject vault1;
extern struct MindustryObject unit;
extern struct MindustryObject message1;

double get_low_resource_int() {
	double low_resource_int = read(cell1, OFFSET_RESOURCE_NEEDED);
	double low_resource_count = 90000000;
	double res_count;
	double res_int;
	int resources_written = read(cell1, OFFSET_NUM_RESOURCES_NEEDED);
	for (int i = 0; i < resources_written; i++) {
		res_int = read(cell1, OFFSET_RESOURCE_NEEDED + i);
		res_count = count_from_resource_int(vault1, res_int);
		if (res_count < low_resource_count) {
			low_resource_count = res_count;
			low_resource_int = res_int;
		}
	}
	return low_resource_int;
}

void main_inner() {
	setup();
	println("SETUP");
	int this_vault_id = read(cell1, 0);
	print("VAULT_ID ");
	printdln(this_vault_id);
	ubind(UNIT);
	int flag = sensor(unit, "flag");
	double ident = get_flag(flag, F_IDENT);
	print("IDENT ");
	printdln(ident);
	double vx = sensor(vault1, "x");
	double vy = sensor(vault1, "y");
	if (ident != IDENT) {
		println("WRONG IDENT");
		return;
	}
	double mode = get_flag(flag, F_MODE);
	print("MODE ");
	printdln(mode);
	if ((mode == LOADING) | (mode == CLAIMED)) {
		println("WRONG MODE");
		return;
	}
	double resource_int = get_low_resource_int();
	print("RESOURCE ");
	printdln(resource_int);
	if (mode == IDLE) {
		double count = count_from_resource_int(vault1, resource_int);
		double storage = sensor(vault1, "itemCapacity");
		// don't be greedy
		if (count / storage > THRESHOLD_FULL) {
			return;
		}
		println("NOT FULL");
		// claim any idle units immediately
		flag = mod_flag(flag, F_MODE, CLAIMED);
		unit_flag(flag);
		println("CLAIMED");
		// set relevant parameters
		flag = mod_flag(flag, F_RESOURCE, resource_int);
		flag = mod_flag(flag, F_VAULT_ID, this_vault_id);
		flag = mod_flag(flag, F_MODE, LOADING);
		unit_flag(flag);
	}
}
void main() {
	main_inner();
	printflush(message1);
}
