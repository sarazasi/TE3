#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<sys/time.h>


#define N 3000
/*-----forが一番早そう？誤差-----*/
/*-----ポインタは配列の形で書かない方が早い-----*/

/*-----配列の中身を全表示-----*/
void show_data(int *x,int n){
  int i;
  for(i=0;i<n;i++){
    printf("%d ,",*(x+i));
  }
}

int main(void){
  struct timeval z,e;
  gettimeofday(&z,NULL);
  
  int *serch;
  int *prime;
  int i,j,flag;
  int n = sqrt(N);//Nの平方根
  int s = N-1;//要素数,size

  /*-----探索リスト,素数リストの領域確保,malloc,sizeof(int) = 4-----*/
  serch = (int *)malloc(4*N);
  prime = (int *)malloc(4*N);

  /*-----探索リストの作成-----*/
  for (i = 2; i <= N; i++)
  {
    *(serch+i-2)= i;
  }

  /*-----操作,Nの平方根回-----*/
  for (i = 0; i < n; i++)
  {
    /*-----先頭を素数リストへ-----*/
    *(prime+i) = *(serch);
    

    /*-----素数リストの最後尾の倍数を探索リストから削除,残りの要素数回-----*/
    flag = *(prime+i);
    
    for (j = 0; j <= s; j++)
    {
      if(*(serch+j) % flag == 0){
        memmove(serch+j,serch+j+1,s*4); //sizeof(int) = 4
        
        /*-----一個動かしたので要素数　-１-----*/
        s--;
      }
    }
  }
  /*-----serchの残りをprimeの末尾に追加-----*/
  memmove(prime+i,serch,s*4);
  
  
  /*-----出力-----*/
  show_data(prime,i+s);

  free(serch);
  free(prime);

  gettimeofday(&e,NULL);
  printf("time = %lf\n",(e.tv_sec - z.tv_sec)+(e.tv_usec-z.tv_usec)*1.0E-6);
 
  return 0;
}