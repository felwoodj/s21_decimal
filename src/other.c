#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (result) {
    value.bits[3] = value.bits[3] ^ ((unsigned int)1 << 31);  // * -1
    *result = value;
  } else {
    error = 1;
  }
  return error;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (result) {
    uint64_t rem = 0;  // остаток
    uint64_t num = 0;  // число
    int scale = get_scale(value);

    while (scale > 0) {
      for (int i = 2; i > -1; i--) {
        num = value.bits[i];
        num += rem << 32;  // прибавляет остаток к след итерации num, 10 + 7 =
                           // 17, 10 + 7 в остатке
        rem = num % 10;
        num /= 10;
        value.bits[i] = num;
      }
      scale--;
      rem = 0;
      num = 0;
    }
    set_scale(&value, 0);
    *result = value;
  } else {
    error = 1;
  }
  return error;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int error = 0;
  if (result) {
    s21_decimal trunc_value = {0};
    s21_decimal fraction = {0};
    s21_decimal zero_dec = {0};
    s21_truncate(value, &trunc_value);  // убираем дробную часть
    s21_sub(value, trunc_value, &fraction);  // находим дробную часть
    if (value.bits[3] >> 31) {               // если -
      s21_negate(fraction, &fraction);            // ; -1
      if (!s21_is_greater(fraction, zero_dec)) {  // если < 0
        int_add_decimal(
            trunc_value, -1,
            &trunc_value);  // отнимаем -1 - округление в сторону -INF
      }
    }
    *result = trunc_value;
  } else {
    error = 1;
  }
  return error;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  // логика что если число отрицательное и fraction >= 5 то -1
  // если положительное то +1
  // если никуда не заходит то просто копирует trunc_value в result
  int error = 0;
  if (result) {
    s21_decimal five = {{5, 0, 0, 0}};
    s21_decimal trunc_value = {0};
    s21_decimal fraction = {0};
    set_scale(&five, 1);
    s21_truncate(value, &trunc_value);  // убираем дробную часть
    s21_sub(value, trunc_value, &fraction);  // находим дробную часть
    if (get_bit(value, 127)) {               // -
      s21_negate(fraction, &fraction);                // *-1
      if (s21_is_greater_or_equal(fraction, five)) {  // >=0.5
        int_add_decimal(
            trunc_value, -1,
            &trunc_value);  // -1 потому что в этом if trunc_value отрицательное
      }
    } else {
      if (s21_is_greater_or_equal(fraction, five)) {    // >= 0.5
        int_add_decimal(trunc_value, 1, &trunc_value);  // + 1
      }
    }
    *result = trunc_value;
  } else {
    error = 1;
  }
  return error;
}
