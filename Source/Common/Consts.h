/*
*********************************************************************************************************
*
*                                     COMMON TASK AND SEMAPHORE
* 
* Project       : libReactor
* Filename      : ConstsX.h
* Version       : V1.0
* Programmer(s) : xclyfe@gmail.com
*********************************************************************************************************
*/
/*
*********************************************************************************************************
*                                        INCLUDE FILES
*********************************************************************************************************
*/
#pragma once

#define DEBUG_X                             (1)

#define MAX_DGRAM_BUFFER_SIZE               (1432)

#define MAX_SIZE_OF_RING_BUFFER             (64)

#ifndef SOCKET_ERROR
#define SOCKET_ERROR                        (-1)

#endif

#define BUFFER_LOGGER_BUFFER_SIZE           (1024*1) //Bytes
#define MAX_SINGLE_LOG_FILE_SIZE            (1024 * 1024 * 30) //Bytes


#define LITTLE_ENDIAN_X                     (1)
#define BIG_ENDIAN_X                        (2)
#define CPU_BYTE_ORDER_X                    (LITTLE_ENDIAN_X)


#define FAULT_BUFFER_LEN                    (200)

#define APP_CYCLE_TIME                      (100)

#define HSI_COMM_LOST_TIME                  (3000)//HSI_TOLERATE_TIME
#define HSI_COMM_POLL_TIME                  (500)

#define MAX_COMM_MESSAGE_DATA_SIZE          (1400)

#define MAX_UINT_16                         (65535)


#define MAX_NUM_OF_FAULT_ELEMENT            (16) //MAX_NUM_OF_FAULT_ELEMENT必须为2的指数倍，否则快速取模操作会失败

#define SERVER_LISTEN_PORT                  (6001)
#define CLIENT_LISTEN_PORT                  (8001)


#define USERVER_BUFFER_SIZE                 (MAX_SIZE_OF_RING_BUFFER)
#define NUM_USERVER_DATA_READER             (2)
#define NUM_USERVER_DATA_PROCESSER          (3)
#define USERVER_LISTEN_TIMEOUT              (50)

#define MIN(a,b)                            ((a)<(b)?(a):(b))
#define MAX(a,b)                            ((a)>(b)?(a):(b))
#define RANGE(a,b,c)                        ((c)<(a)?(a):((c)>(b)?(b):(c)))       
#define ABS(a)                              ((a)<0?(-a):(a))
