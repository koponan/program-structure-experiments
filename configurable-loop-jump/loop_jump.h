#ifndef LOOP_JUMP_H_
#define LOOP_JUMP_H_

enum LoopJumpStrategy {
    HARD,
    SOFT
};

#define LOOP_JUMP(strategy)    \
({                             \
    if ((strategy) == HARD) {  \
        break;                 \
    } else {                   \
        continue;              \
    }                          \
})

#endif