import networkx as nx
import matplotlib.pyplot as plt

def parse_wbs_file(filename):
    """
    Reads a hierarchical WBS text file (assuming 2 spaces per level) and returns:
      - nodes: a dict mapping node_id to a dictionary containing the node's label and its level
      - edges: a list of tuples (parent_id, child_id)
    """
    with open(filename, 'r') as f:
        lines = f.readlines()

    nodes = {}    # key: node_id, value: {'label': ..., 'level': ...}
    edges = []    # list of (parent_id, child_id)
    stack = []    # will hold tuples (level, node_id)
    counter = 0

    for line in lines:
        if not line.strip():
            continue
        # Determine level by counting leading spaces (assume 2 spaces per level)
        indent = len(line) - len(line.lstrip())
        level = indent // 2 + 1
        label = line.strip()
        counter += 1
        node_id = f"node{counter}"
        nodes[node_id] = {'label': label, 'level': level}
        # Pop from stack until finding a node with a lower level (i.e. the parent)
        while stack and stack[-1][0] >= level:
            stack.pop()
        if stack:
            parent_id = stack[-1][1]
            edges.append((parent_id, node_id))
        stack.append((level, node_id))
    return nodes, edges

def assign_positions_custom(G, node, pos, base_pos, h_spacing=2, v_spacing=1):
    """
    Recursively assigns positions to nodes based on the following rules:
      - If the parent's level is 1 or 2 (i.e. the parent is either the root "Office Move"
        or one of the horizontal first-level groups), arrange the children horizontally.
      - Otherwise (if the parent's level is 3 or greater), arrange the children vertically.
    
    Parameters:
      G: NetworkX graph (with node attribute 'level')
      node: current node id
      pos: dictionary to store positions
      base_pos: (x, y) coordinates for the current node
      h_spacing: horizontal spacing offset
      v_spacing: vertical spacing offset
    """
    pos[node] = base_pos
    children = list(G.successors(node))
    if not children:
        return
    parent_level = G.nodes[node]['level']
    if parent_level <= 2:
        # Arrange children horizontally (all in one row at parent's y)
        current_x = base_pos[0] + h_spacing
        for child in children:
            child_pos = (current_x, base_pos[1])
            assign_positions_custom(G, child, pos, child_pos, h_spacing, v_spacing)
            current_x += h_spacing
    else:
        # For parent's level 3 or deeper, arrange children vertically (same x offset)
        current_y = base_pos[1] - v_spacing
        for child in children:
            child_pos = (base_pos[0] + h_spacing, current_y)
            assign_positions_custom(G, child, pos, child_pos, h_spacing, v_spacing)
            current_y -= v_spacing

# --- Main Script Execution ---

# Replace "wbs-sheet.txt" with the path to your WBS data file.
nodes, edges = parse_wbs_file("wbs-sheet.txt")

# Create a directed graph and add nodes and edges.
G = nx.DiGraph()
for node_id, data in nodes.items():
    G.add_node(node_id, label=data['label'], level=data['level'])
G.add_edges_from(edges)

# Identify the root node (should be the one with no incoming edges).
roots = [n for n, d in G.in_degree() if d == 0]
if not roots:
    raise Exception("No root found in the WBS data.")
root = roots[0]

# Set up positions:
# We place the root ("Office Move") at (0, 0).
pos = {}
assign_positions_custom(G, root, pos, base_pos=(0, 0), h_spacing=2, v_spacing=1)

# Define color mapping for levels (adjust as desired)
color_mapping = {
    1: "blue",    # "Office Move" (root)
    2: "orange",  # Horizontal group (e.g. "1. Manage Project", "2. New Office", etc.)
    3: "green",   # Still part of the horizontal grouping (e.g. "1.1 Define Requirements")
    4: "red",     # Vertical breakdown (e.g. "1.1.1 Identify Stakeholders", etc.)
}
node_colors = [color_mapping.get(G.nodes[n]['level'], "gray") for n in G.nodes()]
labels = nx.get_node_attributes(G, 'label')

# Draw the WBS graph.
plt.figure(figsize=(12, 8))
nx.draw(G, pos, labels=labels, node_color=node_colors, with_labels=True,
        arrows=True, node_size=1500, font_size=10)
plt.title("WBS Org Chart: 'Office Move' on Top; Horizontal (Levels 2-3), Vertical (Level 4+)")
plt.axis('off')
plt.show()
