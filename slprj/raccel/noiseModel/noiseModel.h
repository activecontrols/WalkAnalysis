#ifndef RTW_HEADER_noiseModel_h_
#define RTW_HEADER_noiseModel_h_
#ifndef noiseModel_COMMON_INCLUDES_
#define noiseModel_COMMON_INCLUDES_
#include <stdlib.h>
#include "rtwtypes.h"
#include "sigstream_rtw.h"
#include "simtarget/slSimTgtSigstreamRTW.h"
#include "simtarget/slSimTgtSlioCoreRTW.h"
#include "simtarget/slSimTgtSlioClientsRTW.h"
#include "simtarget/slSimTgtSlioSdiRTW.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "rt_logging_simtarget.h"
#include "dt_info.h"
#include "ext_work.h"
#include "stdlib.h"
#endif
#include "noiseModel_types.h"
#include "rt_zcfcn.h"
#include <stddef.h>
#include "rtw_modelmap_simtarget.h"
#include "rt_defines.h"
#include <string.h>
#include "rt_nonfinite.h"
#include "zero_crossing_types.h"
#define MODEL_NAME noiseModel
#define NSAMPLE_TIMES (2) 
#define NINPUTS (0)       
#define NOUTPUTS (1)     
#define NBLOCKIO (3) 
#define NUM_ZC_EVENTS (1) 
#ifndef NCSTATES
#define NCSTATES (0)   
#elif NCSTATES != 0
#error Invalid specification of NCSTATES defined in compiler command
#endif
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm) (*rt_dataMapInfoPtr)
#endif
#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val) (rt_dataMapInfoPtr = &val)
#endif
#ifndef IN_RACCEL_MAIN
#endif
typedef struct { real_T jk2x5buor2 ; real_T kn1ychlxq1 ; real_T hjgy0qkemj ;
} B ; typedef struct { real_T fgnsvot2ce ; struct { void * LoggedData ; }
brrrgxdcja ; int32_T ng03ok42jx ; uint32_T bkra4tmwsa ; uint32_T gj15j2jqkc [
2 ] ; int8_T inhmg5t014 ; } DW ; typedef struct { ZCSigState jyrigbzmbe ; }
PrevZCX ; typedef struct { real_T f1vr0kdjbf ; } ExtY ; typedef struct {
rtwCAPI_ModelMappingInfo mmi ; } DataMapInfo ; struct P_ { real_T
RandomSource_MeanVal ; real_T _Y0 ; real_T
TmpLatchAtSampleandHoldInport1_InitialCondition ; real_T PulseGenerator_Amp ;
real_T PulseGenerator_Period ; real_T PulseGenerator_Duty ; real_T
PulseGenerator_PhaseDelay ; real_T RandomSource_VarianceRTP ; real_T
Gain_Gain ; } ; extern const char_T * RT_MEMORY_ALLOCATION_ERROR ; extern B
rtB ; extern DW rtDW ; extern PrevZCX rtPrevZCX ; extern ExtY rtY ; extern P
rtP ; extern mxArray * mr_noiseModel_GetDWork ( ) ; extern void
mr_noiseModel_SetDWork ( const mxArray * ssDW ) ; extern mxArray *
mr_noiseModel_GetSimStateDisallowedBlocks ( ) ; extern const
rtwCAPI_ModelMappingStaticInfo * noiseModel_GetCAPIStaticMap ( void ) ;
extern SimStruct * const rtS ; extern DataMapInfo * rt_dataMapInfoPtr ;
extern rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr ; void MdlOutputs (
int_T tid ) ; void MdlOutputsParameterSampleTime ( int_T tid ) ; void
MdlUpdate ( int_T tid ) ; void MdlTerminate ( void ) ; void
MdlInitializeSizes ( void ) ; void MdlInitializeSampleTimes ( void ) ;
SimStruct * raccel_register_model ( ssExecutionInfo * executionInfo ) ;
#endif
