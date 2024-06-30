class Graph:
    def __init__(self, size):
        self.size = size
        self.adjacency_matrix = [[0] * size for _ in range(size)]
        self.vertex_data = [''] * size
        # the parent array is used to contain the root vertex for every subset, and this will check is there is a cycle
        # by checking if two vertices of either side of an edge already exist in the same subset
        self.parent = [i for i in range(size)] 
    
    def add_edge(self, u , v):
        if 0 <= u < self.size and 0 <= v < self.size:
            self.adjacency_matrix[u][v] = 1
            self.adjacency_matrix[v][u] = 1 
    
    def add_vertex_data(self, vertex, data):
        if 0 <= vertex < self.size:
            self.vertex_data[vertex] = data
    
    # Used to find the root of the tree
    def find(self, i):
        # if the parent of i is i, then i is the root of the tree
        if self.parent[i] == i:
            return i
        # otherwise, we recursively call find on the parent of i as the new vertex until we find the root of the tree
        return self.find(self.parent[i])
    
    def union(self, x, y):
        x_root = self.find(x) # find the root of the tree of vertex x
        y_root = self.find(y) # find the root of the tree of vertex y

        # print the vertices being merged together
        print("Union: ", self.vertex_data[x], ' + ', self.vertex_data[y]) 
        # set the parent of the x root to the y root to effectively merge the two trees together (union)
        self.parent[x_root] = y_root
        print(self.parent, '\n') # updated parent array after the merging of the two trees
    
    def is_cyclic(self):
        # iterate over every pair of vertices in the graph
        for i in range(self.size):
            for j in range(i + 1, self.size):
                # If there is an edge between vertices i and j
                if self.adjacency_matrix[i][j]:
                    # find the root of the tree of vertex i and the root of the tree of vertex j
                    x = self.find(i)
                    y = self.find(j)
                    # if the roots of the trees are the same, then there is a cycle
                    if x == y:
                        return True
                    # if the roots of the trees are not the same, then we merge the two trees together (union)
                    self.union(x, y)
        return False
    
g = Graph(7)

g.add_vertex_data(0, 'A')
g.add_vertex_data(1, 'B')
g.add_vertex_data(2, 'C')
g.add_vertex_data(3, 'D')
g.add_vertex_data(4, 'E')
g.add_vertex_data(5, 'F')
g.add_vertex_data(6, 'G')

g.add_edge(1, 0)  # B - A
g.add_edge(0, 3)  # A - D
g.add_edge(0, 2)  # A - C
g.add_edge(2, 3)  # C - D
g.add_edge(3, 4)  # D - E
g.add_edge(3, 5)  # D - F
g.add_edge(3, 6)  # D - G
g.add_edge(4, 5)  # E - F

print("Graph has cycle:", g.is_cyclic())