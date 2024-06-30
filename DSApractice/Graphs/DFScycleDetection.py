class Graph:
    def __init__(self, size):
        self.size = size
        self.adjacency_matrix = [[None] * size for _ in range(size)]
        self.vertexData = [''] * size

    def addEdge(self, u, v):
        if 0 <= u < self.size and 0 <= v < self.size:
            self.adjacency_matrix[u][v] = 1
            self.adjacency_matrix[v][u] = 1 # if graph was directed, then this line is not needed
    
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

    def dfs_helper(self, v, visited, parent_vertex):
        visited[v] = True # marks the current vertex as visited by setting it to True in the visited array

        # recStack[v] = True # recursion stack for the current vertex which is used to detect cycles for directed graphs

        for i in range(self.size): # iterate over all the vertices in the graph
            if self.adjacency_matrix[v][i] == 1: # if there is an edge between the current vetex v and vertex i
                if visited[i] == False: # if the vertex i has not been visited yet
                    # recurse on vertex i on the updated visited array and v as the parent vertex
                    if self.dfs_helper(i, visited, v): # for directed graphs, the parent_vertex is recStack
                        return True # if the if statement is True, then a cycle has been found
                # if vertex i has been visisted and is not the parent vertex, then a back edge has been found, hence a cycle
                elif parent_vertex != i: # if for directed graphs, then this would check recStack[i] == True
                    return True
                
        # if this was for directed graphs, then we set recStack[v] = False
        return False # if no cycle has been found after all iterations, return False
    
    def isCyclic(self):
        visited = [False] * self.size # initialize a visited array to all False to indicate that no vertices have been visited yet

        # recStack = [False] * self.size # if this was for directed graph cycle detection

        for i in range(self.size): # iterate over all the vertices in the graph
            if visited[i] == False: # if the current vertex has not been visited yet
                # recursively call dfs_helper on vertex i on the updated visited array with -1 as the parent vertex
                # (-1 is used as the parent vertex since the first call to dfs_helper has no parent vertex yet)
                if self.dfs_helper(i, visited, -1): # if this was for directed graphs, the parent_vertex is recStack
                    return True
        return False

    def bfs(self, start_vertex):
        # initialize a queue (list) with the index of the start_vertex parameter using vertexData.index()
        queue = [self.vertexData.index(start_vertex)]
        # visited array set to the size of the graph is all False to indicate that no vertices have been visited yet
        visited = [False] * self.size
        # set the visited array at the index of the start_vertex index parameter to True
        visited[queue[0]] = True
        # continue iterating until the queue is empty
        while queue:
            # pop the first element of the queue and set it to currentVertex
            currentVertex = queue.pop(0)
            # print the data associated with the current vertex
            print(self.vertexData[currentVertex], end = ' ')
            # for each vertex i
            for i in range(self.size):
                # check if there is an edge between the current vertex and vertex i
                # additionally, make sure the vertex i has not been visited yet
                if self.adjacency_matrix[currentVertex][i] == 1 and visited[i] == False:
                    # add vertex i to the back of the queue
                    queue.append(i)
                    # set the visited array at the index of vertex i to True to indicate that it has been visited
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

print("\nGraph has a cycle: ", g.isCyclic())