#include <bits/stdc++.h>
using namespace std;

unordered_map<string, vector<pair<string, int>>> graph;

// ADDED: Heuristic values
unordered_map<string, int> heuristic = {
    {"Mumbai", 500},
    {"Pune", 450},
    {"Nashik", 350},
    {"Aurangabad", 250},
    {"Solapur", 600},
    {"Kolhapur", 700},
    {"Amravati", 150},
    {"Nagpur", 0},
    {"Akola", 200}
};

void addedge(string u, string v, int dist){
    graph[u].push_back({v, dist});
    graph[v].push_back({u, dist});
}

void dijkstra(string src, string dest){
    unordered_map<string, int> dist;
    unordered_map<string, string> parent;
    for(auto node : graph) dist[node.first] = INT_MAX;
    dist[src] = 0;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    pq.push({heuristic[src], src});
    while(!pq.empty()){
        pair<int, string> curr = pq.top();
        pq.pop();
        int currdist = curr.first;
        string city = curr.second;
        if(currdist > dist[city] + heuristic[city]) continue;
        for(pair<string, int> neigh : graph[city]){
            string next = neigh.first;
            int wt = neigh.second;
            if(dist[city]+wt < dist[next]){
                dist[next] = dist[city] + wt;
                parent[next] = city;
                pq.push({dist[next] + heuristic[next], next});
            }
        }
    }
    if(dist[dest]==INT_MAX){
        cout << "No path found.\n";
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
    cout << "\nTotal Distance = " << dist[dest] << endl;
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

    dijkstra(src, dest);

    return 0;
}