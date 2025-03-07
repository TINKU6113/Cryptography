#include<stdio.h>
#include<string.h>

typedef struct words{
unsigned int a[4];}wrd;

unsigned int hash[5]={0x67452301,0xefcdab89,0x98badcfe,0x10325476,0xc3d2e1f0};
unsigned int keys[4]={0x5a827999,0x6ed9eba1,0x8f1bbcdc,0xca62c1d6};



void padding(wrd *c,int i,int j,int length){
if (i==1){
c->a[j]=128;}
else if(i==0){
c->a[j]=0;}
else if(i==2){
if(length>255){
c->a[j]=(length & 0xff00)>>8;}
else{c->a[j]=0;}}
else {
c->a[j]=(length & 0x00ff);}
}


unsigned int combine(wrd*z){//function for combining
unsigned int combine=0;
for(int i=0;i<4;i++){
combine |=(z->a[i] << (8 * (3 - i))); //to append the words in a single variable for doing one left shift
}
return combine;}


void extend(wrd*z,wrd*b,wrd*c,wrd*d,wrd*e){//to extend keys upto 80
unsigned int append=0;
for(int i=0;i<4;i++){
z->a[i]=b->a[i] ^ c->a[i] ^ d->a[i] ^ e->a[i];//xor for extending words
}
append=(combine(z))<<1;
for (int i=0;i<4;i++) {
        z->a[i] =(append>>(8*(3-i)))&0xFF;  // to store them again in previous way 
}}



int main(){
wrd w[80];
char str[56];
printf("enter the string less than 56 characters");
fgets(str,56,stdin);

int l=strlen(str);
if (str[l - 1] == '\n') {
    str[l - 1] = '\0';
    l--;
    }
    printf("%d",l);
int i,j=0,k=0;

while(k<l){
for (i=0;i<4;i++){
w[j].a[i]=(int)str[k];
k++;}
j++;}
i=l/4;
j=l%4;
l=l*8;

//padding 1
padding(&w[i],1,j,l);
j=j+1;
//padding zeros upto 448 bit for padding zeros
for(i=i;i<15;i++){
for(j=j;j<4;j++){
padding(&w[i],0,j,l);}
j=0;
} 
padding(&w[15],0,0,l);
// padding the lenght of the string given as 64 bit representation
for(j=1;j<2;j++){
padding(&w[15],0,j,l);}
for(j=2;j<4;j++){
padding(&w[15],j,j,l);}


for(i=0;i<16;i++){
for(j=0;j<4;j++){
 printf("%d %x \n ",w[i].a[j],w[i].a[j]);}}

// to extend the keys till 80 words
 
 for(i=16;i<80;i++){
 extend(&w[i],&w[i-3],&w[i-8],&w[i-14],&w[i-16]);}
 
 

for(i=0;i<80;i++){
for(j=0;j<4;j++){
printf("%d %x \n",w[i].a[j],w[i].a[j]);}}
 unsigned int A,B,C,D,E,T,F,K;
 A=hash[0];
 B=hash[1];
 C=hash[2];
 D=hash[3];
 E=hash[4];
 
 for(i=0;i<80;i++){
 if(i>=0 & i<20){
 F=(B&C)|((~B)&D);
 K=keys[0];}
 
 if(i>=20 & i<40){
 F=(B^C^D);
 K=keys[1];}
 
 if(i>=40 & i<60){
 F=(B&C)|(B&D)|(C&D);
 K=keys[2];}
 
 if(i>=60 & i<80){
 F=(B^C^D);
 K=keys[0];}
 
 T=(A<<5)+F+E+K+combine(&w[i]);
 E=D;
 D=C;
 C=B<<30;
 B=A;
 A=T;}
 
 
printf("\n%x\n%x\n%x\n%x\n%x\n",(A+hash[0]),(B+hash[1]),(C+hash[2]),(D+hash[3]),(E+hash[4]));
//printf("\n%x\n",combine(&w[0])); to check working of combine funxtion


}


