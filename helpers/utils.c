#include "c2logic/builtins.h"
#include "consts.h"
extern struct MindustryObject cell1;
void take_from_resource_int(struct MindustryObject obj, int resource_int) {
	if (resource_int == LEAD)
		unit_item_take(obj, "lead", INCR_DROP);
	if (resource_int == COPPER)
		unit_item_take(obj, "copper", INCR_DROP);
	if (resource_int == COAL)
		unit_item_take(obj, "coal", INCR_DROP);
	if (resource_int == SAND)
		unit_item_take(obj, "sand", INCR_DROP);
	if (resource_int == SCRAP)
		unit_item_take(obj, "scrap", INCR_DROP);
	if (resource_int == THORIUM)
		unit_item_take(obj, "thorium", INCR_DROP);
	if (resource_int == TITANIUM)
		unit_item_take(obj, "titanium", INCR_DROP);
	if (resource_int == SPORE_POD)
		unit_item_take(obj, "spore-pod", INCR_DROP);
	if (resource_int == PYRATITE)
		unit_item_take(obj, "pyratite", INCR_DROP);
	if (resource_int == SURGE_ALLOY)
		unit_item_take(obj, "surge-alloy", INCR_DROP);
	if (resource_int == PHASE_FABRIC)
		unit_item_take(obj, "phase-fabric", INCR_DROP);
	if (resource_int == PLASTANIUM)
		unit_item_take(obj, "plastanium", INCR_DROP);
	if (resource_int == SILICON)
		unit_item_take(obj, "silicon", INCR_DROP);
	if (resource_int == GRAPHITE)
		unit_item_take(obj, "graphite", INCR_DROP);
	if (resource_int == METAGLASS)
		unit_item_take(obj, "metaglass", INCR_DROP);
}
double count_from_resource_int(struct MindustryObject obj, int resource_int) {
	if (resource_int == LEAD)
		return sensor(obj, "lead");
	if (resource_int == COPPER)
		return sensor(obj, "copper");
	if (resource_int == COAL)
		return sensor(obj, "coal");
	if (resource_int == SAND)
		return sensor(obj, "sand");
	if (resource_int == SCRAP)
		return sensor(obj, "scrap");
	if (resource_int == THORIUM)
		return sensor(obj, "thorium");
	if (resource_int == TITANIUM)
		return sensor(obj, "titanium");
	if (resource_int == SPORE_POD)
		return sensor(obj, "spore-pod");
	if (resource_int == PYRATITE)
		return sensor(obj, "pyratite");
	if (resource_int == SURGE_ALLOY)
		return sensor(obj, "surge-alloy");
	if (resource_int == PHASE_FABRIC)
		return sensor(obj, "phase-fabric");
	if (resource_int == PLASTANIUM)
		return sensor(obj, "plastanium");
	if (resource_int == SILICON)
		return sensor(obj, "silicon");
	if (resource_int == GRAPHITE)
		return sensor(obj, "graphite");
	if (resource_int == METAGLASS)
		return sensor(obj, "metaglass");
}
int _get_flag(int flag, int _end, int mask) {
	int val = flag >> _end;
	return val & mask;
}
int _mod_flag(int flag, int _end, int mask, int val) {
	flag = flag & mask;
	val = val << _end;
	return flag | val;
}
int get_flag(int flag, int index) {
	int _end = read(cell1, OFFSET_ENDS + index);
	int mask = read(cell1, OFFSET_READ_MASK + index);
	return _get_flag(flag, _end, mask);
}
int mod_flag(int flag, int index, int val) {
	int _end = read(cell1, OFFSET_ENDS + index);
	int mask = read(cell1, OFFSET_WRITE_MASK + index);
	return _mod_flag(flag, _end, mask, val);
}
