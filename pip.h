#ifndef _PIP_H_
#define _PIP_H_

struct Problem{
	int probNumber;
	char probDesc[500];
	struct Problem *probNext;
};

struct Proposal{
	int propNumber;
	char propDesc[500];
	struct Proposal *propNext;
};

struct ProcessImprovementProposal{
	struct Problem *problem;
	struct Proposal *proposal;
	char NotesAndComments[500];
};

typedef struct Problem Problem;
typedef struct Proposal Proposal;
typedef struct ProcessImprovementProposal ProcessImprovementProposal;
typedef struct ProcessImprovementProposal *procImPro;

#endif // _PIP_H_
