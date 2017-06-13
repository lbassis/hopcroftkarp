gcc transform.c -o transform
./transform teste.gr    # creates the source and sink nodes and lines
nodes=10
sed -i '.bak' '/p / r transformed.gr' teste.gr   # appends the source node
sed -i '.bak' 's/$/ 1/' teste.gr    # insert the weights


set -- `wc teste.gr`
edges=$(($1 - 6))
sed -i '.bak' "s/.*edge*/p sp ${nodes} ${edges}/" teste.gr  #set correct number of nodes and edges
