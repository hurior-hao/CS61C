#include <stdio.h>
#include <math.h>
int main(void){
    int angle_degree;
    double angle_radian,pi,value;

    printf("Compute a table of the sine function\n\n\n");
    pi = M_PI;
    printf("Value of PI is %f\n\n",pi);
    printf("Angle\tSine\n");
    angle_degree = 0;
    while (angle_degree <= 360){
        angle_radian = pi * angle_degree / 180.0;
        value = sin(angle_radian);
        printf("%3d\t%f\n",angle_degree,value);
        angle_degree += 10;
    }
    return 0;
}