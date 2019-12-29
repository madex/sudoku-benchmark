#include <stdio.h>
#define _ 0
#define S(x) x,
#define D(x) x x x
#define L(x) D(S(x))
#define R(x) D(D(S(x)))
#define E(f,x) f(x)f(x+1)f(x+2)
char sudoku[] = { 
  1, _, _,  _, _, 7,  _, 9, _,
  _, 3, _,  _, 2, _,  _, _, 8,
  _, _, 9,  6, _, _,  5, _, _, 

  _, _, 5,  3, _, _,  9, _, _,
  _, 1, _,  _, 8, _,  _, _, 2,
  6, _, _,  _, _, 4,  _, _, _,

  3, _, _,  _, _, _,  _, 1, _, 
  _, 4, _,  _, _, _,  _, _, 7,
  _, _, 7,  _, _, _,  3, _, _,
};
char c[]={E(R,0)E(R,3)E(R,6)},q[]={D(D(E(S,0)E(S,3)E(S,6)))},w[]={D(E(L,0))
D(E(L,3))D(E(L,6))};v(char *b, char *r){int l[]={R(0)0},i=82,f,s;for(;--i;l[s]
|=1<<f){f=*b++;s=*r++;if(f&&s<9&&l[s]&(1<<f))return 0;}return 1;}h(char *b,char
**r){char *o;while(o=*r++)if(!v(b,o))return 0;return 1;}t(char n,char *b,char 
**r){char i=1;while(1){if(n>80)return 1;if(!b[n])break;n++;}for(;i<10;i++){
b[n]=i;if(h(b,r))if(t(n+1,b,r))return 1;}b[n]=0;return 0;}p(char*b){char j=0,l=
0,i=82;for(;--i;){printf(" %d",*b++);if((j%3)==2)printf(" ");if(++j==9){if((
l++%3)==2)puts("");j=0;puts("");}}}main(){char *b=sudoku,*r[]={q,c,w,0};p(b);
if(t(0,b,r)){puts("solution:");p(b);}else puts("no solition found");return 0;}
// by Martin Ongsiek