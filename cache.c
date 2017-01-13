/* Hello World program */

#include<stdio.h>

struct row {
    int valid;
    int tag;
    int counter;
};

int counter = 0;
struct row cache[5000];
int test_set_1[] = {0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80, 0, 4, 8, 12, 16, 71, 3, 41, 81, 39, 38, 71, 15, 39, 11, 51, 57, 41};

int isHitOrMissForSetAssoc(int setSize, int tag, int set) {
    // check for cache hit
    for ( int rowIndex = setSize * set; rowIndex < setSize * set + setSize; rowIndex++ ) {
        if (cache[rowIndex].valid && cache[rowIndex].tag == tag) {
            return 1;
        }
        if (cache[rowIndex].valid == 0) {
            cache[rowIndex].valid = 1;
            cache[rowIndex].tag = tag;
            cache[rowIndex].counter = ++counter;
            return 0;
        }
    }
    //if no open slot evict oldest
    struct row *oldestRow = &cache[setSize * set];
    for ( int rowIndex = setSize * set + 1; rowIndex < setSize * set + setSize; rowIndex++ ) {
        if (cache[rowIndex].counter < oldestRow->counter) {
            oldestRow = &cache[rowIndex];
        }
    }
    oldestRow->counter = ++counter;
    oldestRow->tag = tag;
    return 0;
}

int base(int num) {
    int answer = 0;
    while (num > 1) {
        num = num / 2;
        answer++;
    }
    return answer;
}

int base2(int block, int sets) {
    int amount = base(block) + base(sets);

    int sum = 1;
    for (int i = 0; i < amount; i++) {
        sum *= 2;
    }
    return sum;
}


void sim(int sets, int size, int block, int addresses[]) {
    for (int i = 0; i < 39; i++) {

        int address = addresses[i];

        int tag = address / base2(block, sets);
        int set = (address / block) % sets;
        int offset = address % block;

        if (isHitOrMissForSetAssoc((size / block / sets), tag, set) == 1) {
            printf("%d: HIT %d/%d/%d \n", address, tag, set, offset);
        }
        else {
            printf("%d: MISS %d/%d/%d \n", address, tag, set, offset);
        }
    }
}

void resetCache() {
    for (int i =0; i < 5000; i++) {
        cache[i].valid = 0;
    }
}

int main() {
    // use number of sets instead of n-way
//    resetCache();
//    printf("First Test:\n");
//    sim(16, 128, 8, test_set_1);
//    printf("\n");
//
//    resetCache();
//    printf("Second Test:\n");
//    sim(4, 64, 8, test_set_1);
//    printf("\n");
//
//    resetCache();
//    printf("Third Test:\n");
//    sim(8, 128, 16, test_set_1);
//    printf("\n");

    resetCache();
    printf("Fourth Test:\n");
    sim(8192, 131072, 8, test_set_1);
}
