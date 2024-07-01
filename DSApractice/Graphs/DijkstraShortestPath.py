class Graph:
    def __init__(self, size):
        self.adjacency_matrix = [[0] * size for _ in range(size)]
        self.size = size
        self.vertex_data = [''] * size
    
    def add_edge(self, u, v, weight):
        if 0 <= u < self.size and 0 <= v < self.size:
            self.adjacency_matrix[u][v] = weight
            self.adjacency_matrix[v][u] = weight # if graph is directed, this line needs to be deleted
    
    def add_vertex_data(self, vertex, data):
        if 0 <= vertex < self.size:
            self.vertex_data[vertex] = data
    
    def dijkstra(self, start_vertex_data):
        # set start_vertex to the index of the start_vertex_data parameter
        start_vertex = self.vertex_data.index(start_vertex_data)
        # initialize the distance array to the size of the graph and set all values to infinity
        distances = [float('inf')] * self.size
        # create a predecessors array to backtract and find the shortest path for each vertex
        predecessors = [None] * self.size
        # set the distance of the start_vertex to 0
        distances[start_vertex] = 0
        # initialize the visited array and set all values to False to indicate that no vertices have been visited yet
        visited = [False] * self.size

        # iterate over every vertex in the graph
        for _ in range(self.size):
            # set min_distance to infinity initially and initialize u to None
            min_distance = float('inf')
            u = None

            # iterate over every vertex and find the unvisited vertex with the minimum distance to the start_vertex
            for i in range(self.size):
                if visited[i] == False and distances[i] < min_distance:
                    min_distance = distances[i]
                    u = i

            # if no unvisited vertex with the minimum distance to the start_vertex is found, then break out of the loop
            if u is None:
                break
            # mark the vertex u as visited
            visited[u] = True

            # update the distance value of the adjacent vertices of the selected vertex u
            for v in range(self.size):
                if self.adjacency_matrix[u][v] != 0 and visited[v] == False:
                    alt = distances[u] + self.adjacency_matrix[u][v]
                    if alt < distances[v]:
                        distances[v] = alt
                        predecessors[v] = u
            
        return distances, predecessors
    
    def get_path(self, predecessors, start_vertex, end_vertex):
        path = []
        # set current to the index of the end_vertex
        current = self.vertex_data.index(end_vertex)

        # backtrack from the end_vertex to the start_vertex using the predecessors array
        while current is not None:
            # insert the current vertex into the front of the path array
            path.insert(0, self.vertex_data[current])
            # move to the predecessor of the current vertex
            current = predecessors[current]

            # if we reach the start_vertex, insert it at the beginning of the path and break
            if current == self.vertex_data.index(start_vertex):
                path.insert(0, start_vertex)
                break
        # join the path list into a string with '->' separator
        return '->'.join(path)
    
g = Graph(7)

g.add_vertex_data(0, 'A')
g.add_vertex_data(1, 'B')
g.add_vertex_data(2, 'C')
g.add_vertex_data(3, 'D')
g.add_vertex_data(4, 'E')
g.add_vertex_data(5, 'F')
g.add_vertex_data(6, 'G')

g.add_edge(3, 0, 4)  # D -> A, weight 5
g.add_edge(3, 4, 2)  # D -> E, weight 2
g.add_edge(0, 2, 3)  # A -> C, weight 3
g.add_edge(0, 4, 4)  # A -> E, weight 4
g.add_edge(4, 2, 4)  # E -> C, weight 4
g.add_edge(4, 6, 5)  # E -> G, weight 5
g.add_edge(2, 5, 5)  # C -> F, weight 5
g.add_edge(1, 2, 2)  # B -> C, weight 2
g.add_edge(1, 5, 2)  # B -> F, weight 2
g.add_edge(6, 5, 5)  # G -> F, weight 5

# Dijkstra's algorithm from D to all vertices
print("Dijkstra's Algorithm starting from vertex D:\n")
distances, predecessors = g.dijkstra('D')
for i, d in enumerate(distances):
    path = g.get_path(predecessors, 'D', g.vertex_data[i])
    print(f"{path}, Distance: {d}")


