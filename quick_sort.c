#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>

#define N 40//全体数
#define swap(x,y,type) do{type t; t = x; x = y; y = t;}while(0)

void quick_sort(int *,int,int);

int main(void){
  struct timeval s,e;
  int i,j;
  int a[N];

  srand(time(NULL));

  for(i = 0;i<N;i++){ //値の代入
    a[i] = rand() % 1000; //0~999の乱数
    printf("%d ",a[i]);
  }
  putchar('\n');

  gettimeofday(&s,NULL);
  quick_sort(a,0,N-1);
  gettimeofday(&e,NULL);

  puts("ソート後");
  for(i = 0;i<N;i++){
    printf("%d ",a[i]);
  }
  putchar('\n');

  printf("計測時間 : %lf\n",(e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec)*1.0E-6);

  return 0;
}

//基準点は左端から見ていって左端より小さい数があったら左端, 左端より大きい数があったらその数, どちらもなかったらソート終了
// num...ソートする対象, s ~ eの要素で分割
void quick_sort(int *num,int s,int e){
  int i = s;
  int j = e;
  int x; //デバッグ用
  int p; //基準点
  int flag = 1; //ソート終了判定

  while(flag == 1){

    //基準点を決定
    int n = 1;
    p = num[i];
    while(1){
      puts("a");
      fflush(stdout);

      if(i + n > j){ //値が全部同じ
        flag = 0; //終了
        break;
      }

      if(p > num[i + n]){ //小さい数があったら
        break;
      }else if(p < num[i + n]){ //大きい数があったら
        p = num[i + n];
        break;
      }
      n++;
    }
    

    while(flag == 1){ //基準点以上の値を探索
      puts("k");
      fflush(stdout);

      if(num[i] >= p){
        break;
      }
      if(i == e){ //num[i]が最大の値の時
        quick_sort(num,s,e-1); //最大の値を除外して判定
        flag = 0; //終了
      }
      i++;
    }
    

    while(flag == 1){ //基準点未満の値を探索
      puts("c");
      fflush(stdout);
      
      if(num[j] < p){
        swap(num[i],num[j],int);
        
        puts("--------------------------------------------------------------");
        for(x = 0;x<N;x++){
          printf("%d ",num[x]);
        }
        fflush(stdout);
        putchar('\n');

        break;
      }
      if(j == i){
        if(j == s){ //num[j]が最小の時
          quick_sort(num,s+1,e); // 最小の値を除外して判定
          flag = 0;
          break;
        }
        quick_sort(num,s,j-1); //分割した小さいほうの値を判定
        j = e; //大きいほうを判定するためにjを末尾に持っていく
        break;
      }
      j--;
    }
  }
}