import matplotlib.pyplot as plt
import networkx as nx

try:
    import pygraphviz
    from networkx.drawing.nx_agraph import graphviz_layout
except ImportError:
    try:
        import pydot
        from networkx.drawing.nx_pydot import graphviz_layout
    except ImportError:
        raise ImportError("This example needs Graphviz and either "
                "PyGraphviz or pydot")
G= nx.Graph()
for i in range (20):
    G.add_node(i)

for i in range (20):
    for j in range (20):
        G.add_edge(i,j)

pos = graphviz_layout(G, prog='twopi', args='')
fig = plt.figure()
nx.draw(G, pos, node_size=100, alpha=.5, node_color="skyblue",edge_color="white", with_labels=True,font_color="white", font_size="30")
fig.set_facecolor("#00000F")
plt.axis('equal')

plt.show()
