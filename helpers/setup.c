#include "c2logic/builtins.h"
#include "consts.h"
extern struct MindustryObject cell1;
extern struct MindustryObject vault1;

int compute_read_mask(int length) {
	return (1 << length) - 1;
}
int compute_write_mask(int length, int _end) {
	int mask = compute_read_mask(length) << _end;
	return ~mask;
}
void setup() {
	while (!read(cell1, 0)) {
		int index;
		// change for what resources should be carried to storage vault
		index = 0;
		write(PHASE_FABRIC, cell1, OFFSET_RESOURCE_NEEDED + index);
		index++;
		write(SILICON, cell1, OFFSET_RESOURCE_NEEDED + index);
		index++;
		// set len/ends for fields
		int sum = BLEN_F_RESOURCE + BLEN_F_MODE + BLEN_F_VAULT_ID + BLEN_F_IDENT;

		write(BLEN_F_RESOURCE, cell1, OFFSET_BITLEN + F_RESOURCE);
		sum = sum - BLEN_F_RESOURCE;
		write(sum, cell1, OFFSET_ENDS + F_RESOURCE);

		write(BLEN_F_MODE, cell1, OFFSET_BITLEN + F_MODE);
		sum = sum - BLEN_F_MODE;
		write(sum, cell1, OFFSET_ENDS + F_MODE);

		write(BLEN_F_VAULT_ID, cell1, OFFSET_BITLEN + F_VAULT_ID);
		sum = sum - BLEN_F_VAULT_ID;
		write(sum, cell1, OFFSET_ENDS + F_VAULT_ID);

		write(BLEN_F_IDENT, cell1, OFFSET_BITLEN + F_IDENT);
		sum = sum - BLEN_F_IDENT;
		write(sum, cell1, OFFSET_ENDS + F_IDENT);
		// pre compute masks for read/write field to make things faster
		for (int i = 0; i < LEN_FIELDS; i++) {
			// read
			int length = read(cell1, OFFSET_BITLEN + i);
			write(compute_read_mask(length), cell1, OFFSET_READ_MASK + i);
			// write
			int _end = read(cell1, OFFSET_ENDS + i);
			write(compute_write_mask(length, _end), cell1, OFFSET_WRITE_MASK + i);
		}
		// mark as configured
		if (read(cell1, OFFSET_RESOURCE_NEEDED) == PHASE_FABRIC) {
			write(ceil(rand(1023)), cell1, 0);
		}
	}
}
