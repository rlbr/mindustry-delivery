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

// <START Memory layout>
#define OFFSET_NUM_RESOURCES_NEEDED 1
#define OFFSET_RESOURCE_NEEDED 2
// Set this to the number of resources you are asking for in setup.c
#define LEN_RESOURCE_NEEDED 15

// None of this really needs to be changed.
#define OFFSET_ENDS BOOST_PP_ADD(OFFSET_RESOURCE_NEEDED, LEN_RESOURCE_NEEDED)
#define LEN_FIELDS 4
#define OFFSET_BITLEN BOOST_PP_ADD(OFFSET_ENDS, LEN_FIELDS)
#define OFFSET_READ_MASK BOOST_PP_ADD(OFFSET_BITLEN, LEN_FIELDS)
#define OFFSET_WRITE_MASK BOOST_PP_ADD(OFFSET_READ_MASK, LEN_FIELDS)
#define FREE BOOST_PP_ADD(OFFSET_WRITE_MASK, LEN_FIELDS)
// </END Memory Layout>

// <START flag layout>
#define F_RESOURCE 0
#define F_MODE 1
#define F_VAULT_ID 2
#define F_IDENT 3

// bit lengths for flag values
#define BLEN_F_RESOURCE 4
#define BLEN_F_MODE 3
#define BLEN_F_VAULT_ID 10
#define BLEN_F_IDENT 8
// </END flag layout>

// modes
#define IDLE 0
#define LOADING 1
#define FULL 2
#define CLAIMED 3

// <START application constants>
// Change IDENT if you want to be special
#define IDENT 19
#define UNIT "flare"

// Bitmap for what resources to grab from the core

// #define NEEDED                                                        \
	32321  // 1<<LEAD | 1<<TITANIUM | 1<<SURGE_ALLOY | 1<<PHASE_FABRIC | 1<<PLASTANIUM | 1<<SILICON
// | 1<<GRAPHITE | 1<<METAGLASS |

// #define NEEDED 5120	 // 1<<PHASE_FABRIC | 1<<SILICON

// Will only call for resouces when (amount / capacity) is less than this.
#define THRESHOLD_FULL .75

// Don't take resources if amount in core is less than this number
#define THRESHOLD_CORE_FULL 1000

// Set this to the unit carrying capacity
#define INCR_TAKE 40
#define INCR_DROP 40
// </END application constants>
#endif
