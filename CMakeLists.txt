CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

PROJECT (hashtable)

#ADD_COMPILE_OPTIONS (-Wall -O --std=c99)
ADD_COMPILE_OPTIONS (-Wall -g --std=c99)

ADD_DEFINITIONS (-D_DEFAULT_SOURCE)

SET (SRCS test.c hashtable.c halfsiphash.c hashtable_error.c)

ADD_EXECUTABLE (test ${SRCS})
