class Graph:
    def __init__(self, size):
        self.size = size
        self.adjacency_matrix = [[None] * size for _ in range(size)]
        self.vertexData = [''] * size

    def addEdge(self, u, v, weight): # add the weight parameter to account for the weighted graph property
        if 0 <= u < self.size and 0 <= v < self.size:
            self.adjacency_matrix[u][v] = weight  # only different between this and and undirected graph is that 
                                                # you change the 1 to the actual weight and you only use the direction 
                                                # from u to v, not both ways

    def addVertexData(self, vertex, data):
        if 0 <= vertex < self.size:
            self.vertexData[vertex] = data

    def printGraph(self):
        print("Adjacency Matrix:")
        for row in self.adjacency_matrix:
            print(' '.join(map(lambda x: str(x) if x is not None else '0', row)))
        print("\nVertex Data:")
        for vertex, data in enumerate(self.vertexData):
            print(f"Vertex {vertex}: {data}")

g = Graph(4)
g.addVertexData(0, 'A')
g.addVertexData(1, 'B')
g.addVertexData(2, 'C')
g.addVertexData(3, 'D')
g.addEdge(0, 1, 3)  # A - B
g.addEdge(0, 2, 2)  # A - C
g.addEdge(0, 3, 4)  # A - D
g.addEdge(1, 2, 1)  # B - C

g.printGraph()