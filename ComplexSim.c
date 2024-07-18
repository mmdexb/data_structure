//
// Created by ChenYifan on 24-7-18.
//
#include <stdio.h>
typedef struct{
    float realpart; //实部
    float imagpart; //虚部
}Complex;

void assign(Complex *A,float real,float imag){
    A->realpart=real;
    A->imagpart=imag;
} //赋值

void add(Complex *C,Complex *A,Complex *B){
    C->realpart=A->realpart+B->realpart;
    C->imagpart=A->imagpart+B->realpart;

}

void main(){
    Complex A,B,C;
    assign(&A,1.0,2.0);
    assign(&B,3.0,4.0);
    add(&C,&A,&B);
    printf("A+B=%f+%fi\n",C.realpart,C.imagpart);
}


