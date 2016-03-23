//

//  main.cpp

//  Graph

//

//  Created by 麦小明 on 15/6/9.

//  Copyright (c) 2015年 麦小明. All rights reserved.

//


#include <iostream>

#define MaxInt 999
#define MVNum 100
#define OK 1
#define ERROR 0

using namespace std;

/******  邻接矩阵  ******/  //  事先已经分配好了固定的空间，等待填充
typedef struct {
    char vexs[MVNum];     // 顶点表
    int arcs[MVNum][MVNum]; //邻接矩阵
    int vexnum,arcnum;     //点数和边数
}AMGraph;


/*******  邻接表  *******/
typedef struct ArcNode{          //边表
    int adjvex;
    struct ArcNode *nextarc;
    int info;
}ArcNode;

typedef struct VNode{         //顶点表
    char data;
    ArcNode *firstacr;
}VNode,AdjList[MVNum];

typedef struct {
    AdjList vertices;        //结构体数组
    int vexnum,arcnum;       //顶点数、边数
}ALGraph;


/***** 普里姆算法 辅助数组  *****/
typedef  struct closedge1{
    char adjvex;
    int lowcost;
}closedge1,closedge2[MVNum];

int LocateVex_ALG(ALGraph G,int v)
{
    int i=0;
    while(v!= G.vertices[i].data)
        i++;
    
    return i;
}


//普里姆算法 辅助数组
typedef  struct closedge{
    char adjvex;
    int lowcost;
}closedge,closedge_a[MVNum];



/*根据数组名定位下标*/
int LocateVex_AMG(AMGraph G , char v){
    int i=0;
    while (v != G.vexs[i])
    {
        i++;
    }
    return i;
}


/*创建邻接矩阵、无向图*/
int CreateUDN(AMGraph &G , int mode)
{
    if(mode == 1)   //使用已有无向图
    {
        G.vexnum = 5;
        G.arcnum = 6;
       
        G.vexs[0] = 'a';
        G.vexs[1] = 'b';
        G.vexs[2] = 'c';
        G.vexs[3] = 'd';
        G.vexs[4] = 'e';
        
        G.arcs[0][0] = MaxInt;
        G.arcs[0][1] = 1;
        G.arcs[0][2] = MaxInt;
        G.arcs[0][3] = 6;
        G.arcs[0][4] = MaxInt;
        
        G.arcs[1][0] = 1;
        G.arcs[1][1] = MaxInt;
        G.arcs[1][2] = 2;
        G.arcs[1][3] = MaxInt;
        G.arcs[1][4] = 9;
        
        G.arcs[2][0] = MaxInt;
        G.arcs[2][1] = 2;
        G.arcs[2][2] = MaxInt;
        G.arcs[2][3] = 3;
        G.arcs[2][4] = 7;
        
        G.arcs[3][0] = 6;
        G.arcs[3][1] = MaxInt;
        G.arcs[3][2] = 3;
        G.arcs[3][3] = MaxInt;
        G.arcs[3][4] = MaxInt;
        
        G.arcs[4][0] = MaxInt;
        G.arcs[4][1] = 9;
        G.arcs[4][2] = 7;
        G.arcs[4][3] = MaxInt;
        G.arcs[4][4] = MaxInt;
        
    }
    else
    {
        /*输入顶点数和边数*/
        cout<<"请输入点数和边数";
        cin>>G.vexnum>>G.arcnum;
        
        /*创建顶点表*/
        for (int i = 0; i < G.vexnum; i++){
            cout<<"请输入顶点";
            cin>>G.vexs[i];
        }
        
        /*创建邻接矩阵*/
        for (int i=0; i<G.vexnum; i++)
            for (int j=0; j<G.vexnum; j++)
            {
                G.arcs[i][j]=MaxInt;   //默认边与边之间的距离无穷大
            }
        
        /*填充邻接矩阵，共有arcnum（边数）*2 个元素*/
        for (int k=0; k < G.arcnum; k++)   //循环arcnum次
        {
            char v1,v2;
            int w;
            
            cout<<"请输入第"<<k+1<<"条边的两个点和权值w";
            cin>>v1>>v2>>w;
            
            int i=LocateVex_AMG(G,v1);
            int j=LocateVex_AMG(G,v2);
            
            G.arcs[i][j] = w;
            G.arcs[j][i]= G.arcs[i][j];   //对称点也要填充
        }
    }
    return OK;

}



int CreateUDG(ALGraph &G){        //创建邻接表
    cout<<"请输入点数和边数";
    cin>>G.vexnum>>G.arcnum;
    
    for (int i=0; i<G.vexnum; i++) {
        cout<<"请输入第"<<i+1<<"个点的data";
        cin>>G.vertices[i].data;    //输入每个顶点的名称，eg.a,b,c
        G.vertices[i].firstacr=NULL;
    }
    
    for (int k=0; k<G.arcnum; ++k) {
        
        char v1,v2;
        
        int i,j;
        
        ArcNode *p1,*p2;
        
        cout<<"请输入第"<<k+1<<"条边的两个点";
        
        cin>>v1>>v2;
        
        i=LocateVex_ALG(G,v1);
        
        j=LocateVex_ALG(G,v2);
        
        p1=new ArcNode;
        
        p1->adjvex=j;
        
        p1->nextarc=G.vertices[i].firstacr;
        
        G.vertices[i].firstacr=p1;
        
        p2=new ArcNode;
        
        p2->adjvex=i;
        
        p2->nextarc=G.vertices[j].firstacr;
        
        G.vertices[j].firstacr=p2;// 将p1改成p2 2015.6.12 0：40
        
    }
    
    
    
    return OK;
    
}



void CHECK(ALGraph G){
    
    char d;
    
    int i;
    
    for (int j=0; j<G.vexnum; j++) {
        
        cout<<"输入要check的data";
        
        cin>>d;
        
        i=LocateVex_ALG(G,d);
        
        cout<<"data的adjvex为"<<i;
        
    }
    
}


void Print_AMG(AMGraph G){
    
    for (int k=0; k<G.vexnum; k++)
        
        cout<<G.vexs[k];
    
    for (int i=0; i<G.vexnum; i++){
        
        cout<<endl;
        
        for (int j=0; j<G.vexnum; j++)
            
            cout<<G.arcs[i][j]<<" ";
        
    }
    
    
    
}



void Print_ALG(ALGraph G){
    
    for (int i=0 ; i<G.vexnum; i++) {
        
        cout<<i;
        
        cout<<G.vertices[i].data;
        
        ArcNode *p;
        
        p=new ArcNode;
        
        p=G.vertices[i].firstacr;
        
        while(p!=NULL ) {
            
            cout<<"→"<<p->adjvex;
            
            p=p->nextarc;
            
        }
        
        cout<<endl;
        
    }
    
    
    
}



int visited[MVNum]={0};

void DFS1(ALGraph G,char d){
    
    ArcNode *p;
    
    int v,w;
    
    v=LocateVex_ALG(G,d);
    
    cout<<d;
    
    visited[v]=-1;
    
    p=G.vertices[v].firstacr;
    
    while (p!=NULL) {
        
        w=p->adjvex;
        
        if (visited[w]!=-1)
            
            DFS1(G, w);
        
        p=p->nextarc;
        
    }
    
}



void DFS2(ALGraph G,int v){    //邻接表图的遍历
    
    ArcNode *p;
    
    int w;
    
    cout<<v;
    
    visited[v]=true;
    
    p=G.vertices[v].firstacr;
    
    while (p!=NULL) {
        
        w=p->adjvex;
        
        if(!visited[w])
            
            DFS2(G, w);
        
        p=p->nextarc;
        
    }
    
}





//int Min(closedge A){
//
//    for(int i=0;i<G.vexnum;i++){
//
//        int a=closedge[i].lowcost;
//
//        if
//
//            }
//
//    return i;
//
//}


//
//void MiniSpanTree_Prim(AMGraph G,char u){
//
//    int k=LocateVex_AMG(G, u);
//
//    for (int j=0; j<G.vexnum; j++)
//
//        if (j!=k)
//
//            closedge_a[j]={u,G.arcs[k][j]};
//
//    closedge_a[k].lowcost=0;
//
//    for{int i=1;i<G.vexnum;++i){
//
//        k=Min(closedge_a);
//
//        int u0=closedge_a[k].adjvex;
//
//        int v0=G.vexs[k];
//
//        cout<<u0<<v0<<endl;
//
//        closedge_a[k].lowcost=0;
//
//        for (int j=0; j<G.vexnum; j++) {
//
//            if(G.arcs[k][j]<closedge_a[j].lowcost)
//
//                closedge_a[j]={G.vexs[k],G.arcs[k][j]};
//
//        }
//
//    }
//
//        return OK;
//
//    }
//

int main() {
    
    while (true) {
        
        cout<<endl<<"请选择"<<endl;
        cout<<"1------邻接矩阵"<<endl;
        cout<<"2------邻接表"<<endl;
        cout<<"3------生成最小生成树_普里姆算法"<<endl;
        
        int a;
        cin>>a;
        
        switch (a) {
            case 1:{
                cout<<"请选择：1使用已有无向图，2自定义无向图"<<endl;
                int mode;
                cin>>mode;
                
                AMGraph G_M;
                
                CreateUDN(G_M , mode);
                Print_AMG(G_M);}break;
                
            case 2:{
                ALGraph G_L;
                CreateUDG(G_L);  // CHECK( G);//cout<<"请输入第一个深度优先搜索遍历的data";cin>>d;
                Print_ALG(G_L);
                
                cout<<"遍历结果如下"<<endl;
                
                int v=0; //邻接表图的遍历
                
                DFS2(G_L, v);}break;
                
        }
        
    }
    
}
