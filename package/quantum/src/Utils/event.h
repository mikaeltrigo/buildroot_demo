/*
 * event.h
 *
 *  Created on: Jul 1, 2019
 *      Author: mybbubuntu
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t quantumEventPcSportMsgAvailable;


#define QUANTUM_EVENT_PC_SPORT_MSG_AVAILABLE &quantumEventPcSportMsgAvailable

void event_init();

#endif /* EVENT_H_ */
