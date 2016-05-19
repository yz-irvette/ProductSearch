//  Copyright 2013 Google Inc. All Rights Reserved.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "malloc.h"

// film: 206 314 420 537 656 769 903 997 1102 1200 1301 1385 1462 1558 1654 1753 1846 1967 2076 2177 27144
// phone: 14 15 20 26 38 46 58 85 106 123 146 178 203 234 272 298 336 369 398 440 6479
// protect: 2867 5789 8501 11127 13370 15428 17350 19237 20987 22771
// 24457 26090 27798 29464 31144 32765 34530 36222 37895 39618 287456

const long long max_size = 2000;    // max length of strings
const long long N = 20;             // number of closest words that will be shown
const long long max_w = 50;         // max length of vocabulary entries
//const long long prod_num = 2337985; // bag: 319155, cloth: 265539, earphone: 540267, film: 723340,
                                    // laptop: 458501, phone: 2337985, protect: 1125198, 
                                    // shoe: 419339, skin: 1456281
const long long ratio_neg = 500;    // ratio of negative test cases and positive test cases
const char prod_file[10] = "pos_phone";

std::string line;
//char st1s[prod_num][max_size], prod_name[prod_num][50];

struct Closest {
  long long pos_;
  float cos_sim_;
  Closest() {
    pos_ = -1;
    cos_sim_ = 0;
  }
  Closest(const Closest& a) {
    pos_ = a.pos_;
    cos_sim_ = a.cos_sim_;
  }
  Closest(int pos, float cos_sim) {
    pos_ = pos;
    cos_sim_ = cos_sim;
  }
  bool operator < (const Closest &a) const {
    return cos_sim_ > a.cos_sim_;
  }
};

int main(int argc, char **argv) {
  FILE *f;
  char prod_c[50000];
  std::vector<long long> prods;
  std::vector<Closest> best(ratio_neg+1);
  int correct[N], total = 0, total_line = 0, i, prods_num, prod_pos;
  std::string prod;
  std::size_t len_in;
  char st1[100 * max_size];                       // words typed in for comparison, seperated by space
  char file_name[max_size], st[100][max_size];    // file_name: vector.bin; st: splited input
  float dist, len;
  long long words, size, a, b, c, d, cn, bi[100]; // size: size of each vectors; bi: positions of input words
                                                  // cn: number of input words
  char ch;
  float *M;                                       // vectors of each vocabulary entries
  char *vocab;                                    // vocabulary entries
  if (argc < 2) {
    printf("Usage: ./distance <FILE>\nwhere FILE contains word projections in the BINARY FORMAT\n");
    return 0;
  }
  strcpy(file_name, argv[1]);
  f = fopen(file_name, "rb");
  if (f == NULL) {
    printf("Input file not found\n");
    return -1;
  }
  fscanf(f, "%lld", &words);
  fscanf(f, "%lld", &size);
  // allocate memory
  for (i = 0; i < N; i++) correct[i] = 0;
  vocab = (char *)malloc((long long)words * max_w * sizeof(char));
  M = (float *)malloc((long long)words * (long long)size * sizeof(float));
  if (M == NULL) {
    printf("Cannot allocate memory: %lld MB    %lld  %lld\n", (long long)words * size * sizeof(float) / 1048576, words, size);
    return -1;
  }

  // read vector.bin
  for (b = 0; b < words; b++) {
    a = 0;
    while (1) {
      vocab[b * max_w + a] = fgetc(f);
      if (feof(f) || (vocab[b * max_w + a] == ' ')) break;
      if ((a < max_w) && (vocab[b * max_w + a] != '\n')) a++;
    }
    vocab[b * max_w + a] = 0;
    printf("%s", &vocab[b * max_w]);
    for (a = 0; a < size; a++) fread(&M[a + b * size], sizeof(float), 1, f);
    len = 0;
    for (a = 0; a < size; a++) len += M[a + b * size] * M[a + b * size];
    len = sqrt(len);
    for (a = 0; a < size; a++) {
    	M[a + b * size] /= len;  // normalization
    	printf(" %f", M[a + b * size]);
    }
    printf("\n");
  }
  fclose(f);
  return 0;
}