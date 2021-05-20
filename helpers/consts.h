#include <boost/preprocessor/arithmetic/add.hpp>

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

#define OFFSET_ENDS BOOST_PP_ADD(OFFSET_RESOURCE_NEEDED, LEN_RESOURCE_NEEDED)
#define LEN_FIELDS 4
#define OFFSET_BITLEN BOOST_PP_ADD(OFFSET_ENDS, LEN_FIELDS)
#define OFFSET_READ_MASK BOOST_PP_ADD(OFFSET_BITLEN, LEN_FIELDS)
#define OFFSET_WRITE_MASK BOOST_PP_ADD(OFFSET_READ_MASK, LEN_FIELDS)
#define FREE BOOST_PP_ADD(OFFSET_WRITE_MASK, LEN_FIELDS)
// flag layout
#define F_RESOURCE 0
#define F_MODE 1
#define F_VAULT_ID 2
#define F_IDENT 3

#define BLEN_F_RESOURCE 4
#define BLEN_F_MODE 3
#define BLEN_F_VAULT_ID 10
#define BLEN_F_IDENT 8

// modes
#define IDLE 0
#define LOADING 1
#define FULL 2
// application constants
#define IDENT 19
#define THRESHOLD_FULL .75
#define THRESHOLD_UNIT_FULL 20
#define INCR_TAKE 40
#define INCR_DROP 40
#endif
