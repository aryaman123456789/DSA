class Graph:
    def __init__(self, size):
        self.size = size
        self.adjacency_matrix = [[0] * size for _ in range(size)]
        self.vertex_data = [''] * size
    
    # finish the implementation of Dijkstra algorithm