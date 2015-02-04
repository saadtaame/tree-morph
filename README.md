# tree-morph
Given two binary trees on n nodes, the program finds a sequence of rotations to transform the first binary tree into the second one. The program first reads n, the number of nodes, then it reads the trees one at a time.

Each binary tree is specified by listing the left and right children of each node. Internal nodes are assigned the numbers 0, 1, ..., n-1 and external nodes are assigned the number -1.

Sample input/output:

input:
<pre>
4

1 -1
2 -1
-1 3
-1 -1

-1 1
-1 2
-1 3
-1 -1
</pre>

output:
<pre>
rotate-left(3)
rotate-right(3)
rotate-right(3)
rotate-right(1)
rotate-right(2)
</pre>
