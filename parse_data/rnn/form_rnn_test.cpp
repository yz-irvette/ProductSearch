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
#include <map>
#include <set>
#include <string>
#include <vector>

#include "malloc.h"

const long long ratio_neg = 1;    // ratio of negative test cases and positive test cases
const char prod_file[10] = "../../data/phone";

std::string line;


int main(int argc, char **argv) {
  FILE *f;
  char prod_c[50000];
  std::map<std::string, int> prods;
  int prods_num, i;
  std::string prod, review;

  // read products
  f = fopen(prod_file, "r");
  while (f != NULL && !feof(f)) {
    fscanf(f, "%[^,]%*[^\n]\n", prod_c);
    std::string prod = std::string(prod_c);
    if (prod.find_first_of('\n') != -1) {
      prod = prod.substr(prod.find_first_of('\n') + 1);
    }
    prods[prod]++;
  }
  fclose(f);
  
  prods_num = prods.size();
  printf("Context,Ground Truth Utterance,Distractor_0,Distractor_1,Distractor_2,Distractor_3,Distractor_4,Distractor_5,Distractor_6,Distractor_7,Distractor_8\n");
  
  bool single = false;

  srand((unsigned) time(NULL));
  while (std::getline(std::cin, line) > 0) {
    if (line.length() != 0 && (line[0] < '0' || line[0] > '9') || line.find_first_of(',') == -1) continue;
    single = !single;
    if (single) continue;

    prod = line.substr(0, line.find_first_of(','));
    review = line.substr(line.find_first_of(',') + 2);
    printf("\"%s\",\"%s\"", review.c_str(), prod.c_str());

    for (i = 0; i < ratio_neg; i++) {
      std::map<std::string, int>::iterator it = prods.begin();
      advance(it, rand() % prods_num);
      bool conflict = (it->first) == prod;
      while (conflict) {
        std::map<std::string, int>::iterator it = prods.begin();
        advance(it, rand() % prods_num);
        conflict = (it->first) == prod;
      }
      printf(",\"%s\"", (it->first).c_str());
    }
    printf("\n");
  }
  return 0;
}