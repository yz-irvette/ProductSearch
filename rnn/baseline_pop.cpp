#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
// phone: 1193863 / 2337985

const int N = 1;

int main() {
  // count review number of each product
  FILE* f = fopen("phone", "r");
  char prod[50000];
  std::map<std::string, int> prods;
  while (f != NULL && !feof(f)) {
    fscanf(f, "%[^,]%*[^\n]\n", prod);
  //std::string line;
  //while (fp != NULL && !feof(fp)) {
    // input
  //while (std::getline(std::cin, line)) {
    //if (line[1] >= '0' && line[1] <= '9' && line.find_first_of(',') != -1) {
      //prods[line.substr(1, line.find_first_of(',')-2)] ++;
    std::string prod_str = std::string(prod);
    if (prod_str.find_first_of('\n') != -1) {
      prod_str = prod_str.substr(prod_str.find_first_of('\n') + 1);
    }
    prods[prod_str] ++;
    //}
  }
  fclose(f);
  
  int total = 0, correct[N], bestn[N];
  std::string bestw[N];
  for (int i = 0; i < N; i++) {
    correct[i] = 0;
  }
  f = fopen("phone", "r");
  srand((unsigned) time(NULL));

  // read data
  while (f != NULL && !feof(f)) {
    fscanf(f, "%[^,]%*[^\n]\n", prod);

    std::string prod_str = std::string(prod);
    if (prod_str.find_first_of('\n') != -1) {
      prod_str = prod_str.substr(prod_str.find_first_of('\n') + 1);
    }

    std::set<std::string> prods_test;
    prods_test.insert(prod_str);
    // generate negative test cases
    for (int i = 0; i < 9; i++) {
      std::map<std::string, int>::iterator it = prods.begin();
      advance(it, rand() % prods.size());
      while (prods_test.find(it->first) != prods_test.end()) {
        it = prods.begin();
        advance(it, rand() % prods.size());
      }
      prods_test.insert(it->first);
    }

    // best
    for (int i = 0; i < N; i++) {
      bestn[i] = 0;
    }
    for (std::set<std::string>::iterator p = prods_test.begin(); p != prods_test.end(); p++) {
      std::map<std::string, int>::iterator p1 = prods.find(*p);
      for (int i = 0; i < N; i++) {
        if (p1->second > bestn[i]) {
          for (int j = N - 1; j > i; j--) {
            bestw[j] = bestw[j-1];
            bestn[j] = bestn[j-1];
          }
          bestw[i] = p1->first;
          bestn[i] = p1->second;
          break;
        }
      }
    }

    for (int i = 0; i < N; i++) {
      //printf("%s,%f\n", bestw[a], bestd[a]);
      if (bestw[i] == prod_str) {
        for (int j = i; j < N; j++) {
          correct[j] ++;
        }
      }
    }
    total ++;
  }
  fclose(f);
  
  for (int i = 0; i < N; i++) {
    printf("%d ", correct[i]);
  }
  printf("%d\n", total);
  
  //std::string line;
  //std::string bestw[N] = {"302887","302886","410672","257488","410671","499505","311349","339244","765798","519685","538922","405452","405453","583760","585087","585066","409516","260827","721049","316901"};
  //while (std::getline(std::cin, line)) {
  /*
    if (line[0] >= '0' && line[0] <= '9' && line.find_first_of(',') != -1) {
      std::string prod = line.substr(0, line.find_first_of(','));
      for (int i = 0; i < N; i++) {
        if (bestw[i] == prod) {
          correct++;
        }
      }
      total++;
    }
    */
  //}
  //printf("%f\n", ((float) correct) / total);
  return 0;
}
