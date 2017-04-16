all: assign_vec assign_vec_rand

assign_vec: assign_vec.cpp
	g++ -O2 -o par-det-cc assign_vec.cpp -fcilkplus
assign_vec_rand: assign_vec_rand.cpp
	g++ -O2 -o par-ran-cc assign_vec_rand.cpp -fcilkplus

run:
	./par-det-cc <test/com-youtube-in.txt >test/temp-youtube.out
	diff test/com-youtube-out.txt test/temp-youtube.out
	./par-ran-cc <test/com-youtube-in.txt >test/temp-youtube.out
	diff test/com-youtube-out.txt test/temp-youtube.out
	rm test/temp-youtube.out
