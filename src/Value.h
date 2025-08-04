//
// Created by Sakura on 25-7-28.
//

#ifndef VALUE_H
#define VALUE_H

template <typename T>
struct Value {
    T now, nxt;

    void tick() {
        now = nxt;
    }

    void operator =(T x) {
        nxt = x;
    }

    void set(T x) {
        nxt = x;
    }

    T get() {
        return now;
    }
};

#endif //VALUE_H
