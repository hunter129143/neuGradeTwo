#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
    char start[30];
    char end[30];
    int distance;
    int cost;
}Edge;
char name[22][30];
int find(int father[],char* n){
    int t;
    for (int i = 0; i < 22; i++)
    {
        if (strcmp(name[i],n)==0)
        {
            t=i;
        }

    }
    while (father[t]>=0)
    {
        t = father[t];
    }



    return t;
}

void Kruskal(Edge edges[],int n){
   int father[54];
   int i,j,vf1,vf2;
   for (i = 0; i < n; i++)
   {
       father[i]=-1;
   }
   i=0;j=0;
   while (i<54&&j<n-1)
   {
       vf1=find(father,edges[i].start);
       vf2=find(father,edges[i].end);
       if (vf1!=vf2)
       {
           father[vf2] = vf1;
           j++;
           printf("%s %s %d\n",edges[i].start,edges[i].end,edges[i].distance);
       }
       i++;

   }

}

int cmp(const void * a, const void * b)
{
   return ( ((Edge*)a)->distance - ((Edge*)b)->distance );
}



int main(){
    Edge edges[54];
    int i=0;
    int count =0;
    int flag=0;
    freopen("C:\\Users\\29908\\OneDrive\\桌面\\实验数据\\services.txt","r",stdin);
    while(scanf("%s%s%d%d",&edges[i].start,&edges[i].end,&edges[i].cost,&edges[i].distance)!=EOF){
        if (count==0)
        {
            strcpy(name[count],edges[i].start);
            count++;
        }else if (strcmp(edges[i].start,name[count-1])!=0)
        {
            strcpy(name[count],edges[i].start);
            count++;
        }
        i++;
    }
    qsort(edges,54,sizeof(Edge),cmp);
    Kruskal(edges,22);

    for(count=0;count<53;count++){
        printf("%d",edges[count]);
    }
    }
