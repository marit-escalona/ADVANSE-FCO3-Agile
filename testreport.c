#include "testreport.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

TestReport *init_testReport(){
	TestReport *testReport;
	
	if((testReport = malloc(sizeof(struct TestReport))) == NULL){
		printf("Error: NOT ENOUGH MEMORY! \n");
		exit(1);
	}
	
	testReport->testReportNumber = 1; 
	testReport->nextTestReport = NULL;
	return testReport;
}

TestReport *add_testReport(TestReport *testReport, char testReportDesc[], char testReportConditions[], char expectedResults[], char actualResults[]){
	TestReport *testReportCurrent;
	TestReport *testReportNext;
	int testReportNumber = 1;
	
	if(testReport == NULL){
		testReport = store_to_NextTestReport(testReport, 1, testReportDesc, testReportConditions, expectedResults, actualResults);
	}
	
	else{
	
		testReportCurrent = testReport;
	
		while(testReportCurrent->nextTestReport!=NULL){
			testReportCurrent = testReportCurrent->nextTestReport;
			testReportNumber++;
		}
	
		testReportNext = store_to_NextTestReport(testReportNext, testReportNumber, testReportDesc, testReportConditions, expectedResults, actualResults);
		testReportCurrent->nextTestReport = testReportNext;
	}
	
	return testReport; 
}

TestReport *store_to_NextTestReport(TestReport *testReportNext, int testReportNumber, char testReportDesc[], char testReportConditions[], char expectedResults[], char actualResults[]){
	
	testReportNext->testReportNumber = testReportNumber;
	strcpy(testReportNext->testReportDesc, testReportDesc);
	strcpy(testReportNext->testReportConditions, testReportConditions);
	strcpy(testRepostNext->expectedResults, expectedResults);
	strcpy(testReportNext->actualResults, actualResults);
	
	return testReportNext;
}
