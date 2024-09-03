#ifndef __LOG_UTILS_H__
#define __LOG_UTILS_H__

#include <libgen.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>

#ifdef MEMORY_LIMIT_DEBUG
#define LOG_DEBUG(msg, ...) fprintf(stderr, msg"\n", ##__VA_ARGS__);
#else
#define LOG_DEBUG(msg, ...) { \
    if ((getenv("LIBCUDA_LOG_LEVEL")!=NULL) && (atoi(getenv("LIBCUDA_LOG_LEVEL"))>=8)) \
       fprintf(stderr, "Debug(pid:%d thread=%ld %s:%d)]: "msg"\n", getpid(),pthread_self(),basename(__FILE__),__LINE__,##__VA_ARGS__); }
#endif

#define LOG_INFO(msg, ...) { \
    if ( \
         /*(getenv("LIBCUDA_LOG_LEVEL")==NULL) || */\
         (getenv("LIBCUDA_LOG_LEVEL")!=NULL) && (atoi(getenv("LIBCUDA_LOG_LEVEL"))>=7)) \
       fprintf(stderr, "Info(pid:%d thread=%ld %s:%d)]: "msg"\n", getpid(),pthread_self(),basename(__FILE__),__LINE__,##__VA_ARGS__); }

#define LOG_WARN(msg, ...) { \
    if ( \
        (getenv("LIBCUDA_LOG_LEVEL")==NULL) || \
        ((getenv("LIBCUDA_LOG_LEVEL")!=NULL) && (atoi(getenv("LIBCUDA_LOG_LEVEL"))>=6))) \
       fprintf(stderr, "Warn(pid:%d thread=%ld %s:%d)]: "msg"\n", getpid(),pthread_self(),basename(__FILE__),__LINE__,##__VA_ARGS__); }

#define LOG_MSG(msg, ...) { \
    if ( \
        (getenv("LIBCUDA_LOG_LEVEL")==NULL) || \
        ((getenv("LIBCUDA_LOG_LEVEL")!=NULL) && (atoi(getenv("LIBCUDA_LOG_LEVEL"))>=5))) \
       fprintf(stderr, "Msg(pid:%d thread=%ld %s:%d)]: "msg"\n", getpid(),pthread_self(),basename(__FILE__),__LINE__,##__VA_ARGS__); }

#define LOG_ERROR(msg, ...) { \
    if ( \
        (getenv("LIBCUDA_LOG_LEVEL")==NULL) || \
        ((getenv("LIBCUDA_LOG_LEVEL")!=NULL) && (atoi(getenv("LIBCUDA_LOG_LEVEL"))>=4))) \
       fprintf(stderr, "ERROR(pid:%d thread=%ld %s:%d)]: "msg"\n", getpid(),pthread_self(),basename(__FILE__),__LINE__,##__VA_ARGS__); }

#define CHECK_DRV_API(f)  {                   \
    CUresult status = (f);                    \
    if (status != CUDA_SUCCESS) {             \
        LOG_WARN("Driver error at %d: %d",   \
            __LINE__, status);                \
        return status;                        \
    } }                                       \

#define CHECK_NVML_API(f)  {                  \
    nvmlReturn_t status = (f);                \
    if (status != NVML_SUCCESS) {             \
        LOG_WARN("NVML error at line %d: %d",    \
            __LINE__, status);                \
        return status;                        \
    } }                                       \

#define CHECK_CU_RESULT(res)  {               \
    if (res != CUDA_SUCCESS) {                \
        LOG_WARN("Driver error at %d: %d",   \
            __LINE__, res);                   \
        return res;                           \
    } }                                       \

#define CHECK_SUCCESS(res) {                  \
    if (res != CUDA_SUCCESS)                  \
        return res;                           \
}

#define IF_CHECK_OOM(res) {                   \
    if (res < 0)                              \
        return CUDA_ERROR_OUT_OF_MEMORY;      \
}     


#endif