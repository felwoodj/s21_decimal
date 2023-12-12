#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  memset(result, 0, sizeof(s21_decimal));
  int flag = 0;
  s21_big_decimal big_value_1 = {0};
  s21_big_decimal big_value_2 = {0};
  s21_big_decimal big_result = {0};
  transfer_decimal_to_big_decimal(&value_1, &big_value_1);
  transfer_decimal_to_big_decimal(&value_2, &big_value_2);
  normalization_bigdec(&big_value_1, &big_value_2);
  big_result.scale = big_value_1.scale;
  if (big_value_1.sign == big_value_2.sign) {  // 0 && 0 || 1 & 1
    addition(big_value_1, big_value_2, &big_result);
    big_result.sign = big_value_1.sign;
  } else if (comparison_mantiss(big_value_1, big_value_2)) {  // 1 > 2
    substraction(big_value_1, big_value_2, &big_result);      // 1 - 2
    big_result.sign = big_value_1.sign;
  } else if (comparison_mantiss(big_value_2, big_value_1)) {  // 2 > 1
    substraction(big_value_2, big_value_1, &big_result);      // 2 -1
    big_result.sign = big_value_2.sign;
  }
  flag = transfer_bigdecimal_to_decimal(&big_result, result);
  if (flag && big_result.sign) flag += 1;
  return flag;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  memset(result, 0, sizeof(s21_decimal));
  int flag = 0;
  s21_negate(value_2, &value_2);             // *-1
  flag = s21_add(value_1, value_2, result);  // +
  if (s21_decimal_is_zero(*result)) {        // проверка на 0
    result->bits[3] = 0;
  }
  return flag;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  memset(result, 0, sizeof(s21_decimal));
  s21_big_decimal big_value_1 = {0};
  s21_big_decimal big_value_2 = {0};
  s21_big_decimal big_result = {0};
  transfer_decimal_to_big_decimal(&value_1, &big_value_1);
  transfer_decimal_to_big_decimal(&value_2, &big_value_2);
  normalization_bigdec(&big_value_1, &big_value_2);
  big_result.scale = big_value_1.scale;
  multiplication(big_value_1, big_value_2, &big_result);
  big_result.scale *= 2;
  if (big_value_1.sign == big_value_2.sign)
    big_result.sign = 0;
  else if (big_value_1.sign != big_value_2.sign)
    big_result.sign = 1;
  flag = transfer_bigdecimal_to_decimal(&big_result, result);
  if (flag && big_result.sign) flag += 1;
  return flag;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  memset(result, 0, sizeof(s21_decimal));
  int flag = 0;
  s21_big_decimal big_value_1 = {0};
  s21_big_decimal big_value_2 = {0};
  s21_big_decimal big_result = {0};
  transfer_decimal_to_big_decimal(&value_1, &big_value_1);
  transfer_decimal_to_big_decimal(&value_2, &big_value_2);
  normalization_bigdec(&big_value_1, &big_value_2);
  big_result.scale = big_value_1.scale;
  if (big_value_1.sign == big_value_2.sign) {
    addition(big_value_1, big_value_2, &big_result);
    big_result.sign = big_value_1.sign;
  } else if (comparison_mantiss(big_value_1, big_value_2)) {
    substraction(big_value_1, big_value_2, &big_result);
    big_result.sign = big_value_1.sign;
  } else if (comparison_mantiss(big_value_2, big_value_1)) {
    substraction(big_value_2, big_value_1, &big_result);
    big_result.sign = big_value_2.sign;
  }
  flag = transfer_bigdecimal_to_decimal(&big_result, result);
  if (flag && big_result.sign) flag += 1;
  return flag;
}
