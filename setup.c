#include "consts.h"
int carrier_state() {
	struct MindustryObject unit;
	return sensor(unit, "flag");
}
int compute_read_mask(int length) {
	return (1 << length) - 1;
}
int compute_write_mask(int length, int end) {
	int mask = compute_read_mask(length) << end;
	return ~mask;
}
void setup() {
	struct MindustryObject cell1;
	struct MindustryObject vault1;
	if (!read(cell1, 0)) {
		int index;
		// change for what resources should be carried to storage vault
		index = 0;
		write(PHASE_FABRIC, cell1, OFFSET_RESOURCE_NEEDED + index);
		index++;
		write(SILICON, cell1, OFFSET_RESOURCE_NEEDED + index);
		index++;
		// set len/ends for fields
		int sum = BLEN_F_RESOURCE + BLEN_F_MODE + BLEN_F_MOVING + BLEN_F_IDENT;

		write(BLEN_F_RESOURCE, cell1, OFFSET_BITLEN + F_RESOURCE);
		sum = sum - BLEN_F_RESOURCE;
		write(sum, cell1, OFFSET_ENDS + F_RESOURCE);

		write(BLEN_F_MODE, cell1, OFFSET_BITLEN + F_MODE);
		sum = sum - BLEN_F_MODE;
		write(sum, cell1, OFFSET_ENDS + F_MODE);

		write(BLEN_F_MOVING, cell1, OFFSET_BITLEN + F_MOVING);
		sum = sum - BLEN_F_MOVING;
		write(sum, cell1, OFFSET_ENDS + F_MOVING);

		write(BLEN_F_IDENT, cell1, OFFSET_BITLEN + F_IDENT);
		sum = sum - BLEN_F_IDENT;
		write(sum, cell1, OFFSET_ENDS + F_IDENT);
		// pre compute masks for read/write field to make things faster
		for (int i = 0; i < LEN_FIELDS; i++) {
			// read
			write(compute_read_mask(read(cell1, OFFSET_BITLEN + i)), cell1, OFFSET_READ_MASK + i);
			// write
			int length = read(cell1, OFFSET_BITLEN + i);
			int end = read(cell1, OFFSET_ENDS + i);
			write(compute_write_mask(length, end), cell1, OFFSET_WRITE_MASK + i);
		}
		// mark as configured
		write(true, cell1, 0);
	}
}
