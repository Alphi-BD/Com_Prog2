#include "Gammatron.h"
#include <iostream>
#include <iomanip>
using namespace std;

void Gammatron::memory_dump() {
    char prev = std::cout.fill('0');
    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 9; col++) {
            std::cout << std::setw(4) << memory[10 * row + col] << " ";
        }
        std::cout << std::setw(4) << memory[10 * row + 9] << std::endl;
    }
    std::cout.fill(prev);
}

void Gammatron::read_program() {
    for (int i = 0; i < 100; i++) memory[i]=0;

    std::string line;
    int memcounter = 1;
    while (std::getline(std::cin, line) && line.find("RUN") != 0) {
        int command = std::stoi(line);
        memory[memcounter++] = command;
    }
}

void Gammatron::run_program() {
    program_counter = 1;
    accumulator = 0;

    while (true) {
        int instruction = memory[program_counter];
        int opcode = instruction / 100;
        int operand = instruction % 100;
        bool increment_pc = true;

        switch (opcode) {
            case LOAD:
                accumulator = memory[operand];
                break;

            case STORE:
                memory[operand] = accumulator;
                break;

            case INPUT:
                {
                    int input_value;
                    cin >> input_value;
                    if (operand == 0) {
                        accumulator = input_value;
                    } else {
                        memory[operand] = input_value;
                    }
                }
                break;

            case OUTPUT:
                if (operand == 0) {
                    cout << accumulator << endl;
                } else {
                    cout << memory[operand] << endl;
                }
                break;

            case JUMP:
                program_counter = operand;
                increment_pc = false;
                break;

            case JUMPPOS:
                if (accumulator > 0) {
                    program_counter = operand;
                    increment_pc = false;
                }
                break;

            case JUMPZERO:
                if (accumulator == 0) {
                    program_counter = operand;
                    increment_pc = false;
                }
                break;

            case INC:
                accumulator++;
                break;

            case DEC:
                accumulator--;
                break;

            case ADD:
                accumulator += memory[operand];
                break;

            case SUB:
                accumulator -= memory[operand];
                break;

            case HALT:
                return;

            case SKIP:
                break;

            default:
                cerr << "Invalid opcode: " << opcode << endl;
                return;
        }

        if (increment_pc) {
            program_counter++;
        }

        if (program_counter < 1 || program_counter >= 100) {
            cerr << "Program counter out of bounds: " << program_counter << endl;
            return;
        }
    }
}