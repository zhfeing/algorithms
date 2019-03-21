/***
*sort.h - definitions and declarations for all kinds of sort library
*
*       Copyright (c) ZHF. All rights reserved.
*
*Purpose:
*       This file contains constant definitions and external subroutine
*       declarations for the sort subroutine library.
*       [ANSI/System V]
*
*       [Personal]
*
****/

#pragma once

#ifndef _INC_SORT
#define _INC_SORT
#endif // !SORT_ERROR

#define SORT_SYSTEM_ERROR -1
#define INPUT_ERROR 2
#define ALL_RIGHT 0

extern int SORT_ERROR;

int BubbleSort(int*A, int start, int end, char judge);
int QuickSort(int*A, int start, int end, char judge);
int InsertionSort(int*A, int start, int end, char judge);
int SeltionSort(int*A, int start, int end, char judge);
