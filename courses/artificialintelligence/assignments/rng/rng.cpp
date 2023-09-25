// add your imports here
#include <cstdint>
#include <iostream>

using namespace std;

int main() {
  uint32_t seed, numOutputs;
  int32_t min, max;

  cin >> seed >> numOutputs >> min >> max;

  for (int i = 0; i < numOutputs; i++) {
    seed ^= seed << 13;
    seed ^= seed >> 17;
    seed ^= seed << 5;

    cout << min + seed % (max - min + 1) << endl;
  }


  return 0;
}