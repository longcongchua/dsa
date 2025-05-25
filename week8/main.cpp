#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

//1. The file contains an adjacency matrix. Read the file and output the corresponding adjacency list.
vector<vector<int>> convertMatrixToList(const string& filename){
    ifstream file(filename);
    if(!file.is_open()){
        cerr << "can not open file"<< endl;
        return {};
    }

    vector<vector<int>> res;
    int n;
    file >> n;
    for(int i =0; i < n; i++){
        vector <int> arr;
        for(int j =0; j < n; j ++){
            int val;
            file >> val;
            if(val == 1){
                arr.push_back(j);
            }
        }
        vector<int> line;
        line.push_back(arr.size());
        line.insert(line.end(), arr.begin(), arr.end());
        res.push_back(line);
    }
    return res;
}   

//2. The file contains an adjacency list. Read the file and output the corresponding adjacency matrix.
vector<vector<int>> convertListToMatrix(const string& filename){
    ifstream file(filename);
    if(!file.is_open()){
        cerr <<"can not open file" << endl;
        return {};
    }
    vector<vector<int>> res;
    int n;
    file >> n;
    for(int i = 0; i < n; i++){
        vector<int> arr(n, 0);
        int cnt;
        file >> cnt;
        for(int j = 0; j < cnt; j++){
            int pos ;
            file >> pos;
            arr[pos] = 1;
        }
        res.push_back(arr);
    }
    return res;
}  

//3. Implement functions to provide the following information about a given graph:
// Directed or Undirected Graph.
bool isDirected(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    for(int i = 0; i < n ; i ++){
        for(int j = 0; j < n; j ++){
            if(adjMatrix[i][j] != adjMatrix[j][i]) return true; 
        }
    }
    return false;
}

// The number of vertices.
int countVertices(const vector<vector<int>>& adjMatrix){
    return adjMatrix.size();
}

// The number of edges.
int countEdges(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    int cnt = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(adjMatrix[i][j] == 1) cnt++;
        }
    }
    if(!isDirected(adjMatrix)) cnt = cnt /2;
    return cnt;    
}

// List of isolated vertices.
vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<vector<int>> list = adjMatrix;
    vector <int> v;
    for(int i = 0; i< n ; i ++){
        int chk = 0;
        for(int j = 0 ; j< n; j ++ ){
            if(list[i][j] == 1 || list[j][i] == 1){
                chk =1;
                break;
            }
        }
        if(chk == 0){
            v.push_back(i);
        }
    }
    return v;
}

// Undirected Graph.
bool isCompleteUndirectedGraph(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (adjMatrix[i][j] == 0 || adjMatrix[i][j] != adjMatrix[j][i]) {
                return false;
            }
        }
    }
    return true;
}


// Undirected Graph
bool isBipartite(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> color(n, -1);  

    for (int start = 0; start < n; ++start) {
        if (color[start] == -1) {
            queue<int> q;
            q.push(start);
            color[start] = 0;

            while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (int v = 0; v < n; ++v) {
                    if (adjMatrix[u][v]) {
                        if (color[v] == -1) {
                            color[v] = 1 - color[u];
                            q.push(v);
                        } else if (color[v] == color[u]) {
                            return false; 
                        }
                    }
                }
            }
        }
    }
    return true;
}

// Undirected Graph
bool isCompleteBipartite(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> color(n, -1);
    vector<int> group[2];  

    for (int start = 0; start < n; ++start) {
        if (color[start] == -1) {
            queue<int> q;
            q.push(start);
            color[start] = 0;
            group[0].push_back(start);

            while (!q.empty()) {
                int u = q.front(); q.pop();
                for (int v = 0; v < n; ++v) {
                    if (adjMatrix[u][v]) {
                        if (color[v] == -1) {
                            color[v] = 1 - color[u];
                            group[color[v]].push_back(v);
                            q.push(v);
                        } else if (color[v] == color[u]) {
                            return false; 
                        }
                    }
                }
            }
        }
    }

    for (int u : group[0]) {
        for (int v : group[1]) {
            if (adjMatrix[u][v] == 0) {
                return false;  
            }
        }
    }
    for (int i : group[0]) {
        for (int j : group[0]) {
            if (i != j && adjMatrix[i][j] != 0)
                return false;
        }
    }

    for (int i : group[1]) {
        for (int j : group[1]) {
            if (i != j && adjMatrix[i][j] != 0)
                return false;
        }
    }

    return true;
}

//--------------------------------------------------------------------------------------------------------------------------------------
//4. Generate a base undirected graph from a given directed graph.
vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<vector<int>> newmat = adjMatrix;
    for(int k =0; k < n; k++){
        for(int l = 0; l < n; l++){
            if(newmat[k][l] != newmat[l][k]){
                newmat[k][l] = newmat[l][k] = max(newmat[k][l] , newmat[l][k]);
            }
        }
    }
    return newmat;
}
//5. Generate a complement graph from a given undirected graph and output its adjacency matrix (*undirected graph).
vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<int>> newmat(n,vector<int>(n,0));
    for(int i = 0; i< n ; i++){
        for(int j =0; j< n; j++){
            if(i != j && adjMatrix[i][j] == 0){
                newmat[i][j] = 1;
            }
        }
    }
    return newmat;
}

//6. Determine the Euler cycle from a given graph using Hierholzer’s Algorithm
bool isGraphConnectedForEuler(const vector<vector<int>>& adjMatrix, int start) {
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 0; v < n; v++) {
            if (adjMatrix[u][v] && !visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        int deg = 0;
        for (int j = 0; j < n; j++) deg += adjMatrix[i][j];
        if (deg > 0 && !visited[i]) return false;
    }
    return true;
}

vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<vector<int>> list = adjMatrix; 
    vector<int> cycle;
    stack<int> s;
    for (int i = 0; i < n; i++) {
        int degree = 0;
        for (int j = 0; j < n; j++) {
            degree += adjMatrix[i][j];
        }
        if (degree % 2 != 0) {
            cout << "Do thi khong co chu trinh Euler";
            return {};
        }
    }
    int start = -1;
    for (int i = 0; i < n; i++) {
        int deg = 0;
        for (int j = 0; j < n; j++) {
            if (adjMatrix[i][j] == 1) deg++;
        }
        if (deg > 0) {
            start = i;
            break;
        }
    }
    if (start == -1) {
        cout << "Do thi rong\n";
        return {};
    }
    if (!isGraphConnectedForEuler(adjMatrix, start)) {
        cout << "Do thi khong lien thong";
        return {};
    }
    s.push(start);
    while (!s.empty()) {
        int x = s.top();
        int next = -1;
        for (int i = 0; i < n; i++) {
            if (list[x][i] == 1) {
                next = i;
                break;
            }
        }
        if (next != -1) {
            list[x][next] = 0;
            list[next][x] = 0;
            s.push(next);
        } else {
            s.pop();
            cycle.push_back(x);
        }
    }
    reverse(cycle.begin(), cycle.end());
    return cycle;
}

//7. Find the spanning tree of a given graph using(*undirected graph):
void DFS(int u,const vector<vector<int>> &adjMatrix, vector<bool> &visit, vector<vector<int>> &treeEdge){
    visit[u] = true;
    int n = adjMatrix.size();
    for(int  v =0; v < n; v++){
        if(adjMatrix[u][v] ==1 && !visit[v]){
            treeEdge.push_back({u,v});
            DFS(v,adjMatrix, visit, treeEdge);
        }
    }
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start){
    int n = adjMatrix.size();
    vector<bool> visit(n, false);
    vector<vector<int>> treeEdge;
    DFS(start, adjMatrix, visit, treeEdge);
    return treeEdge;
}


vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start){
    int n = adjMatrix.size();
    vector<bool> visit(n, false);
    vector<vector<int>> treeEdge;
    queue<int> q;
    visit[start] = true;
    q.push(start);
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v = 0; v < n; v++){
            if(adjMatrix[u][v]==1 && !visit[v]){
                visit[v] = true;
                treeEdge.push_back({u,v});
                q.push(v);
            }
        }
    }
    return treeEdge;
}

//8. Verify the connection between two vertices of a given graph.
bool check(int u, int v, const vector<vector<int>>& adjMatrix, vector<bool>& visit) {
    if (u == v) return true;
    visit[u] = true;
    int n = adjMatrix.size();
    for (int i = 0; i < n; i++) {
        if (adjMatrix[u][i] == 1 && !visit[i]) {
            if (check(i, v, adjMatrix, visit)) {
                return true;
            }
        }
    }
    return false;
}

bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix) {    
    int n = adjMatrix.size();
    vector<bool> visit(n, false);
    return check(u, v, adjMatrix, visit);
}

//9. Find the shortest path between two vertices of a given graph using (*Weighted Graph):
vector<int> getPath(int start, int end, const vector<int>& parent) {
    vector<int> path;
    int cur = end;
    while (cur != -1) {
        path.push_back(cur);
        cur = parent[cur];
    }
    reverse(path.begin(), path.end());
    if (path.front() == start)
        return path;
    else
        return {};  
}

vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<vector<pair<int, int>>> adj(n);
    vector<int> dis(n, 1e9);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    vector<int> parent(n, -1);
    vector<bool> visit(n, false);

    for(int i =0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(adjMatrix[i][j] != 0 ){
                adj[i].push_back({j, adjMatrix[i][j]});
            }
        }
    }
    
    dis[start] =0;
    q.push({0, start});
    while(!q.empty()){
        auto [dis_u, u] = q.top();
        q.pop();
        if (visit[u]) continue; 
        visit[u] = true;
        if(u == end) break; 
        for(int k =0 ; k < adj[u].size() ; k ++){
            int v = adj[u][k].first;
            int w = adj[u][k].second;
            if(dis_u + w < dis[v]){
                dis[v] = dis_u + w;
                parent[v] = u;
                q.push({dis[v], v});
            }
        }
    } 
    return getPath(start, end, parent);
}

struct Edge{
    int head;
    int tail;
    int w;
};

vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<int> dis(n, 1e9);
    vector<int> parent(n, -1);
    vector<Edge> edge;

    for(int i = 0; i < n; i++){
        for(int j = 0 ; j < n; j++){
            if(adjMatrix[i][j] != 0){
                edge.push_back({i, j, adjMatrix[i][j]});
            }
        }
    }
    dis[start] = 0;
    for(int k = 0; k < n -1; k++){
        for(int l = 0; l < edge.size(); l ++){
            int u = edge[l].head;
            int v = edge[l].tail;
            int w = edge[l].w;
            if(dis[u] != 1e9 && dis[u] + w < dis[v]){
                dis[v] = dis[u] + w;
                parent[v] = u; 
            } 
        }
    }
        for (int l = 0; l < edge.size(); l++) {
        int u = edge[l].head;
        int v = edge[l].tail;
        int w = edge[l].w;
        if (dis[u] != 1e9 && dis[u] + w < dis[v]) {
            cout << "Do thi co chu trinh trong so am" << endl;
            return {};
        }
    }

    // Truy vết đường đi từ end về start
    vector<int> path;
    if (dis[end] == 1e9) return path;  // Không có đường đi
    for (int cur = end; cur != -1; cur = parent[cur]) {
        path.push_back(cur);
    }
    reverse(path.begin(), path.end());
    return path;
}
