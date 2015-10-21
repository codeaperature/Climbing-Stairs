//
//  https://www.codeeval.com/open_challenges/64/
//  climbingstairs
//
//  Created by Stephan Warren on 1/3/15.
//  Copyright (c) 2015 Stephan Warren. All rights reserved.
//

/*
 CLIMBING STAIRS
 CHALLENGE DESCRIPTION:
 
 You are climbing a stair case. It takes n steps to reach to the top. Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
 
 INPUT SAMPLE:
 
 Your program should accept as its first argument a path to a filename. Each line in this file contains a positive integer which is the total number of stairs.
 Ignore all empty lines. E.g.
 
 10
 20
 
 OUTPUT SAMPLE:
 
 Print out the number of ways to climb to the top of the staircase. E.g.
  
 89
 10946
 Constraints:
 The total number of stairs is <= 1000
 
*/

#include <stdio.h>
#define BIGGEST_ULL  1000000000000000000ULL
//                  18446744073709551615
//                  09876543210987654321
#define FIELDWIDTH  12



typedef struct { unsigned long long nines[FIELDWIDTH]; char len; } bigint_t;



void resetFlipFlop(bigint_t * biptr)
{
    biptr[0].nines[0] = 1;
    biptr[1].nines[0] = 2;
    for(char i = 1; i < FIELDWIDTH; i++) biptr[0].nines[i] = biptr[1].nines[i] = 0;
    biptr[0].len = biptr[1].len = 1;
}




int main(int argc, const char * argv[]) {

    int n = 10;
    bigint_t bi[2];
    resetFlipFlop(bi);
   
    
    char flip, flop;
    short next = 2;
    FILE *file = fopen(argv[1], "r");

    while(fscanf(file, "%d\n", &n) == 1) {
        if(n >= 2) {
            if(next > n) {
                next = 2;
                resetFlipFlop(bi);
            }
            for(short i = next; i < n; i++) {
                char CARRY = 0;
                flip = i & 1;
                flop = flip ^ 1;
                for(char j = 0; j < bi[flop].len; j++) {
                    bi[flip].nines[j] += bi[flop].nines[j];
                    if(CARRY) bi[flip].nines[j]++;
                    if(BIGGEST_ULL <= bi[flip].nines[j]) {
                        bi[flip].nines[j] -= BIGGEST_ULL;
                        CARRY = 1;
                    }
                    else {
                        CARRY = 0;
                    }
                    if((bi[flip].len - 1 == j) && (CARRY)) {
                        bi[flip].len = bi[flop].len = j + 2;
                       // bi[flip].nines[j + 1] = 1;
                    }
                }
//                if(n == i + 1) {
//                printf("%d (%d): ", n, i);
//                for(char j = bi[flip].len - 1; j >= 0; j--) {
//                    if(j == bi[flip].len - 1) printf("%llu", bi[flip].nines[j]);
//                    else printf("%018llu", bi[flip].nines[j]);
//                    //                printf("%019llu ", bi[flip].nines[j]);
//                }
//                printf("\n");
//                }
//    //            printf("    %019llu%019llu%019llu\n", BIGGEST_ULL, BIGGEST_ULL, BIGGEST_ULL);
            }
            flip = (n & 1) ^ 1;
    //        printf("%d (%d): ", n, bi[flip].len);
            for(char j = bi[flip].len - 1; j >= 0; j--) {
                if(j == bi[flip].len - 1) printf("%llu", bi[flip].nines[j]);
                else printf("%018llu", bi[flip].nines[j]);
                //                printf("%018llu ", bi[flip].nines[j]);
            }
            printf("\n");
            next = n;
        }
        else {
            printf("%d\n", n & 0x1);
        }
    }
    return 0;
}
