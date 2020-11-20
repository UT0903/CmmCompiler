make

echo 'array'
./parser testdata/array.c
diff gv_file/array.gv AST_Graph.gv

echo 'builtin'
./parser testdata/builtin.c
diff gv_file/builtin.gv AST_Graph.gv

echo 'control'
./parser testdata/control.c
diff gv_file/control.gv AST_Graph.gv

echo 'decl'
./parser testdata/decl.c
diff gv_file/decl.gv AST_Graph.gv

echo 'eof'
./parser testdata/eof.c
diff gv_file/eof.gv AST_Graph.gv

echo 'expr'
./parser testdata/expr.c
diff gv_file/expr.gv AST_Graph.gv

echo 'for'
./parser testdata/for.c
diff gv_file/for.gv AST_Graph.gv

echo 'func'
./parser testdata/func.c
diff gv_file/func.gv AST_Graph.gv

echo 'if'
./parser testdata/if.c
diff gv_file/if.gv AST_Graph.gv

echo 'typedef'
./parser testdata/typedef.c
diff gv_file/typedef.gv AST_Graph.gv

echo 'while'
./parser testdata/while.c
diff gv_file/while.gv AST_Graph.gv

echo 'plusplus'
./parser testdata/plusplus.c
#diff gv_file/plusplus.gv AST_Graph.gv

make clean
rm AST_Graph.gv parser.output
