//

//  main.cpp

//  Graph

//

//  Created by 麦小明 on 15/6/9.

//  Copyright (c) 2015年 麦小明. All rights reserved.

//



#include <iostream>

#define MaxInt 32767

#define MVNum 100

#define OK 1

#define ERROR 0

using namespace std;







//邻接矩阵



typedef struct {
    
    char vexs[MVNum];    // 顶点表
    
    int arcs[MVNum][MVNum]; //邻接矩阵
    
    int vexnum,arcnum;
    
}AMGraph;





//邻接表

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
    
    int vexnum,arcnum;       //
    
}ALGraph;



//普里姆算法 辅助数组

typedef  struct closedge1{
    
    char adjvex;
    
    int lowcost;
    
}closedge1,closedge2[MVNum];



int LocateVex_ALG(ALGraph G,int v){
    
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



int LocateVex_AMG(AMGraph G,char v){
    
    int i=0;
    
    while (v!= G.vexs[i])
        
        i++;
    
    return i;
    
}





int CreateUDN(AMGraph &G){        //创建邻接矩阵
    
    cout<<"请输入点数和边数";
    
    cin>>G.vexnum>>G.arcnum;
    
    for (int i=0; i<G.vexnum; i++){
        
        cout<<"请输入顶点";
        
        cin>>G.vexs[i];        //输入顶点表
        
    }
    
    for (int i=0; i<G.vexnum; i++)
        
        for (int j=0; j<G.vexnum; j++)
            
            G.arcs[i][j]=MaxInt;
    
    
    
    for (int k=0; k<G.arcnum; k++) {
        
        char v1,v2;
        
        int w;
        
        int i,j;
        
        cout<<"请输入第"<<k+1<<"条边的两个点和权值w";
        
        cin>>v1>>v2>>w;
        
        i=LocateVex_AMG(G,v1);
        
        j=LocateVex_AMG(G,v2);
        
        G.arcs[i][j]=w;
        
        G.arcs[j][i]= G.arcs[i][j];
        
    }
    
    return OK;
    
}





int CreateUDG(ALGraph &G){        //创建邻接表
    
    cout<<"请输入点数和边数";
    
    cin>>G.vexnum>>G.arcnum;
    
    for (int i=0; i<G.vexnum; i++) {
        
        cout<<"请输入第"<<i+1<<"个点的data";
        
        cin>>G.vertices[i].data;
        
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






    
    
    
    
    int main() {
        
        int temp=1;
        
        while (temp) {
            
            cout<<endl<<"请选择"<<endl;
            
            cout<<"1------邻接矩阵"<<endl;
            
            cout<<"2------邻接表"<<endl;
            
            cout<<"3------生成最小生成树_普里姆算法"<<endl;
            
            int switchnumber;
            
            cin>>switchnumber;
            
            switch (switchnumber) {
                    
                case 1:{
                    
                    AMGraph G_M;
                    
                    CreateUDN(G_M);
                    
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
    
