#include <bits/stdc++.h>
using namespace std;

unordered_map<string, vector<pair<string, int>>> graph;

void addedge(string u, string v, int dist) {
    graph[u].push_back({v, dist});
    graph[v].push_back({u, dist});
}

void astar(string src, string dest) {

    //Heuristic values
    unordered_map<string, int> h={{"Mumbai",700},{"Pune",550},{"Nashik",500},{"Aurangabad",350},{"Solapur",500},{"Kolhapur",450},{"Nagpur",250},
    {"Amravati",100},{"Akola",0}};

    unordered_map<string, int> g;
    unordered_map<string, string> parent;

    for(auto node : graph) g[node.first] = INT_MAX;

    g[src] = 0;

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    pq.push({h[src], src});

    while(!pq.empty()){
        string curr = pq.top().second;
        pq.pop();

        if(curr==dest) break;

        for(pair<string, int> neigh : graph[curr]){
            string next = neigh.first;
            int wt = neigh.second;
            if(g[curr]+wt < g[next]){
                g[next] = g[curr] + wt;
                parent[next] = curr;
                int f = g[next] + h[next];
                pq.push({f, next});
            }
        }
    }

    if(g[dest]==INT_MAX){
        cout << "No path found\n";
        return;
    }

    vector<string> path;

    string curr = dest;
    while(curr != src){
        path.push_back(curr);
        curr = parent[curr];
    }
    path.push_back(src);
    reverse(path.begin(), path.end());

    cout << "\nShortest Path:\n";
    for(int i = 0; i < path.size(); i++){
        cout << path[i];
        if(i != path.size()-1) cout << " -> ";
    }

    cout << "\nTotal Distance = " << g[dest] << endl;
}

int main(){
    addedge("Mumbai", "Pune", 150);
    addedge("Mumbai", "Nashik", 170);
    addedge("Pune", "Aurangabad", 235);
    addedge("Pune", "Solapur", 250);
    addedge("Nashik", "Aurangabad", 180);
    addedge("Nashik", "Nagpur", 500);
    addedge("Aurangabad", "Amravati", 320);
    addedge("Aurangabad", "Nagpur", 470);
    addedge("Solapur", "Kolhapur", 230);
    addedge("Kolhapur", "Amravati", 400);
    addedge("Amravati", "Akola", 100);
    addedge("Nagpur", "Akola", 250);

    cout << "Cities: ";
    int i = 0;
    for(auto node : graph){
        cout << node.first;
        i++;
        if(i != graph.size()) cout << ", ";
    }
    cout << endl;

    string src, dest;
    cout << "Enter source city: ";
    cin >> src;
    cout << "Enter destination city: ";
    cin >> dest;

    astar(src, dest);

    return 0;
}