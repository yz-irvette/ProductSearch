make
time ./word2vec -train ../data/vector/text -output ../data/vector/vectors.bin -cbow 0 -size 200 -window 10 -negative 25 -hs 0 -sample 1e-4 -threads 20 -binary 1 -iter 15
