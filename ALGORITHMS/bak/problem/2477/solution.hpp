#ifndef SOLUTION
#define SOLUTION
inline int max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}
inline int solution(int const sides[6], int const directions[6], int fruits) {
  int max_hori = -1;
  int max_vert = -1;
  int concave1 = -1;
  int concave2 = -1;

  for (int idx = 0; idx < 6; ++idx) {
    int side = sides[idx];
    int dir = directions[idx];
    if (directions[idx] == directions[(idx + 2) % 6] &&
        directions[(idx + 1) % 6] == directions[(idx + 3) % 6]) {
      concave1 = sides[(idx + 1) % 6];
      concave2 = sides[(idx + 2) % 6];
    }
    switch (dir) {
    case 1: // intentional fallthrough
    case 2: {
      max_hori = max(max_hori, side);
      break;
    }
    case 3: // intentional fallthrough
    case 4: {
      max_vert = max(max_vert, side);
      break;
    }
    default:
      return -1;
    }
  }

  return fruits * ((max_hori * max_vert) - (concave1 * concave2));
}
#endif