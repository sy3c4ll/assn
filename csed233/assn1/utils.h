#include <iostream>

using namespace std;

typedef struct Instruction {
  string command;
  int value;
} Instruction;

typedef struct InstructionSequence {
  Instruction *instructions;
  int length;
} InstructionSequence;

InstructionSequence *ParseInstructions(const char *arg);
void DeleteInstructionSequence(InstructionSequence *instr_seq);
void PrintInstructionSequence(InstructionSequence *instr_seq);

const char *const TASK_3_DEFAULT_ARGUMENT =
    "[('insert',2),('insert',1),('insert',3)]";
const char *const TASK_4_DEFAULT_ARGUMENT =
    "[]{}()";
const char *const TASK_5_DEFAULT_ARGUMENT =
    "[('e',4),('e',7),('d',NULL),('show',NULL)]";
const char *const TASK_6_DEFAULT_ARGUMENT =
    "[('e',5),('e',3),('d', NULL),('show', NULL)]";