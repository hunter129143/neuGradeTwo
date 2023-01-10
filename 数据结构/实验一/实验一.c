#include <stdio.h>
#include <stdlib.h>

typedef struct Polynomial
{
    float coef;
    int expn;
    struct Polynomial *next;

}Polynomial,*Poly;

Poly Create_Poly(){
    Polynomial *head,*tail,*s;
    int c,e;
    head=(Poly)malloc(sizeof(Polynomial));
    tail=head;
    scanf("%d,%d",&c,&e);
    while(c!=0){
        s=(Poly)malloc(sizeof(Polynomial));
        s->coef=c;
        s->expn=e;
        tail->next=s;
        tail=s;
        scanf("%d,%d",&c,&e);
    }
    tail->next=NULL;
    return head;
}

void Print_Poly(Polynomial *head){
Poly q=head->next;
int flag=1;
if(!q){
    putchar('0');
    printf("\n");
    return ;
}
while(q){
    if(q->coef>0&&flag!=1){
        putchar('+');
    }
    if(q->coef!=1&&q->coef!=-1){
        printf("%g",q->coef);
        if(q->expn==1)putchar('x');
        else if (q->expn)printf("x^%d",q->expn);
    }
    else{
        if(q->coef==1){
            if(!q->expn)putchar('1');
            else if (q->expn==1)putchar('x');
            else printf("x^%d",q->expn);
        }
         if(q->coef==-1){
            if(!q->expn)putchar('-1');
            else if (q->expn==1)putchar('-x');
            else printf("-x^%d",q->expn);
    }
}
q=q->next;
flag++;
}
printf("\n");
}


Poly Add_Poly(Polynomial *pa,Polynomial *pb){
    Poly qa=pa->next;
    Poly qb=pb->next;
    Poly headc,pc,qc;
    pc=(Poly)malloc(sizeof(Polynomial));
    pc->next=NULL;
    headc=pc;
    while(qa!=NULL&&qb!=NULL){
        qc=(Poly)malloc(sizeof(Polynomial));
        if(qa->expn<qb->expn){
            qc->coef=qa->coef;
            qc->expn=qa->expn;
            qa=qa->next;
        }
        else if(qa->expn==qb->expn){
            qc->coef=qa->coef+qb->coef;
            qc->expn=qa->expn;
            qa=qa->next;
            qb=qb->next;

        }
        else {
            qc->coef=qb->coef;
            qc->expn=qb->expn;
            qb=qb->next;
        }
        if(qc->coef!=0){
            qc->next=pc->next;
            pc->next=qc;
            pc=qc;
        }
        else free(qc);
    }
    while(qa!=NULL){
        qc=(Poly)malloc(sizeof(Polynomial));
        qc->coef=qa->coef;
        qc->expn=qa->expn;
        qa=qa->next;
        qc->next=pc->next;
        pc->next=qc;
        pc=qc;
    }
    while(qb!=NULL){
        qc=(Poly)malloc(sizeof(Polynomial));
        qc->coef=qb->coef;
        qc->expn=qb->expn;
        qb=qb->next;
        qc->next=pc->next;
        pc->next=qc;
        pc=qc;
    }
    return headc;
}




int main(){
Polynomial *pa,*pb,*pc,*pd;
printf("请输入第一个多项式： 通过按0结束");
pa=Create_Poly();
printf(" pa = ");
Print_Poly(pa);
printf("请输入第二个多项式： 通过按0结束");
pb=Create_Poly();
printf(" pb = ");
Print_Poly(pb);
printf("多项式相加结果为：");
printf("pa+pb = ");
pc=Add_Poly(pa,pb);
Print_Poly(pc);
return 0;


}
