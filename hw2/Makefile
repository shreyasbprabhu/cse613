all: assign_vec

assign_vec: assign_vec.cpp
	g++-5 -O3 -g -o par-det-cc assign_vec.cpp -fcilkplus
assign_vec_rand: assign_vec_rand.cpp
	g++-5 -O3 -o par-ran-cc assign_vec_rand.cpp -fcilkplus

run: det

det:
	./par-det-cc <test/com-youtube-in.txt >test/temp-youtube.out
	diff test/com-youtube-out.txt test/temp-youtube.out
	#./par-det-cc <test-real/as-skitter-in.txt >test/as-skitter-in.txt.out 
	#./par-det-cc <test-real/ca-AstroPh-in.txt >test/ca-AstroPh-in.txt.out 
	echo ./par-det-cc <test-real/com-amazon-in.txt >test/com-amazon-in.txt.out 
	#./par-det-cc <test-real/com-dblp-in.txt >test/com-dblp-in.txt.out 
	#./par-det-cc <test-real/com-friendster-in.txt >test/com-friendster-in.txt.out 
	#./par-det-cc <test-real/com-lj-in.txt >test/com-lj-in.txt.out 
	#./par-det-cc <test-real/com-orkut-in.txt >test/com-orkut-in.txt.out 
	#./par-det-cc <test-real/roadNet-CA-in.txt >test/roadNet-CA-in.txt.out 
	#./par-det-cc <test-real/roadNet-PA-in.txt >test/roadNet-PA-in.txt.out 
	#./par-det-cc <test-real/roadNet-TX-in.txt >test/roadNet-TX-in.txt.out 


rand:
	./par-ran-cc <test/com-youtube-in.txt >test/temp-youtube.out
	diff test/com-youtube-out.txt test/temp-youtube.out
	rm test/temp-youtube.out
	./par-ran-cc <test-real/as-skitter-in.txt >test/as-skitter-in.txt.out 
	./par-ran-cc <test-real/ca-AstroPh-in.txt >test/ca-AstroPh-in.txt.out 
	./par-ran-cc <test-real/com-amazon-in.txt >test/com-amazon-in.txt.out 
	./par-ran-cc <test-real/com-dblp-in.txt >test/com-dblp-in.txt.out 
	./par-ran-cc <test-real/com-friendster-in.txt >test/com-friendster-in.txt.out 
	./par-ran-cc <test-real/com-lj-in.txt >test/com-lj-in.txt.out 
	./par-ran-cc <test-real/com-orkut-in.txt >test/com-orkut-in.txt.out 
	./par-ran-cc <test-real/roadNet-CA-in.txt >test/roadNet-CA-in.txt.out 
	./par-ran-cc <test-real/roadNet-PA-in.txt >test/roadNet-PA-in.txt.out 
	./par-ran-cc <test-real/roadNet-TX-in.txt >test/roadNet-TX-in.txt.out 

