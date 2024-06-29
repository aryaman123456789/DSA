class Graph:
    def __init__(self, size):
        self.size = size
        self.adjacency_matrix = [[0] * size for _ in range(size)]
        self.vertexData = [''] * size

    def addEdge(self, u, v):
        if 0 <= u < self.size and 0 <= v < self.size:
            self.adjacency_matrix[u][v] = 1
            self.adjacency_matrix[v][u] = 1
    
    def addVertexData(self, vertex, data):
        if 0 <= vertex < self.size:
            self.vertexData[vertex] = data

    def printGraph(self):
        print("Adjacency Matrix:")
        for row in self.adjacency_matrix:
            print(' '.join(map(str, row)))
        print("\nVertex Data:")
        for vertex, data in enumerate(self.vertexData):
            print(f"Vertex {vertex}: {data}")

g = Graph(4)
g.addVertexData(0, 'A')
g.addVertexData(1, 'B')
g.addVertexData(2, 'C')
g.addVertexData(3, 'D')
g.addEdge(0, 1)  # A - B
g.addEdge(0, 2)  # A - C
g.addEdge(0, 3)  # A - D
g.addEdge(1, 2)  # B - C

g.printGraph()
