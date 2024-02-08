#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "noiseModel_capi_host.h"
#define sizeof(s) ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el) ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s) (s)
#ifndef SS_UINT64
#define SS_UINT64 17
#endif
#ifndef SS_INT64
#define SS_INT64 18
#endif
#else
#include "builtin_typeid_types.h"
#include "noiseModel.h"
#include "noiseModel_capi.h"
#include "noiseModel_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST
#define TARGET_STRING(s)               ((NULL))
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif
static const rtwCAPI_Signals rtBlockSignals [ ] = { { 0 , 1 , TARGET_STRING (
"noiseModel/Sample and Hold" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } ,
{ 1 , 0 , TARGET_STRING ( "noiseModel/Gain" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 1 } , { 2 , 0 , TARGET_STRING ( "noiseModel/Add" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 2 } , { 3 , 1 , TARGET_STRING (
"noiseModel/Sample and Hold/In" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0
} , { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ; static const
rtwCAPI_BlockParameters rtBlockParameters [ ] = { { 4 , TARGET_STRING (
"noiseModel/Pulse Generator" ) , TARGET_STRING ( "Amplitude" ) , 0 , 0 , 0 }
, { 5 , TARGET_STRING ( "noiseModel/Pulse Generator" ) , TARGET_STRING (
"Period" ) , 0 , 0 , 0 } , { 6 , TARGET_STRING ( "noiseModel/Pulse Generator"
) , TARGET_STRING ( "PulseWidth" ) , 0 , 0 , 0 } , { 7 , TARGET_STRING (
"noiseModel/Pulse Generator" ) , TARGET_STRING ( "PhaseDelay" ) , 0 , 0 , 0 }
, { 8 , TARGET_STRING ( "noiseModel/Gain" ) , TARGET_STRING ( "Gain" ) , 0 ,
0 , 0 } , { 9 , TARGET_STRING ( "noiseModel/Random Source" ) , TARGET_STRING
( "MeanVal" ) , 0 , 0 , 0 } , { 10 , TARGET_STRING (
"noiseModel/Random Source" ) , TARGET_STRING ( "VarianceRTP" ) , 0 , 0 , 0 }
, { 11 , TARGET_STRING ( "noiseModel/Sample and Hold/ " ) , TARGET_STRING (
"InitialOutput" ) , 0 , 0 , 0 } , { 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 } } ;
static int_T rt_LoggedStateIdxList [ ] = { - 1 } ; static const
rtwCAPI_Signals rtRootInputs [ ] = { { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 ,
0 , 0 , 0 } } ; static const rtwCAPI_Signals rtRootOutputs [ ] = { { 12 , 0 ,
TARGET_STRING ( "noiseModel/Output" ) , TARGET_STRING ( "" ) , 1 , 0 , 0 , 0
, 2 } , { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ; static const
rtwCAPI_ModelParameters rtModelParameters [ ] = { { 0 , ( NULL ) , 0 , 0 , 0
} } ;
#ifndef HOST_CAPI_BUILD
static void * rtDataAddrMap [ ] = { & rtB . hjgy0qkemj , & rtB . jk2x5buor2 ,
& rtB . kn1ychlxq1 , & rtB . hjgy0qkemj , & rtP . PulseGenerator_Amp , & rtP
. PulseGenerator_Period , & rtP . PulseGenerator_Duty , & rtP .
PulseGenerator_PhaseDelay , & rtP . Gain_Gain , & rtP . RandomSource_MeanVal
, & rtP . RandomSource_VarianceRTP , & rtP . _Y0 , & rtY . f1vr0kdjbf , } ;
static int32_T * rtVarDimsAddrMap [ ] = { ( NULL ) } ;
#endif
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap [ ] = { { "double" ,
"real_T" , 0 , 0 , sizeof ( real_T ) , ( uint8_T ) SS_DOUBLE , 0 , 0 , 0 } }
;
#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif
static TARGET_CONST rtwCAPI_ElementMap rtElementMap [ ] = { { ( NULL ) , 0 ,
0 , 0 , 0 } , } ; static const rtwCAPI_DimensionMap rtDimensionMap [ ] = { {
rtwCAPI_SCALAR , 0 , 2 , 0 } } ; static const uint_T rtDimensionArray [ ] = {
1 , 1 } ; static const real_T rtcapiStoredFloats [ ] = { 0.01 , 0.0 , 0.0001
} ; static const rtwCAPI_FixPtMap rtFixPtMap [ ] = { { ( NULL ) , ( NULL ) ,
rtwCAPI_FIX_RESERVED , 0 , 0 , ( boolean_T ) 0 } , } ; static const
rtwCAPI_SampleTimeMap rtSampleTimeMap [ ] = { { ( NULL ) , ( NULL ) , - 1 , 0
} , { ( const void * ) & rtcapiStoredFloats [ 0 ] , ( const void * ) &
rtcapiStoredFloats [ 1 ] , ( int8_T ) 1 , ( uint8_T ) 0 } , { ( const void *
) & rtcapiStoredFloats [ 2 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] ,
( int8_T ) 0 , ( uint8_T ) 0 } } ; static rtwCAPI_ModelMappingStaticInfo
mmiStatic = { { rtBlockSignals , 4 , rtRootInputs , 0 , rtRootOutputs , 1 } ,
{ rtBlockParameters , 8 , rtModelParameters , 0 } , { ( NULL ) , 0 } , {
rtDataTypeMap , rtDimensionMap , rtFixPtMap , rtElementMap , rtSampleTimeMap
, rtDimensionArray } , "float" , { 4076865962U , 1338213228U , 2234981081U ,
2678157750U } , ( NULL ) , 0 , ( boolean_T ) 0 , rt_LoggedStateIdxList } ;
const rtwCAPI_ModelMappingStaticInfo * noiseModel_GetCAPIStaticMap ( void ) {
return & mmiStatic ; }
#ifndef HOST_CAPI_BUILD
void noiseModel_InitializeDataMapInfo ( void ) { rtwCAPI_SetVersion ( ( *
rt_dataMapInfoPtr ) . mmi , 1 ) ; rtwCAPI_SetStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , & mmiStatic ) ; rtwCAPI_SetLoggingStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ; rtwCAPI_SetDataAddressMap ( ( *
rt_dataMapInfoPtr ) . mmi , rtDataAddrMap ) ; rtwCAPI_SetVarDimsAddressMap (
( * rt_dataMapInfoPtr ) . mmi , rtVarDimsAddrMap ) ;
rtwCAPI_SetInstanceLoggingInfo ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArray ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( ( * rt_dataMapInfoPtr ) . mmi , 0 ) ; }
#else
#ifdef __cplusplus
extern "C" {
#endif
void noiseModel_host_InitializeDataMapInfo ( noiseModel_host_DataMapInfo_T *
dataMap , const char * path ) { rtwCAPI_SetVersion ( dataMap -> mmi , 1 ) ;
rtwCAPI_SetStaticMap ( dataMap -> mmi , & mmiStatic ) ;
rtwCAPI_SetDataAddressMap ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetVarDimsAddressMap ( dataMap -> mmi , ( NULL ) ) ; rtwCAPI_SetPath
( dataMap -> mmi , path ) ; rtwCAPI_SetFullPath ( dataMap -> mmi , ( NULL ) )
; rtwCAPI_SetChildMMIArray ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( dataMap -> mmi , 0 ) ; }
#ifdef __cplusplus
}
#endif
#endif
