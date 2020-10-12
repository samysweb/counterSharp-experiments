Benchmark File		| Benchmark Set			| Benchmark Family			| Modified					| Runnable by Dimovski et al.
---|---| ---|--- | ---
usqrt-broken.c		| c-snippets			| ---						| yes (long to int, calculation of result) | no (bit ops)
usqrt.c				| c-snippets			| ---						| yes (long to int, calculation of result) | no (bit ops)
rangesum05.c		| sv-benchmarks			| reducercommutativity		| yes (input variables) | no (arrays?)
rangesum07.c		| sv-benchmarks			| reducercommutativity		| yes (7 instead of 5/10 inputs) | no (arrays?)
Problem10_16.c		| sv-benchmarks			| eca-rers2018				| yes (input variables, unwinding to depth 16) | yes
Problem13_4.c		| sv-benchmarks			| eca-rers2018				| yes (input variables, unwinding to depth 4) | yes
nondet.c 			| --- 					| --- 						| crafted | yes
confidence.c 		| --- 					| ---						| crafted | no (bit ops, division does not seem to help (fatal error))
floor.c				| c-snippets			| ---						| yes (added assertion/assumption) | no (float)
floor-broken.c		| c-snippets			| ---						| yes (added assertion/assumption, broke bit ops) | no (float)
---					| ---					| ---						| --- | ---
bwd_loop1a.c		| A. Dimovski et al.	| deterministic				| yes (adjusted input format) | ---
bwd_loop2.c			| A. Dimovski et al.	| deterministic				| yes (adjusted input format) | ---
count_up_down*.c	| A. Dimovski et al.	| deterministic				| yes (adjusted input format) | ---
example1a.c			| A. Dimovski et al.	| deterministic				| yes (adjusted input format) | ---
example7a.c			| A. Dimovski et al.	| deterministic				| yes (adjusted input format) | ---
hhk2008.c			| A. Dimovski et al.	| deterministic				| yes (adjusted input format) | ---
gsv2008.c			| A. Dimovski et al.	| deterministic				| yes (adjusted input format) | ---
Log.c				| A. Dimovski et al.	| deterministic				| yes (adjusted input format) | ---
Mono3_1.c			| A. Dimovski et al.	| deterministic				| yes (adjusted input format) | ---
Waldkirch.c			| A. Dimovski et al.	| deterministic				| yes (adjusted input format) | ---
for-bounded*.c		| A. Dimovski et al.	| nondeterministic			| yes (adjusted input format) | ---
bwd_loop7.c			| A. Dimovski et al.	| nondeterministic			| yes (adjusted input format) | ---
bwd_loop10.c		| A. Dimovski et al.	| nondeterministic			| yes (adjusted input format) | ---
example7b.c			| A. Dimovski et al.	| nondeterministic			| yes (adjusted input format) | ---
