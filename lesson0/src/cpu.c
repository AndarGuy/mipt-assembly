/* Программа эмуляции трехадрессного процессора */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX(a, b) a < b ? b : a

#define DEBUG 0

const int MEMORY_SIZE = 16384;
const int CELL_SIZE = 7;
const int COMMAND_SIZE = 8;
const int ADDRESS_SIZE = 16;

typedef union {
  unsigned char memory[CELL_SIZE];
  long int value;
  struct Command {
    unsigned char code : COMMAND_SIZE;
    unsigned int param1 : ADDRESS_SIZE;
    unsigned int param2 : ADDRESS_SIZE;
    unsigned int param3 : ADDRESS_SIZE;
  } command;
} CellData;

typedef enum {
    CELL_TYPE_CONSTANT,
    CELL_TYPE_VARIABLE,
    CELL_TYPE_COMMAND,
    CELL_TYPE_VOID
} CellType;

typedef struct {
    CellType type;
    CellData data;
    char *comment;
} Cell;

enum Commands {
    COMMAND_MOV = 0x00,
    COMMAND_ADD = 0x01,
    COMMAND_SUB = 0x02,
    COMMAND_IMUL = 0x03,
    COMMAND_DIV = 0x04,

    COMMAND_MUL = 0x13,
    COMMAND_MOD = 0x14,

    COMMAND_INPUT = 0x20,
    COMMAND_OUTPUT = 0x21,

    COMMAND_JMP = 0x80,
    COMMAND_JMP_EQUAL = 0x81,
    COMMAND_JMP_NOT_EQUAL = 0x82,
    COMMAND_JMP_I_LESSER = 0x83,
    COMMAND_JMP_I_GREATER_EQUAL = 0x84,
    COMMAND_JMP_I_GREATER = 0x85,
    COMMAND_JMP_I_LESSER_EQUAL = 0x86,

    COMMAND_JMP_LESSER = 0x93,
    COMMAND_JMP_GREATER_EQUAL = 0x94,
    COMMAND_JMP_GREATER = 0x95,
    COMMAND_JMP_LESSER_EQUAL = 0x96,

    COMMAND_EXIT = 0x99
};

long int mov_handler(Cell memory[MEMORY_SIZE], long int needle) {
    CellData cell = memory[needle].data;
    printf("MOV [%x](%ld) -> [%x]\n", cell.command.param1, memory[cell.command.param1].data.value, cell.command.param3);
    memory[cell.command.param3].data.value = memory[cell.command.param1].data.value;
    return needle + 1;
}

long int add_handler(Cell memory[MEMORY_SIZE], long int needle) {
    CellData cell = memory[needle].data;
    printf("ADD [%x](%ld) -> [%x](%ld) + [%x](%ld)\n", cell.command.param3, memory[cell.command.param3].data.value, cell.command.param1, memory[cell.command.param1].data.value, cell.command.param2, memory[cell.command.param2].data.value);
    memory[cell.command.param3].data.value = memory[cell.command.param1].data.value + memory[cell.command.param2].data.value;
    return needle + 1;
}

long int sub_handler(Cell memory[MEMORY_SIZE], long int needle) {
    CellData cell = memory[needle].data;
    printf("SUB [%x](%ld) -> [%x](%ld) - [%x](%ld)\n", cell.command.param3, memory[cell.command.param3].data.value, cell.command.param1, memory[cell.command.param1].data.value, cell.command.param2, memory[cell.command.param2].data.value);
    memory[cell.command.param3].data.value = memory[cell.command.param1].data.value - memory[cell.command.param2].data.value;
    return needle + 1;
}

long int mul_handler(Cell memory[MEMORY_SIZE], long int needle) {
    CellData cell = memory[needle].data;
    printf("MUL [%x](%ld) -> [%x](%ld) * [%x](%ld)\n", cell.command.param3, memory[cell.command.param3].data.value, cell.command.param1, memory[cell.command.param1].data.value, cell.command.param2, memory[cell.command.param2].data.value);
    memory[cell.command.param3].data.value = memory[cell.command.param1].data.value * memory[cell.command.param2].data.value;
    return needle + 1;
}

long int imul_handler(Cell memory[MEMORY_SIZE], long int needle) {
    CellData cell = memory[needle].data;
    printf("IMUL [%x](%ld) -> [%x](%ld) * [%x](%ld)\n", cell.command.param3, memory[cell.command.param3].data.value, cell.command.param1, memory[cell.command.param1].data.value, cell.command.param2, memory[cell.command.param2].data.value);
    memory[cell.command.param3].data.value = labs(memory[cell.command.param1].data.value * memory[cell.command.param2].data.value);
    return needle + 1;
}

long int div_handler(Cell memory[MEMORY_SIZE], long int needle) {
    CellData cell = memory[needle].data;
    printf("DIV [%x](%ld) -> [%x](%ld) / [%x](%ld)\n", cell.command.param3, memory[cell.command.param3].data.value, cell.command.param1, memory[cell.command.param1].data.value, cell.command.param2, memory[cell.command.param2].data.value);
    memory[cell.command.param3].data.value = memory[cell.command.param1].data.value / memory[cell.command.param2].data.value;
    return needle + 1;
}

long int mod_handler(Cell memory[MEMORY_SIZE], long int needle) {
    CellData cell = memory[needle].data;
    printf("MOD [%x](%ld) -> [%x](%ld) mod [%x](%ld)\n", cell.command.param3, memory[cell.command.param3].data.value, cell.command.param1, memory[cell.command.param1].data.value, cell.command.param2, memory[cell.command.param2].data.value);
    memory[cell.command.param3].data.value = memory[cell.command.param1].data.value % memory[cell.command.param2].data.value;
    return needle + 1;
}

long int input_handler(Cell memory[MEMORY_SIZE], long int needle) {
    CellData cell = memory[needle].data;
    printf("Waiting for input...\n\n");
    long int value;
    scanf("%ld%*c", &value);
    printf("\n");
    printf("INPUT [%x](%ld) -> (%ld)\n", cell.command.param1, memory[cell.command.param1].data.value, value);
    memory[cell.command.param1].data.value = value;
    return needle + 1;
} 

long int output_handler(Cell memory[MEMORY_SIZE], long int needle) {
    CellData cell = memory[needle].data;
    printf("OUTPUT [%x](%ld)\n", cell.command.param1, memory[cell.command.param1].data.value);
    // printf("%ld\n", memory[cell.command.param1].data.value);
    return needle + 1;
}

long int jump_handler(Cell memory[MEMORY_SIZE], long int needle) {
    CellData cell = memory[needle].data;
    printf("JMP [%lx] -> [%x]\n", needle, cell.command.param1);
    return cell.command.param1;
}

long int jump_equal_handler(Cell memory[MEMORY_SIZE], long int needle) {
    CellData cell = memory[needle].data;
    printf("JMP_EQ [%x](%ld) == [%x](%ld) -> [%x] : [%lx]\n", cell.command.param1, memory[cell.command.param1].data.value, cell.command.param2, memory[cell.command.param2].data.value, cell.command.param3, needle);
    return memory[cell.command.param1].data.value == memory[cell.command.param2].data.value ? cell.command.param3 : needle + 1;
}

long int jump_not_equal_handler(Cell memory[MEMORY_SIZE], long int needle) {
    CellData cell = memory[needle].data;
    printf("JMP_N_EQ [%x](%ld) <> [%x](%ld) -> [%x] : [%lx]\n", cell.command.param1, memory[cell.command.param1].data.value, cell.command.param2, memory[cell.command.param2].data.value, cell.command.param3, needle);
    return memory[cell.command.param1].data.value != memory[cell.command.param2].data.value ? cell.command.param3 : needle + 1;
}

long int jump_i_lesser_handler(Cell memory[MEMORY_SIZE], long int needle) {
    CellData cell = memory[needle].data;
    printf("JMP_I_LE |[%x](%ld)| < |[%x](%ld)| -> [%x] : [%lx]\n", cell.command.param1, memory[cell.command.param1].data.value, cell.command.param2, memory[cell.command.param2].data.value, cell.command.param3, needle);
    return labs(memory[cell.command.param1].data.value) < labs(memory[cell.command.param2].data.value) ? cell.command.param3 : needle + 1;
}

long int jump_i_greater_handler(Cell memory[MEMORY_SIZE], long int needle) {
    CellData cell = memory[needle].data;
    printf("JMP_I_GR |[%x](%ld)| > |[%x](%ld)| -> [%x] : [%lx]\n", cell.command.param1, memory[cell.command.param1].data.value, cell.command.param2, memory[cell.command.param2].data.value, cell.command.param3, needle);
    return labs(memory[cell.command.param1].data.value) > labs(memory[cell.command.param2].data.value) ? cell.command.param3 : needle + 1;
}

long int jump_i_lesser_equal_handler(Cell memory[MEMORY_SIZE], long int needle) {
    CellData cell = memory[needle].data;
    printf("JMP_I_LE_EQ |[%x](%ld)| <= |[%x](%ld)| -> [%x] : [%lx]\n", cell.command.param1, memory[cell.command.param1].data.value, cell.command.param2, memory[cell.command.param2].data.value, cell.command.param3, needle);
    return labs(memory[cell.command.param1].data.value) <= labs(memory[cell.command.param2].data.value) ? cell.command.param3 : needle + 1;
}

long int jump_i_greater_equal_handler(Cell memory[MEMORY_SIZE], long int needle) {
    CellData cell = memory[needle].data;
    printf("JMP_I_GR_EQ |[%x](%ld)| >= |[%x](%ld)| -> [%x] : [%lx]\n", cell.command.param1, memory[cell.command.param1].data.value, cell.command.param2, memory[cell.command.param2].data.value, cell.command.param3, needle);
    return labs(memory[cell.command.param1].data.value) >= labs(memory[cell.command.param2].data.value) ? cell.command.param3 : needle + 1;
}

long int jump_lesser_handler(Cell memory[MEMORY_SIZE], long int needle) {
    CellData cell = memory[needle].data;
    printf("JMP_LE [%x](%ld) < [%x](%ld) -> [%x] : [%lx]\n", cell.command.param1, memory[cell.command.param1].data.value, cell.command.param2, memory[cell.command.param2].data.value, cell.command.param3, needle);
    return memory[cell.command.param1].data.value < memory[cell.command.param2].data.value ? cell.command.param3 : needle + 1;
}

long int jump_greater_handler(Cell memory[MEMORY_SIZE], long int needle) {
    CellData cell = memory[needle].data;
    printf("JMP_GR [%x](%ld) > [%x](%ld) -> [%x] : [%lx]\n", cell.command.param1, memory[cell.command.param1].data.value, cell.command.param2, memory[cell.command.param2].data.value, cell.command.param3, needle);
    return memory[cell.command.param1].data.value > memory[cell.command.param2].data.value ? cell.command.param3 : needle + 1;
}

long int jump_lesser_equal_handler(Cell memory[MEMORY_SIZE], long int needle) {
    CellData cell = memory[needle].data;
    printf("JMP_LE_EQ [%x](%ld) <= [%x](%ld) -> [%x] : [%lx]\n", cell.command.param1, memory[cell.command.param1].data.value, cell.command.param2, memory[cell.command.param2].data.value, cell.command.param3, needle);
    return memory[cell.command.param1].data.value <= memory[cell.command.param2].data.value ? cell.command.param3 : needle + 1;
}

long int jump_greater_equal_handler(Cell memory[MEMORY_SIZE], long int needle) {
    CellData cell = memory[needle].data;
    printf("JMP_GR_EQ [%x](%ld) >= [%x](%ld) -> [%x] : [%lx]\n", cell.command.param1, memory[cell.command.param1].data.value, cell.command.param2, memory[cell.command.param2].data.value, cell.command.param3, needle);
    return memory[cell.command.param1].data.value >= memory[cell.command.param2].data.value ? cell.command.param3 : needle + 1;
}

long int exit_handler(Cell memory[MEMORY_SIZE], long int needle) {
    printf("Exiting the program!\n");
    return -1;
}

char *remove_comment(char *line) {
    char *comment;
    int length = strlen(line);
    for (int i = 0; line[i] > 0; i++) {
        if (line[i] == '#') {
            line[i] = '\0';
            i++;
            while (line[i] != '\0' && line[i] == ' ') i++;
            if (line[i] == '\0') return NULL;
            comment = malloc(length - i + 1);
            strcpy(comment, line + i);
            return comment;
        }
    }
    return NULL;
}

bool load_program(Cell memory[MEMORY_SIZE], char *filename) {
    if (DEBUG) printf("[LOAD_PROGRAM] Trying to load ASM from file «%s»\n", filename);
    const size_t CONSTANT_ARGS = 2, COMMAND_ARGS = 5;
    const int MAX_LINE_SIZE = 128;
    FILE *program = fopen(filename, "r");
    if (DEBUG) printf("[LOAD_PROGRAM] ASM was successfully loaded to address %p\n", program);
    for (int line = 1; !feof(program); line++) {
        if (DEBUG) printf("[LOAD_PROGRAM] Trying to read line №%d\n", line);
        char *buffer = malloc(sizeof(char) * MAX_LINE_SIZE);

        fgets(buffer, MAX_LINE_SIZE, program);
        int line_length = strlen(buffer);
        if (line_length && buffer[line_length - 1] == '\n') buffer[line_length - 1] = '\0';

        if (DEBUG) printf("[LOAD_PROGRAM] The line was read: «%s»\n", buffer);
        
        char *comment = remove_comment(buffer);

        if (DEBUG) printf("[LOAD_PROGRAM] Removing comments from line: «%s»\n", buffer);

        long int args[5];
        int number_of_args = sscanf(buffer, "%lx%lx%lx%lx%lx", args + 0, args + 1, args + 2, args + 3, args + 4);

        // printf("%ld %ld %ld %ld %ld\n", args[0], args[1], args[2], args[3], args[4]);

        if (number_of_args <= 0) {
            if (DEBUG) printf("[LOAD_PROGRAM] Empty line, skipping...\n");
        } else {
            if (args[0] > MEMORY_SIZE) return line;

            if (number_of_args == CONSTANT_ARGS) {

                memory[args[0]].data = (CellData) args[1];
                memory[args[0]].comment = comment;
                memory[args[0]].type = CELL_TYPE_CONSTANT;

            } else if (number_of_args == COMMAND_ARGS) {
                if (args[1] > UINT8_MAX) return line;

                // check correctness of arguments
                for (int arg = 2; arg < 5; arg++) 
                    if (args[arg] > MEMORY_SIZE)
                        if (args[arg] < 0)
                            return line;

                memory[args[0]].comment = comment;
                memory[args[0]].data = (CellData) (struct Command) {(char) args[1], (unsigned int) args[2], (unsigned int) args[3], (unsigned int) args[4]};
                memory[args[0]].type = CELL_TYPE_COMMAND;

                if ((char) args[1] == COMMAND_ADD || (char) args[1] == COMMAND_DIV || (char) args[1] == COMMAND_MUL || (char) args[1] == COMMAND_SUB || (char) args[1] == COMMAND_IMUL || (char) args[1] == COMMAND_MOD || (char) args[1] == COMMAND_MOV) memory[args[4]].type = CELL_TYPE_VARIABLE;
                if ((char) args[1] == COMMAND_INPUT) memory[args[2]].type = CELL_TYPE_VARIABLE;
                
            } else return line;
        }
    }

    return 0;
}

void print_greetings() {
    printf("**Welcome to PEMU**\n");
}

void ui_command_hander() {
    printf("--select command to continue--\n");
}

int get_number_length(long int number) {
    int length = 0;
    if (number < 0) length++;
    for (length = 0; labs(number) > 0; number /= 10, length++);
    return length;
}

int get_hex_number_length(long int number) {
    int length = 0;
    if (number < 0) length++;
    for (length = 0; labs(number) > 0; number /= 16, length++);
    return length;
}

int max(int a, int b) {  
    if (a > b) return a;
    return b;
}

void print_constants(Cell memory[MEMORY_SIZE]) {
    Cell variables[UINT8_MAX];
    int seps[UINT8_MAX];
    unsigned long addresses[UINT16_MAX];
    int amount = 0;
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].type == CELL_TYPE_CONSTANT) {
            variables[amount] = memory[i];
            addresses[amount] = i;
            seps[amount] = max(get_hex_number_length(i) + 2, get_number_length(memory[i].data.value));
            amount++;
        }
    }

    if (amount > 0) {
        printf("--CONSTANTS--\n\n");

    for (int i = 0; i < amount; i++) {
        printf("%*p\t", seps[i], addresses[i]);
    }
    
    printf("\n");

    for (int i = 0; i < amount; i++) 
        printf("%*ld\t", seps[i], variables[i].data.value);
    
    printf("\n\n"); 

    } else {
        printf("--NO CONSTANTS--\n\n");
    }
}

void print_variables(Cell memory[MEMORY_SIZE]) {
    Cell variables[UINT8_MAX];
    int seps[UINT8_MAX];
    unsigned long addresses[UINT16_MAX];
    int amount = 0;
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if (memory[i].type == CELL_TYPE_VARIABLE) {
            variables[amount] = memory[i];
            addresses[amount] = i;
            seps[amount] = max(memory[i].comment == NULL ? get_hex_number_length(i) + 2 : strlen(memory[i].comment), get_number_length(memory[i].data.value));
            amount++;
        }
    }

    if (amount > 0) {
        printf("--VARIABLES--\n\n");

    for (int i = 0; i < amount; i++) {
        if (variables[i].comment != NULL) {
            printf("%*s\t", seps[i], variables[i].comment);
        } else {
            printf("%*p\t", seps[i], addresses[i]);
        }
    }
    
    printf("\n");

    for (int i = 0; i < amount; i++) 
        printf("%*ld\t", seps[i], variables[i].data.value);
    
    printf("\n\n"); 

    } else {
        printf("--NO VARIABLES--\n\n");
    }

}

int run_program(Cell memory[MEMORY_SIZE], long int (*handlers[UINT8_MAX])(Cell memory[MEMORY_SIZE], long int needle)) {
    long int needle = 0x0;
    for (long int iteration = 0; true; iteration++) {
        // if (DEBUG) printf("[RUN_PROGRAM] Executing line 0x%lx...\n", needle);
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        print_constants(memory);
        print_variables(memory);
        printf("--COMMAND--\n\n");
        needle = handlers[memory[needle].data.command.code](memory, needle);
        printf("\n");
        printf("Press to continue...\n\n");
        while (getc(stdin) != '\n');
        if (needle < 0) return 0;
        if (needle >= MEMORY_SIZE) return 1;
    }
}

void prepare_handlers(long int (*handlers[UINT8_MAX])(Cell memory[MEMORY_SIZE], long int needle)) {
    handlers[COMMAND_MOV] = mov_handler;
    handlers[COMMAND_ADD] = add_handler;
    handlers[COMMAND_SUB] = sub_handler;
    handlers[COMMAND_MUL] = mul_handler;
    handlers[COMMAND_IMUL] = imul_handler;
    handlers[COMMAND_DIV] = div_handler;
    handlers[COMMAND_MOD] = mod_handler;

    handlers[COMMAND_INPUT] = input_handler;
    handlers[COMMAND_OUTPUT] = output_handler;
    
    handlers[COMMAND_JMP] = jump_handler;
    handlers[COMMAND_JMP_EQUAL] = jump_equal_handler;
    handlers[COMMAND_JMP_NOT_EQUAL] = jump_not_equal_handler;

    handlers[COMMAND_JMP_GREATER] = jump_greater_handler;
    handlers[COMMAND_JMP_LESSER] = jump_lesser_handler;
    handlers[COMMAND_JMP_GREATER_EQUAL] = jump_greater_equal_handler;
    handlers[COMMAND_JMP_LESSER_EQUAL] = jump_lesser_equal_handler;

    handlers[COMMAND_JMP_I_GREATER] = jump_i_greater_handler;
    handlers[COMMAND_JMP_I_LESSER] = jump_i_lesser_handler;
    handlers[COMMAND_JMP_I_GREATER_EQUAL] = jump_i_greater_equal_handler;
    handlers[COMMAND_JMP_I_LESSER_EQUAL] = jump_i_lesser_equal_handler;

    handlers[COMMAND_EXIT] = exit_handler;
}

int main() {
    Cell memory[MEMORY_SIZE];

    for (int i = 0; i < MEMORY_SIZE; i++) memory[i].type = CELL_TYPE_VOID;

    long int (*handlers[UINT8_MAX])(Cell memory[MEMORY_SIZE], long int needle);

    prepare_handlers(handlers);
    
    print_greetings();
    char *PROGRAM = "programs/sin_2.asm";
    int exceptional_line = load_program(memory, PROGRAM);
    if (exceptional_line != 0) {
        printf("[MAIN] Exception occured at line №%d while loading program «%s»", exceptional_line, PROGRAM);
        return 0;
    }

    run_program(memory, handlers);

    return 0;
}