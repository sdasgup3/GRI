#include<iostream> 
#include<vector> 
#include<climits> 
#include<cassert> 
#include<queue> 
#include<fstream>
#include<map>

using namespace std;

std::vector<std::vector<float>> 
loadFromFile(std::string& filename) {

  ifstream is(filename.c_str());

  if(!is.is_open()) {
    std::cerr  << filename.c_str();
    assert(0 && "File was not found or is not readable: ");
  }

  int m_directed;
  int num_vertices = 0;
  int num_edges = 0;
  int num_vertices_props = 0;
  int num_edges_props = 0;

  map<int, int > vertices;

  // Is directed flag, number of vertices, number of edges
  is >> m_directed;
  is >> num_vertices;
  is >> num_edges;

  // Number of properties for vertices, names of properties for vertices
  is >> num_vertices_props;
  for(int i = 0; i < num_vertices_props; i++) {
    string name;
    is >> name;
  }

  // Number of properties for edges, names of properties for edges
  is >> num_edges_props;
  for(int i = 0; i < num_edges_props; i++) { 
    string name;
    is >> name;
  }
  
   // Vertices
  std::vector<std::vector<float>> 
    graph(num_vertices, std::vector<float>(num_vertices, 0.0));
  for(int j = 0; j < num_vertices; j++) {
    int id = 0;
    is >> id;
    vertices.insert(make_pair(id, j));
    
    for(int i = 0; i < num_vertices_props; i++) {
      float value = 0.0f;
      is >> value;
    }
  }

  // Edges
  for(int j = 0; j < num_edges; j++) {
    int id = 0;
    is >> id;

    map<int, int >::iterator begin = vertices.find(id);
    if(begin == vertices.end()) {
      assert(0 && "edge id does not belong to a vertex");
    }

    is >> id;

    map<int, int >::iterator end = vertices.find(id);
    if(end == vertices.end()) {
      assert(0 && "edge id does not belong to a vertex");
    }


    float value = 0.0f;
    for(int i = 0; i < num_edges_props; i++) {
      is >> value;
    }

    graph[(*begin).second][(*end).second] = value;
    if(0 == m_directed) {
      graph[(*end).second][(*begin).second] = value;
    }

  }

  is.close();
  return graph;
}


vector<int>
getPath(std::vector<int> parent, int start, int end)
{
  vector<int> path;
  int runner = end;
  while(runner != start) {
    path.push_back(runner);
    runner = parent[runner];
  }
  path.push_back(start);

  return path;
}

std::vector<int>
dijkstra(vector<vector<float>> graph, int start) 
{
  int V = graph.size();
  std::vector<float> dist(V, INT_MAX);
  std::vector<int> parent(V, -1);
  //std::priority_queue<node> Q;
  std::vector<bool> visited(V, false);


  //Q.push(node(0,0));
  dist[start] = 0.0;
  parent[0] = 0;

  //while(false == Q.empty()) {
  for(int count = 0 ; count < V; count ++) {  

    float min = INT_MAX;
    int minI = -1;
    for(int i = 0 ; i < V; i++) {
      if(dist[i] < min && false == visited[i]) {
        min = dist[i];
        minI = i;
      }
    }

    if(-1 == minI) {
      break;
    }
    //std::cout << min << " " << minI << "\n";

    //node minNode = Q.top();
    //Q.pop();
    //int minI = minNode.id;

    visited[minI] = true;

    for(int i = 0; i < V; i++) {
      if(i == minI || 0 == graph[minI][i] || true == visited[i]) {
        continue;
      }

      if(dist[minI] + graph[minI][i] < dist[i]) {
        dist[i] = dist[minI] + graph[minI][i];
        //Q.push(node(i, dist[i]));
        parent[i] = minI;

      }
    }
  }

  //print
  //for(int v = 0 ; v < V; v++) {
  //  std::cout << v << " : " << dist[v] << " " << v << "--" << parent[v] << " \n";
  ////}

  for(int v = 0 ; v < V; v++) {
    //vector<int> path = getPath(parent, start, v);
    cout << "" << v << " | " << dist[v] << " | " << parent[v] ;
    //for(int i  =  path.size() -1;  i >= 0; i--) {
    //  cout << "" << path[i] << " " ;    
    //}
    cout<<"\n";
  }

  return parent;
}


void
displayADJMatrix(std::vector<std::vector<float>> &graph) 
{
  int size = graph.size();
  std::cout << "  ";
  for(int i = 0 ; i < size; i++) {
    std::cout << i << " ";
  }
  std::cout << "\n";

  for(int i = 0 ; i < size; i++) {
    std::cout << i << "|";
    for(int j  = 0 ; j <  size; j++) {
      std::cout << graph[i][j] << " "; 
    }
    std::cout << "\n"; 
  }
    std::cout << "\n"; 
}


int main(int argc, char** argv)
{
   string filename(argv[1]);
    std::vector<std::vector<float>> graph = 
          loadFromFile(filename);

   //displayADJMatrix(graph);

   std::vector<int > T = dijkstra(graph, 0);
   return 0;
}
