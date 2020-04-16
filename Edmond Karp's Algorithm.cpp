#include<bits/stdc++.h>
using namespace std;
//BFS Algorithm to find augmented path
/*The logic behind using residualcapacity is for every augmented path found in network
graph we were decreasing the current flow and increasing all the edges in the reverse 
direction by current flow. So after update we will get a new residual graph*/
bool bfs(int **residualcapacity,int source,int sink,int n,int *parent){
    bool visited[n];
    memset(visited,0,sizeof(visited));
    queue<int>que;
    visited[source]=true;
    que.push(source);
    bool foundAugmentedPath=false;
    while(not que.empty()){
        int u=que.front();
        que.pop();
        for(int v=0;v<n;v++){
            if(visited[v] == false and residualcapacity[u][v] >0){
                parent[v]=u;
                visited[v]=true;
                que.push(v);
                if(v==sink){
                    foundAugmentedPath=true;
                    break;
                }
            }
        }
    }
    return foundAugmentedPath;
}
void printAugmentedPaths(vector<vector<int>> augmentedPaths){
    for(int i=0;i<augmentedPaths.size();i++){
        for(int j=0;j<augmentedPaths[i].size();j++){
            cout<<augmentedPaths[i][j]<<"--> ";
        }
        cout<<endl;
    }
}
/*So inside the max flow function we are taking the parameter of our original graph,the source ,the sink and
 the no of vertices. We are initialising another graph which denote our residual graph.Initially the residual 
 graph will be same as our original graph and all the edge weight will be equal to edge weight of the original graph.
 Then one by one we will decrease the edge weight and calculate the new residual capacity for each edge and then
 we are initialising a parent array that will take care of the parent vertex of the current vertex . Then we will 
 take vector of vector which will store all the path found using Ford Fulkerson's Algorithm.Thenw we are initialising
 variable max_flow which will store all the final value of our maxFlow algorithm. While the bfs algorithm is returning
 augmented path from the residual graph we will iterat and then for the current augmented path we will calculate the
 flow value.The flow value is the minimum weight along the edges.We are backtracing so we reverse the path and then 
 push it into vector. And we increase the maxflow with current flow. And after we have found the flow. SO we decrease
 the weight of all forward edges and increase the weight of all backward edges. As there is no backward edges we 
 assume hyptothetical edges */
int maxFlow(int **capacity,int source,int sink,int v){
    int **residualcapacity=new int*[v];
    for(int i=0;i<v;i++){
        residualcapacity[i]=new int[v];
    }
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
            residualcapacity[i][j]=capacity[i][j];
        }
    }
    int *parent=new int[1000];
    vector<vector<int>>augmentedPaths;
    int maxFlow=0;
    while(bfs(residualcapacity,source,sink,v,parent)){
        vector<int>currentAugmentedPath;
        int u=parent[v];
        int flow=INT_MAX;
        int v=sink;
        //BackTrace our path
        while(v!=source){
            currentAugmentedPath.push_back(v);
            int u=parent[v];
            if(flow>residualcapacity[u][v]){
                flow=residualcapacity[u][v];
            }
            //Updating v so after certain iteration it reaches source
            v=u;
        }
        currentAugmentedPath.push_back(source);
        //Since we have stored the path in reverese pattern so we reverse and then store it
        std:: reverse(currentAugmentedPath.begin(),currentAugmentedPath.end());
        augmentedPaths.push_back(currentAugmentedPath);
        maxFlow+=flow;
        //Update residualcapacity graph
        v=sink;
        while(v!=source){
            int u=parent[v];
            residualcapacity[u][v] -=flow;//Forward edge decreease
            residualcapacity[v][u] +=flow;//Backward flow increase
            //Updating v so after certain iteration it reaches source
            v=u;
        }
    }
    printAugmentedPaths(augmentedPaths);
    return maxFlow;
}
int main()
{
    int v,e;
    cin>>v>>e;
    //2-d Array 
    int **capacity= new int*[v];
    for(int i=0;i<v;i++){
        capacity[i]=new int[v];
    }
    //We will start flling the matrix
    for(int i=0;i<e;i++){
        //u will give initial vertex,v will give destination vertex 
        //and c will give capacity
        int u,v,c;
        cin>>u>>v>>c;
        capacity[u][v]=c;
    }
    cout<<endl<<maxFlow(capacity,0,1,v);
}