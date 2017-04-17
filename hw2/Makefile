all: assign_vec_rand

assign_vec: assign_vec.cpp
	g++-5 -O3 -g -o par-det-cc assign_vec.cpp -fcilkplus
assign_vec_rand: assign_vec_rand.cpp
	g++-5 -O3 -o par-ran-cc assign_vec_rand.cpp -fcilkplus

run: rand

det:
	./par-det-cc <test/com-youtube-in.txt >test/temp-youtube.out
	./par-det-cc <test-real/as-skitter-in.txt >test/as-skitter-in.txt.out 
	./par-det-cc <test-real/ca-AstroPh-in.txt >test/ca-AstroPh-in.txt.out 
	./par-det-cc <test-real/com-amazon-in.txt >test/com-amazon-in.txt.out 
	./par-det-cc <test-real/com-dblp-in.txt >test/com-dblp-in.txt.out 
	#time ./par-det-cc <test-real/com-friendster-in.txt >test/com-friendster-in.txt.out 
	./par-det-cc <test-real/com-lj-in.txt >test/com-lj-in.txt.out 
	 ./par-det-cc <test-real/com-orkut-in.txt >test/com-orkut-in.txt.out 
	 ./par-det-cc <test-real/roadNet-CA-in.txt >test/roadNet-CA-in.txt.out 
	 ./par-det-cc <test-real/roadNet-PA-in.txt >test/roadNet-PA-in.txt.out 
	 ./par-det-cc <test-real/roadNet-TX-in.txt >test/roadNet-TX-in.txt.out 


rand: youtube skitter astro amazon dblp lj orkut CA PA TX

youtube:
	./par-det-cc <test/com-youtube-in.txt >test/temp-youtube.out
	./par-ran-cc <test/com-youtube-in.txt >test/temp-youtube.outr
	diff test/com-youtube-out.txt test/temp-youtube.outr
skitter:
	./par-det-cc <test-real/as-skitter-in.txt >test/as-skitter-in.txt.out 
	./par-ran-cc <test-real/as-skitter-in.txt >test/as-skitter-in.txt.outr
	diff test/as-skitter-in.txt.outr test/as-skitter-in.txt.out
astro:
	./par-det-cc <test-real/ca-AstroPh-in.txt >test/ca-AstroPh-in.txt.out 
	./par-ran-cc <test-real/ca-AstroPh-in.txt >test/ca-AstroPh-in.txt.outr
	diff test/ca-AstroPh-in.txt.out test/ca-AstroPh-in.txt.outr
amazon:
	./par-det-cc <test-real/com-amazon-in.txt >test/com-amazon-in.txt.out 
	./par-ran-cc <test-real/com-amazon-in.txt >test/com-amazon-in.txt.outr
	diff test/com-amazon-in.txt.outr test/com-amazon-in.txt.out
dblp:
	./par-det-cc <test-real/com-dblp-in.txt >test/com-dblp-in.txt.out 
	./par-ran-cc <test-real/com-dblp-in.txt >test/com-dblp-in.txt.outr 
	diff test/com-dblp-in.txt.outr test/com-dblp-in.txt.out
friendster:
	./par-det-cc <test-real/com-friendster-in.txt >test/com-friendster-in.txt.out 
	./par-ran-cc <test-real/com-friendster-in.txt >test/com-friendster-in.txt.outr
	diff test/com-friendster-in.txt.out test/com-friendster-in.txt.outr
lj:
	./par-det-cc <test-real/com-lj-in.txt >test/com-lj-in.txt.out 
	./par-ran-cc <test-real/com-lj-in.txt >test/com-lj-in.txt.outr 
	diff test/com-lj-in.txt.out test/com-lj-in.txt.outr

orkut:
	./par-det-cc <test-real/com-orkut-in.txt >test/com-orkut-in.txt.out 
	./par-ran-cc <test-real/com-orkut-in.txt >test/com-orkut-in.txt.outr 
	diff test/com-orkut-in.txt.outr test/com-orkut-in.txt.out
CA:
	./par-ran-cc <test-real/roadNet-CA-in.txt >test/roadNet-CA-in.txt.outr 
	./par-det-cc <test-real/roadNet-CA-in.txt >test/roadNet-CA-in.txt.out 
	diff test/roadNet-CA-in.txt.out test/roadNet-CA-in.txt.outr
PA:
	./par-det-cc <test-real/roadNet-PA-in.txt >test/roadNet-PA-in.txt.out 
	./par-ran-cc <test-real/roadNet-PA-in.txt >test/roadNet-PA-in.txt.outr 
	diff test/roadNet-PA-in.txt.out test/roadNet-PA-in.txt.outr
TX:
	./par-det-cc <test-real/roadNet-TX-in.txt >test/roadNet-TX-in.txt.out 
	./par-ran-cc <test-real/roadNet-TX-in.txt >test/roadNet-TX-in.txt.outr 
	diff test/roadNet-TX-in.txt.out test/roadNet-TX-in.txt.outr

