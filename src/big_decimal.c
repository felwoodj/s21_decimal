#include "s21_decimal.h"

int addition(s21_big_decimal value1, s21_big_decimal value2,
             s21_big_decimal *res) {
  int temp = 0;
  unsigned sum = 0;
  for (int i = 0; i < 256; i++) {
    sum = get_bit_bigdecimal(value1, i) + get_bit_bigdecimal(value2, i) + temp;
    if (sum == 0) {  // 0 + 0
      set_bit_bigdecimal(res, i, 0);
      temp = 0;
    } else if (sum == 1) {  // 1 + 0 || 0 + 1
      set_bit_bigdecimal(res, i, 1);
      temp = 0;
    } else if (sum == 2) {  // 1 + 1
      set_bit_bigdecimal(res, i, 0);
      temp = 1;
    } else if (sum == 3) {  // 1 + 1 и 1 в уме
      set_bit_bigdecimal(res, i, 1);
      temp = 1;
    }
  }
  return 0;
}

int take_one_to_sub(s21_big_decimal *val, int i) {
  int flag = 1;
  while (flag) {
    if (get_bit_bigdecimal(*val, i) == 0) {
      set_bit_bigdecimal(val, i, 1);
    } else if (get_bit_bigdecimal(*val, i)) {
      set_bit_bigdecimal(val, i, 0);
      flag = 0;
    }
    i++;
  }
  return 0;
}

int substraction(s21_big_decimal big_value, s21_big_decimal small_value,
                 s21_big_decimal *res) {
  unsigned small_bit = 0;
  unsigned big_bit = 0;
  for (int i = 0; i < 256; i++) {
    small_bit = get_bit_bigdecimal(small_value, i);
    big_bit = get_bit_bigdecimal(big_value, i);
    if (small_bit == 1 && big_bit == 0) {
      take_one_to_sub(&big_value, i);
      set_bit_bigdecimal(res, i, 1);
    } else {
      set_bit_bigdecimal(res, i, big_bit - small_bit);
    }
  }
  return 0;
}

unsigned get_bit_bigdecimal(s21_big_decimal val,
                            int bit) {  // получаем бит по индексу
  unsigned int mask = set_mask(bit);
  return (val.bits[bit / 32] & mask) != 0;
}

void set_bit_bigdecimal(s21_big_decimal *dec, int bit,
                        int value) {  // устанавливаем бит 1 или 0
  if (value == 1) {
    dec->bits[bit / 32] |= (set_mask(bit));
  } else if (value == 0) {
    dec->bits[bit / 32] &= ~(set_mask(bit));
  }
}

void transfer_decimal_to_big_decimal(
    s21_decimal *dec, s21_big_decimal *big_decimal) {  // перенос в big_decimal
  big_decimal->sign = get_sign(*dec);
  big_decimal->scale = get_scale(*dec);
  big_decimal->bits[0] = dec->bits[0];
  big_decimal->bits[1] = dec->bits[1];
  big_decimal->bits[2] = dec->bits[2];
}

int check_bigdec(s21_big_decimal dec) {
  int check = 0;
  for (int i = 7; i > 2; i--) {
    if (dec.bits[i] != 0) {
      check = 1;
      i = 0;
    }
  }
  return check;
}

int reduction_bigdec(s21_big_decimal *dec) {
  int flag = 0;
  while ((check_bigdec(*dec) || dec->scale > 28)) {
    division_by_ten_bigdec(*dec, dec);
    --dec->scale;
  }
  if (dec->scale < 0) flag = 1;
  return flag;
}

int transfer_bigdecimal_to_decimal(s21_big_decimal *big, s21_decimal *dec) {
  int flag = reduction_bigdec(big);
  set_scale(dec, big->scale);
  set_sign(dec, big->sign);
  for (int i = 2; i >= 0; i--) {
    dec->bits[i] = big->bits[i];
  }
  if (check_zero_value(dec)) set_scale(dec, 0);
  return flag;
}

void shift_left_mantissa(s21_big_decimal *dec) {
  s21_big_decimal tmp = {0};
  int bit = 0;
  tmp.scale = dec->scale;
  for (int i = 7; i > -1; i--) {
    bit = get_bit_bigdecimal(*dec, ((i * 32) - 1));
    tmp.bits[i] = dec->bits[i] << 1;  // *2
    if (i) set_bit_bigdecimal(&tmp, (i * 32), bit);
  }
  *dec = tmp;
}

void shift_left_num_bigdecimal(s21_big_decimal *dec,
                               int num) {  // на сколько сдвигать мантиссу влево
  for (int i = 0; i < num; i++) {
    shift_left_mantissa(dec);
  }
}

int multiplication(s21_big_decimal value_1, s21_big_decimal value_2,
                   s21_big_decimal *res) {
  s21_big_decimal tmp = {0};
  tmp.scale = value_1.scale;
  for (int i = 0; i < 256; i++) {
    s21_big_decimal temp_value_1 = value_1;
    if (get_bit_bigdecimal(value_2,
                           i)) {  // если value_1 * value_2; value_2[i] = 1
      shift_left_num_bigdecimal(&temp_value_1, i);  // temp_value_1 * 2^i
      addition(tmp, temp_value_1, &tmp);            // tmp + temp_value
    }
  }
  *res = tmp;
  return 0;
}

int check_zero_value(s21_decimal *dec) {
  int flag = 1;
  for (int i = 0; i < 3; i++) {
    if (dec->bits[i]) {
      flag = 0;
    }
  }
  return flag;
}

int s21_decimal_is_zero(s21_decimal dec) {
  int res = 0;
  if (dec.bits[0] == 0 && dec.bits[1] == 0 && dec.bits[2] == 0) {
    res = 1;
  }
  return res;
}

int division_by_ten_bigdec(s21_big_decimal dec,
                           s21_big_decimal *res) {  // деление на 10
  uint64_t tmp_u = 0;
  uint64_t remained = 0;
  for (int i = 7; i > -1; i--) {
    tmp_u = dec.bits[i];
    tmp_u |= remained << 32;
    remained = tmp_u % 10;
    tmp_u /= 10;
    res->bits[i] = UINT_MAX & tmp_u;
  }
  if (remained > 4) {  // > 0.5
    res->bits[0] += 1;
  }
  return 0;
}

int multiplication_by_ten_bigdec(s21_big_decimal dec,
                                 s21_big_decimal *res) {  // умножение на 10
  uint64_t tmp_u = 0;
  unsigned remained = 0;
  for (int i = 0; i < 8; i++) {
    tmp_u = dec.bits[i];
    tmp_u *= 10;
    tmp_u += remained;
    remained = tmp_u >> 32;
    res->bits[i] = UINT_MAX & tmp_u;
  }
  return 0;
}

void normalization_bigdec(s21_big_decimal *first_value,
                          s21_big_decimal *second_value) {
  int difference = first_value->scale - second_value->scale;
  while (first_value->scale > 28) {
    division_by_ten_bigdec(*first_value, first_value);
    first_value->scale--;
    difference--;
  }
  while (second_value->scale > 28) {
    division_by_ten_bigdec(*second_value, second_value);
    second_value->scale--;
    difference--;
  }
  while (difference > 0) {
    multiplication_by_ten_bigdec(*second_value, second_value);
    second_value->scale++;
    difference--;
  }
  while (difference < 0) {
    multiplication_by_ten_bigdec(*first_value, first_value);
    first_value->scale++;
    difference++;
  }
}

int comparison_mantiss(s21_big_decimal val_1, s21_big_decimal val_2) {
  int flag = 0;
  for (int i = 255; i > -1; i--) {
    if (get_bit_bigdecimal(val_1, i) > get_bit_bigdecimal(val_2, i)) {
      flag = 1;
      break;
    } else if (get_bit_bigdecimal(val_1, i) < get_bit_bigdecimal(val_2, i)) {
      break;
    }
  }
  return flag;
}

int diff_mantiss(s21_big_decimal val_1, s21_big_decimal val_2) {
  int result = 0;
  for (int i = 255; i > -1; i--) {
    if (get_bit_bigdecimal(val_1, i) > get_bit_bigdecimal(val_2, i)) {
      result = 1;
      break;
    } else if (get_bit_bigdecimal(val_1, i) < get_bit_bigdecimal(val_2, i)) {
      result = -1;
      break;
    }
  }
  return result;
}
