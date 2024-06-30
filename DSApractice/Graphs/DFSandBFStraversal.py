class Graph:
    def __init__(self, size):
        self.size = size
        self.adjacency_matrix = [[None] * size for _ in range(size)]
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
            print(' '.join(map(lambda x : str(x) if x is not None else '0', row)))
        print("\nVertex Data:")
        for vertex, data in enumerate(self.vertexData):
            print(f"Vertex {vertex}: {data}")

    def dfs_helper(self, v, visited):
        visited[v] = True
        print(self.vertexData[v], end = ' ')
        for i in range(self.size):
            if self.adjacency_matrix[v][i] == 1 and not visited[i]:
                self.dfs_helper(i, visited)
    
    def dfs(self, start_vertex):
        visited = [False] * self.size
        start_vertex = self.vertexData.index(start_vertex)
        self.dfs_helper(start_vertex, visited)

    def bfs(self, start_vertex):
        queue = [self.vertexData.index(start_vertex)]
        visited = [False] * self.size
        visited[queue[0]] = True
        while queue:
            currentVertex = queue.pop(0)
            print(self.vertexData[currentVertex], end = ' ')
            for i in range(self.size):
                if self.adjacency_matrix[currentVertex][i] == 1 and not visited[i]:
                    queue.append(i)
                    visited[i] = True

g = Graph(7)

g.addVertexData(0, 'A')
g.addVertexData(1, 'B')
g.addVertexData(2, 'C')
g.addVertexData(3, 'D')
g.addVertexData(4, 'E')
g.addVertexData(5, 'F')
g.addVertexData(6, 'G')

g.addEdge(3, 0)  # D - A
g.addEdge(0, 2)  # A - C
g.addEdge(0, 3)  # A - D
g.addEdge(0, 4)  # A - E
g.addEdge(4, 2)  # E - C
g.addEdge(2, 5)  # C - F
g.addEdge(2, 1)  # C - B
g.addEdge(2, 6)  # C - G
g.addEdge(1, 5)  # B - F

g.printGraph()

print("\nDepth First Search starting from vertex D:")
g.dfs('D')

print("\nBreadth First Search starting from vertex D:")
g.bfs('D')