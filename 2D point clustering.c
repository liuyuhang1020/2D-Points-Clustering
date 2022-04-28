#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define size 182807

int father[size],rank[size];
int map[2500][2500]={{0,},};
int point[size][2];
int ring[76][2];

//并查集初始化操作
void Initial_Union_Find_Set(int n)
{
    int i;
    for(i=1;i<n;++i)
    {
        father[i]=i;
        rank[i]=1;                           
    }
}

//查找根节点并压缩路径
int Find_Root_Node(int node)
{
    if (father[node]!=node)
    {
        father[node]=Find_Root_Node(father[node]);
    }                                           
    return father[node];                                                                                                        
}

//合并并查集并压缩路径
int  Ally_Union_Find_Set(int p,int q)
{
    int root1=Find_Root_Node(p);
    int root2=Find_Root_Node(q);
    if(root1==root2)
    {
        return 0;                 
    }
    if(rank[root1]>rank[root2])
    {
        father[root2]=root1;                                  
        rank[root1]+=rank[root2];
    }
    else
    {
        father[root1]=root2;
        rank[root2]+=rank[root1];
    }
    return 1;
}

int Read_CSV(char* path,int(*array)[2],int n)
{
    FILE *fp=fopen(path,"r");
    if(!fp)
    {
        return 0;
    }
    char *token;
    char line[100];
    for(int i=0;i<n;i++)
    {
        fgets(line,100,fp);
        token=strtok(line, ",");
        array[i][0]=atoi(token);
        token=strtok(NULL,",");
        token=strtok(token,"\n");
        array[i][1]=atoi(token);
    }
    fclose(fp);
    return 1;
}

int Write_CSV(char* path,int* array,int n)
{
    FILE *fp=fopen(path,"w");
    if(!fp)
    {
        return 0;
    }
    for(int i=0;i<n;i++)
    {
        fprintf(fp,"%d,%d\n",i,array[i]);
    }
    fclose(fp);
    return 1;
}

int main()
{
    char* point_path="C:\\Users\\86191\\Desktop\\point.csv";
    Read_CSV(point_path,point,size);
    char* ring_path="C:\\Users\\86191\\Desktop\\ring.csv";
    Read_CSV(ring_path,ring,76);
    Initial_Union_Find_Set(size);
    int x0,y0,x,y;
    int i,r,p;
    for(i=1;i<=size;i++)
    {
        x0=point[i-1][0];
        y0=point[i-1][1];
        //该for循环为生成圆环的过程，固定循环76次，不影响时间复杂度
        for(r=0;r<76;r++)
        {
            x=x0+ring[r][0];
            y=y0+ring[r][1];
            if(x>=0&&x<=2499&&y>=0&&y<=2499)
            {
                p=map[x][y];
                if(p==0)
                {
                    map[x][y]=i;
                }
                else
                {
                    Ally_Union_Find_Set(i-1,p-1);
                }
            }
        }
    }
    for(i=0;i<size;i++)
    {
        father[i]=Find_Root_Node(i);
    }
    char* result_path="C:\\Users\\86191\\Desktop\\result.csv";
    Write_CSV(result_path,father,size);
    return 0;
}