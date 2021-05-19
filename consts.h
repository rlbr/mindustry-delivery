#include "c2logic/builtins.h"
#ifndef GT_CONSTS_H
#define GT_CONSTS_H
#define true 1
#define false 0
// basic resources
#define LEAD 0
#define COPPER 1
#define COAL 2
#define SAND 3
#define SCRAP 4
#define THORIUM 5
#define TITANIUM 6
#define SPORE_POD 7
// derived resources
#define PYRATITE 8
#define SURGE_ALLOY 9
#define PHASE_FABRIC 10
#define PLASTANIUM 11
#define SILICON 12
#define GRAPHITE 13
#define METAGLASS 14

// Memory layout
#define OFFSET_RESOURCE_NEEDED 1
#define LEN_RESOURCE_NEEDED 2

#define OFFSET_ENDS OFFSET_RESOURCE_NEEDED + LEN_RESOURCE_NEEDED
#define LEN_FIELDS 4
#define OFFSET_BITLEN OFFSET_ENDS + LEN_FIELDS
#define OFFSET_READ_MASK OFFSET_BITLEN + LEN_FIELDS
#define OFFSET_WRITE_MASK OFFSET_READ_MASK + LEN_FIELDS
#define FREE OFFSET_WRITE_MASK + LEN_FIELDS
// flag layout
#define F_RESOURCE 0
#define F_MODE 1
#define F_MOVING 2
#define F_IDENT 3

#define BLEN_F_RESOURCE 4
#define BLEN_F_MODE 3
#define BLEN_F_MOVING 1
#define BLEN_F_IDENT 8

// application constants
#define IDENT 19
#define EMPTY 0
#define FULL 1
#define THRESHOLD_FULL .75
#define INCR_TAKE 20
#define INCR_DROP 20
#endif
