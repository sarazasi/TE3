#include<stdio.h>
#include<math.h>

#define func(x) 0.5 * (expo((x),6)-expo((x),3))
#define lim(x) func(1+x)/x 


double expo(double x,int n){
  double sum = x;
  while(--n){
    sum *= x;
  }

  return sum;
}

/*
double func(double dx){
  return (0.5 * pow(dx,6)) - (0.5 * pow(dx,3));
}

double bibun(double x){
  return func(1 + x)/x;
}
*/


int main(void){
  double dx;
  dx = 1.0;

  while(dx > pow(0.1,100)){
    //printf("f(x) = %.50lf\n",func(dx));
    printf("dx = %.50f\n",dx);
    //printf("f(a) = %.50f\n",bibun(dx));
    //printf("f(a) = %.50f\n",func(1+dx)/dx);
    printf("f(a) = %.50f\n",lim(dx));
    puts("------------------------------------------------");
    dx = dx / 2.0;
  }
  return 0;
}
