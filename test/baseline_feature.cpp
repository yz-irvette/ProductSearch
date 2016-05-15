#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

// film: 49326 93158 128680 157483 182619 203990 221459 236305 249583 262122
// 274095 285371 296363 306953 317207 327021 336160 345311 353860 362113 723340
// phone: 164802 266859 345853 410721 466312 515197 559664 600460 638301 673450
// 705800 736333 765301 792780 819008 844008 868008 890829 912893 933962 2337985
// protect: 105760 159990 193113 219563 243730 265766 285915 304003 320727 336030
// 350145 363130 375395 387084 398402 409023 419196 429192 438890 448249 1125198
// skin: 99653 175308 234571 285691 333035 377653 420124 461263 500618 538331 
// 573907 606729 636244 662207 685114 704888 722323 738157 752680 766347 1456281

const long long max_size = 2000;    // max length of strings
const int N = 20;

std::map<std::string, std::map<std::string, int> > fp_map;

int main() {
  std::string line, prod;
  char st1[100 * max_size], st[100][max_size];
  std::size_t len_in;
  int cn, b, c, i, j, score;
  bool conflict;
  std::map<std::string, std::map<std::string, int> >::iterator it;
  /*
  while (std::getline(std::cin, line) > 0) {
    if (line.length() != 0 && (line[0] < '0' || line[0] > '9') || line.find_first_of(',') == -1) continue;
    prod = line.substr(0, line.find_first_of(','));
    len_in = line.copy(st1, 100 * max_size - 1, line.find_first_of(',') + 2);
    st1[len_in] = 0;

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

    for (c = 0; c < cn; c++) {
      fp_map[std::string(st[c])][prod]++;
    }
  }

  for (std::map<std::string, std::map<std::string, int> >::iterator it = fp_map.begin();
      it != fp_map.end(); it++) {
    for (std::map<std::string, int>::iterator it2 = (it->second).begin();
        it2 != (it->second).end(); it2++) {
      printf("\"%s\",\"%s\",\"%d\"\n", (it->first).c_str(), (it2->first).c_str(), it2->second);
    }
  }
  */
  char feature_c[50], prod_c[50];
  int fp_num;
  FILE* f = fopen("fpmap_phone", "r");
  while (f != NULL && !feof(f)) {
    fscanf(f, "\"%[^\"]\",\"%[^\"]\",\"%d\"\n", feature_c, prod_c, &fp_num);
    fp_map[std::string(prod_c)][std::string(feature_c)] = fp_num;
  }
  fclose(f);

  int total = 0, correct[N], bestn[N];
  std::string bestw[N];
  for (i = 0; i < N; i++) {
    correct[i] = 0;
  }
  srand((unsigned) time(NULL));
  // read data
  while (std::getline(std::cin, line) > 0) {
    if (line.length() != 0 && (line[0] < '0' || line[0] > '9') || line.find_first_of(',') == -1) continue;
    prod = line.substr(0, line.find_first_of(','));
    len_in = line.copy(st1, 100 * max_size - 1, line.find_first_of(',') + 2);
    st1[len_in] = 0;

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

    for (i = 0; i < N; i++) {
      bestn[i] = 0;
    }

    score = 0;
    for (c = 0; c < cn; c++) {
      score += fp_map[prod][std::string(st[c])];
    }
    for (i = 0; i < N; i++) {
      if (score > bestn[i]) {
        for (j = N - 1; j > i; j--) {
          bestw[j] = bestw[j-1];
          bestn[j] = bestn[j-1];
        }
        bestw[i] = prod;
        bestn[i] = score;
        break;
      }
    }

    // generate negative test cases
    for (b = 0; b < 500; b++) {
      it = fp_map.begin();
      advance(it, rand() % fp_map.size());
      conflict = (it->first == prod);
      while (conflict) {
        it = fp_map.begin();
        advance(it, rand() % fp_map.size());
        conflict = (it->first == prod);
      }

      score = 0;
      for (c = 0; c < cn; c++) {
        score += (it->second)[std::string(st[c])];
      }
      for (i = 0; i < N; i++) {
        if (score > bestn[i]) {
          for (j = N - 1; j > i; j--) {
            bestw[j] = bestw[j-1];
            bestn[j] = bestn[j-1];
          }
          bestw[i] = it->first;
          bestn[i] = score;
          break;
        }
      }
    }

    for (i = 0; i < N; i++) {
      //printf("%s,%f\n", bestw[a], bestd[a]);
      if (bestw[i] == prod) {
        for (j = i; j < N; j++) {
          correct[j] ++;
        }
      }
    }
    total ++;

    for (i = 0; i < N; i++) {
      printf("%d ", correct[i]);
    }
    printf("%d\n", total);    
  }
  return 0;
}
