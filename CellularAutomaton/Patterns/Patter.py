import networkx as nx
import matplotlib.pyplot as plt


G=nx.DiGraph
G.add_edge(1,2)
nx.draw(G,node_size=20,alpha=0.5,node_color="blue", with_labels=False)
plt.axis('equal')
plt.savefig('circular_tree.png')
plt.show()
