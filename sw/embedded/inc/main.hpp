#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdint.h>

const uint32_t uwTickFreq = 1U;

// Interrupt Service Routines
#pragma once
#ifdef __cplusplus
extern "C" 
{
#endif

void TIM15_IRQHandler();
void TIM17_IRQHandler();

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__