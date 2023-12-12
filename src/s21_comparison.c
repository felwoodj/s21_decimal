#include "s21_decimal.h"

int s21_is_greater(s21_decimal dec_1, s21_decimal dec_2) {
  int res = 0;
  if (!s21_decimal_is_zero(dec_1) && !s21_decimal_is_zero(dec_2)) {
    if (get_bit(dec_1, 127) < get_bit(dec_2, 127)) {
      res = 1;
    } else if (get_bit(dec_1, 127) > get_bit(dec_2, 127)) {
      res = 0;
    } else {
      normalization(&dec_1, &dec_2);
      for (int i = 95; i > -1; i--) {
        if (get_bit(dec_1, i) > get_bit(dec_2, i)) {
          if (!get_bit(dec_1, 127)) {
            res = 1;
          }
          break;
        } else if (get_bit(dec_1, i) < get_bit(dec_2, i)) {
          if (get_bit(dec_1, 127)) {
            res = 1;
          }
          break;
        }
      }
    }
  }
  return res;
}

int s21_is_equal(s21_decimal dec_1, s21_decimal dec_2) {
  int res = 0;
  normalization(&dec_1, &dec_2);
  if (dec_1.bits[0] == dec_2.bits[0] && dec_1.bits[1] == dec_2.bits[1] &&
      dec_1.bits[2] == dec_2.bits[2] && dec_1.bits[3] == dec_2.bits[3]) {
    res = 1;
  }
  return res;
}

// dec_1 != dec_2 return 1;

int s21_is_not_equal(s21_decimal dec_1, s21_decimal dec_2) {
  return !s21_is_equal(dec_1, dec_2);
}

// dec_1 >= dec_2 return 1;
int s21_is_greater_or_equal(s21_decimal dec_1, s21_decimal dec_2) {
  return (s21_is_equal(dec_1, dec_2) || s21_is_greater(dec_1, dec_2) ? 1 : 0);
}

// dec_1 < dec_2 return 1;

int s21_is_less(s21_decimal dec_1, s21_decimal dec_2) {
  return (s21_is_equal(dec_1, dec_2) || s21_is_greater(dec_1, dec_2) ? 0 : 1);
}

// dec_1 <= dec_2 return 1;

int s21_is_less_or_equal(s21_decimal dec_1, s21_decimal dec_2) {
  return (s21_is_equal(dec_1, dec_2) || s21_is_less(dec_1, dec_2) ? 1 : 0);
}
