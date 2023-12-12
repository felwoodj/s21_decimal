#ifndef _S21_DECIMAL_H
#define _S21_DECIMAL_H

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DECIMAL 79228162514264337593543950335.0F
#define MIN_DECIMAL -1 * MAX_DECIMAL
#define MAX_SCALE 28
#define MAX_FLOAT 1.0E-28
#define s21_INF 1.0 / 0.0
#define s21_NAN 0.0 / 0.0
#define MINUS 0x80000000  // 10000000 00000000 00000000 00000000
#define SCALE 0x00ff0000  // 00000000 11111111 00000000 00000000

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned sign;
  int scale;
  unsigned int bits[8];
} s21_big_decimal;

/* UTILTY FUNCTIONS */
int get_before_scale(s21_decimal dec);
void normalization(s21_decimal *dec_one, s21_decimal *dec_two);
void equalization(int ext_big, int ext_small, s21_decimal *big_ext,
                  s21_decimal *small_ext);
int multiplay_by_ten(s21_decimal dec, s21_decimal *res);
int division_by_ten(s21_decimal dec, s21_decimal *res);
unsigned int set_mask(int index);
unsigned int get_bit(s21_decimal val, int bit);
void set_bit(s21_decimal *dec, int bit, int value);
void set_sign(s21_decimal *dec, int n);
int get_sign(s21_decimal dec);
int get_scale(s21_decimal dec);
void set_scale(s21_decimal *dec, int value);
int addition(s21_big_decimal value1, s21_big_decimal value2,
             s21_big_decimal *res);
int substraction(s21_big_decimal big_value, s21_big_decimal small_value,
                 s21_big_decimal *res);
unsigned get_bit_bigdecimal(s21_big_decimal val, int bit);
void set_bit_bigdecimal(s21_big_decimal *dec, int bit, int value);
int take_one_to_sub(s21_big_decimal *val, int i);
void transfer_decimal_to_big_decimal(s21_decimal *dec,
                                     s21_big_decimal *big_decimal);
int comparison_mantiss(s21_big_decimal val_1, s21_big_decimal val_2);
void normalization_bigdec(s21_big_decimal *first_value,
                          s21_big_decimal *second_value);
int multiplication_by_ten_bigdec(s21_big_decimal dec, s21_big_decimal *res);
int division_by_ten_bigdec(s21_big_decimal dec, s21_big_decimal *res);
int check_zero_value(s21_decimal *dec);
int transfer_bigdecimal_to_decimal(s21_big_decimal *big_dec, s21_decimal *dec);
int reduction_bigdec(s21_big_decimal *dec);
int check_bigdec(s21_big_decimal dec);
int s21_decimal_is_zero(s21_decimal dec);
void shift_left_mantissa(s21_big_decimal *dec);
void shift_left_num_bigdecimal(s21_big_decimal *dec, int num);
int multiplication(s21_big_decimal value_1, s21_big_decimal value_2,
                   s21_big_decimal *res);
int int_add_decimal(s21_decimal dec, int a, s21_decimal *res);
int diff_mantiss(s21_big_decimal val_1, s21_big_decimal val_2);
int comparison_decimal_mantiss(s21_decimal dec1, s21_decimal dec2);
s21_decimal check_minus_null(s21_decimal dec);

/*
 ARITHMETIC FUNCTIONS
 0 - OK
 1 - the number is too large or equal to infinity
 2 - the number is too small or equal to negative infinity
 3 - division by 0;
*/

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/*
OTHER DECIMAL FUNCTIONS
 0 - OK
 1 - ERROR
*/

int s21_negate(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);

/*
COMPARISON FUNCTIONS
 0 - FALSE
 1 - TRUE
*/

int s21_is_less(s21_decimal dec1, s21_decimal dec2);
int s21_is_less_or_equal(s21_decimal dec1, s21_decimal dec2);
int s21_is_greater(s21_decimal dec1, s21_decimal dec2);
int s21_is_greater_or_equal(s21_decimal dec1, s21_decimal dec2);
int s21_is_equal(s21_decimal dec1, s21_decimal dec2);
int s21_is_not_equal(s21_decimal dec1, s21_decimal dec2);

/*
CONVERTATION FUNCTIONS
 0 - OK
 1 - ERROR
*/

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

#endif