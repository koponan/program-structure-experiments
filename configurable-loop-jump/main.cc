#include <stdio.h>

#include <stdexcept>
#include <string>
#include <vector>

#include "loop_jump.h"

typedef struct {
    int value;
    LoopJumpStrategy strategy;
    std::vector<int> invalid_number_positions;

} SumResult;

SumResult args_to_sum(int argc, const char **argv) {
    SumResult res = {
        .value = 0,
        .strategy = HARD,
        .invalid_number_positions = std::vector<int>()
    };
    int number_start = 1;

    if (argc > 1 && std::string(argv[1]) == "-s" ) {
        res.strategy = SOFT;
        number_start = 2;
    }

    for (int i = number_start; i < argc; i++) {
        try {
            int num = std::stoi(argv[i]);
            res.value += num;
        } catch (std::invalid_argument & e) {
            res.invalid_number_positions.push_back(i);
            LOOP_JUMP(res.strategy);
        }
    }

    return res;
}

int main(int argc, const char **argv) {
    SumResult sum = args_to_sum(argc, argv);
    if (sum.strategy == HARD && !sum.invalid_number_positions.empty()) {
        fprintf(stderr, "Error: Invalid integer '%s'\n", argv[sum.invalid_number_positions[0]]);
        return 1;

    } else if (!sum.invalid_number_positions.empty()) {
        fputs("Warning: Skipped invalid integers", stderr);
        for (int i : sum.invalid_number_positions) {
            fprintf(stderr, " '%s'", argv[i]);
        }
        fputc('\n', stderr);
    }

    printf("%d\n", sum.value);

    return 0;
}