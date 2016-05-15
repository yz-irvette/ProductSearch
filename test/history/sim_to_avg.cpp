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
const char prod_file[10] = "phone";

std::string line;
//char st1s[prod_num][max_size], prod_name[prod_num][50];

int main(int argc, char **argv) {
  FILE *f;
  char prod_c[50000];
  std::vector<std::string> prods;
  int correct[N], total = 0, total_line = 0;
  char st1[100 * max_size];                       // words typed in for comparison, seperated by space
  char *bestw[N];                                 // closest words
  char file_name[max_size], st[100][max_size];    // file_name: vector.bin; st: splited input
  float dist, len, bestd[N], vec[max_size];       // bestd: distances of closest words
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
  for (int i = 0; i < N; i++) correct[i] = 0;
  vocab = (char *)malloc((long long)words * max_w * sizeof(char));
  for (a = 0; a < N; a++) bestw[a] = (char *)malloc(max_size * sizeof(char));
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
    for (a = 0; a < size; a++) fread(&M[a + b * size], sizeof(float), 1, f);
    len = 0;
    for (a = 0; a < size; a++) len += M[a + b * size] * M[a + b * size];
    len = sqrt(len);
    for (a = 0; a < size; a++) M[a + b * size] /= len;  // normalization
  }
  fclose(f);

  // read products
  f = fopen(prod_file, "r");
  while (f != NULL && !feof(f)) {
    fscanf(f, "%[^,]%*[^\n]\n", prod_c);
    std::string prod = std::string(prod_c);
    if (prod.find_first_of('\n') != -1) {
      prod = prod.substr(prod.find_first_of('\n') + 1);
    }
    // check product's validity
    for (b = 0; b < words; b++) {
      if (!strcmp(&vocab[b * max_w], prod.c_str())) {
        break;
      }
    }
    if (b != words) {
      prods.push_back(prod);
    }
  }
  fclose(f);

  srand((unsigned) time(NULL));
  while (std::getline(std::cin, line) > 0) {
    total_line++;
    printf("%d\n", total_line);
    //std::cout << line << std::endl;

    if (line.length() != 0 && (line[0] < '0' || line[0] > '9') || line.find_first_of(',') == -1) continue;
    std::string prod = line.substr(0, line.find_first_of(','));
    std::size_t len_in = line.copy(st1, 100 * max_size - 1, line.find_first_of(',') + 2);
    st1[len_in] = 0;

    // check product's validity
    for (b = 0; b < words; b++) {
      if (!strcmp(&vocab[b * max_w], prod.c_str())) {
        break;
      }
    }
    if (b == words) continue;
    //printf("%s\n", st1);
    /*fscanf(f, "%[^,], ", prod);
    fgets(st1, 200000, f);
    int len = strlen(st1);
    st1[len - 1] = 0;
    if(len == 200000) fscanf(f, "%*[^\n]\n");*/
    //printf("%s\n", st1);
    //printf("%s,1\n", prod);
    std::set<std::string> prods_test;
    prods_test.insert(prod);

    // generate negative test cases
    for (int i = 0; i < 500; i++) {
      int j = rand() % prods.size();
      while (prods_test.find(prods[j]) != prods_test.end()) {
        j = rand() % prods.size();
      }
      prods_test.insert(prods[j]);
    }

    for (a = 0; a < N; a++) bestd[a] = 0;
    for (a = 0; a < N; a++) bestw[a][0] = 0;

    // split input
    cn = 0;
    b = 0;
    c = 0;
    while (1) {
      st[cn][b] = st1[c];
      b++;
      c++;
      st[cn][b] = 0;
      if (st1[c] == 0) break;
      if (st1[c] == ' ') {
        if (cn == 99) break;
        cn++;
        b = 0;
        c++;
      }
    }
    cn++;
    // check input's validity
    bool all_invalid = true;
    for (a = 0; a < cn; a++) {
      for (b = 0; b < words; b++) if (!strcmp(&vocab[b * max_w], st[a])) break;
      if (b == words) b = -1;
      bi[a] = b;
      //printf("\nWord: %s  Position in vocabulary: %lld\n", st[a], bi[a]);
      //printf("%s ", st[a]);
      if (b != -1) {
        all_invalid = false;
      }
    }
    if (all_invalid) continue;

    //printf("\n                                              Word       Cosine distance\n------------------------------------------------------------------------\n");
    // calculate average
    for (a = 0; a < size; a++) vec[a] = 0;
    for (b = 0; b < cn; b++) {
      if (bi[b] == -1) continue;
      for (a = 0; a < size; a++) vec[a] += M[a + bi[b] * size];
    }
    len = 0;
    for (a = 0; a < size; a++) len += vec[a] * vec[a];
    len = sqrt(len);
    for (a = 0; a < size; a++) vec[a] /= len;
    // find the closest words
    for (a = 0; a < N; a++) bestd[a] = -1;
    for (a = 0; a < N; a++) bestw[a][0] = 0;
    for (c = 0; c < words; c++) {
      a = 0;
      // should be in the same category
      if (vocab[c * max_w] < '0' || vocab[c * max_w] > '9' 
          || prods_test.find(std::string(&vocab[c * max_w])) == prods_test.end()) continue;
      // should not be input words
      //for (b = 0; b < cn; b++) if (bi[b] == c) a = 1;
      //if (a == 1) continue;
      // cosine distance. the larger, the more similar.
      dist = 0;
      for (a = 0; a < size; a++) dist += vec[a] * M[a + c * size];
      // update bestd & bestw
      for (a = 0; a < N; a++) {
        if (dist > bestd[a]) {
          for (d = N - 1; d > a; d--) {
            bestd[d] = bestd[d - 1];
            strcpy(bestw[d], bestw[d - 1]);
          }
          bestd[a] = dist;
          strcpy(bestw[a], &vocab[c * max_w]);
          break;
        }
      }
    }

    for (a = 0; a < N; a++) {
      //printf("%s,%f\n", bestw[a], bestd[a]);
      if (!strcmp(bestw[a], prod.c_str())) {
        for (int i = a; i < N; i++) correct[i] ++;
      }
    }
    total ++;

    for (int i = 0; i < N; i++) printf("%d ", correct[i]);
    printf("%d\n", total);
  }
  fclose(f);
  return 0;
}