
#ifndef _TESTREPORT_H_
#define _TESTREPORT_H_
struct TestReport{
	int testReportNumber;
	char testReportDesc[500];
	char testReportConditions[500];
	char expectedResults[500];
	char actualResults[500];
	struct TestReport *nextTestReport;
};

#endif
