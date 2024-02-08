#include "noiseModel.h"
#include <stdlib.h>
#include "noiseModel_private.h"
#include "rtwtypes.h"
#include "rt_logging_mmi.h"
#include "noiseModel_capi.h"
#include "zero_crossing_types.h"
#include <math.h>
#include <string.h>
#include "mwmathutil.h"
#include "noiseModel_dt.h"
extern void * CreateDiagnosticAsVoidPtr_wrapper ( const char * id , int nargs
, ... ) ; extern ssExecutionInfo gblExecutionInfo ; RTWExtModeInfo *
gblRTWExtModeInfo = NULL ; void raccelForceExtModeShutdown ( boolean_T
extModeStartPktReceived ) { if ( ! extModeStartPktReceived ) { boolean_T
stopRequested = false ; rtExtModeWaitForStartPkt ( gblRTWExtModeInfo , 2 , &
stopRequested ) ; } rtExtModeShutdown ( 2 ) ; }
#include "slsv_diagnostic_codegen_c_api.h"
#include "slsa_sim_engine.h"
#ifdef RSIM_WITH_SOLVER_MULTITASKING
boolean_T gbl_raccel_isMultitasking = 1 ;
#else
boolean_T gbl_raccel_isMultitasking = 0 ;
#endif
boolean_T gbl_raccel_tid01eq = 0 ; int_T gbl_raccel_NumST = 2 ; const char_T
* gbl_raccel_Version = "23.2 (R2023b) 01-Aug-2023" ; void
raccel_setup_MMIStateLog ( SimStruct * S ) {
#ifdef UseMMIDataLogging
rt_FillStateSigInfoFromMMI ( ssGetRTWLogInfo ( S ) , & ssGetErrorStatus ( S )
) ;
#else
UNUSED_PARAMETER ( S ) ;
#endif
} static DataMapInfo rt_dataMapInfo ; DataMapInfo * rt_dataMapInfoPtr = &
rt_dataMapInfo ; rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr = & (
rt_dataMapInfo . mmi ) ; int_T enableFcnCallFlag [ ] = { 1 , 1 } ; const char
* raccelLoadInputsAndAperiodicHitTimes ( SimStruct * S , const char *
inportFileName , int * matFileFormat ) { return rt_RAccelReadInportsMatFile (
S , inportFileName , matFileFormat ) ; }
#include "simstruc.h"
#include "fixedpoint.h"
#include "slsa_sim_engine.h"
#include "simtarget/slSimTgtSLExecSimBridge.h"
B rtB ; DW rtDW ; PrevZCX rtPrevZCX ; ExtY rtY ; static SimStruct model_S ;
SimStruct * const rtS = & model_S ; void RandSrcInitState_U_64 ( const
uint32_T seed [ ] , real_T state [ ] , int32_T nChans ) { real_T d ; int32_T
i ; int32_T k ; int32_T n ; uint32_T j ; for ( i = 0 ; i < nChans ; i ++ ) {
if ( seed [ i ] != 0U ) { j = seed [ i ] ; } else { j = 2147483648U ; } state
[ 35 * i + 34 ] = j ; for ( k = 0 ; k < 32 ; k ++ ) { d = 0.0 ; for ( n = 0 ;
n < 53 ; n ++ ) { j ^= j << 13 ; j ^= j >> 17 ; j ^= j << 5 ; d = ( real_T )
( ( int32_T ) ( j >> 19 ) & 1 ) + ( d + d ) ; } state [ 35 * i + k ] = ldexp
( d , - 53 ) ; } state [ 35 * i + 32 ] = 0.0 ; state [ 35 * i + 33 ] = 0.0 ;
} } void RandSrc_U_D ( real_T y [ ] , const real_T minVec [ ] , int32_T
minLen , const real_T maxVec [ ] , int32_T maxLen , real_T state [ ] ,
int32_T nChans , int32_T nSamps ) { real_T d ; real_T min ; real_T scale ;
int32_T ii [ 2 ] ; int32_T chan ; int32_T i ; int32_T one ; int32_T samps ;
uint32_T j ; int8_T * onePtr ; one = 1 ; onePtr = ( int8_T * ) & one ; one =
( onePtr [ 0U ] == 0 ) ; for ( chan = 0 ; chan < nChans ; chan ++ ) { if (
minLen > 1 ) { i = chan ; } else { i = 0 ; } min = minVec [ i ] ; if ( maxLen
> 1 ) { i = chan ; } else { i = 0 ; } scale = maxVec [ i ] - min ; i = (
int32_T ) ( ( uint32_T ) state [ chan * 35 + 33 ] & 31U ) ; j = ( uint32_T )
state [ chan * 35 + 34 ] ; for ( samps = 0 ; samps < nSamps ; samps ++ ) { d
= ( state [ ( ( i + 20 ) & 31 ) + chan * 35 ] - state [ ( ( i + 5 ) & 31 ) +
chan * 35 ] ) - state [ chan * 35 + 32 ] ; if ( d >= 0.0 ) { state [ chan *
35 + 32 ] = 0.0 ; } else { d ++ ; state [ chan * 35 + 32 ] =
1.1102230246251565E-16 ; } state [ chan * 35 + i ] = d ; i = ( i + 1 ) & 31 ;
memcpy ( & ii [ 0U ] , & d , sizeof ( real_T ) ) ; ii [ one ] = ( int32_T ) (
( uint32_T ) ii [ one ] ^ j ) ; j ^= j << 13 ; j ^= j >> 17 ; j ^= j << 5 ;
ii [ one ^ 1 ] = ( int32_T ) ( ( uint32_T ) ii [ one ^ 1 ] ^ ( j & 1048575U )
) ; memcpy ( & d , & ii [ 0U ] , sizeof ( real_T ) ) ; y [ chan * nSamps +
samps ] = scale * d + min ; } state [ chan * 35 + 33 ] = i ; state [ chan *
35 + 34 ] = j ; } } void RandSrcCreateSeeds_64 ( uint32_T initSeed , uint32_T
seedArray [ ] , int32_T numSeeds ) { real_T state [ 35 ] ; real_T max ;
real_T min ; real_T tmp ; int32_T i ; min = 0.0 ; max = 1.0 ;
RandSrcInitState_U_64 ( & initSeed , & state [ 0 ] , 1 ) ; for ( i = 0 ; i <
numSeeds ; i ++ ) { RandSrc_U_D ( & tmp , & min , 1 , & max , 1 , state , 1 ,
1 ) ; seedArray [ i ] = ( uint32_T ) ( tmp * 2.147483648E+9 ) ; } } void
RandSrcInitState_GZ ( const uint32_T seed [ ] , uint32_T state [ ] , int32_T
nChans ) { int32_T i ; for ( i = 0 ; i < nChans ; i ++ ) { state [ i << 1 ] =
362436069U ; if ( seed [ i ] == 0U ) { state [ ( i << 1 ) + 1 ] = 521288629U
; } else { state [ ( i << 1 ) + 1 ] = seed [ i ] ; } } } void RandSrc_GZ_D (
real_T y [ ] , const real_T mean [ ] , int32_T meanLen , const real_T xstd [
] , int32_T xstdLen , uint32_T state [ ] , int32_T nChans , int32_T nSamps )
{ real_T r ; real_T s ; real_T std ; real_T x ; real_T y_p ; int32_T chan ;
int32_T i ; int32_T j ; int32_T samp ; uint32_T icng ; uint32_T jsr ; static
const real_T vt [ 65 ] = { 0.340945 , 0.4573146 , 0.5397793 , 0.6062427 ,
0.6631691 , 0.7136975 , 0.7596125 , 0.8020356 , 0.8417227 , 0.8792102 ,
0.9148948 , 0.9490791 , 0.9820005 , 1.0138492 , 1.044781 , 1.0749254 ,
1.1043917 , 1.1332738 , 1.161653 , 1.189601 , 1.2171815 , 1.2444516 ,
1.2714635 , 1.298265 , 1.3249008 , 1.3514125 , 1.3778399 , 1.4042211 ,
1.4305929 , 1.4569915 , 1.4834527 , 1.5100122 , 1.5367061 , 1.5635712 ,
1.5906454 , 1.617968 , 1.6455802 , 1.6735255 , 1.7018503 , 1.7306045 ,
1.7598422 , 1.7896223 , 1.8200099 , 1.851077 , 1.8829044 , 1.9155831 ,
1.9492166 , 1.9839239 , 2.0198431 , 2.0571356 , 2.095993 , 2.136645 ,
2.1793713 , 2.2245175 , 2.2725186 , 2.3239338 , 2.3795008 , 2.4402218 ,
2.5075117 , 2.5834658 , 2.6713916 , 2.7769942 , 2.7769942 , 2.7769942 ,
2.7769942 } ; for ( chan = 0 ; chan < nChans ; chan ++ ) { if ( xstdLen > 1 )
{ i = chan ; } else { i = 0 ; } std = xstd [ i ] ; icng = state [ chan << 1 ]
; jsr = state [ ( chan << 1 ) + 1 ] ; for ( samp = 0 ; samp < nSamps ; samp
++ ) { icng = 69069U * icng + 1234567U ; jsr ^= jsr << 13 ; jsr ^= jsr >> 17
; jsr ^= jsr << 5 ; i = ( int32_T ) ( icng + jsr ) ; j = ( i & 63 ) + 1 ; r =
( real_T ) i * 4.6566128730773926E-10 * vt [ j ] ; if ( ! ( muDoubleScalarAbs
( r ) <= vt [ j - 1 ] ) ) { x = ( muDoubleScalarAbs ( r ) - vt [ j - 1 ] ) /
( vt [ j ] - vt [ j - 1 ] ) ; icng = 69069U * icng + 1234567U ; jsr ^= jsr <<
13 ; jsr ^= jsr >> 17 ; jsr ^= jsr << 5 ; y_p = ( real_T ) ( int32_T ) ( icng
+ jsr ) * 2.328306436538696E-10 + 0.5 ; s = x + y_p ; if ( s > 1.301198 ) {
if ( r < 0.0 ) { r = 0.4878992 * x - 0.4878992 ; } else { r = 0.4878992 -
0.4878992 * x ; } } else if ( ! ( s <= 0.9689279 ) ) { x = 0.4878992 -
0.4878992 * x ; if ( y_p > 12.67706 - muDoubleScalarExp ( - 0.5 * x * x ) *
12.37586 ) { if ( r < 0.0 ) { r = - x ; } else { r = x ; } } else if ( ! (
muDoubleScalarExp ( - 0.5 * vt [ j ] * vt [ j ] ) + y_p * 0.01958303 / vt [ j
] <= muDoubleScalarExp ( - 0.5 * r * r ) ) ) { do { icng = 69069U * icng +
1234567U ; jsr ^= jsr << 13 ; jsr ^= jsr >> 17 ; jsr ^= jsr << 5 ; x =
muDoubleScalarLog ( ( real_T ) ( int32_T ) ( icng + jsr ) *
2.328306436538696E-10 + 0.5 ) / 2.776994 ; icng = 69069U * icng + 1234567U ;
jsr ^= jsr << 13 ; jsr ^= jsr >> 17 ; jsr ^= jsr << 5 ; } while (
muDoubleScalarLog ( ( real_T ) ( int32_T ) ( icng + jsr ) *
2.328306436538696E-10 + 0.5 ) * - 2.0 <= x * x ) ; if ( r < 0.0 ) { r = x -
2.776994 ; } else { r = 2.776994 - x ; } } } } if ( meanLen > 1 ) { i = chan
; } else { i = 0 ; } y [ chan * nSamps + samp ] = std * r + mean [ i ] ; }
state [ chan << 1 ] = icng ; state [ ( chan << 1 ) + 1 ] = jsr ; } } void
MdlInitialize ( void ) { rtDW . fgnsvot2ce = rtP .
TmpLatchAtSampleandHoldInport1_InitialCondition ; rtB . hjgy0qkemj = rtP .
_Y0 ; } void MdlStart ( void ) { uint32_T initSeed ; { bool
externalInputIsInDatasetFormat = false ; void * pISigstreamManager =
rt_GetISigstreamManager ( rtS ) ;
rtwISigstreamManagerGetInputIsInDatasetFormat ( pISigstreamManager , &
externalInputIsInDatasetFormat ) ; if ( externalInputIsInDatasetFormat ) { }
} rtDW . ng03ok42jx = 0 ; initSeed = ( uint32_T ) ( 100000 * rand ( ) ) ;
RandSrcCreateSeeds_64 ( initSeed , & rtDW . bkra4tmwsa , 1 ) ;
RandSrcInitState_GZ ( & rtDW . bkra4tmwsa , & rtDW . gj15j2jqkc [ 0 ] , 1 ) ;
MdlInitialize ( ) ; } void MdlOutputs ( int_T tid ) { real_T a0i5urqsns ;
real_T hsbpz1id3b ; ZCEventType zcEvent ; srClearBC ( rtDW . inhmg5t014 ) ;
if ( ( rtDW . ng03ok42jx < rtP . PulseGenerator_Duty ) && ( rtDW . ng03ok42jx
>= 0 ) ) { a0i5urqsns = rtP . PulseGenerator_Amp ; } else { a0i5urqsns = 0.0
; } if ( rtDW . ng03ok42jx >= rtP . PulseGenerator_Period - 1.0 ) { rtDW .
ng03ok42jx = 0 ; } else { rtDW . ng03ok42jx ++ ; } zcEvent = rt_ZCFcn (
RISING_ZERO_CROSSING , & rtPrevZCX . jyrigbzmbe , ( a0i5urqsns ) ) ; if (
zcEvent != NO_ZCEVENT ) { rtB . hjgy0qkemj = rtDW . fgnsvot2ce ; rtDW .
inhmg5t014 = 4 ; } rtY . f1vr0kdjbf = rtB . hjgy0qkemj ; if ( ssIsSampleHit (
rtS , 1 , 0 ) ) { RandSrc_GZ_D ( & hsbpz1id3b , & rtP . RandomSource_MeanVal
, 1 , & rtP . RandomSource_VarianceRTP , 1 , rtDW . gj15j2jqkc , 1 , 1 ) ;
rtB . jk2x5buor2 = rtP . Gain_Gain * hsbpz1id3b ; } rtB . kn1ychlxq1 = rtB .
jk2x5buor2 + rtB . hjgy0qkemj ; UNUSED_PARAMETER ( tid ) ; } void MdlUpdate (
int_T tid ) { rtDW . fgnsvot2ce = rtB . kn1ychlxq1 ; UNUSED_PARAMETER ( tid )
; } void MdlTerminate ( void ) { } static void
mr_noiseModel_cacheDataAsMxArray ( mxArray * destArray , mwIndex i , int j ,
const void * srcData , size_t numBytes ) ; static void
mr_noiseModel_cacheDataAsMxArray ( mxArray * destArray , mwIndex i , int j ,
const void * srcData , size_t numBytes ) { mxArray * newArray =
mxCreateUninitNumericMatrix ( ( size_t ) 1 , numBytes , mxUINT8_CLASS ,
mxREAL ) ; memcpy ( ( uint8_T * ) mxGetData ( newArray ) , ( const uint8_T *
) srcData , numBytes ) ; mxSetFieldByNumber ( destArray , i , j , newArray )
; } static void mr_noiseModel_restoreDataFromMxArray ( void * destData ,
const mxArray * srcArray , mwIndex i , int j , size_t numBytes ) ; static
void mr_noiseModel_restoreDataFromMxArray ( void * destData , const mxArray *
srcArray , mwIndex i , int j , size_t numBytes ) { memcpy ( ( uint8_T * )
destData , ( const uint8_T * ) mxGetData ( mxGetFieldByNumber ( srcArray , i
, j ) ) , numBytes ) ; } static void mr_noiseModel_cacheBitFieldToMxArray (
mxArray * destArray , mwIndex i , int j , uint_T bitVal ) ; static void
mr_noiseModel_cacheBitFieldToMxArray ( mxArray * destArray , mwIndex i , int
j , uint_T bitVal ) { mxSetFieldByNumber ( destArray , i , j ,
mxCreateDoubleScalar ( ( real_T ) bitVal ) ) ; } static uint_T
mr_noiseModel_extractBitFieldFromMxArray ( const mxArray * srcArray , mwIndex
i , int j , uint_T numBits ) ; static uint_T
mr_noiseModel_extractBitFieldFromMxArray ( const mxArray * srcArray , mwIndex
i , int j , uint_T numBits ) { const uint_T varVal = ( uint_T ) mxGetScalar (
mxGetFieldByNumber ( srcArray , i , j ) ) ; return varVal & ( ( 1u << numBits
) - 1u ) ; } static void mr_noiseModel_cacheDataToMxArrayWithOffset ( mxArray
* destArray , mwIndex i , int j , mwIndex offset , const void * srcData ,
size_t numBytes ) ; static void mr_noiseModel_cacheDataToMxArrayWithOffset (
mxArray * destArray , mwIndex i , int j , mwIndex offset , const void *
srcData , size_t numBytes ) { uint8_T * varData = ( uint8_T * ) mxGetData (
mxGetFieldByNumber ( destArray , i , j ) ) ; memcpy ( ( uint8_T * ) & varData
[ offset * numBytes ] , ( const uint8_T * ) srcData , numBytes ) ; } static
void mr_noiseModel_restoreDataFromMxArrayWithOffset ( void * destData , const
mxArray * srcArray , mwIndex i , int j , mwIndex offset , size_t numBytes ) ;
static void mr_noiseModel_restoreDataFromMxArrayWithOffset ( void * destData
, const mxArray * srcArray , mwIndex i , int j , mwIndex offset , size_t
numBytes ) { const uint8_T * varData = ( const uint8_T * ) mxGetData (
mxGetFieldByNumber ( srcArray , i , j ) ) ; memcpy ( ( uint8_T * ) destData ,
( const uint8_T * ) & varData [ offset * numBytes ] , numBytes ) ; } static
void mr_noiseModel_cacheBitFieldToCellArrayWithOffset ( mxArray * destArray ,
mwIndex i , int j , mwIndex offset , uint_T fieldVal ) ; static void
mr_noiseModel_cacheBitFieldToCellArrayWithOffset ( mxArray * destArray ,
mwIndex i , int j , mwIndex offset , uint_T fieldVal ) { mxSetCell (
mxGetFieldByNumber ( destArray , i , j ) , offset , mxCreateDoubleScalar ( (
real_T ) fieldVal ) ) ; } static uint_T
mr_noiseModel_extractBitFieldFromCellArrayWithOffset ( const mxArray *
srcArray , mwIndex i , int j , mwIndex offset , uint_T numBits ) ; static
uint_T mr_noiseModel_extractBitFieldFromCellArrayWithOffset ( const mxArray *
srcArray , mwIndex i , int j , mwIndex offset , uint_T numBits ) { const
uint_T fieldVal = ( uint_T ) mxGetScalar ( mxGetCell ( mxGetFieldByNumber (
srcArray , i , j ) , offset ) ) ; return fieldVal & ( ( 1u << numBits ) - 1u
) ; } mxArray * mr_noiseModel_GetDWork ( ) { static const char_T *
ssDWFieldNames [ 3 ] = { "rtB" , "rtDW" , "rtPrevZCX" , } ; mxArray * ssDW =
mxCreateStructMatrix ( 1 , 1 , 3 , ssDWFieldNames ) ;
mr_noiseModel_cacheDataAsMxArray ( ssDW , 0 , 0 , ( const void * ) & ( rtB )
, sizeof ( rtB ) ) ; { static const char_T * rtdwDataFieldNames [ 5 ] = {
"rtDW.fgnsvot2ce" , "rtDW.ng03ok42jx" , "rtDW.bkra4tmwsa" , "rtDW.gj15j2jqkc"
, "rtDW.inhmg5t014" , } ; mxArray * rtdwData = mxCreateStructMatrix ( 1 , 1 ,
5 , rtdwDataFieldNames ) ; mr_noiseModel_cacheDataAsMxArray ( rtdwData , 0 ,
0 , ( const void * ) & ( rtDW . fgnsvot2ce ) , sizeof ( rtDW . fgnsvot2ce ) )
; mr_noiseModel_cacheDataAsMxArray ( rtdwData , 0 , 1 , ( const void * ) & (
rtDW . ng03ok42jx ) , sizeof ( rtDW . ng03ok42jx ) ) ;
mr_noiseModel_cacheDataAsMxArray ( rtdwData , 0 , 2 , ( const void * ) & (
rtDW . bkra4tmwsa ) , sizeof ( rtDW . bkra4tmwsa ) ) ;
mr_noiseModel_cacheDataAsMxArray ( rtdwData , 0 , 3 , ( const void * ) & (
rtDW . gj15j2jqkc ) , sizeof ( rtDW . gj15j2jqkc ) ) ;
mr_noiseModel_cacheDataAsMxArray ( rtdwData , 0 , 4 , ( const void * ) & (
rtDW . inhmg5t014 ) , sizeof ( rtDW . inhmg5t014 ) ) ; mxSetFieldByNumber (
ssDW , 0 , 1 , rtdwData ) ; } mr_noiseModel_cacheDataAsMxArray ( ssDW , 0 , 2
, ( const void * ) & ( rtPrevZCX ) , sizeof ( rtPrevZCX ) ) ; return ssDW ; }
void mr_noiseModel_SetDWork ( const mxArray * ssDW ) { ( void ) ssDW ;
mr_noiseModel_restoreDataFromMxArray ( ( void * ) & ( rtB ) , ssDW , 0 , 0 ,
sizeof ( rtB ) ) ; { const mxArray * rtdwData = mxGetFieldByNumber ( ssDW , 0
, 1 ) ; mr_noiseModel_restoreDataFromMxArray ( ( void * ) & ( rtDW .
fgnsvot2ce ) , rtdwData , 0 , 0 , sizeof ( rtDW . fgnsvot2ce ) ) ;
mr_noiseModel_restoreDataFromMxArray ( ( void * ) & ( rtDW . ng03ok42jx ) ,
rtdwData , 0 , 1 , sizeof ( rtDW . ng03ok42jx ) ) ;
mr_noiseModel_restoreDataFromMxArray ( ( void * ) & ( rtDW . bkra4tmwsa ) ,
rtdwData , 0 , 2 , sizeof ( rtDW . bkra4tmwsa ) ) ;
mr_noiseModel_restoreDataFromMxArray ( ( void * ) & ( rtDW . gj15j2jqkc ) ,
rtdwData , 0 , 3 , sizeof ( rtDW . gj15j2jqkc ) ) ;
mr_noiseModel_restoreDataFromMxArray ( ( void * ) & ( rtDW . inhmg5t014 ) ,
rtdwData , 0 , 4 , sizeof ( rtDW . inhmg5t014 ) ) ; }
mr_noiseModel_restoreDataFromMxArray ( ( void * ) & ( rtPrevZCX ) , ssDW , 0
, 2 , sizeof ( rtPrevZCX ) ) ; } mxArray *
mr_noiseModel_GetSimStateDisallowedBlocks ( ) { mxArray * data =
mxCreateCellMatrix ( 1 , 3 ) ; mwIndex subs [ 2 ] , offset ; { static const
char_T * blockType [ 1 ] = { "Scope" , } ; static const char_T * blockPath [
1 ] = { "noiseModel/Scope" , } ; static const int reason [ 1 ] = { 0 , } ;
for ( subs [ 0 ] = 0 ; subs [ 0 ] < 1 ; ++ ( subs [ 0 ] ) ) { subs [ 1 ] = 0
; offset = mxCalcSingleSubscript ( data , 2 , subs ) ; mxSetCell ( data ,
offset , mxCreateString ( blockType [ subs [ 0 ] ] ) ) ; subs [ 1 ] = 1 ;
offset = mxCalcSingleSubscript ( data , 2 , subs ) ; mxSetCell ( data ,
offset , mxCreateString ( blockPath [ subs [ 0 ] ] ) ) ; subs [ 1 ] = 2 ;
offset = mxCalcSingleSubscript ( data , 2 , subs ) ; mxSetCell ( data ,
offset , mxCreateDoubleScalar ( ( real_T ) reason [ subs [ 0 ] ] ) ) ; } }
return data ; } void MdlInitializeSizes ( void ) { ssSetNumContStates ( rtS ,
0 ) ; ssSetNumY ( rtS , 1 ) ; ssSetNumU ( rtS , 0 ) ; ssSetDirectFeedThrough
( rtS , 0 ) ; ssSetNumSampleTimes ( rtS , 2 ) ; ssSetNumBlocks ( rtS , 9 ) ;
ssSetNumBlockIO ( rtS , 3 ) ; ssSetNumBlockParams ( rtS , 9 ) ; } void
MdlInitializeSampleTimes ( void ) { ssSetSampleTime ( rtS , 0 , 0.0001 ) ;
ssSetSampleTime ( rtS , 1 , 0.01 ) ; ssSetOffsetTime ( rtS , 0 , 0.0 ) ;
ssSetOffsetTime ( rtS , 1 , 0.0 ) ; } void raccel_set_checksum ( ) {
ssSetChecksumVal ( rtS , 0 , 4076865962U ) ; ssSetChecksumVal ( rtS , 1 ,
1338213228U ) ; ssSetChecksumVal ( rtS , 2 , 2234981081U ) ; ssSetChecksumVal
( rtS , 3 , 2678157750U ) ; }
#if defined(_MSC_VER)
#pragma optimize( "", off )
#endif
SimStruct * raccel_register_model ( ssExecutionInfo * executionInfo ) {
static struct _ssMdlInfo mdlInfo ; static struct _ssBlkInfo2 blkInfo2 ;
static struct _ssBlkInfoSLSize blkInfoSLSize ; rt_modelMapInfoPtr = & (
rt_dataMapInfo . mmi ) ; executionInfo -> gblObjects_ . numToFiles = 0 ;
executionInfo -> gblObjects_ . numFrFiles = 0 ; executionInfo -> gblObjects_
. numFrWksBlocks = 0 ; executionInfo -> gblObjects_ . numModelInputs = 0 ;
executionInfo -> gblObjects_ . numRootInportBlks = 0 ; executionInfo ->
gblObjects_ . inportDataTypeIdx = NULL ; executionInfo -> gblObjects_ .
inportDims = NULL ; executionInfo -> gblObjects_ . inportComplex = NULL ;
executionInfo -> gblObjects_ . inportInterpoFlag = NULL ; executionInfo ->
gblObjects_ . inportContinuous = NULL ; ( void ) memset ( ( char_T * ) rtS ,
0 , sizeof ( SimStruct ) ) ; ( void ) memset ( ( char_T * ) & mdlInfo , 0 ,
sizeof ( struct _ssMdlInfo ) ) ; ( void ) memset ( ( char_T * ) & blkInfo2 ,
0 , sizeof ( struct _ssBlkInfo2 ) ) ; ( void ) memset ( ( char_T * ) &
blkInfoSLSize , 0 , sizeof ( struct _ssBlkInfoSLSize ) ) ; ssSetBlkInfo2Ptr (
rtS , & blkInfo2 ) ; ssSetBlkInfoSLSizePtr ( rtS , & blkInfoSLSize ) ;
ssSetMdlInfoPtr ( rtS , & mdlInfo ) ; ssSetExecutionInfo ( rtS ,
executionInfo ) ; slsaAllocOPModelData ( rtS ) ; { static time_T mdlPeriod [
NSAMPLE_TIMES ] ; static time_T mdlOffset [ NSAMPLE_TIMES ] ; static time_T
mdlTaskTimes [ NSAMPLE_TIMES ] ; static int_T mdlTsMap [ NSAMPLE_TIMES ] ;
static int_T mdlSampleHits [ NSAMPLE_TIMES ] ; static boolean_T
mdlTNextWasAdjustedPtr [ NSAMPLE_TIMES ] ; static int_T mdlPerTaskSampleHits
[ NSAMPLE_TIMES * NSAMPLE_TIMES ] ; static time_T mdlTimeOfNextSampleHit [
NSAMPLE_TIMES ] ; { int_T i ; for ( i = 0 ; i < NSAMPLE_TIMES ; i ++ ) {
mdlPeriod [ i ] = 0.0 ; mdlOffset [ i ] = 0.0 ; mdlTaskTimes [ i ] = 0.0 ;
mdlTsMap [ i ] = i ; mdlSampleHits [ i ] = 1 ; } } ssSetSampleTimePtr ( rtS ,
& mdlPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rtS , & mdlOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rtS , & mdlTsMap [ 0 ] ) ; ssSetTPtr ( rtS , &
mdlTaskTimes [ 0 ] ) ; ssSetSampleHitPtr ( rtS , & mdlSampleHits [ 0 ] ) ;
ssSetTNextWasAdjustedPtr ( rtS , & mdlTNextWasAdjustedPtr [ 0 ] ) ;
ssSetPerTaskSampleHitsPtr ( rtS , & mdlPerTaskSampleHits [ 0 ] ) ;
ssSetTimeOfNextSampleHitPtr ( rtS , & mdlTimeOfNextSampleHit [ 0 ] ) ; }
ssSetSolverMode ( rtS , SOLVER_MODE_SINGLETASKING ) ; { ssSetBlockIO ( rtS ,
( ( void * ) & rtB ) ) ; ( void ) memset ( ( ( void * ) & rtB ) , 0 , sizeof
( B ) ) ; } { ssSetY ( rtS , & rtY ) ; rtY . f1vr0kdjbf = 0.0 ;
ssSetWorkSizeInBytes ( rtS , sizeof ( rtY ) , "YOut" ) ; } { void * dwork = (
void * ) & rtDW ; ssSetRootDWork ( rtS , dwork ) ; ( void ) memset ( dwork ,
0 , sizeof ( DW ) ) ; } { static DataTypeTransInfo dtInfo ; ( void ) memset (
( char_T * ) & dtInfo , 0 , sizeof ( dtInfo ) ) ; ssSetModelMappingInfo ( rtS
, & dtInfo ) ; dtInfo . numDataTypes = 23 ; dtInfo . dataTypeSizes = &
rtDataTypeSizes [ 0 ] ; dtInfo . dataTypeNames = & rtDataTypeNames [ 0 ] ;
dtInfo . BTransTable = & rtBTransTable ; dtInfo . PTransTable = &
rtPTransTable ; dtInfo . dataTypeInfoTable = rtDataTypeInfoTable ; }
noiseModel_InitializeDataMapInfo ( ) ; ssSetIsRapidAcceleratorActive ( rtS ,
true ) ; ssSetRootSS ( rtS , rtS ) ; ssSetVersion ( rtS ,
SIMSTRUCT_VERSION_LEVEL2 ) ; ssSetModelName ( rtS , "noiseModel" ) ;
ssSetPath ( rtS , "noiseModel" ) ; ssSetTStart ( rtS , 0.0 ) ; ssSetTFinal (
rtS , 3600.0 ) ; ssSetStepSize ( rtS , 0.0001 ) ; ssSetFixedStepSize ( rtS ,
0.0001 ) ; { static RTWLogInfo rt_DataLoggingInfo ; rt_DataLoggingInfo .
loggingInterval = ( NULL ) ; ssSetRTWLogInfo ( rtS , & rt_DataLoggingInfo ) ;
} { rtliSetLogT ( ssGetRTWLogInfo ( rtS ) , "tout" ) ; rtliSetLogX (
ssGetRTWLogInfo ( rtS ) , "" ) ; rtliSetLogXFinal ( ssGetRTWLogInfo ( rtS ) ,
"" ) ; rtliSetLogVarNameModifier ( ssGetRTWLogInfo ( rtS ) , "none" ) ;
rtliSetLogFormat ( ssGetRTWLogInfo ( rtS ) , 2 ) ; rtliSetLogMaxRows (
ssGetRTWLogInfo ( rtS ) , 0 ) ; rtliSetLogDecimation ( ssGetRTWLogInfo ( rtS
) , 1 ) ; { static void * rt_LoggedOutputSignalPtrs [ ] = { & rtY .
f1vr0kdjbf } ; rtliSetLogYSignalPtrs ( ssGetRTWLogInfo ( rtS ) , ( (
LogSignalPtrsType ) rt_LoggedOutputSignalPtrs ) ) ; } { static int_T
rt_LoggedOutputWidths [ ] = { 1 } ; static int_T rt_LoggedOutputNumDimensions
[ ] = { 1 } ; static int_T rt_LoggedOutputDimensions [ ] = { 1 } ; static
boolean_T rt_LoggedOutputIsVarDims [ ] = { 0 } ; static void *
rt_LoggedCurrentSignalDimensions [ ] = { ( NULL ) } ; static int_T
rt_LoggedCurrentSignalDimensionsSize [ ] = { 4 } ; static BuiltInDTypeId
rt_LoggedOutputDataTypeIds [ ] = { SS_DOUBLE } ; static int_T
rt_LoggedOutputComplexSignals [ ] = { 0 } ; static RTWPreprocessingFcnPtr
rt_LoggingPreprocessingFcnPtrs [ ] = { ( NULL ) } ; static const char_T *
rt_LoggedOutputLabels [ ] = { "" } ; static const char_T *
rt_LoggedOutputBlockNames [ ] = { "noiseModel/Output" } ; static
RTWLogDataTypeConvert rt_RTWLogDataTypeConvert [ ] = { { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } } ; static RTWLogSignalInfo
rt_LoggedOutputSignalInfo [ ] = { { 1 , rt_LoggedOutputWidths ,
rt_LoggedOutputNumDimensions , rt_LoggedOutputDimensions ,
rt_LoggedOutputIsVarDims , rt_LoggedCurrentSignalDimensions ,
rt_LoggedCurrentSignalDimensionsSize , rt_LoggedOutputDataTypeIds ,
rt_LoggedOutputComplexSignals , ( NULL ) , rt_LoggingPreprocessingFcnPtrs , {
rt_LoggedOutputLabels } , ( NULL ) , ( NULL ) , ( NULL ) , {
rt_LoggedOutputBlockNames } , { ( NULL ) } , ( NULL ) ,
rt_RTWLogDataTypeConvert , ( NULL ) } } ; rtliSetLogYSignalInfo (
ssGetRTWLogInfo ( rtS ) , rt_LoggedOutputSignalInfo ) ;
rt_LoggedCurrentSignalDimensions [ 0 ] = & rt_LoggedOutputWidths [ 0 ] ; }
rtliSetLogY ( ssGetRTWLogInfo ( rtS ) , "tmp_raccel_yout1" ) ; } { static
struct _ssStatesInfo2 statesInfo2 ; ssSetStatesInfo2 ( rtS , & statesInfo2 )
; } { static ssPeriodicStatesInfo periodicStatesInfo ;
ssSetPeriodicStatesInfo ( rtS , & periodicStatesInfo ) ; } { static
ssJacobianPerturbationBounds jacobianPerturbationBounds ;
ssSetJacobianPerturbationBounds ( rtS , & jacobianPerturbationBounds ) ; } {
static ssSolverInfo slvrInfo ; ssSetNumNonContDerivSigInfos ( rtS , 0 ) ;
ssSetNonContDerivSigInfos ( rtS , ( NULL ) ) ; ssSetSolverInfo ( rtS , &
slvrInfo ) ; ssSetSolverName ( rtS , "FixedStepDiscrete" ) ;
ssSetVariableStepSolver ( rtS , 0 ) ; ssSetSolverConsistencyChecking ( rtS ,
0 ) ; ssSetSolverAdaptiveZcDetection ( rtS , 0 ) ;
ssSetSolverRobustResetMethod ( rtS , 0 ) ; ssSetSolverStateProjection ( rtS ,
0 ) ; ssSetSolverMassMatrixType ( rtS , ( ssMatrixType ) 0 ) ;
ssSetSolverMassMatrixNzMax ( rtS , 0 ) ; ssSetModelOutputs ( rtS , MdlOutputs
) ; ssSetModelUpdate ( rtS , MdlUpdate ) ; ssSetTNextTid ( rtS , INT_MIN ) ;
ssSetTNext ( rtS , rtMinusInf ) ; ssSetSolverNeedsReset ( rtS ) ;
ssSetNumNonsampledZCs ( rtS , 0 ) ; } { ZCSigState * zc = ( ZCSigState * ) &
rtPrevZCX ; ssSetPrevZCSigState ( rtS , zc ) ; } { rtPrevZCX . jyrigbzmbe =
UNINITIALIZED_ZCSIG ; } ssSetChecksumVal ( rtS , 0 , 4076865962U ) ;
ssSetChecksumVal ( rtS , 1 , 1338213228U ) ; ssSetChecksumVal ( rtS , 2 ,
2234981081U ) ; ssSetChecksumVal ( rtS , 3 , 2678157750U ) ; { static const
sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE ; static RTWExtModeInfo
rt_ExtModeInfo ; static const sysRanDType * systemRan [ 2 ] ;
gblRTWExtModeInfo = & rt_ExtModeInfo ; ssSetRTWExtModeInfo ( rtS , &
rt_ExtModeInfo ) ; rteiSetSubSystemActiveVectorAddresses ( & rt_ExtModeInfo ,
systemRan ) ; systemRan [ 0 ] = & rtAlwaysEnabled ; systemRan [ 1 ] = (
sysRanDType * ) & rtDW . inhmg5t014 ; rteiSetModelMappingInfoPtr (
ssGetRTWExtModeInfo ( rtS ) , & ssGetModelMappingInfo ( rtS ) ) ;
rteiSetChecksumsPtr ( ssGetRTWExtModeInfo ( rtS ) , ssGetChecksums ( rtS ) )
; rteiSetTPtr ( ssGetRTWExtModeInfo ( rtS ) , ssGetTPtr ( rtS ) ) ; }
slsaDisallowedBlocksForSimTargetOP ( rtS ,
mr_noiseModel_GetSimStateDisallowedBlocks ) ; slsaGetWorkFcnForSimTargetOP (
rtS , mr_noiseModel_GetDWork ) ; slsaSetWorkFcnForSimTargetOP ( rtS ,
mr_noiseModel_SetDWork ) ; rt_RapidReadMatFileAndUpdateParams ( rtS ) ; if (
ssGetErrorStatus ( rtS ) ) { return rtS ; } return rtS ; }
#if defined(_MSC_VER)
#pragma optimize( "", on )
#endif
void MdlOutputsParameterSampleTime ( int_T tid ) { UNUSED_PARAMETER ( tid ) ;
}
