#ifndef PATTERNS_H
#define PATTERNS_H

//TODO: distinguish and select depending on number of lamps

const bool defaultMask[5] = {1, 1, 1, 1, 1};
const bool leftMask[5] = {1, 1, 1, 0, 0};
const bool rightMask[5] = {0, 0, 1, 1, 1};

const bool chaserPattern[5][NUM_LAMPS] = {
  { 1, 0, 0, 0, 0 },
  { 0, 1, 0, 0, 0 },
  { 0, 0, 1, 0, 0 },
  { 0, 0, 0, 1, 0 },
  { 0, 0, 0, 0, 1 }
};

const bool changerPattern[2][NUM_LAMPS] = {
  { 1, 0, 1, 0, 1 },
  { 0, 1, 0, 1, 0 }
};

const bool stroboPattern[2][NUM_LAMPS] = {
  { 1, 1, 1, 1, 1 },
  { 0, 0, 0, 0, 0 }
};

const bool alternatePattern[2][NUM_LAMPS] = {
  { 1, 1, 1, 0, 0 },
  { 0, 0, 1, 1, 1 }
};

const bool runnerPattern[6][NUM_LAMPS] = {
  { 1, 0, 0, 0, 0 },
  { 1, 1, 0, 0, 0 },
  { 0, 1, 1, 0, 0 },
  { 0, 0, 1, 1, 0 },
  { 0, 0, 0, 1, 1 },
  { 0, 0, 0, 0, 1 }
};

#endif