#include <stdio.h>     
typedef struct round_key{
char b[48];
}keys;
    
void left_shift(char *c,char *d){
    char temp;
    temp=*c;
    for(int i=0;i<27;i++){
    *(c+i)=*(c+i+1);}
    *(c+27)=temp;
    
    temp=*d;
    for(int i=0;i<27;i++){
    *(d+i)=*(d+i+1);}
    *(d+27)=temp;}
    
    
void key_gen(char* a){
         int pc1[56] = {
        57, 49, 41, 33, 25, 17, 9,
        1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29,
        21, 13, 5, 28, 20, 12, 4
    };

    int pc2[48] = {
        14, 17, 11, 24, 1, 5,
        3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8,
        16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32
    };

        
     keys f[16];
     char c[28],d[28],e[56];
     
     for(int i=0;i<28;i++){
     c[i]=a[pc1[i]-1];
     d[i]=a[pc1[i+28]-1];}
     
     for(int j=0;j<16;j++){
     if(j==0 || j==1 || j==8 || j==15){
     left_shift(c,d);}
     else{
     left_shift(c,d);
     left_shift(c,d);}
     for(int k=0;k<28;k++){
     e[k]=c[k];
     e[28+k]=d[k];}
          
     printf("The round %d key is : ",j+1);
     for(int l=0;l<48;l++){
     f[j].b[l]=e[pc2[l]-1];
     printf("%c",f[j].b[l]);}
     printf("\n");
     }}
     
int main(){
     char a[]="0001001100110100010101110111100110011011101111001101111111110001";   
    
     key_gen(a);} 
     
     
     
     
    
    

