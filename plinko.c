#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define LAYERS 16
#define BALLS 5

//randomizer is to make the ball go either left (-1) or right (+1)
int randomizer() {
    return (rand() % 2 == 0) ? 1 : -1;
}

//multiplier is to change the value on the ball based on where it fell
int multiplier(int dist, float *value) {
    switch(abs(dist)){
    case 0:
        *value = 0.5 * *value;
        break;
    case 2:
        *value = 1 * *value;
        break;
    case 4:
        *value = 1.1 * *value;
        break;
    case 6:
        *value = 1.2 * *value;
        break;
    case 8:
        *value = 1.4 * *value;
        break;
    case 10:
        *value = 1.6 * *value;
        break;
    case 12:
        *value = 2 * *value;
        break;
    case 14:
        *value = 9 * *value;
        break;
    case 16:
        *value = 16 * *value;
        break;
    }
}

int main() {

    //THIS DOES NOT HAVE AN INTERFACE AND CANT RETHROW THE BALLS YET, IT JUST SIMULATES PLNIKO, BUT IT WORKS JUST AS FINE!!

    //balls falling have 3 stats: exist, distance, ball value
    int ball[2][BALLS];
    float ballValue[BALLS];
    int i, j, inputB;
    float money, moneyCopy;
    money = 100.0; //initial money the user has
    moneyCopy = money;

    srand(time(NULL));


    //this for(for)) clears the whole array, removing the balls, expect to be executed once, just to open the program
    for(i = 0; i< BALLS; i++){
        for(j = 0; j<2; j++){
            ball[j][i] = 0;
        }
    }

    //this will receive the amount of balls the person wants to throw
    printf("How many balls you wish to throw? (1 to 5): ");
    scanf("%d", &inputB);
    while(inputB < 1 || inputB > 5){ //in case the person misclicked it
        printf("\nInvalid! The amount of balls has to be from 1 to 5: ");
        scanf("%d", &inputB);
    }


    for(i = 0; i<inputB; i++){
        ball[0][i] = 1;
        printf("How much money you put on Ball %d? (1.00 - %.2f) ", i+1, moneyCopy-inputB+i+1); //the amount is based on 'if the rest of the next balls could get at least 1'
        scanf("%f", &ballValue[i]);
        while(ballValue[i] < 1 || ballValue[i] > (moneyCopy-inputB+i+1)){
            printf("Invalid amount! It should be less than your remaining money and more than 1! (1.00 - %.2f)", moneyCopy-inputB+i+1); //nothing below 1$ and nothing above the limit
            scanf("%f", &ballValue[i]);
        }
        moneyCopy = moneyCopy - ballValue[i];

    }

    //this section makes the 'magic' of the game, it takes the ball and makes it either go left or right.
    for(j = 0; j< LAYERS; j++){
        for(i = 0; i<BALLS; i++){
            if(ball[0][i] == 1){
                ball[1][i] = ball[1][i] + randomizer();
            }
        }
        printf("\n");
    }

    //this part takes the value of the multipliers the balls fell on and apply to the value that each ball had
    for(i = 0; i<inputB; i++){
        multiplier(ball[1][i], &ballValue[i]);
        printf("Value of ball %d: %f\n", i+1, ballValue[i]);
        moneyCopy = moneyCopy + ballValue[i];
    }

    printf("Money before: %.2f, Money now: %.2f\n", money, moneyCopy);
    money = moneyCopy; //the money receives the copy now.

    return 0;
}
