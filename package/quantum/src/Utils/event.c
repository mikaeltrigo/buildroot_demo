/*
 * event.c
 *
 *  Created on: Jul 1, 2019
 *      Author: mybbubuntu
 */
#include "event.h"

void event_init()
{
    sem_init(&quantumEventPcSportMsgAvailable, 0, 1);

}
