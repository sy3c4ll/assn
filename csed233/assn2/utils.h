#include <iostream>

using namespace std;

class Instruction {
public:
    void setCommand(string cmd);
    void setValue(int val);

    string getCommand();
    int getValue();

private:
    string command;
    int value;
};

class InstructionSequence {
public:
    InstructionSequence();
    ~InstructionSequence();

    int getLength();
    Instruction &getInstruction(int index);

    void parseInstructions(const char *arg);
    void printInstructions();

private:
    Instruction *instructions;
    int length;
};

const char *const TASK_2_DEFAULT_ARGUMENT = "1(2(4()(5()(6)))(3))()";
const char *const TASK_3_DEFAULT_ARGUMENT = "4(2(3)(1))(6(5))";
const char *const TASK_3_DEFAULT_ARGUMENT_2 = "inorder";
const char* const TASK_4_DEFAULT_ARGUMENT[]={"[2,1,3]", "[1,2,3]", "pre"};
const char *const TASK_5_DEFAULT_ARGUMENT =
        "[('insert',5),('insert',-3),('insert',2)]";
const char *const TASK_6_DEFAULT_ARGUMENT =
        "[('insert',5),( 'insert',-3),( 'insert',2), ('removeMax', 0)]";
