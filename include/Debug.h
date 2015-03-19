#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <string.h>

#define print_pos() printf(" @ %s:%d in %s \n\n", __FILE__, __LINE__, __FUNCTION__)
#define dbg_fail()	printf("\nQUITTING\n");exit(EXIT_FAILURE)

#ifdef SUPPRESS_LOGS

	#define log_err(M, ...)
	#define log_warn(M, ...)
	#define check(A, M)		if(!(A)) dbg_fail()
	#define check_mem(A)  	check(A)
	#define sentinel() 		dbg_fail()

#else

	//Utils to print out errors runtime
	#define log_err(M, ...)		printf("[ERROR] " M"\n", ##__VA_ARGS__); print_pos()
	#define log_warn(M, ...)	printf("[WARN]  " M"\n", ##__VA_ARGS__); print_pos()

	//CHECK FOR MEMORY/LOGIC ERRORS
	#define check(A, M, ...) 	if(!(A)) {log_err(M, ##__VA_ARGS__); dbg_fail();}
	#define check_mem(A)    check(A, "Memory Error")

	//SENTINEL FOR SWITCH/CASE
	#define sentinel() 		log_err("VALUE NOT HANDLED IN SWITCH/CASE"); dbg_fail()

#endif

#ifdef SUPPRESS_INFO
	#define log_info(M, ...)
#else
	#define log_info(M, ...) printf("[INFO]  " M"\n", ##__VA_ARGS__)
#endif

#endif // DEBUG_H


