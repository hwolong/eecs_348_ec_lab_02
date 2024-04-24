#include <stdio.h>
#include <stdbool.h>

void printScore(int td2, int td1, int td, int fg, int safety) {
    printf("%d TD + 2pt, %d TD + FG, %d TD, %d 3pt FG, %d safety\n", td2, td1, td, fg, safety);
}

void iterateScore(int currentScore, int score, int td2Count, int td1Count, int tdCount, int fgCount, int safetyCount, bool iterateTD2, bool iterateTD1, bool iterateTD, bool iterateFG, bool iterateSafety) {
    int safety = 2;
    int fg = 3;
    int td = 6;
    int td1 = 7;
    int td2 = 8;

    if (iterateTD2 == true) {
        while (((td2Count+1) * td2) <= score) {
            td2Count++;
        }
        currentScore += (td2Count * td2);
        if (currentScore == score) {
            printScore(td2Count, td1Count, tdCount, fgCount, safetyCount);
        } else {
            iterateScore(currentScore, score, td2Count, 0, 0, 0, 0, false, true, true, true, true);
        }
        while (td2Count > 0) {
            td2Count--;
            iterateScore((td2Count * td2), score, td2Count, 0, 0, 0, 0, false, true, true, true, true);
        }
    } else {
        if (iterateTD1 == true) {
            while ((currentScore + ((td1Count+1) * td1)) <= score) {
                td1Count++;
            }
            currentScore += (td1Count * td1);
            if (currentScore == score) {
                printScore(td2Count, td1Count, tdCount, fgCount, safetyCount);
            } else {
                iterateScore(currentScore, score, td2Count, td1Count, 0, 0, 0, false, false, true, true, true);
            }
            while (td1Count > 0) {
                td1Count--;
                iterateScore(((td2Count * td2) + (td1Count * td1)), score, td2Count, td1Count, 0, 0, 0, false, false, true, true, true);
            }
        } else {
            if (iterateTD == true) {
                while ((currentScore + ((tdCount+1) * td)) <= score) {
                    tdCount++;
                }
                currentScore += (tdCount * td);
                if (currentScore == score) {
                    printScore(td2Count, td1Count, tdCount, fgCount, safetyCount);
                } else {
                    iterateScore(currentScore, score, td2Count, td1Count, tdCount, 0, 0, false, false, false, true, true);
                }
                while (tdCount > 0) {
                    tdCount--;
                    iterateScore(((td2Count * td2) + (td1Count * td1) + (tdCount * td)), score, td2Count, td1Count, tdCount, 0, 0, false, false, false, true, true);
                }
            } else {
                if (iterateFG == true) {
                    while ((currentScore + ((fgCount+1) * fg)) <= score) {
                        fgCount++;
                    }
                    currentScore += (fgCount * fg);
                    if (currentScore == score) {
                        printScore(td2Count, td1Count, tdCount, fgCount, safetyCount);
                    } else {
                        iterateScore(currentScore, score, td2Count, td1Count, tdCount, fgCount, 0, false, false, false, false, true);
                    }
                    while (fgCount > 0) {
                        fgCount--;
                        iterateScore(((td2Count * td2) + (td1Count * td1) + (tdCount * td) + (fgCount * fg)), score, td2Count, td1Count, tdCount, fgCount, 0, false, false, false, false, true);
                    }
                } else {
                    if (iterateSafety == true) {
                        while ((currentScore + ((safetyCount+1) * safety)) <= score) {
                            safetyCount++;
                        }
                        currentScore += (safetyCount * safety);
                        if (currentScore == score) {
                            printScore(td2Count, td1Count, tdCount, fgCount, safetyCount);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int safety = 2;
    int fg = 3;
    int td = 6;
    int td1 = 7;
    int td2 = 8;
    bool keepRunning = true;
    while (keepRunning == true) {
        int score;
        printf("Enter 0 or 1 to STOP.\nEnter the NFL score: ");
        scanf("%d", &score);
        if (score <= 1) {
            keepRunning = false;
        } else {
            iterateScore(0, score, 0, 0, 0, 0, 0, true, true, true, true, true);
        }
    }
    return 0;
}