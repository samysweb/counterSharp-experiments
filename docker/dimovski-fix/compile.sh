#!/bin/bash
eval $(opam config env)
echo "Compiling probab_analyzer..."
ocamlbuild ml_float.o Main.native -use-ocamlfind -use-menhir -pkgs 'bddapron,apron,gmp,oUnit,zarith' -I utils -I banal -I domains -I frontend -I main -libs boxMPQ,octD,polkaMPQ,str,zarith,bddapron -lflags banal/ml_float.o
mv Main.native Probab.native
chmod u+x Probab.native