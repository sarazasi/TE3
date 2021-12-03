#include<stdio.h>

#define DX 0.000000000931322574615478515625
#define func(x) (expo((x),5)-(expo((x),2)/2))*3

double expo(double x,double n){
	double sum=1.0;
	while(n--){
		sum = sum*x;
	}
	return sum;
}

int main(void){
  double k,sum=0;

  for(k=0.0; k<=1;k+=DX){
    sum += ((func(k)+func(k+DX))*DX) /2;
		//printf("\r%.50f",sum);
  }
	printf("%.25f\n",sum);
	return 0;
}