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

const long long max_size = 2000;    // max length of strings
const long long N = 3;             // number of closest words that will be shown
const long long max_w = 50;         // max length of vocabulary entries

int main(int argc, char **argv) {
  FILE *f;
  char *bestw[N];                                 // closest words
  char file_name[max_size];                       // file_name: vector.bin
  float dist, len, bestd[N], vec[max_size];       // bestd: distances of closest words
  long long words, size, a, b, c, d;              // size: size of each vectors
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

  for (int i = 0; i < words; i++) {

    if (!strcmp(&vocab[i * max_w], "</s>") || vocab[i * max_w] >= '0' && vocab[i * max_w] <= '9') continue;

    // find the closest words
    for (a = 0; a < N; a++) bestd[a] = -1;
    for (a = 0; a < N; a++) bestw[a][0] = 0;
    for (c = 0; c < words; c++) {
      if (c == i || vocab[c * max_w] >= '0' && vocab[c * max_w] <= '9') continue;
      dist = 0;
      for (a = 0; a < size; a++) dist += M[a + i * size] * M[a + c * size];
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
      printf("\"%s\",\"%s\"\n", &vocab[i * max_w], bestw[a]);
    }
  }
  return 0;
}