#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>

#define N 20000//全体数
#define swap(x,y,type) do{type t; t = x; x = y; y = t;}while(0)

void quick_sort(int *,int);

typedef struct Store{
  int *store;
  int number; 
}store;

int main(void){
  struct timeval s,e;
  int i,j;
  int a[N];
  //int test[N] = {3,2,0,5,2,3,4,1,3,8};

  srand(time(NULL));

  for(i = 0;i<N;i++){ //値の代入
    a[i] = rand() % 1000; //0~999の乱数
    //a[i] = test[i];
    printf("%d ",a[i]);
  }
  putchar('\n');

  gettimeofday(&s,NULL);
  quick_sort(a,N-1);
  gettimeofday(&e,NULL);

  puts("ソート後");
  for(i = 0;i<N;i++){
    printf("%d ",a[i]);
  }
  putchar('\n');

  printf("計測時間 : %lf\n",(e.tv_sec - s.tv_sec) + (e.tv_usec - s.tv_usec)*1.0E-6);

  return 0;
}

//基準点の決め方
//一番左の値より大きい値を探す
// num...ソートする対象, s ~ eの要素で分割
void quick_sort(int *num,int e){
  int i,j;
  int l,r; //分割する配列の要素数
  store *small,*large,temp;
  int pivot;
  int flag;
  int s_num = 0; //smallの添え字
  int l_num = 0; //largeの添え字
  int n = 0; //numの添え字
  int sma,lar;
  int max; //各配列の要素数

  //領域の確保
  small = (store *)malloc(sizeof(store) * e);
  large = (store *)malloc(sizeof(store) * e);

  //基準点を決める　最小の値はだめ
  i = 1;
  while(1){
    if(num[0] > num[i]){
      pivot = num[0];
      break;
    }
    if(num[0] < num[i]){
      pivot = num[i];
      break;
    }
    i++;
  }
  printf("%d\n",pivot);

  //基準点で分割する
  l = 0;
  r = 1;
  flag = 1;
  while(flag == 1){
    while(flag == 1){ //左から基準点以上を探索
      if(l == (e - (r-1))){
        flag = 0;
        break;
      }
      if(num[l] >= pivot){
        break;
      }
      l++;
    }
    while(flag == 1){ //右から基準点未満を探索
      if(l == (e - (r-1))){
        flag = 0;
        break;
      }
      if(num[e - (r-1)] < pivot){
        swap(num[l],num[e - (r-1)],int);
        break;
      }
      r++;
    }
  }

  //分割したものを配列に入れる
  //領域を確保
  small[s_num].store = (int *)malloc(sizeof(int) * l);
  large[l_num].store = (int *)malloc(sizeof(int) * r);

  //要素数
  //printf("l : %d\nr : %d\n",l,r);
  small[s_num].number = l-1;
  large[l_num].number = r-1;

  //基準点より下の値
  for(i = 0;i<l;i++){
    small[s_num].store[i] = num[i];
    
    //printf("small[%d] : %d ",i,small[s_num].store[i]);
    //fflush(stdout);
  }
  //putchar('\n');
  
  //基準点以上の値
  for(j = 0;j<r;j++){
    large[l_num].store[j] = num[j+l];
    
    //printf("large[%d] : %d ",j,large[s_num].store[j]);
    //fflush(stdout);
  }
  //putchar('\n');
  //-------------numを分割完了-------------------------
  
  //smallの方から見る
  sma = 1;
  lar = 0;
  
  while(n <= e){ //numの値が全部決定するまで
    if(sma == 1){ //smallの方を見る-------------------------------------
      //要素が一個しかなかったら確定なのでnumに入れてlargeを見る
      if(small[s_num].number == 0){
        num[n] = small[s_num].store[0];
        n++;
        free(small[s_num].store);
        sma = 0,lar = 1;
        //printf("n : %d\n",n);
        s_num--;
        continue;
      }

      max = small[s_num].number; //maxを更新

      //基準点を決める　最小の値はだめ
      i = 1;
      while(1){
        if(i == small[s_num].number + 1){ //値がぜんぶ一緒
          flag = 1;
          break;
        }

        if(small[s_num].store[0] > small[s_num].store[i]){
          
          pivot = small[s_num].store[0];
          break;
        }
        if(small[s_num].store[0] < small[s_num].store[i]){
          
          pivot = small[s_num].store[i];
          break;
        }
        i++;
      }
      if(flag == 1){
        for(j = 0;j<i;j++){
          num[n] = small[s_num].store[j];
          n++;
        }
        free(small[s_num].store);
        sma = 0;lar = 1;
        s_num--;
        flag = 0;
        continue;
      }

      //printf("%d\n",pivot);
      //fflush(stdout);

      //基準点で分割する
      l = 0;
      r = 1;
      flag = 1;
      while(flag == 1){
        while(flag == 1){ //左から基準点以上を探索
          if(l == (max - (r-1))){
            flag = 0;
            break;
          }
          if(small[s_num].store[l] >= pivot){
            break;
          }
          l++;
        }
        while(flag == 1){ //右から基準点未満を探索
          if(l == (max - (r-1))){
            flag = 0;
            break;
          }
          if(small[s_num].store[max - (r-1)] < pivot){
            swap(small[s_num].store[l],small[s_num].store[max - (r-1)],int);
            break;
          }
          r++;
        }
      }
      //printf("l : %d\nr : %d\n",l,r);
      //fflush(stdout);

      //分割したものを配列に入れる
      //領域を確保
      l_num++,s_num++;

      //printf("l_num : %d s_num : %d\n",l_num,s_num);
      //fflush(stdout);

      small[s_num].store = (int *)malloc(sizeof(int) * l);
      large[l_num].store = (int *)malloc(sizeof(int) * r);

      
      //要素数
      small[s_num].number = l-1;
      large[l_num].number = r-1;

      //基準点より下の値
      //puts("sma");
      //fflush(stdout);
      for(i = 0;i<l;i++){
        small[s_num].store[i] = small[s_num-1].store[i];
        //printf("small[%d] : %d ",i,small[s_num].store[i]);
        //fflush(stdout);
      }
      //putchar('\n');

      //基準点以上の値
      for(j = 0;j<r;j++){
        large[l_num].store[j] = small[s_num-1].store[j+l];
        //rintf("large[%d] : %d ",j,large[l_num].store[j]);
        //fflush(stdout);
      }
      //putchar('\n');

      free(small[s_num-1].store); //一個前のsmallを解放
    }

    if(lar == 1){ //largeの方を見る-------------------------------------------------------------
      if(large[l_num].number == 0){ //要素が一個しかなかったらnumに入れて一個前のlargeを見る
        num[n] = large[l_num].store[0];
        n++;
        //printf("l_num[%d] : %d\nn : %d\n",l_num,large[l_num].store[0],n);
        free(large[l_num].store);
        l_num--;
        continue;
      }

      max = large[l_num].number; //maxを更新

      //printf("max : %d\n",max);
      //fflush(stdout);

      //基準点を決める　最小の値はだめ
      i = 1;
      while(1){
        if(i == large[l_num].number + 1){ //値がぜんぶ一緒
          flag = 1;
          break;
        }
        if(large[l_num].store[0] > large[l_num].store[i]){
          pivot = large[l_num].store[0];
          break;
        }
        if(large[l_num].store[0] < large[l_num].store[i]){
          pivot = large[l_num].store[i];
          break;
        }
        i++;
      }
      if(flag == 1){
        for(j = 0;j<i;j++){
          num[n] = large[l_num].store[j];
          n++;
        }
        free(large[l_num].store);
        l_num--;
        flag = 0;
        continue;
      }

      //printf("pivot : %d\n",pivot);
      //fflush(stdout);
      
      //基準点で分割する
      l = 0;
      r = 1;
      flag = 1;
      while(flag == 1){
        while(flag == 1){ //左から基準点以上を探索
          if(l == (max - (r-1))){
            flag = 0;
            break;
          }
          if(large[l_num].store[l] >= pivot){
            break;
          }
          l++;
        }
        while(flag == 1){ //右から基準点未満を探索
          if(l == (max - (r-1))){
            flag = 0;
            break;
          }
          if(large[l_num].store[max - (r-1)] < pivot){
            swap(large[l_num].store[l],large[l_num].store[max - (r-1)],int);
            break;
          }
          r++;
        }
      }

      //分割したものを配列に入れる
      //領域を確保
      s_num++;

      //printf("l_num : %d s_num : %d\n",l_num,s_num);
      //fflush(stdout);

      small[s_num].store = (int *)malloc(sizeof(int) * l);
      //large[l_num].store = (int *)malloc(sizeof(int) * r);
      temp.store = (int *)malloc(sizeof(int) * r);

      //要素数
      small[s_num].number = l-1;
      temp.number = r-1;

      //基準点より下の値
      
      for(i = 0;i<l;i++){
        small[s_num].store[i] = large[l_num].store[i];
        
        //printf("small[%d] : %d ",i,small[s_num].store[i]);
        //fflush(stdout);
      }
      //putchar('\n');

      //基準点以上の値
      for(j = 0;j<r;j++){
        temp.store[j] = large[l_num].store[j+l];
        //printf("large[%d] : %d ",j,large[l_num].store[j]);
        //fflush(stdout);
      }
      //putchar('\n');
      
      free(large[l_num].store);

      //tempをlargeに入れる
      large[l_num].store = (int *)malloc(sizeof(int) * r);
      
      large[l_num].number = temp.number;
      for(i = 0;i<r;i++){
        large[l_num].store[i] = temp.store[i];

        //printf("large[%d] : %d ",j,large[l_num].store[i]);
        //fflush(stdout);
      }
      //putchar('\n');

      free(temp.store);

      sma = 1,lar = 0;//smallの方見る
      //puts("end");
      //fflush(stdout);
    }
  }

  free(small);
  free(large);
}