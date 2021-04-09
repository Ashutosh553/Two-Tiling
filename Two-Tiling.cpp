/**
 *    author:  tourist
 *    created: 10.08.2018
**/
#undef _GLIBCXX_DEBUG

#include <bits/stdc++.h>

using namespace std;

class dsu {
  public:
  vector<int> p;
  int n;

  dsu(int _n) : n(_n) {
    p.resize(n);
    iota(p.begin(), p.end(), 0);
  }

  inline int get(int x) {
    return (x == p[x] ? x : (p[x] = get(p[x])));
  }

  inline bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x != y) {
      p[x] = y;
      return true;
    }
    return false;
  }
};

int main() {
//  ios::sync_with_stdio(false);
//  cin.tie(0);
  vector<int> alive(1 << 9, 0);
  vector<int> canonic(1 << 9, 0);
  dsu d(1 << 9);
  for (int mask = 1; mask < (1 << 9); mask++) {
    int grid[3][3];
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        grid[i][j] = (mask >> (3 * i + j)) & 1;
      }
    }
    dsu dg(9);
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 2; j++) {
        if (grid[i][j] + grid[i][j + 1] == 2) {
          dg.unite(3 * i + j, 3 * i + j + 1);
        }
        if (grid[j][i] + grid[j + 1][i] == 2) {
          dg.unite(3 * j + i, 3 * (j + 1) + i);
        }
      }
    }
    set<int> all;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (grid[i][j] == 1) {
          all.insert(dg.get(3 * i + j));
        }
      }
    }
    if (all.size() != 1) {
      continue;
    }
    alive[mask] = 1;
    if (grid[0][0] + grid[0][1] + grid[0][2] > 0) {
      if (grid[0][0] + grid[1][0] + grid[2][0] > 0) {
        canonic[mask] = 1;
      }
    }
    if (grid[0][0] + grid[0][1] + grid[0][2] == 0) {
      int new_mask = 0;
      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
          new_mask |= (grid[i + 1][j] << (3 * i + j));
        }
      }
      d.unite(mask, new_mask);
    }
    if (grid[2][0] + grid[2][1] + grid[2][2] == 0) {
      int new_mask = 0;
      for (int i = 1; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          new_mask |= (grid[i - 1][j] << (3 * i + j));
        }
      }
      d.unite(mask, new_mask);
    }
    if (grid[0][0] + grid[1][0] + grid[2][0] == 0) {
      int new_mask = 0;
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
          new_mask |= (grid[i][j + 1] << (3 * i + j));
        }
      }
      d.unite(mask, new_mask);
    }
    if (grid[0][2] + grid[1][2] + grid[2][2] == 0) {
      int new_mask = 0;
      for (int i = 0; i < 3; i++) {
        for (int j = 1; j < 3; j++) {
          new_mask |= (grid[i][j - 1] << (3 * i + j));
        }
      }
      d.unite(mask, new_mask);
    }
    // rotate left
    {
      int new_mask = 0;
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          new_mask |= (grid[j][2 - i] << (3 * i + j));
        }
      }
      d.unite(mask, new_mask);
    }
    // rotate right
    {
      int new_mask = 0;
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          new_mask |= (grid[2 - j][i] << (3 * i + j));
        }
      }
      d.unite(mask, new_mask);
    }
    // reflect
    {
      int new_mask = 0;
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          new_mask |= (grid[2 - i][j] << (3 * i + j));
        }
      }
      d.unite(mask, new_mask);
    }
    // transpose
    {
      int new_mask = 0;
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          new_mask |= (grid[j][i] << (3 * i + j));
        }
      }
      d.unite(mask, new_mask);
    }
  }
  vector<vector<int>> friends(1 << 9);
  for (int i = 0; i < (1 << 9); i++) {
    for (int j = 0; j < (1 << 9); j++) {
      if (canonic[j] && d.get(i) == d.get(j)) {
        friends[i].push_back(j);
      }
    }
  }
  vector<int> basic(1 << 9);
  for (int mask = 1; mask < (1 << 9); mask++) {
    basic[mask] = (canonic[mask] && friends[mask][0] == mask);
  }
  unsigned long long one = 1;
  int cc = 0;
  for (int m0 = (1 << 9) - 1; m0 >= 1; m0--) {
    if (basic[m0]) {
      cc++;
    }
  }
//  int counter = 0;
  const string let = "!?0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  vector<vector<vector<string>>> ret(1 << 9, vector<vector<string>>(1 << 9));

  vector<pair<int,int>> bad_pairs = {
  {511, 495}, {511, 383}, {511, 381}, {511, 367}, {511, 255}, {511, 254}, {511, 247}, {511, 239}, {511, 191}, {511, 189}, 
{511, 187}, {511, 186}, {511, 127}, {511, 126}, {511, 125}, {511, 124}, {511, 123}, {511, 122}, {511, 121}, {511, 111}, 
{511, 95}, {511, 94}, {511, 79}, {511, 47}, {511, 31}, {511, 30}, {511, 23}, {511, 15}, {495, 511}, {495, 383}, 
{495, 381}, {495, 367}, {495, 255}, {495, 254}, {495, 247}, {495, 239}, {495, 191}, {495, 189}, {495, 187}, {495, 186}, 
{495, 127}, {495, 126}, {495, 125}, {495, 124}, {495, 123}, {495, 122}, {495, 121}, {495, 95}, {495, 94}, {495, 79}, 
{495, 63}, {495, 47}, {495, 31}, {495, 30}, {495, 27}, {495, 23}, {495, 11}, {495, 7}, {383, 511}, {383, 495}, 
{383, 381}, {383, 367}, {383, 254}, {383, 247}, {383, 239}, {383, 191}, {383, 189}, {383, 187}, {383, 186}, {383, 127}, 
{383, 126}, {383, 125}, {383, 124}, {383, 123}, {383, 122}, {383, 121}, {383, 111}, {383, 95}, {383, 94}, {383, 79}, 
{383, 63}, {383, 47}, {383, 30}, {383, 27}, {381, 511}, {381, 495}, {381, 383}, {381, 367}, {381, 255}, {381, 254}, 
{381, 239}, {381, 191}, {381, 189}, {381, 187}, {381, 186}, {381, 127}, {381, 126}, {381, 125}, {381, 124}, {381, 123}, 
{381, 122}, {381, 121}, {381, 111}, {381, 95}, {381, 94}, {381, 79}, {381, 63}, {381, 47}, {381, 31}, {381, 30}, 
{381, 27}, {381, 23}, {381, 15}, {381, 7}, {367, 511}, {367, 495}, {367, 383}, {367, 381}, {367, 255}, {367, 254}, 
{367, 247}, {367, 191}, {367, 189}, {367, 187}, {367, 186}, {367, 126}, {367, 125}, {367, 124}, {367, 123}, {367, 122}, 
{367, 121}, {367, 111}, {367, 95}, {367, 94}, {367, 63}, {367, 31}, {367, 30}, {367, 27}, {367, 23}, {255, 511}, 
{255, 495}, {255, 381}, {255, 367}, {255, 254}, {255, 247}, {255, 239}, {255, 191}, {255, 189}, {255, 187}, {255, 186}, 
{255, 127}, {255, 125}, {255, 124}, {255, 122}, {255, 121}, {255, 95}, {255, 94}, {255, 79}, {255, 47}, {254, 511}, 
{254, 495}, {254, 383}, {254, 381}, {254, 367}, {254, 255}, {254, 239}, {254, 189}, {254, 187}, {254, 186}, {254, 125}, 
{254, 124}, {254, 123}, {254, 122}, {254, 121}, {254, 111}, {254, 95}, {254, 79}, {254, 63}, {254, 47}, {254, 30}, 
{254, 27}, {254, 23}, {254, 15}, {254, 7}, {247, 511}, {247, 495}, {247, 383}, {247, 367}, {247, 255}, {247, 239}, 
{247, 189}, {247, 187}, {247, 186}, {247, 124}, {247, 121}, {247, 111}, {247, 95}, {247, 79}, {247, 63}, {247, 27}, 
{247, 23}, {239, 511}, {239, 495}, {239, 383}, {239, 381}, {239, 255}, {239, 254}, {239, 247}, {239, 191}, {239, 189}, 
{239, 187}, {239, 186}, {239, 127}, {239, 126}, {239, 125}, {239, 124}, {239, 123}, {239, 122}, {239, 121}, {239, 111}, 
{239, 95}, {239, 94}, {239, 79}, {239, 63}, {239, 31}, {239, 30}, {239, 27}, {239, 23}, {239, 7}, {191, 511}, 
{191, 495}, {191, 383}, {191, 381}, {191, 367}, {191, 255}, {191, 239}, {191, 189}, {191, 187}, {191, 186}, {191, 125}, 
{191, 124}, {191, 121}, {191, 111}, {191, 95}, {191, 94}, {191, 79}, {191, 47}, {191, 27}, {189, 511}, {189, 495}, 
{189, 383}, {189, 381}, {189, 367}, {189, 255}, {189, 254}, {189, 247}, {189, 239}, {189, 191}, {189, 186}, {189, 127}, 
{189, 124}, {189, 121}, {189, 94}, {189, 79}, {189, 63}, {189, 47}, {189, 31}, {189, 27}, {187, 511}, {187, 495}, 
{187, 383}, {187, 381}, {187, 367}, {187, 255}, {187, 254}, {187, 247}, {187, 239}, {187, 191}, {187, 186}, {187, 127}, 
{187, 121}, {187, 111}, {187, 79}, {187, 47}, {187, 27}, {186, 511}, {186, 495}, {186, 383}, {186, 381}, {186, 367}, 
{186, 255}, {186, 254}, {186, 247}, {186, 239}, {186, 191}, {186, 189}, {186, 187}, {186, 127}, {186, 126}, {186, 125}, 
{186, 124}, {186, 123}, {186, 111}, {186, 95}, {186, 94}, {186, 79}, {186, 63}, {186, 47}, {186, 30}, {186, 27}, 
{186, 15}, {186, 7}, {127, 511}, {127, 495}, {127, 383}, {127, 381}, {127, 255}, {127, 239}, {127, 189}, {127, 187}, 
{127, 186}, {127, 125}, {127, 122}, {127, 111}, {127, 94}, {127, 47}, {126, 511}, {126, 495}, {126, 383}, {126, 381}, 
{126, 367}, {126, 239}, {126, 186}, {126, 121}, {126, 79}, {125, 511}, {125, 495}, {125, 383}, {125, 381}, {125, 367}, 
{125, 255}, {125, 254}, {125, 239}, {125, 191}, {125, 186}, {125, 127}, {125, 94}, {125, 79}, {125, 63}, {125, 27}, 
{124, 511}, {124, 495}, {124, 383}, {124, 381}, {124, 367}, {124, 255}, {124, 254}, {124, 247}, {124, 239}, {124, 191}, 
{124, 189}, {124, 186}, {124, 123}, {124, 111}, {124, 95}, {124, 63}, {123, 511}, {123, 495}, {123, 383}, {123, 381}, 
{123, 367}, {123, 254}, {123, 239}, {123, 186}, {123, 124}, {123, 79}, {123, 47}, {122, 511}, {122, 495}, {122, 383}, 
{122, 381}, {122, 367}, {122, 255}, {122, 254}, {122, 239}, {122, 127}, {122, 111}, {122, 95}, {122, 63}, {122, 27}, 
{121, 511}, {121, 495}, {121, 383}, {121, 381}, {121, 367}, {121, 255}, {121, 254}, {121, 247}, {121, 239}, {121, 191}, 
{121, 189}, {121, 187}, {121, 126}, {121, 111}, {121, 95}, {121, 94}, {121, 63}, {121, 30}, {121, 27}, {111, 511}, 
{111, 383}, {111, 381}, {111, 367}, {111, 254}, {111, 247}, {111, 239}, {111, 191}, {111, 187}, {111, 186}, {111, 127}, 
{111, 124}, {111, 122}, {111, 121}, {111, 94}, {95, 511}, {95, 495}, {95, 383}, {95, 381}, {95, 367}, {95, 255}, 
{95, 254}, {95, 247}, {95, 239}, {95, 191}, {95, 186}, {95, 124}, {95, 122}, {95, 121}, {95, 94}, {95, 79}, 
{95, 47}, {94, 511}, {94, 495}, {94, 383}, {94, 381}, {94, 367}, {94, 255}, {94, 239}, {94, 191}, {94, 189}, 
{94, 186}, {94, 127}, {94, 125}, {94, 121}, {94, 111}, {94, 95}, {94, 63}, {94, 27}, {79, 511}, {79, 495}, 
{79, 383}, {79, 381}, {79, 255}, {79, 254}, {79, 247}, {79, 239}, {79, 191}, {79, 189}, {79, 187}, {79, 186}, 
{79, 126}, {79, 125}, {79, 123}, {79, 95}, {79, 63}, {63, 495}, {63, 383}, {63, 381}, {63, 367}, {63, 254}, 
{63, 247}, {63, 239}, {63, 189}, {63, 186}, {63, 125}, {63, 124}, {63, 122}, {63, 121}, {63, 94}, {63, 79}, 
{63, 47}, {47, 511}, {47, 495}, {47, 383}, {47, 381}, {47, 255}, {47, 254}, {47, 191}, {47, 189}, {47, 187}, 
{47, 186}, {47, 127}, {47, 123}, {47, 95}, {47, 63}, {47, 27}, {31, 511}, {31, 495}, {31, 381}, {31, 367}, 
{31, 239}, {31, 189}, {30, 511}, {30, 495}, {30, 383}, {30, 381}, {30, 367}, {30, 254}, {30, 239}, {30, 186}, 
{30, 121}, {27, 495}, {27, 383}, {27, 381}, {27, 367}, {27, 254}, {27, 247}, {27, 239}, {27, 191}, {27, 189}, 
{27, 187}, {27, 186}, {27, 125}, {27, 122}, {27, 121}, {27, 94}, {27, 47}, {23, 511}, {23, 495}, {23, 381}, 
{23, 367}, {23, 254}, {23, 247}, {23, 239}, {15, 511}, {15, 381}, {15, 254}, {15, 186}, {11, 495}, {7, 495}, 
{7, 381}, {7, 254}, {7, 239}, {7, 186}};

  for (int m0 = (1 << 9) - 1; m0 >= 1; m0--) {
    if (basic[m0]) {
      for (int m1 = (1 << 9) - 1; m1 >= 1; m1--) {
        if (basic[m1]) {
          if (find(bad_pairs.begin(), bad_pairs.end(), make_pair(m0, m1)) != bad_pairs.end()) {
            continue;
          }
          if (m0 < m1) {
            ret[m0][m1] = ret[m1][m0];
            for (int i = 0; i < 8; i++) {
              for (int j = 0; j < 8; j++) {
                swap(ret[m0][m1][i][j], ret[m0][m1][i][j + 9]);
              }
            }
            continue;
          }
    /*      int grid[3][3];
          for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
              grid[i][j] = ;
            }
          }*/
    /*      for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
              cout << ((m0 >> (3 * i + j)) & 1);
            }
            cout << " ";
            for (int j = 0; j < 3; j++) {
              cout << ((m1 >> (3 * i + j)) & 1);
            }
            if (i < 2) cout << '\n'; else cout << " ";
          }
          fflush(stdout);*/
    //      vector<string> ret;
          bool found = false;
          int bg0[8][8], bg1[8][8];
          for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
              bg0[i][j] = bg1[i][j] = -1;
            }
          }
          function<void(int,int,int,unsigned long long,unsigned long long)> dfs = [&](int i, int j, int k, unsigned long long bm0, unsigned long long bm1) {
            if (found) {
              return;
            }
            if (bm0 == bm1 && bm0 != 0) {
              ret[m0][m1].assign(8, string(17, ' '));
              for (i = 0; i < 8; i++) {
                for (j = 0; j < 8; j++) {
                  ret[m0][m1][i][j] = (bg0[i][j] == -1 ? '.' : let[bg0[i][j]]);
                  ret[m0][m1][i][j + 9] = (bg1[i][j] == -1 ? '.' : let[bg1[i][j]]);
                }
              }
    //          cout << "found!" << '\n';
    //          for (int i = 0; i < 8; i++) {
    //            cout << ret[i] << '\n';
    //          }
              found = true;
              return;
            }
            if (i == 8) {
              return;
            }
            if (j == 8) {
              dfs(i + 1, 0, 0, bm0, bm1);
              return;
            }
            if (k == 0) {
              if ((bm0 & (one << (8 * i + j))) || !(bm1 & (one << (8 * i + j)))) {
                dfs(i, j, 1, bm0, bm1);
              }
              if (!(bm0 & (one << (8 * i + j)))) {
                for (int who : friends[m0]) {
                  int sj = 0;
                  while ((who & (1 << sj)) == 0) {
                    sj++;
                  }
                  int ok = 1;
                  long long new_bm0 = bm0;
                  for (int ii = 0; ii < 3; ii++) {
                    for (int jj = 0; jj < 3; jj++) {
                      if (who & (1 << (3 * ii + jj))) {
                        int ri = i + ii;
                        int rj = j + jj - sj;
                        if (ri < 0 || rj < 0 || ri >= 8 || rj >= 8) {
                          ok = 0;
                          break;
                        }
                        if (bm0 & (one << (8 * ri + rj))) {
                          ok = 0;
                          break;
                        }
                        new_bm0 |= (one << (8 * ri + rj));
                      }
                    }
                    if (!ok) break;
                  }
                  if (ok) {
                    for (int ii = 0; ii < 3; ii++) {
                      for (int jj = 0; jj < 3; jj++) {
                        if (who & (1 << (3 * ii + jj))) {
                          int ri = i + ii;
                          int rj = j + jj - sj;
                          bg0[ri][rj] = 8 * i + j;
                        }
                      }
                    }
                    dfs(i, j, 1, new_bm0, bm1);
                    for (int ii = 0; ii < 3; ii++) {
                      for (int jj = 0; jj < 3; jj++) {
                        if (who & (1 << (3 * ii + jj))) {
                          int ri = i + ii;
                          int rj = j + jj - sj;
                          bg0[ri][rj] = -1;
                        }
                      }
                    }
                  }
                }
              }
            } else {
              if ((bm0 & (one << (8 * i + j))) == (bm1 & (one << (8 * i + j)))) {
                dfs(i, j + 1, 0, bm0, bm1);
              }
              if ((bm0 & (one << (8 * i + j))) && !(bm1 & (one << (8 * i + j)))) {
                for (int who : friends[m1]) {
                  int sj = 0;
                  while ((who & (1 << sj)) == 0) {
                    sj++;
                  }
                  int ok = 1;
                  long long new_bm1 = bm1;
                  for (int ii = 0; ii < 3; ii++) {
                    for (int jj = 0; jj < 3; jj++) {
                      if (who & (1 << (3 * ii + jj))) {
                        int ri = i + ii;
                        int rj = j + jj - sj;
                        if (ri < 0 || rj < 0 || ri >= 8 || rj >= 8) {
                          ok = 0;
                          break;
                        }
                        if (bm1 & (one << (8 * ri + rj))) {
                          ok = 0;
                          break;
                        }
                        new_bm1 |= (one << (8 * ri + rj));
                      }
                    }
                    if (!ok) break;
                  }
                  if (ok) {
                    for (int ii = 0; ii < 3; ii++) {
                      for (int jj = 0; jj < 3; jj++) {
                        if (who & (1 << (3 * ii + jj))) {
                          int ri = i + ii;
                          int rj = j + jj - sj;
                          bg1[ri][rj] = 8 * i + j;
                        }
                      }
                    }
                    dfs(i, j + 1, 0, bm0, new_bm1);
                    for (int ii = 0; ii < 3; ii++) {
                      for (int jj = 0; jj < 3; jj++) {
                        if (who & (1 << (3 * ii + jj))) {
                          int ri = i + ii;
                          int rj = j + jj - sj;
                          bg1[ri][rj] = -1;
                        }
                      }
                    }
                  }
                }
              }
            }
          };
          dfs(0, 0, 0, 0, 0);
/*          if (!found) {
            cerr << "{" << m0 << ", " << m1 << "}, ";
            counter++;
            if (counter % 10 == 0) cerr << '\n';
          }*/
    //      if (!found) cout << "not found" << '\n';
//          cerr << found << " time = " << clock() << '\n';
        }
      }
    }
  }
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    cout << "Case #" << qq << ": ";
    vector<string> inp(6);
    for (int i = 0; i < 6; i++) {
      cin >> inp[i];
    }
    int m0 = 0, m1 = 0;
    for (int i = 0; i < 6; i++) {
      for (int j = 0; j < 3; j++) {
        if (inp[i][j] == '@') {
          if (i % 2 == 0) {
            m0 |= (1 << (3 * (i / 2) + j));
          } else {
            m1 |= (1 << (3 * (i / 2) + j));
          }
        }
      }
    }
    m0 = friends[m0][0];
    m1 = friends[m1][0];
    if (ret[m0][m1].empty()) {
      cout << "IMPOSSIBLE" << '\n';
    } else {
      cout << "POSSIBLE" << '\n';
      for (int i = 0; i < 8; i++) {
        cout << ret[m0][m1][i] << '\n';
      }
    }
  }
  return 0;
}