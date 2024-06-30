// // from the V4 software
// const int _p_nozzleTableAddresses[300] =
// {//0                                     +10                                     +20                                     +30
//   6, 12, 9, 1, 12, 16, 1, 7, 16, 2,
//   7, 13, 2, 19, 13, 5, 19, 18, 5, 3,
//   18, 11, 3, 14, 11, 17, 14, 4, 17, 20,
//   4, 8, 20, 15, 8, 10, 16, 21, 10, 0,
//   21, 6, 0, 17, 6, 12, 9, 1, 12, 16,
//   1, 7, 16, 2, 7, 13, 2, 19, 13, 5,
//   19, 18, 5, 3, 18, 11, 3, 14, 11, 17,
//   14, 4, 17, 20, 4, 8, 20, 15, 8, 10,
//   15, 21, 10, 0, 21, 6, 0, 9, 6, 12,
//   9, 1, 12, 16, 1, 7, 16, 2, 7, 13,
//   2, 19, 13, 5, 19, 18, 5, 3, 18, 11,
//   3, 14, 11, 17, 14, 4, 17, 20, 4, 8,
//   20, 15, 8, 10, 15, 21, 10, 0, 21, 6,
//   0, 9, 6, 12, 9, 1, 12, 16, 1, 7,
//   16, 2, 7, 13, 2, 19, 13, 5, 19, 18,
//   5, 3, 18, 11, 3, 14, 11, 17, 14, 4,
//   17, 20, 4, 8, 20, 15, 8, 10, 15, 21,
//   6, 0, 9, 6, 0, 9, 6, 12, 9, 1,
//   12, 16, 1, 7, 18, 2, 7, 13, 2, 19,
//   13, 5, 19, 18, 5, 3, 18, 11, 3, 14,
//   11, 17, 14, 4, 17, 20, 4, 8, 20, 15,
//   8, 10, 15, 21, 10, 0, 21, 6, 0, 9,
//   6, 12, 9, 1, 12, 16, 1, 7, 16, 2,
//   7, 13, 2, 19, 13, 5, 19, 18, 5, 3,
//   18, 11, 3, 10, 11, 17, 14, 4, 17, 20,
//   4, 8, 20, 15, 8, 10, 15, 21, 10, 0,
//   21, 6, 0, 9, 6, 12, 9, 1, 12, 16,
//   1, 7, 16, 2, 7, 13, 2, 19, 13, 5,
//   19, 18, 5, 3, 18, 11, 3, 14, 11, 17,
//   14, 4, 17, 20, 4, 8, 20, 15, 8, 20
// };
// const int _p_nozzleTablePrimitives[300] =
// {//0                                     +10                                     +20                                     +30
//   3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 3, 1,
//   3, 1, 3, 1, 3, 1, 3, 1, 3, 1, 11, 2, 11, 2, 11, 2, 11, 2, 11, 2, 11, 2, 11, 2, 11, 2, 11, 2, 11, 2,
//   11, 2, 11, 2, 11, 2, 11, 2, 11, 2, 11, 2, 11, 2, 11, 2, 11, 2, 11, 2, 11, 2, 11, 2, 10, 8, 10, 8, 10, 8,
//   10, 8, 10, 8, 10, 8, 10, 8, 10, 8, 10, 8, 10, 8, 10, 8, 10, 8, 10, 8, 10, 8, 10, 8, 10, 8, 10, 8, 10, 8,
//   10, 8, 10, 8, 10, 8, 10, 8, 12, 5, 12, 5, 12, 5, 12, 5, 12, 5, 12, 5, 12, 5, 12, 5, 12, 5, 12, 5, 12, 5,
//   12, 5, 12, 5, 12, 5, 12, 5, 12, 5, 12, 5, 12, 5, 12, 5, 12, 5, 12, 5, 12, 5, 7, 9, 7, 9, 7, 9, 7, 9,
//   7, 9, 7, 9, 7, 9, 7, 9, 7, 9, 7, 9, 7, 9, 7, 9, 7, 9, 7, 9, 7, 9, 7, 9, 7, 9, 7, 9, 7, 9,
//   7, 9, 7, 9, 7, 9, 6, 0, 6, 0, 6, 0, 6, 0, 6, 0, 6, 0, 6, 0, 6, 0, 6, 0, 6, 0, 6, 0, 6, 0,
//   6, 0, 6, 0, 6, 0, 6, 0, 6, 0, 6, 0, 6, 0, 6, 0, 6, 0, 6, 0, 4, 13, 4, 13, 4, 13, 4, 13, 4, 13,
//   4, 13, 4, 13, 4, 13, 4, 13, 4, 13, 4, 13, 4, 13, 4, 13, 4, 13, 4, 13, 4, 13, 4, 13, 4, 13, 4, 13, 4, 13
// };



// // Fixed (???) nozzle tables
// const int _p_nozzleTablePrimitives[300] =
// {//0                                     +10                                     +20                                     +30
//    0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1, //   0 - 29
//    0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3, //  30 - 59
//    2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  4,  5,  4,  5,  4,  5, //  60 - 89
//    4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5, //  90 - 119
//    4,  5,  4,  5,  4,  5,  4,  5,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7, // 120 - 149
//    6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  8,  9,  8,  9,  8,  9,  8,  9, // 150 - 179
//    8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9, // 180 - 209
//    8,  9,  8,  9,  8,  9, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, // 210 - 239
//   10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, // 240 - 269
//   12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13  // 270 - 299
// };

// const int _p_nozzleTableAddresses[300] =
// {//0                                     +10                                     +20                                     +30
//   21, 16,  5, 19, 16, 10, 19,  8, 10, 14,  8,  6, 14,  4,  6, 18,  4,  7, 18, 12,  7, 17, 12,  2, 17,  1,  2, 13,  1, 11, //   0 - 29
//   13, 15, 11, 20, 15,  3, 10,  0,  3,  9,  0, 21,  9,  1, 21, 16,  5, 19, 16, 10, 19,  8, 10, 14,  8,  6, 14,  4,  6, 18, //  30 - 59
//    4,  7, 18, 12,  7, 17, 12,  2, 17,  1,  2, 13,  1, 11, 13, 15, 11, 20, 15,  3, 20,  0,  3,  9,  0, 21,  9,  5, 21, 16, //  60 - 89
//    5, 19, 16, 10, 19,  8, 10, 14,  8,  6, 14,  4,  6, 18,  4,  7, 18, 12,  7, 17, 12,  2, 17,  1,  2, 13,  1, 11, 13, 15, //  90 - 119
//   11, 20, 15,  3, 20,  0,  3,  9,  0, 21,  9,  5, 21, 16,  5, 19, 16, 10, 19,  8, 10, 14,  8,  6, 14,  4,  6, 18,  4,  7, // 120 - 149
//   18, 12,  7, 17, 12,  2, 17,  1,  2, 13,  1, 11, 13, 15, 11, 20, 15,  3, 20,  0, 21,  9,  5, 21,  9,  5, 21, 16,  5, 19, // 150 - 179
//   16, 10, 19,  8,  7, 14,  8,  6, 14,  4,  6, 18,  4,  7, 18, 12,  7, 17, 12,  2, 17,  1,  2, 13,  1, 11, 13, 15, 11, 20, // 180 - 209
//   15,  3, 20,  0,  3,  9,  0, 21,  9,  5, 21, 16,  5, 19, 16, 10, 19,  8, 10, 14,  8,  6, 14,  4,  6, 18,  4,  7, 18, 12, // 210 - 239
//    7, 17, 12,  3, 17,  1,  2, 13,  1, 11, 13, 15, 11, 20, 15,  3, 20,  0,  3,  9,  0, 21,  9,  5, 21, 16,  5, 19, 16, 10, // 240 - 269
//   19,  8, 10, 14,  8,  6, 14,  4,  6, 18,  4,  7, 18, 12,  7, 17, 12,  2, 17,  1,  2, 13,  1, 11, 13, 15, 11, 20, 15, 11  // 270 - 299
// };

// const int _p_nozzleTableAddresses[300] =
// {//0                                     +10                                     +20                                     +30
//    0,  8, 15,  1,  8, 16,  1,  9, 16,  2,  9, 17,  2, 10, 17,  3, 10, 18,  3, 11, 18,  4, 11, 19,  4, 12, 19,  5, 12, 20, //   0 - 29
//    5, 13, 20,  6, 13, 21, 16, 14, 21,  7, 14,  0,  7, 12,  0,  8, 15,  1,  8, 16,  1,  9, 16,  2,  9, 17,  2, 10, 17,  3, //  30 - 59
//   10, 18,  3, 11, 18,  4, 11, 19,  4, 12, 19,  5, 12, 20,  5, 13, 20,  6, 13, 21,  6, 14, 21,  7, 14,  0,  7, 15,  0,  8, //  60 - 89
//   15,  1,  8, 16,  1,  9, 16,  2,  9, 17,  2, 10, 17,  3, 10, 18,  3, 11, 18,  4, 11, 19,  4, 12, 19,  5, 12, 20,  5, 13, //  90 - 119
//   20,  6, 13, 21,  6, 14, 21,  7, 14,  0,  7, 15,  0,  8, 15,  1,  8, 16,  1,  9, 16,  2,  9, 17,  2, 10, 17,  3, 10, 18, // 120 - 149
//    3, 11, 18,  4, 11, 19,  4, 12, 19,  5, 12, 20,  5, 13, 20,  6, 13, 21,  6, 14,  0,  7, 15,  0,  7, 15,  0,  8, 15,  1, // 150 - 179
//    8, 16,  1,  9, 18,  2,  9, 17,  2, 10, 17,  3, 10, 18,  3, 11, 18,  4, 11, 19,  4, 12, 19,  5, 12, 20,  5, 13, 20,  6, // 180 - 209
//   13, 21,  6, 14, 21,  7, 14,  0,  7, 15,  0,  8, 15,  1,  8, 16,  1,  9, 16,  2,  9, 17,  2, 10, 17,  3, 10, 18,  3, 11, // 210 - 239
//   18,  4, 11, 21,  4, 12, 19,  5, 12, 20,  5, 13, 20,  6, 13, 21,  6, 14, 21,  7, 14,  0,  7, 15,  0,  8, 15,  1,  8, 16, // 240 - 269
//    1,  9, 16,  2,  9, 17,  2, 10, 17,  3, 10, 18,  3, 11, 18,  4, 11, 19,  4, 12, 19,  5, 12, 20,  5, 13, 20,  6, 13, 20  // 270 - 299
// };
// const int _p_nozzleTablePrimitives[300] =
// {//0                                     +10                                     +20                                     +30
//    0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1, //   0 - 29
//    0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3, //  30 - 59
//    2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  4,  5,  4,  5,  4,  5, //  60 - 89
//    4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5, //  90 - 119
//    4,  5,  4,  5,  4,  5,  4,  5,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7, // 120 - 149
//    6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  8,  9,  8,  9,  8,  9,  8,  9, // 150 - 179
//    8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9, // 180 - 209
//    8,  9,  8,  9,  8,  9, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, // 210 - 239
//   10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, // 240 - 269
//   12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13  // 270 - 299
// };

// old nozzle tables

const int _p_nozzleTableAddresses[300] =
{//0                                     +10                                     +20                                     +30
  21, 16,  5, 19, 16, 10, 19,  8, 10, 14,  8,  6, 14,  4,  6, 18,  4,  7, 18, 12,  7, 17, 12,  2, 17,  1,  2, 13,  1, 11, //   0 - 29
  13, 15, 11, 20, 15,  3, 10,  0,  3,  9,  0, 21,  9,  1, 21, 16,  5, 19, 16, 10, 19,  8, 10, 14,  8,  6, 14,  4,  6, 18, //  30 - 59
   4,  7, 18, 12,  7, 17, 12,  2, 17,  1,  2, 13,  1, 11, 13, 15, 11, 20, 15,  3, 20,  0,  3,  9,  0, 21,  9,  5, 21, 16, //  60 - 89
   5, 19, 16, 10, 19,  8, 10, 14,  8,  6, 14,  4,  6, 18,  4,  7, 18, 12,  7, 17, 12,  2, 17,  1,  2, 13,  1, 11, 13, 15, //  90 - 119
  11, 20, 15,  3, 20,  0,  3,  9,  0, 21,  9,  5, 21, 16,  5, 19, 16, 10, 19,  8, 10, 14,  8,  6, 14,  4,  6, 18,  4,  7, // 120 - 149
  18, 12,  7, 17, 12,  2, 17,  1,  2, 13,  1, 11, 13, 15, 11, 20, 15,  3, 20,  0, 21,  9,  5, 21,  9,  5, 21, 16,  5, 19, // 150 - 179
  16, 10, 19,  8,  7, 14,  8,  6, 14,  4,  6, 18,  4,  7, 18, 12,  7, 17, 12,  2, 17,  1,  2, 13,  1, 11, 13, 15, 11, 20, // 180 - 209
  15,  3, 20,  0,  3,  9,  0, 21,  9,  5, 21, 16,  5, 19, 16, 10, 19,  8, 10, 14,  8,  6, 14,  4,  6, 18,  4,  7, 18, 12, // 210 - 239
   7, 17, 12,  3, 17,  1,  2, 13,  1, 11, 13, 15, 11, 20, 15,  3, 20,  0,  3,  9,  0, 21,  9,  5, 21, 16,  5, 19, 16, 10, // 240 - 269
  19,  8, 10, 14,  8,  6, 14,  4,  6, 18,  4,  7, 18, 12,  7, 17, 12,  2, 17,  1,  2, 13,  1, 11, 13, 15, 11, 20, 15, 11  // 270 - 299

//  //0                                     +10                                     +20                                     +30
//   21, 19,  5, 10, 16,  8, 19, 14, 10,  6,  8,  4, 14, 18,  6,  7,  4, 12, 18, 17,  7,  2, 12,  1, 17, 13,  2, 11,  1, 15, //   0 - 29
//   13, 20, 11,  3, 15,  0, 10,  9,  3, 16,  0, 21,  9,  1, 21, 16,  5, 19, 16, 10, 19,  8, 10, 14,  8,  6, 14,  4,  6, 18, //  30 - 59
//    4,  7, 18, 12,  7, 17, 12,  2, 17,  1,  2, 13,  1, 11, 13, 15, 11, 20, 15,  3, 20,  0,  3,  9,  0, 21,  9,  5, 21, 16, //  60 - 89
//    5, 19, 16, 10, 19,  8, 10, 14,  8,  6, 14,  4,  6, 18,  4,  7, 18, 12,  7, 17, 12,  2, 17,  1,  2, 13,  1, 11, 13, 15, //  90 - 119
//   11, 20, 15,  3, 20,  0,  3,  9,  0, 21,  9,  5, 21, 16,  5, 19, 16, 10, 19,  8, 10, 14,  8,  6, 14,  4,  6, 18,  4,  7, // 120 - 149
//   18, 12,  7, 17, 12,  2, 17,  1,  2, 13,  1, 11, 13, 15, 11, 20, 15,  3, 20,  0, 21,  9,  5, 21,  9,  5, 21, 16,  5, 19, // 150 - 179
//   16, 10, 19,  8,  7, 14,  8,  6, 14,  4,  6, 18,  4,  7, 18, 12,  7, 17, 12,  2, 17,  1,  2, 13,  1, 11, 13, 15, 11, 20, // 180 - 209
//   15,  3, 20,  0,  3,  9,  0, 21,  9,  5, 21, 16,  5, 19, 16, 10, 19,  8, 10, 14,  8,  6, 14,  4,  6, 18,  4,  7, 18, 12, // 210 - 239
//    7, 17, 12,  3, 17,  1,  2, 13,  1, 11, 13, 15, 11, 20, 15,  3, 20,  0,  3,  9,  0, 21,  9,  5, 21, 16,  5, 19, 16, 10, // 240 - 269
//   19,  8, 10, 14,  8,  6, 14,  4,  6, 18,  4,  7, 18, 12,  7, 17, 12,  2, 17,  1,  2, 13,  1, 11, 13, 15, 11, 20, 15, 11  // 270 - 299
};

const int _p_nozzleTablePrimitives[300] =
{//0                                     +10                                     +20
   0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  0,  1, //   0 - 29
   0,  1,  0,  1,  0,  1,  0,  1,  0,  1,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3, //  30 - 59
   2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  2,  3,  4,  5,  4,  5,  4,  5, //  60 - 89
   4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5,  4,  5, //  90 - 119
   4,  5,  4,  5,  4,  5,  4,  5,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7, // 120 - 149
   6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  6,  7,  8,  9,  8,  9,  8,  9,  8,  9, // 150 - 179
   8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9,  8,  9, // 180 - 209
   8,  9,  8,  9,  8,  9, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, // 210 - 239
  10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, // 240 - 269
  12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13, 12, 13  // 270 - 299
};

int** _pp_nozzleReverseLookup;

void nozzleLookupInit()
{

  // Serial.println( "nozzleLookupInit()" );
  int ppIntAlloc = sizeof(int*) * PRIMITIVE_COUNT;
  _pp_nozzleReverseLookup = (int**) malloc( ppIntAlloc );
  allocTracker( ppIntAlloc );
  
  // int nozzleNumber;
  for( int p = 0; p < PRIMITIVE_COUNT; p++ )
  {
    // Serial.print( "\tp:  " );
    // Serial.println( p );
    int pIntAlloc = sizeof( int* ) * ADDRESS_COUNT;
    _pp_nozzleReverseLookup[p] = (int*) malloc( pIntAlloc );
    allocTracker( pIntAlloc );
    for( int a = 0; a < ADDRESS_COUNT; a++ )
    {
      // nozzleNumber = nozzleLookup( a, p );
      _pp_nozzleReverseLookup[p][a] = nozzleLookup( a, p );
      // nozzleNumber = 0; // testing only!
      // Serial.print( "\t\ta:  " );
      // Serial.print( a );
      // Serial.print( " \t# " );
      // Serial.println( _pp_nozzleReverseLookup[p][a], DEC );
    }
  }

  if( confirmNozzleTableLookup() )
  {
    // Serial.println( "Nozzle Table Reverse Lookup has passed" );
  }
  else
  {
    Serial.println( "Nozzle Table Reverse Lookup has failed" );
  }
}

void auditNozzleLookup()
{
  Serial.println( "auditNozzleLookup()" );
  int nozzleNumber;
  for( int p = 0; p < PRIMITIVE_COUNT; p++ )
  {
    for( int a = 0; a < ADDRESS_COUNT; a++ )
    {
      Serial.print( "\tp:  ");
      Serial.print( p );
      Serial.print( "\ta:  " );
      Serial.print( a );
      Serial.print( "\tnozzle:  " );
      Serial.print( nozzleNumber = _pp_nozzleReverseLookup[p][a] );
      if( nozzleNumber < 0 )
      {
        Serial.println("");
        continue;
      }
      Serial.print( "\tBuffer Byte:  " );
      Serial.print( nozzleNumber / 6 );
      if( (nozzleNumber / 6) < 10 )
      {
        Serial.print( " " );
      }
      Serial.print( "\tBit shamt:  " );
      Serial.println( nozzleNumber % 6 );

    }
  }
}

bool confirmNozzleTableLookup()
{
  // Serial.println( "confirmNozzleTableLookup()" );
  int nozzleNumber;
  char fetchedAddress, fetchedPrimitive;
  for( int a = 0; a < ADDRESS_COUNT; a++ )
  {
    for( int p = 0; p < PRIMITIVE_COUNT; p++ )
    {
      // Serial.print( "\ta:  " );
      // Serial.print( a );
      // Serial.print( "\tp:  ");
      // Serial.print( p );

      nozzleNumber = getNozzleNumber( a, p );

      // Serial.print( "\t# " );
      // Serial.print( nozzleNumber );

      if( nozzleNumber < 0 )
      {
        // Serial.println( "\tno nozzle corresponds to this address and primitive, no evaluation necessary" );
        continue;
      }

      fetchedAddress = addressLookup( nozzleNumber );
      fetchedPrimitive = primitiveLookup( nozzleNumber );

      // Serial.print( "\tfetchedAddress:  " );
      // Serial.print( fetchedAddress, DEC );
      // Serial.print( "\tfetchedPrimitive:  " );
      // Serial.print( fetchedPrimitive, DEC );
      
      if( fetchedAddress != a || fetchedPrimitive != p )
      {
        // Serial.println( "\tmismatch found" );
        return false;
      }
      // else
      // {
      //   Serial.println( "\tmatch" );
      // }
    }
  }
  return true;
}

bool isValidNozzleNumber( int nozzleNumber )
{
  return nozzleNumber >= 0 && nozzleNumber < NOZZLE_COUNT;
}
bool isValidAddress( int address )
{
  return address >= 0 && address < ADDRESS_COUNT;
}
bool isValidPrimitive( int primitive )  // don't forget that not every address has a primitive associated with it, so this will need refinement later on
{
  return primitive >= 0 && primitive < PRIMITIVE_COUNT;
}
int addressLookup( int nozzleNumber )
{
  // Serial.println( "" );
  // Serial.print( "addressLookup( " );
  // Serial.print( nozzleNumber );
  // Serial.println( " )" );
  if( !isValidNozzleNumber( nozzleNumber ) )
  {
    // Serial.println( "\tBad nozzle number" );
    return -1;
  }
  // Serial.print( "\tReturning " );
  // Serial.println( _p_nozzleTableAddresses[nozzleNumber] );
  return _p_nozzleTableAddresses[nozzleNumber];
}
int primitiveLookup( int nozzleNumber )
{
  if( !isValidNozzleNumber( nozzleNumber ) )
  {
    return -1;
  }

  return _p_nozzleTablePrimitives[nozzleNumber];
}

int getNozzleNumber( int address, int primitive ) // obsolete this
{
  if( !isValidAddress(address) || !isValidPrimitive(primitive) )
  {
    return -1;
  }
  return _pp_nozzleReverseLookup[primitive][address];
}
int nozzleLookup( int address, int primitive )
{
  // Serial.print( "nozzleLookup( " );
  // Serial.print( address );
  // Serial.print( ", " );
  // Serial.print( primitive );
  // Serial.println( " )" );

  int
    pIntAlloc = sizeof(int) * PRIMITIVE_COUNT,
    nozzlesThatBelongToThePrimitive [pIntAlloc],
    primSize = 0,
    retval = -1
    ;
  // first find the nozzles that share the given primitive
  for( int nozzleNumber = 0; nozzleNumber < NOZZLE_COUNT; nozzleNumber++ )
  {
    if( _p_nozzleTablePrimitives[nozzleNumber] == primitive )
    {
      nozzlesThatBelongToThePrimitive[primSize++] = nozzleNumber;
    }
  }
  // Serial.println( "\tPrimitive matches:" );
  // for( int i = 0; i < primSize; i++ )
  // {
  //   Serial.print( "\t\t" );
  //   Serial.println( nozzlesThatBelongToThePrimitive[i] );
  // }
  // // then iterate through their associated addresses until you find the matching

  int potentialAddressMatch;
  // Serial.println( "\tMatching to addresses:" );
  for( int i = 0; i < primSize; i++ )
  {
    potentialAddressMatch = _p_nozzleTableAddresses[ nozzlesThatBelongToThePrimitive[i] ];
    // Serial.print( "\t\t" );
    // Serial.print( potentialAddressMatch );
    if( potentialAddressMatch == address )
    {
      // Serial.println( "\tMATCH FOUND!" );
      retval = nozzlesThatBelongToThePrimitive[i];
      break;
    }
    // else
    // {
    //   Serial.println( "\tno match" );
    // }
  }
  return retval;
}