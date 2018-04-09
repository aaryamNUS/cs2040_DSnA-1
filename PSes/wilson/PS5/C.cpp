// Copy paste this C++ Template and save it as "Labor.cpp"
#include <list>
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>


using namespace std;

// write your matric number here: A0167342E
// write your name here: Ler Wei Sheng
// write list of collaborators here: Arjo
// year 2017 Sem2 hash code: WxxVfOfqw6Be7Cyq2acb (do NOT delete this line)

// We set V, Q, and AdjList to be global variables so that they are directly accessible in all other methods/functions
// But if you want to refactor this template code to avoid any global variable, you can do so
//unordered_map<int, int> added_weight;
//unordered_map<int, int> predecessor;

#define INT_MAX 2000000

class graph {
private:
    int V; // number of vertices in the graph (number of junctions in Singapore map)
    int Q; // number of queries
    
    
public:
    list <pair<int, int> >  AL[1001]; // the weighted graph (the Singapore map), the length of each edge (road) is stored here too, as the weight of edge
    //vector< list <pair<int, int> > > AL_prime;
    graph (int size) {
        this->V = size;
        //vector <list <pair<int, int> > > new_AL (10000);
    }
    
    
    vector<int> perform_djikstra (int source) {
        priority_queue<pair<int, int> > q;
        vector<int> added_weight (V, 1001);
        // Init source to 0
        added_weight[source] = 0;
        q.push(make_pair(0, source));
        
        while (!q.empty()) {
            int current = q.top().second;
            q.pop();
            for (auto it = AL[current].begin(); it != AL[current].end(); it++) {
                //relax(current, it->second, it->first, added_weight); // Update the added_weights
                // Update PQ - sorta
                // Greedy
                
                if (added_weight[it->second] > added_weight[current] + it->first)
                {
                    
                    // Updating distance of v
                    added_weight[it->second] = added_weight[current] + it->first;
                    q.push(make_pair(added_weight[it->second], it->second));
                }
                
            }
        }
        
        return added_weight;
    }
    
    
    // A*
    
    int perform_djikstra_old (int source, int dest) {
        priority_queue<pair<int, int> > q;
        vector<int> added_weight (V, INT_MAX);
        // Init source to 0
        added_weight[source] = 0;
        q.push(make_pair(0, source));
        
        while (!q.empty()) {
            int current = q.top().second;
            q.pop();
            for (auto it = AL[current].begin(); it != AL[current].end(); it++) {
                //relax(current, it->second, it->first, added_weight); // Update the added_weights
                // Update PQ - sorta
                // Greedy
                if (added_weight[it->second] > added_weight[current] + it->first)
                {
                    // Updating distance of v
                    added_weight[it->second] = added_weight[current] + it->first;
                    q.push(make_pair(added_weight[it->second], it->second));
                }
                
            }
        }
        
        return added_weight[dest];
    }
    
    
    
    int perform_djikstra (int source, int dest, int k) {
        set<pair<int, int> > q;
        vector<int> added_weight (V, INT_MAX);
        int len[1001] = {0};
        //unordered_map<int, int> added_weight;
        // Init source to 0
        //added_weight[source] = 0;
        // First one is weight, second is len
        //added_weight[source].push_back(make_pair(1, 0));
        //q.push(make_pair(0, source));
        q.insert(make_pair(0, source));
        added_weight[source] = 0;
        len[source] = 1;
        
        
        // TODO: Make a predecessor table using unordered_map of vectors
        
        while (!q.empty()) {
            //cout << "Queue size: " << q.size() << endl;
            //int current = q.top().second;
            int current = q.begin()->second;
            int length = len[current];
            //q.pop();
            q.erase(q.begin());
            
            for (auto it = AL[current].begin(); it != AL[current].end(); it++) {
                int v = it->second;
                int g_cost = 0;
                
                if (length + 1 > k) {
                    g_cost = INT_MAX;
                }
                
                int weight = it->first + g_cost;
                
                if (added_weight[v] > added_weight[current] + weight) {
                    added_weight[v] = added_weight[current] + weight;
                    //q.push(make_pair(added_weight[v], v));
                    q.insert(make_pair(added_weight[v], v));
                    len[v] = len[current] + 1;
                }
            }
        }
        return added_weight[dest];
    }
    
    int Query(int s, int t, int k, int V) {
        // Product matrix
        //int added_weight_2 [V][V];
        vector<vector<int> > added_weight_2 (V, vector<int> (V));
        
        for (int i = 0; i < k; i++) {
            for (int d = 0; d < V; d++) {
                added_weight_2[i][d] = INT_MAX;
            }
        }

        added_weight_2[0][s] = 0; // Source should have zero weight
        
        for (int i = 1; i < k; i++) { // Relax the edges numv - 1 times
            for (int d = 0; d < V; ++d)
            {
                int v = d;
                for (auto it = AL[d].begin(); it != AL[d].end(); it++) {
                    
                    int v2 = it->second;
                    int w = it->first;
                    
                    // Relax
                    if (added_weight_2[i][v2] > added_weight_2[i-1][v] + w) {
                        added_weight_2[i][v2] =  added_weight_2[i-1][v] + w;
                    }
                }
            }
            for (int d = 0; d < V; d++) {
                if (added_weight_2[i][d] > added_weight_2[i-1][d]) {
                    added_weight_2[i][d] = added_weight_2[i-1][d];
                }
            }
            
        }
        /*
        for (int i = 0; i < V; i++) {
            for (int d = 0; d < V; d++) {
                if (added_weight_2[i][d] >= INT_MAX) cout << "INF\t";
                else cout << added_weight_2[i][d] << "\t";
            }
            cout << endl;
        }
        */
        if (added_weight_2[k-1][t] >= INT_MAX) return -1;
        return added_weight_2[k-1][t];
    }
    
};



int main() {
    int TC;
    scanf("%d", &TC);
    
    while (TC--) {
        int j, k, w, V;
        scanf("%d", &V);
        graph mygraph (V);
        // clear the graph and read in a new graph as Adjacency List
        for (int i = 0; i < V; i++) {
            scanf("%d", &k);
            while (k--) {
                scanf("%d %d", &j, &w);
                //mygraph.AL[i].push_back(make_pair(w, j));
                mygraph.AL[i].push_back(make_pair(w, j));
            }
        }
        
        //mygraph.DFS_second(0);
        int source, destination, required_k, Q;
        
        scanf("%d", &Q);
        //vector<vector<int > > distances(V);
        unordered_map<int, vector<vector<int> > > checks;
        while (Q--) {
            
            scanf("%d %d %d", &source, &destination, &required_k);
            //mygraph.BFS(source, required_k, destination);
            /*
            if (checks.find(source) == checks.end()) {
                checks.insert(make_pair(source, mygraph.Query(source, destination, required_k, V)));
            }
            */
            //int distance = mygraph.perform_djikstra(source, destination, required_k);
            //int distance = mygraph.perform_djikstra_old(source, destination);
            //int distance = mygraph.Query(source, destination, required_k, V);
            //int min = checks[source][required_k-1][destination];
            //if (min >= INT_MAX) printf("-1\n");
            
            printf("%d\n", mygraph.Query(source, destination, required_k, V));
            
            
        }
        
        if (TC)
            printf("\n");
        
        
    }
    return 0;
}