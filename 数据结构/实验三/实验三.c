#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node{ //树的结点
	char* name;
    int num;
	struct node* left;
	struct node* right;
} Node;
typedef struct { //树根
	Node* root;
} Tree;
Node* newNode(char* name,int quantity)//创建树
{
    Node* node=(Node*)malloc(sizeof(Node));//创建一个节点
    node->name = name;
    node->num = quantity;
    node->left = NULL;
    node->right = NULL;
    return node;

}



Node* findParent(Node* t,Node* p){
	if(t == NULL || p ==NULL) return NULL;
	Node* q = t->left;
	Node* s;
	//循长子的兄弟链，递归在子树中搜索
	while(q != NULL&&((strcmp(q->name,p->name)!=0)) ){

            if((s = findParent(q,p)) != NULL) return s; //找到双亲，返回
            q = q->right;
	}
	if(q != NULL){
        if (strcmp(q->name,p->name)==0)
        {
            return t; //找到双亲
        }


    }
	else return NULL; //未找到
}

int main(){
    Tree tree;
    tree.root = NULL;
    Node* temp;
    char str[17][3][30];
    FILE* fp = NULL;
    char* filename = "C:\\Users\\29908\\OneDrive\\桌面\\实验数据\\definitions.txt";
     if((fp = fopen(filename,"r")) == NULL) //判断文件是否存在及可读
    {
        printf("error!");

    }
    int count = 0;
    while(!feof(fp)){
        for (int i = 0; i < 3; i++)
        {
            fscanf(fp, "%s", str[count][i]);
        }
        count++;
    }

    Node* nodes[20];
    int numbers[20]={0};
    int nodecount = 0;
    tree.root = newNode(str[0][0],1);
    nodes[nodecount++] = tree.root;
    temp = tree.root;
    for (int i = 0; i < count; i++)
    {
        nodes[nodecount++] = newNode(str[i][2],atoi(str[i][1]));
    }
    for (int i = 0; i < count; i++){
        for(int j=0;j<nodecount;j++){
            if(strcmp(nodes[j]->name,str[i][0])==0){
                for(int k=0;k<nodecount;k++){
                    if(strcmp(nodes[k]->name,str[i][2])==0){
                        // numbers[k] = nodes[k]->num*nodes[j]->num;//
                        if(nodes[j]->left == NULL){
                            nodes[j]->left = nodes[k];
                        }else{
                            Node* p = nodes[j]->left;
                            while(p->right!=NULL){
                                p = p->right;
                            }
                            p->right = nodes[k];
                        }
                    }
                }
            }
        }
    }
    char query[13][3][30];
    filename = "C:\\Users\\29908\\OneDrive\\桌面\\实验数据\\queries.txt";
     if((fp = fopen(filename,"r")) == NULL) //判断文件是否存在及可读
    {
        printf("error!");

    }
    char temp1[30],temp2[30];
    while(!feof(fp)){
        fscanf(fp, "%s", temp1);
        if (strcmp(temp1,"whatis")==0)
        {
            fscanf(fp, "%s", temp1);
            for (int j = 0; j < nodecount; j++)
            {
                if(strcmp(nodes[j]->name,temp1)==0){
                    printf("Part %s subparts are:\n",temp1);
                    if (nodes[j]->left!=NULL)
                    {
                        Node* p = nodes[j]->left;
                        printf("%d %s\n",p->num,p->name);
                        while (p->right!=NULL)
                        {
                            p = p->right;
                            printf("%d %s\n",p->num,p->name);
                        }
                    }
                }
            }
        }
        if (strcmp(temp1,"howmany")==0)
        {
            fscanf(fp, "%s", temp1);
            fscanf(fp, "%s", temp2);
            Node* p1;
            int num=0;
            for (int i = 0; i < nodecount; i++)
            {
                if (strcmp(nodes[i]->name,temp1)==0)
                {
                    p1 = nodes[i];
                }

            }
            // printf("%s",p1->name);
            Node *t = p1;
            // printf("%s",t);
            while(strcmp(t->name,temp2) != 0){
                if(num==0)
                    num=t->num;
                else
                    num*=t->num;
                    t = findParent(tree.root,t);
                    if(t==NULL){
                    break;
                    }
            }

            printf("%s has %d %s\n",temp2,num,temp1);

        }
    }




    return 0;
}
