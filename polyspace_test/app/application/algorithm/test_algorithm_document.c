/* Requirement-based unit tests. Static source access explicitly authorized. */
#include "application_contract.h"
#include "../../../../src/app/application/algorithm/algorithm.c"

ALGO_TASKS_s algo_algorithms[2]; const uint16_t algo_length=2;
static unsigned init_calls,calc_calls,done_calls;static STD_RETURN_TYPE_e init_result;
static STD_RETURN_TYPE_e init_stub(void){init_calls++;return init_result;}
static void calc_stub(void){calc_calls++;}
void ALGO_MarkAsDone(uint32_t i){PST_ASSERT_LT_UINT(i,2);done_calls++;}
static void reset_algorithm(void){pst_reset_contract();init_calls=calc_calls=done_calls=0;init_result=STD_OK;algo_initializationRequested=false;
for(unsigned i=0;i<2;i++)algo_algorithms[i]=(ALGO_TASKS_s){ALGO_UNINITIALIZED,100,1000,0,i?init_stub:NULL,calc_stub};}

PST_SUITE(algorithm_algorithm);
/* F2-LLR-ALG-036-TC-01 */
PST_TEST(algorithm_algorithm,F2_LLR_ALG_036_TC_01) {
reset_algorithm();
ALGO_MainFunction();
PST_EQ(algo_algorithms[0].state,ALGO_UNINITIALIZED);
PST_EQ(algo_algorithms[1].state,ALGO_UNINITIALIZED);
PST_EQ(pst_enter_calls,1);PST_EQ(pst_exit_calls,1);
PST_EQ(init_calls,0);PST_EQ(calc_calls,0);
}

/* F2-LLR-ALG-036-TC-02 */
PST_TEST(algorithm_algorithm,F2_LLR_ALG_036_TC_02) {
reset_algorithm();
ALGO_MainFunction();PST_EQ(calc_calls,0);
ALGO_UnlockInitialization();
ALGO_MainFunction();
PST_EQ(init_calls,1);
PST_EQ(algo_algorithms[0].state,ALGO_RUNNING);
PST_EQ(algo_algorithms[1].state,ALGO_RUNNING);
PST_EQ(calc_calls,2);
}

/* F2-LLR-ALG-036-TC-03 */
PST_TEST(algorithm_algorithm,F2_LLR_ALG_036_TC_03) {
reset_algorithm();
ALGO_UnlockInitialization();
algo_algorithms[0].cycleTime_ms=101;
PST_EXPECT_SUT_ASSERT(ALGO_MainFunction(),87);
PST_EQ(algo_algorithms[0].state,ALGO_UNINITIALIZED);PST_EQ(algo_algorithms[1].state,ALGO_UNINITIALIZED);
}

/* F2-LLR-ALG-036-TC-04 */
PST_TEST(algorithm_algorithm,F2_LLR_ALG_036_TC_04) {
reset_algorithm();
ALGO_UnlockInitialization();
init_result=STD_NOT_OK;
ALGO_MainFunction();
PST_EQ(init_calls,1);
PST_EQ(algo_algorithms[0].state,ALGO_RUNNING);
PST_EQ(algo_algorithms[1].state,ALGO_FAILED_INIT);
PST_EQ(calc_calls,1);
ALGO_MainFunction();PST_EQ(init_calls,1);PST_EQ(calc_calls,1);
}

/* F2-LLR-ALG-036-TC-05 */
PST_TEST(algorithm_algorithm,F2_LLR_ALG_036_TC_05) {
reset_algorithm();
ALGO_UnlockInitialization();
ALGO_MainFunction();
PST_EQ(init_calls,1);
PST_EQ(algo_algorithms[0].state,ALGO_RUNNING);
PST_EQ(algo_algorithms[1].state,ALGO_RUNNING);
PST_EQ(calc_calls,2);
ALGO_UnlockInitialization();ALGO_MainFunction();PST_EQ(init_calls,1);PST_EQ(calc_calls,2);
}

/* F2-LLR-ALG-036-TC-06 */
PST_TEST(algorithm_algorithm,F2_LLR_ALG_036_TC_06) {
reset_algorithm();
ALGO_UnlockInitialization();
init_result=(STD_RETURN_TYPE_e)42;
PST_EXPECT_SUT_ASSERT(ALGO_MainFunction(),96);
PST_EQ(init_calls,1);
}

/* F2-LLR-ALG-036-TC-07 */
PST_TEST(algorithm_algorithm,F2_LLR_ALG_036_TC_07) {
reset_algorithm();
ALGO_UnlockInitialization();
algo_algorithms[0].cycleTime_ms=0;
ALGO_MainFunction();
PST_EQ(init_calls,1);
PST_EQ(algo_algorithms[0].state,ALGO_RUNNING);
PST_EQ(algo_algorithms[1].state,ALGO_RUNNING);
PST_EQ(calc_calls,2);
}

/* F2-LLR-ALG-036-TC-08 */
PST_TEST(algorithm_algorithm,F2_LLR_ALG_036_TC_08) {
reset_algorithm();
algo_algorithms[0].startTime=500;
algo_algorithms[0].state=ALGO_READY;
pst_tick=0;
ALGO_MonitorExecutionTime();
PST_EQ(algo_algorithms[0].state,ALGO_READY);
}

/* F2-LLR-ALG-036-TC-09 */
PST_TEST(algorithm_algorithm,F2_LLR_ALG_036_TC_09) {
reset_algorithm();
algo_algorithms[0].startTime=500;
algo_algorithms[0].state=ALGO_RUNNING;
pst_tick=500;
ALGO_MonitorExecutionTime();
PST_EQ(algo_algorithms[0].state,ALGO_RUNNING);
}

/* F2-LLR-ALG-036-TC-10 */
PST_TEST(algorithm_algorithm,F2_LLR_ALG_036_TC_10) {
reset_algorithm();
algo_algorithms[0].startTime=500;
algo_algorithms[0].state=ALGO_RUNNING;
pst_tick=50000;
ALGO_MonitorExecutionTime();
PST_EQ(algo_algorithms[0].state,ALGO_BLOCKED);
}

/* F2-LLR-ALG-036-06-ADD-001 */
PST_TEST(algorithm_algorithm,F2_LLR_ALG_036_06_ADD_001) {
reset_algorithm();algo_algorithms[0].state=ALGO_RUNNING;algo_algorithms[0].startTime=0u;pst_tick=1001u;ALGO_MonitorExecutionTime();PST_EQ(algo_algorithms[0].state,ALGO_BLOCKED);
}

/* F2-LLR-ALG-036-06-ADD-002 */
PST_TEST(algorithm_algorithm,F2_LLR_ALG_036_06_ADD_002) {
reset_algorithm();algo_algorithms[0].state=ALGO_RUNNING;algo_algorithms[0].startTime=4294967245u;pst_tick=100u;ALGO_MonitorExecutionTime();PST_EQ(algo_algorithms[0].state,ALGO_BLOCKED);
}

/* F2-LLR-ALG-036-06-ADD-003 */
PST_TEST(algorithm_algorithm,F2_LLR_ALG_036_06_ADD_003) {
reset_algorithm();algo_algorithms[0].state=ALGO_RUNNING;algo_algorithms[0].startTime=500u;pst_tick=1500u;ALGO_MonitorExecutionTime();PST_EQ(algo_algorithms[0].state,ALGO_RUNNING);
}

/* F2-LLR-ALG-036-07-ADD-001: first UNINITIALIZED;next initialized RUNNING */
PST_TEST(algorithm_algorithm,F2_LLR_ALG_036_07_ADD_001) {
reset_algorithm();algo_algorithms[0].cycleTime_ms=0;algo_algorithms[0].state=ALGO_REINIT_REQUESTED;ALGO_MainFunction();PST_EQ(algo_algorithms[0].state,ALGO_UNINITIALIZED);PST_EQ(algo_initializationRequested,true);ALGO_MainFunction();PST_EQ(algo_algorithms[0].state,ALGO_RUNNING);
}
