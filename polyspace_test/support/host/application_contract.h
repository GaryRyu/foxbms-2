#ifndef FOXBMS_PST_APPLICATION_CONTRACT_H
#define FOXBMS_PST_APPLICATION_CONTRACT_H
#include "pstunit.h"
#include "database.h"
#include "bms.h"
#include "diag.h"
#include "os.h"
#include <setjmp.h>
#include <string.h>
#include <math.h>
extern jmp_buf pst_assert_jump;
extern int pst_assert_expected;
extern uint32_t pst_assert_line,pst_tick;
extern unsigned pst_enter_calls,pst_exit_calls,pst_reads,pst_writes;
extern bool pst_closed,pst_precharging;
extern BMS_CURRENT_FLOW_STATE_e pst_direction;
typedef struct { DIAG_ID_e id; DIAG_EVENT_e event; DIAG_IMPACT_LEVEL_e impact; uint32_t index; } PST_DIAG_EVENT;
extern PST_DIAG_EVENT pst_events[256];
extern unsigned pst_event_count;
extern unsigned pst_written_ids[32];
void pst_reset_contract(void);
void pst_check_event(unsigned index,DIAG_ID_e id,DIAG_EVENT_e event,DIAG_IMPACT_LEVEL_e impact,uint32_t string);
#define PST_EQ(a,b) PST_VERIFY_TRUE_MSG((a)==(b), #a " == " #b)
#define PST_EXPECT_SUT_ASSERT(call,location) do { pst_assert_expected=1; if(setjmp(pst_assert_jump)==0) { (void)(call); PST_VERIFY_TRUE_MSG(0,"Expected SUT Assert missing"); } else { PST_EQ(pst_assert_line,location); } pst_assert_expected=0; } while(0)
#endif
