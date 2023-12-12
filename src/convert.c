#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = 1;
  if (dst) {
    error = 0;
    *dst = (s21_decimal){0};
    dst->bits[0] = abs(src);
    if (src < 0) set_sign(dst, 1);
  }
  return error;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int error = 0, res = 0, sign = get_sign(src);
  s21_truncate(src, &src);  // обрезаем дробную часть
  if (src.bits[1] != 0) {   // переполнение
    error = 1;
  } else {
    res = src.bits[0];
    if (sign) res *= -1;
    *dst = res;
  }
  return error;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int error = 0;
  if (dst == NULL) {
    error = 1;
  } else {
    int scale = get_scale(src);
    long double tmp = 0;
    for (int i = 0; i < 96; i++)
      tmp += pow(2, i) * get_bit(src, i);  // 2 в степени бита * сам бит
    while (scale != 0) {  // перевели только мантиссу из децимала, теперь нужно
                          // установить точность
      tmp /= 10.0;
      scale--;
    }
    if (get_sign(src)) tmp *= -1.0;
    *dst = tmp;
  }
  return error;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  // алгоритм:
  // 1)проверяем на ошибки
  // 2)зануляем децимал
  // 3)знак
  // 4)приводим src к инту и добаляем туда целые числа
  // 5) переводим из инт в децимал
  // 6)ставим степень и знак
  int error = 0;
  if (isnan(src) || isinf(src) || fabs(src) > MAX_DECIMAL) error = 1;
  if (dst && !error) {
    for (int i = 0; i < 128; i++) set_bit(dst, i, 0);
    int sign = 0;
    if (src < 0) {
      sign = 1;
      src = fabs(src);
    }
    int temp = (int)src;
    int scale = 0;
    // цикл проверяет остался ли остаток разницы между src new, если нет то
    // десяток прибавляется
    // src = 12,345 new = 12
    // 1 итерация: while 12.345 - 12.0 / 10^0 = 0.345 -> != 0
    // exp = 1; new = 12.345 *10^1 = 123;
    // 2 итерация: while 12.345 - 123/10^1 != 0
    // exp = 2; new = 12.345 * 10^2 = 1234;
    // 3 итерация: while 12.345 - 1234/ 10^2 != 0
    // exp = 3; new = 12.345 * 10^3 = 12345
    // 4 итерация: while 12.345 - 12345 / 10^3 = 12.345 - 12.345 = 0 выходим из
    // цикла
    while (src - ((float)temp / (int)(pow(10, scale))) != 0) {
      scale++;
      temp = src * (int)(pow(10, scale));
    }
    // в итоге имеем целочисленное значение не 12.345 а 12345
    s21_from_int_to_decimal(temp, dst);  // переводит из инта в децимал
    if (sign) s21_negate(*dst, dst);  // *-1
    set_scale(dst, scale);
  } else {
    error = 1;
  }
  return error;
}