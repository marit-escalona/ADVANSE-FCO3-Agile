#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "pip.h"

Problem *prob_new()
{
    Problem *prob;
    
	if((prob = malloc(sizeof(Problem))) == NULL){
		printf("Error: NOT ENOUGH MEMORY! \n");
		exit(1);
	}
	
    return prob;
}

Problem *prob_set(Problem *prob, int probNumber, char *probDesc)
{
	prob->probNumber = probNumber;
	strcpy(prob->probDesc, probDesc);
	return prob;
}

Problem *prob_add(Problem *prob, char *probDesc)
{
	Problem *probCurrent;
	Problem *probNew;
	
	probNew = NULL;
	probNew =  prob_new();
	probNew->probNext = NULL;
	
	int probNumber = 1;
	
	if(prob == NULL)
	{		
		
		probNew = prob_set(probNew, probNumber, probDesc);
		prob = probNew;		
	}
	else
	{		
		probNumber++;
		probCurrent = prob;
		while(probCurrent->probNext != NULL)
		{
			probCurrent = probCurrent->probNext;
			probNumber ++;
		}
		probNew = prob_set(probNew, probNumber, probDesc);
		probCurrent->probNext = probNew;		
	}	
	
	return prob;
}

Proposal *prop_new()
{
    Proposal *prop;    
	if((prop = malloc(sizeof(Proposal))) == NULL){
		printf("Error: NOT ENOUGH MEMORY! \n");
		exit(1);
	}	
    return prop;
}

Proposal *prop_set(Proposal *prop, int propNumber, char *propDesc)
{
	prop->propNumber = propNumber;
	strcpy(prop->propDesc, propDesc);
	return prop;
}

Proposal *prop_add(Proposal *prop, char *propDesc)
{	
	Proposal *propCurrent;
	Proposal *propNew;
	
	propNew = NULL;
	propNew = prop_new();
	propNew->propNext = NULL;
	
	int propNumber = 1;
	
	if(prop == NULL)
	{
		propNew = prop_set(propNew, propNumber, propDesc);
		prop = propNew;	
	}
	else
	{
		propNumber++;
		propCurrent = prop;
		while(propCurrent->propNext != NULL)
		{
			propCurrent = propCurrent->propNext;
			propNumber++;
		}
		propNew = prop_set(propNew, propNumber, propDesc);
		propCurrent->propNext = propNew;		
	}	
	return prop;
}

ProcessImprovementProposal *pip_new()
{
    ProcessImprovementProposal *pip;
	if((pip = malloc(sizeof(ProcessImprovementProposal))) == NULL)
	{
		printf("Error: NOT ENOUGH MEMORY! \n");
		exit(1);
	}
    return pip;
}

ProcessImprovementProposal *pip_set(ProcessImprovementProposal *pip, Problem *prob, Proposal *prop, char *NotesAndComments)
{
	pip->problem = prob;
	pip->proposal = prop;
	strcpy(pip->NotesAndComments, NotesAndComments);
	
	return pip;
}

void pip_print(ProcessImprovementProposal *pip){
	
	Problem *prob = prob_new();
	Proposal *prop = prop_new();
	
	if(pip != NULL)
	{	
		prob = pip->problem;
		prop = pip->proposal;
		
		if(prob != NULL)
		{		
			printf("\nPIP Number\tProblem Description");
			while(prob != NULL)
			{
				printf("\n%d\t\t%s", prob->probNumber, prob->probDesc);
				prob = prob->probNext;
			}
		}
		
		if(prop != NULL)
		{
			printf("\n\nProposal\nPIP Number\tProblem Description");
			while(prop != NULL)
			{
				printf("\n%d\t\t%s", prop->propNumber, prop->propDesc);
				prop = prop->propNext;
			}
		}	
		printf("\n\nNotes and Comments\n%s",pip->NotesAndComments);
	}
}

