//
// Created by Sakura on 25-8-5.
//

#ifndef RRS_H
#define RRS_H

struct Register_Result_Status {
    bool busy;
    int reorder;
    int value;
};

Register_Result_Status rrs[32];

void flush_zero_register() {
    rrs[0].busy = false;
    rrs[0].value = 0;
}

#endif //RRS_H
