// #include <stdio.h>
// #define MAX(x,y) (x>y ? x : y)
// #define COMPARE(x, y) ((x < y) ? -1 : ((x == y) ? 0 : 1)) 
// #define MAX_DEGREE 101

// typedef struct {
//     int highestE;
//     int degree;
//     int size;
//     float coef[MAX_DEGREE];
// }polynomial;


// float Coef(polynomial c, int exp)
// {
//     return c.coef[c.highestE-exp];
// }

// void attach(polynomial d, float cof, int exp)
// {
//     d.coef[d.size++] = cof;
//     d.degree = MAX(d.degree,exp);
// }

// void Remove(polynomial c, int exp)
// {
//     c.coef[c.highestE-exp] = 0;
//     for(int i=0; i<=c.highestE; i++){
//         if(c.coef[i]!=0)
//             c.degree = c.highestE - i;
//     }
// }

// void padd(polynomial a, polynomial b,polynomial d)
// {
//     float sum = 0;
//     float cof;
//     while(a.degree>0 && b.degree>0){
//         switch COMPARE(a.degree,b.degree){
//             case -1:
//                 cof = Coef(a,a.degree);
//                 attach(d,Coef(b,b.degree),b.degree);
//                 Remove(b, b.degree);
//             case 0:
//                 sum = Coef(a,a.degree) + Coef(b,b.degree);
//                 if(sum){
//                     attach(d,sum,a.degree);
//                     Remove(a,a.degree);
//                     Remove(b,b.degree);
//                 }
//             case 1:
//                 cof = Coef(a,a.degree);
//                 attach(d,cof,a.degree);
//                 Remove(a,a.degree);
//         }
//     }
//     if(a.degree==0){
//         for(int i=0; i<b.size; i++){
//             if(b.coef[i]!=0){
//                 attach(d,b.coef[i],b.degree);
//                 Remove(b, b.degree);
//             }
//         }
//     }
//     else{
//         for(int i=0; i<a.size; i++){
//             if(a.coef[i]!=0){
//                 attach(d,a.coef[i],a.degree);
//                 Remove(a, a.degree);
//             }
//         }
//     }
// }

// int main(void)
// {
//     polynomial a,b,d;
//     float tempcof[MAX_DEGREE];
//     int tempexp[MAX_DEGREE];

//     for(int i=0; i<=MAX_DEGREE; i++){
//         a.coef[i] = 0;
//         b.coef[i] = 0;
//         tempcof[i] = 0;
//         tempexp[i] = 0;
//     }
//     a.degree = -1;
//     b.degree = -1;
//     scanf("%d %d", &a.size, &b.size);
//     for(int i=0; i<a.size; i++){
//         scanf("%f %d", &tempcof[i], &tempexp[i]);
//         a.degree = MAX(tempexp[i],a.degree);
//     }
//     a.highestE = a.degree;
//     for(int i=0; i<a.degree; i++){
//         if(tempcof[i])
//             a.coef[a.degree-tempexp[i]] = tempcof[i];
//     }

//     for(int i=0; i<=MAX_DEGREE; i++){
//         tempcof[i] = 0;
//         tempexp[i] = 0;
//     }

//     for(int i=0; i<b.size; i++){
//         scanf("%f %d", &tempcof[i], &tempexp[i]);
//         b.degree = MAX(tempexp[i],b.degree);
//     }
//     for(int i=0; i<b.degree; i++){
//         b.coef[b.degree-tempexp[i]] = tempcof[i];
//     }
//     b.highestE = b.degree;
//     d.size = 0;

//     d.degree = -1;

//     padd(a,b,d);

//     printf("%d", d.degree);
//     for(int i=0; i<d.size; i++){
//         printf("%f ", d.coef[i]);
//     }

//     return 0;
// }
#include <stdio.h>
#include <stdlib.h>

typedef struct poly{
   int degree;  //최고차항 지수 
   int *coef;   // 최고차항지수+1만큼 동적할당  -> 계 수 
}poly;

/*문자상수 -> 숫자 : 문자상수-'0'
문자열 ->정수 :atoi(문자열)*/ 
int first(char *p);
int cut(char *p,int pos,int* expo);
void add(poly a,poly b);

int main(int argc, char *argv[]) {
    struct poly p,q; 
    char str2[100];
    char str[100];
    int i=0,expo,temp;
    int cnt=0,j=0;
    
    
    
/*; printf(">> ");
 gets(str);   //2x^6-32x^5-4x^3+x-12*/
 printf("식 1 입력:");
 scanf("%s",str);
 
 printf("식 2 입력 :");
 scanf("%s",str2); 
 
 p.degree=first(str);
    q.degree=first(str2);
    
 printf("%s\n",str);
    printf("%s\n",str2);
    
    p.coef=(int*)calloc((p.degree+1), sizeof(int));
    q.coef=(int*)calloc((q.degree+1), sizeof(int));
    
 
 for(i=0;i<p.degree;i++){
      
   temp=cut(str, i, &expo);
 //printf("i=%d 차수: %d 위치 %d\n",i,expo,p.degree-expo); 
      p.coef[p.degree-expo]=temp;
      
    }
 
 
 for(i=0;i<q.degree;i++){
      
   temp=cut(str2, i, &expo);
      //printf("i=%d 차수: %d 위치 %d\n",i,expo,q.degree-expo); 
      q.coef[q.degree-expo]=temp;
      
    }
    
   
 printf("최고차항 지수 : %d\n", q.degree);
 printf("계수 : { ");  
 for(j=0;j<p.degree+1;j++){
  printf("%2d, ",p.coef[j]);
 }
 printf("}\n"); 
 
 add(p,q);
 
 return 0;
}
int first(char *p){
  
   int i=0;
    
   while(*p!='\0'){
   
      if(*p=='^'){
          return *(p+1)-'0';
       } 
   i++; p++;
    
 }
 
 return 1; 

}
int cut(char *p, int pos, int *expo){
 
  int i=0;
  int cnt=-1;
  char temp[10];
  
  while(*p!='\0'){
  
     if(pos==0){
        while(1){
          temp[i++]=*p;
          p++;
          if(*p=='x'){
            temp[i]='\0';
            (*expo)=*(p+2)-'0';
            return atoi(temp);
                        }
                             }   }
                             
     else {
      while(1){ 
    temp[i++]=*p;  p++;
     if(*p=='\0'){  temp[i]='\0';   //x가 없을떄 상수 자르 
                     (*expo)=0;
                      return atoi(temp);}
     if(*p=='x') break; 

                               }
    
   p++;
   
       if(*p=='^'){ cnt++;
                          }
                          
    if(cnt==pos){
     temp[i]='\0';
     (*expo)=*(p+1)-'0';
 
     return atoi(temp);
      }
      
    else if(*p!='^'){//x가 있을때 상수 자르기 
     
     if(*expo==1){
       i=0;
       while(1){ 
     temp[i++]=*p; p++;
     if(*p=='\0'){
        temp[i]='\0';
        (*expo)=0;
     return atoi(temp); }  }    }
     
     temp[i]='\0';
     (*expo)=1;
     return atoi(temp);
                                   }    
   
  
    p++; i=0;       //마지막의 제곱승 
   
      
                    
     }   
                             
  p++;
                                  }  }
                                  
 void add(poly a,poly b){
   
   poly c;
   int A_deg=a.degree;
   int B_deg=b.degree;
   int apos=0,bpos=0,cpos=0;
   int i,j;
   int temp=0;
   char aa[10];
   char str[100];
   
   if(a.degree>b.degree){
     c.degree=a.degree;
     c.coef=(int *)calloc((c.degree+1),sizeof(int));
     
  for(i=0;i<=b.degree;i++){
  c.coef[c.degree-i]=a.coef[a.degree-i]+b.coef[b.degree-i];
                   }
  
  for(i=b.degree+1;i<=a.degree;i++){
  c.coef[c.degree-i]=a.coef[a.degree-i];
  }
  
  for(i=0;i<c.degree+1;i++)
  printf(" %2d",c.coef[i]);   
     
   
                                          }   
  

   else if(a.degree==b.degree){
      c.degree=a.degree;
      c.coef=(int*)calloc((c.degree+1),sizeof(int));
      
            for(i=0;i<=a.degree+1;i++){
    c.coef[c.degree-i]=a.coef[a.degree-i]+b.coef[b.degree-i];
                      }
   
     for(i=0;i<c.degree+1;i++){
       printf(" %2d",c.coef[i]);
    
      }  

   }
   
      
   else if(a.degree<b.degree){
     
  c.degree=b.degree;
     c.coef=(int *)calloc((c.degree+1),sizeof(int));
        
        for(i=0;i<=a.degree;i++){
    c.coef[c.degree-i]=a.coef[a.degree-i]+b.coef[b.degree-i];
  }
  
  for(i=a.degree+1;i<=b.degree;i++){
    c.coef[c.degree-i]=b.coef[b.degree-i];
  }
  
     for(i=0;i<c.degree+1;i++)
   printf(" %2d",c.coef[i]);    
      }  
      
    strcpy(str,"\0");
  /* int num=-123;
   char str[10]
   itoa(num, str, 10); 
     itoa(정수형데이터, 문자배열, 10);*/
   
    for(i=0;i<c.degree-1;i++){
   if(c.coef[i]!=0){
       if(c.coef[i]>0) strcat(str,"+");
       itoa(c.coef[i],aa,10);
       strcat(str,aa);
    strcat(str,"x^");
    itoa(c.degree-i,aa,10);
    strcat(str,aa);  
   }    }
 
    if(c.coef[c.degree-1]!=0){
     if(c.coef[c.degree-1]>0) strcat(str,"+");
     itoa(c.coef[c.degree-1],aa,10);
     strcat(str,aa);
  strcat(str,"x");  }
 
    if(c.coef[c.degree]!=0){
  if(c.coef[c.degree]>0) strcat(str,"+");
     itoa(c.coef[c.degree],aa,10);
     strcat(str,aa);
 }
     
   printf("\n%s",str);
 }  

                           


