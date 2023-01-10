#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main(){
    FILE * fr = fopen("input.txt","r");
    FILE * fw = fopen("out.txt","w");
    char op1[10],op2[10],op[10],dest[10],val[10][10],tmp[10][10];
    int i=0;
    while(!feof(fr)){
        fscanf(fr,"%s %s %s %s",op,op1,op2,dest);
        if(strcmp(op,"=")==0 && strcmp(op2,"-")==0){
            strcpy(val[i],op1);
            strcpy(tmp[i],dest);
            i++;
        }
    }
    fclose(fr);
    fr = fopen("input.txt","r");
    while(!feof(fr)){
        fscanf(fr,"%s %s %s %s",op,op1,op2,dest);
        if(strcmp(op,"=")==0 && strcmp(op2,"-")==0)
            continue;
        for(int j=0;j<i;j++){
            if(strcmp(op1,tmp[j])==0)
                strcpy(op1,val[j]);
            if(strcmp(op2,tmp[j])==0)
                strcpy(op2,val[j]);
        }
        fprintf(fw,"%s %s %s %s\n",op,op1,op2,dest);
    }
    fclose(fr);
    fclose(fw);
}