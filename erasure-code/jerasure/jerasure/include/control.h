#ifndef _CONTROL_H
#define _CONTROL_H
#include<stdio.h>
#include<stdlib.h>
typedef struct {
	int symbol_numbers;
	int symbol_ids[0];
} Node_info;

typedef struct {
	int node_id;
	Node_info* node_info;
} Solution;

typedef struct {
	int node_numbers;
	Solution** solution;
} Control;
#endif
