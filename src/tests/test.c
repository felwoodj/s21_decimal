#include <check.h>
#include <stdlib.h>

#include "../s21_decimal.h"

// ============ Test for s21_add ============

// #1 сложение +v1 + v2 (v1 > v2)
START_TEST(test_s21_add_v1) {
  s21_decimal value_1 = {.bits[0] = 0b00000000000000000000000000001111,
                         .bits[1] = 0b00000000000000000000000000001111,
                         .bits[2] = 0b00000000000000000000000000001111,
                         .bits[3] = 0b10000000000001010000000000000000};

  s21_decimal value_2 = {.bits[0] = 0b00000000000000000000000000001010,
                         .bits[1] = 0b00000000000000000000000000001010,
                         .bits[2] = 0b00000000000000000000000000001010,
                         .bits[3] = 0b00000000000001110000000000000000};
  s21_decimal reference_result = {
      .bits[0] = 1490,
      .bits[1] = 1490,
      .bits[2] = 1490,
      .bits[3] = 0b10000000000001110000000000000000};
  s21_decimal result = {0};
  int sub_result = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(sub_result, 0);

  ck_assert_int_eq(result.bits[0], reference_result.bits[0]);
  ck_assert_int_eq(result.bits[1], reference_result.bits[1]);
  ck_assert_int_eq(result.bits[2], reference_result.bits[2]);
  ck_assert_int_eq(result.bits[3], reference_result.bits[3]);
}
END_TEST

// #2 сложение +v1 + v2 (v2 > v1)
START_TEST(test_s21_add_v2) {
  s21_decimal value_1 = {.bits[0] = 0b00000000000000000000000000001010,
                         .bits[1] = 0b00000000000000000000000000001010,
                         .bits[2] = 0b00000000000000000000000000001010,
                         .bits[3] = 0b00000000000001110000000000000000};

  s21_decimal value_2 = {.bits[0] = 0b00000000000000000000000000001111,
                         .bits[1] = 0b00000000000000000000000000001111,
                         .bits[2] = 0b00000000000000000000000000001111,
                         .bits[3] = 0b10000000000001010000000000000000};
  s21_decimal reference_result = {
      .bits[0] = 1490,
      .bits[1] = 1490,
      .bits[2] = 1490,
      .bits[3] = 0b10000000000001110000000000000000};
  s21_decimal result = {0};
  int sub_result = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(sub_result, 0);

  ck_assert_int_eq(result.bits[0], reference_result.bits[0]);
  ck_assert_int_eq(result.bits[1], reference_result.bits[1]);
  ck_assert_int_eq(result.bits[2], reference_result.bits[2]);
  ck_assert_int_eq(result.bits[3], reference_result.bits[3]);

  //   for (int i = 127; i >= 0; i--) {
  //   printf("%d", get_bit(value_1, i));
  // }
  // printf("\n");

  // for (int i = 127; i >= 0; i--) {
  //   printf("%d", get_bit(value_2, i));
  // }
  // printf("\n");
}
END_TEST

// #3 сложение -v1 + v2 (v1  v2)
START_TEST(test_s21_add_v3) {
  s21_decimal value_1 = {.bits[0] = 0x00000001,
                         .bits[1] = 0x00000000,
                         .bits[2] = 0x00000000,
                         .bits[3] = 0x800E0000};  //-0.00000000000001

  s21_decimal value_2 = {.bits[0] = 0x00000006,
                         .bits[1] = 0x00000000,
                         .bits[2] = 0x00000000,
                         .bits[3] = 0x000F0000};  // 0.000000000000006
  s21_decimal reference_result = {.bits[0] = 0x00000004,
                                  .bits[1] = 0x00000000,
                                  .bits[2] = 0x00000000,
                                  .bits[3] = 0x800F0000};  //-0.000000000000004
  s21_decimal result = {0};
  int sub_result = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(sub_result, 0);
  for (int i = 0; i < 4; i++) {
    ck_assert_int_eq(result.bits[i], reference_result.bits[i]);
  }
}
END_TEST

// #4 сложение v1 + -v2 (v1 > v2)
START_TEST(test_s21_add_v4) {
  s21_decimal value_1 = {.bits[0] = 0x058FEC8A,
                         .bits[1] = 0x00000000,
                         .bits[2] = 0x00000000,
                         .bits[3] = 0x00050000};  // 933.18282

  s21_decimal value_2 = {.bits[0] = 0x0707E3C5,
                         .bits[1] = 0x002D8D61,
                         .bits[2] = 0x00000000,
                         .bits[3] = 0x80090000};  // -12821821.821281221

  s21_decimal reference_result = {.bits[0] = 0xC1001525,
                                  .bits[1] = 0x002D8C87,
                                  .bits[2] = 0x00000000,
                                  .bits[3] = 0x80090000};  //-12820888.638461221
  s21_decimal result = {0};
  int sub_result = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(sub_result, 0);
  ck_assert_int_eq(result.bits[0], reference_result.bits[0]);
  ck_assert_int_eq(result.bits[1], reference_result.bits[1]);
  ck_assert_int_eq(result.bits[2], reference_result.bits[2]);
  ck_assert_int_eq(result.bits[3], reference_result.bits[3]);

  //   for (int i = 127; i >= 0; i--) {
  //     printf("%d", get_bit(value_1, i));
  //   }
  //   printf("\n");

  //   for (int i = 127; i >= 0; i--) {
  //     printf("%d", get_bit(value_2, i));
  //   }
  //   printf("\n");
}
END_TEST

// #5 сложение -v1 + -v2 (v1 = v2)
START_TEST(test_s21_add_v5) {
  s21_decimal value_1 = {.bits[0] = 0x00000001,
                         .bits[1] = 0x00000000,
                         .bits[2] = 0x00000000,
                         .bits[3] = 0x80000000};  //-1

  s21_decimal value_2 = {.bits[0] = 0x00000001,
                         .bits[1] = 0x00000000,
                         .bits[2] = 0x00000000,
                         .bits[3] = 0x80000000};  // -1

  s21_decimal reference_result = {.bits[0] = 0x00000002,
                                  .bits[1] = 0x00000000,
                                  .bits[2] = 0x00000000,
                                  .bits[3] = 0x80000000};  //-2
  s21_decimal result = {0};
  int sub_result = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(sub_result, 0);
  ck_assert_int_eq(result.bits[0], reference_result.bits[0]);
  ck_assert_int_eq(result.bits[1], reference_result.bits[1]);
  ck_assert_int_eq(result.bits[2], reference_result.bits[2]);
  ck_assert_int_eq(result.bits[3], reference_result.bits[3]);
  // for (int i = 127; i >= 0; i--) {
  //   printf("%d", get_bit(reference_result, i));
  // }
  // printf("\n");

  // for (int i = 127; i >= 0; i--) {
  //   printf("%d", get_bit(value_2, i));
  // }
  // printf("\n");
}
END_TEST

// #6 сложение - переполнение мантиссы
START_TEST(test_s21_add_v6) {
  s21_decimal value_1;
  s21_decimal value_2;
  for (int i = 0; i < 4; i++) {
    value_1.bits[i] = 0;
    value_2.bits[i] = 0;
  }
  value_1.bits[2] = 0xffffffff;
  value_2.bits[2] = 0xffffffff;
  set_scale(&value_1, 0);
  set_scale(&value_2, 0);
  s21_decimal result;
  ck_assert_int_eq(s21_add(value_1, value_2, &result), 1);
}
END_TEST

// #7 сложение
START_TEST(test_s21_add_v7) {
  s21_decimal value_1;
  s21_decimal value_2;
  for (int i = 0; i < 4; i++) {
    value_1.bits[i] = 0;
    value_2.bits[i] = 0;
  }
  set_scale(&value_1, 5);
  set_scale(&value_2, 5);
  value_1.bits[2] = 0xffffffff;
  value_2.bits[2] = 0xffffffff;
  value_1.bits[3] = 0x80000000;
  value_2.bits[3] = 0x80000000;
  s21_decimal result;
  ck_assert_int_eq(s21_add(value_1, value_2, &result), 2);

  // for (int i = 127; i >= 0; i--) {
  //   printf("%d", get_bit(reference_result, i));
  // }
  // printf("\n");

  // for (int i = 127; i >= 0; i--) {
  //   printf("%d", get_bit(value_2, i));
  // }
  // printf("\n");
}
END_TEST

START_TEST(test_s21_add_v8) {
  s21_decimal value_1 = {.bits[0] = 0x00000001,
                         .bits[1] = 0x00000000,
                         .bits[2] = 0x00000000,
                         .bits[3] = 0x80000000};  // -1

  s21_decimal value_2 = {.bits[0] = 0x00000001,
                         .bits[1] = 0x00000000,
                         .bits[2] = 0x00000000,
                         .bits[3] = 0x00000000};  // 1

  s21_decimal reference_result = {.bits[0] = 0x00000000,
                                  .bits[1] = 0x00000000,
                                  .bits[2] = 0x00000000,
                                  .bits[3] = 0x00000000};  // 0
  s21_decimal result = {0};
  int sub_result = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(sub_result, 0);
  ck_assert_int_eq(result.bits[0], reference_result.bits[0]);
  ck_assert_int_eq(result.bits[1], reference_result.bits[1]);
  ck_assert_int_eq(result.bits[2], reference_result.bits[2]);
  ck_assert_int_eq(result.bits[3], reference_result.bits[3]);
  // for (int i = 127; i >= 0; i--) {
  //   printf("%d", get_bit(reference_result, i));
  // }
  // printf("\n");

  // for (int i = 127; i >= 0; i--) {
  //   printf("%d", get_bit(value_2, i));
  // }
  // printf("\n");
}
END_TEST

START_TEST(test_s21_add_v9) {
  s21_decimal value_1 = {{0x9013129f, 0x36ce5141, 0xfdf280b8, 0x80000000}};
  s21_decimal value_2 = {{0xbd448c27, 0xa4c37397, 0xfdf2974f, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(value_1, value_2, &res);
  s21_decimal expected = {{0x2d317988, 0x6df52256, 0x00001697, 0x00000000}};
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v10) {
  s21_decimal value_1 = {{0xc3469ef3, 0xaa8d2f82, 0xdcd8dc52, 0x80000000}};
  s21_decimal value_2 = {{0x8935e02c, 0xe5931b86, 0xdcda5f33, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(value_1, value_2, &res);
  s21_decimal expected = {{0xc5ef4139, 0x3b05ec03, 0x000182e1, 0x00000000}};
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v11) {
  s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  s21_decimal b = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v12) {
  s21_decimal a = {{0x32026253, 0x06d9ca28, 0xffbe5017, 0x80000000}};
  s21_decimal b = {{0xf7a89184, 0xf4986e72, 0xffbe52e9, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0xc5a62f31, 0xedbea44a, 0x000002d2, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v13) {
  s21_decimal a = {{0x261a399b, 0x4b5bafba, 0xfd2d70fd, 0x80000000}};
  s21_decimal b = {{0xa43e40b6, 0x828cbef0, 0xfd2d900d, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x7e24071b, 0x37310f36, 0x00001f10, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v14) {
  s21_decimal a = {{0xb03937df, 0xa46af3c4, 0xf9d78228, 0x80000000}};
  s21_decimal b = {{0x37cda477, 0xee4a5ac7, 0xf9d7c5ee, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x87946c98, 0x49df6702, 0x000043c6, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v15) {
  s21_decimal a = {{0x5a7e5b63, 0x6b16da52, 0xf26694c4, 0x80000000}};
  s21_decimal b = {{0x45e62088, 0xa38eddcd, 0xf2672a6f, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0xeb67c525, 0x3878037a, 0x000095ab, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v16) {
  s21_decimal a = {{0x48a21e4f, 0xd1d9b2ad, 0xee8d461d, 0x80000000}};
  s21_decimal b = {{0xc8c6a753, 0xf87d5689, 0xee8e0624, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x80248904, 0x26a3a3dc, 0x0000c007, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v17) {
  s21_decimal a = {{0x30d1ccdf, 0x5add7dd1, 0xe96b87ea, 0x80000000}};
  s21_decimal b = {{0x21f205b7, 0x1465f785, 0xe96c806c, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0xf12038d8, 0xb98879b3, 0x0000f881, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v18) {
  s21_decimal a = {{0xe10b04bf, 0xff487195, 0xe3430a12, 0x80000000}};
  s21_decimal b = {{0x59bfaa2f, 0x02b0524c, 0xe344465b, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x78b4a570, 0x0367e0b6, 0x00013c48, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v19) {
  s21_decimal a = {{0x9d2c6557, 0x5f317fc8, 0xdfab6b55, 0x80000000}};
  s21_decimal b = {{0xe4f79f75, 0x63065c95, 0xdfaccf26, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x47cb3a1e, 0x03d4dccd, 0x000163d1, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v20) {
  s21_decimal a = {{0x5359b193, 0xe15b80c4, 0xdacb5d0a, 0x80000000}};
  s21_decimal b = {{0x467a6c54, 0x8a568f1e, 0xdaccf683, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0xf320bac1, 0xa8fb0e59, 0x00019978, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v21) {
  s21_decimal a = {{0x156f2687, 0x1f039c2e, 0xd87c2dda, 0x80000000}};
  s21_decimal b = {{0xfb678a01, 0x23b27128, 0xd87de0bd, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0xe5f8637a, 0x04aed4fa, 0x0001b2e3, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v22) {
  s21_decimal a = {{0x0986fdcf, 0x638581c0, 0xd5eb4ec0, 0x80000000}};
  s21_decimal b = {{0xa7fd3933, 0xb1a6c1a6, 0xd5ed1de0, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x9e763b64, 0x4e213fe6, 0x0001cf20, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v23) {
  s21_decimal a = {{0xcb9c72c3, 0xa12d9d29, 0xd39c1f8f, 0x80000000}};
  s21_decimal b = {{0x5cea56e0, 0x4b02a3b1, 0xd39e081a, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x914de41d, 0xa9d50687, 0x0001e88a, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v24) {
  s21_decimal a = {{0x55bb7107, 0xfa3ce134, 0xd04630ba, 0x80000000}};
  s21_decimal b = {{0xf079baa1, 0xb6c03f87, 0xd0483dfb, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x9abe499a, 0xbc835e53, 0x00020d40, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v25) {
  s21_decimal a = {{0x7e6bde70, 0x2ca6fe90, 0x60e5e176, 0x00000000}};
  s21_decimal b = {{0xfa62dbd3, 0x06d594c6, 0x8ee6f0ba, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x78ceba43, 0x337c9357, 0xefccd230, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v26) {
  s21_decimal a = {{0xbe294208, 0x16851bbf, 0x4e6a59be, 0x00000000}};
  s21_decimal b = {{0x93a5ea43, 0xe27e1652, 0x77d252b8, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x51cf2c4b, 0xf9033212, 0xc63cac76, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v27) {
  s21_decimal a = {{0x53ee80b7, 0xd3a6b915, 0x2e53e373, 0x00000000}};
  s21_decimal b = {{0x0bf338a9, 0x919f13ac, 0x4fc04ea1, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x5fe1b960, 0x6545ccc1, 0x7e143215, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v28) {
  s21_decimal a = {{0x2ad549d5, 0x3399a5ed, 0x1f7060ca, 0x00000000}};
  s21_decimal b = {{0x0e85aef5, 0xfb750a40, 0x3d289675, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x395af8ca, 0x2f0eb02d, 0x5c98f740, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v29) {
  s21_decimal a = {{0x3ce33a26, 0x3dc0f65d, 0x6553c0b1, 0x00010000}};
  s21_decimal b = {{0xc2c134ef, 0x551e66b2, 0x228d43df, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x48d7edf3, 0xa81818ef, 0x2caf3d8a, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v30) {
  s21_decimal a = {{0x53a5c322, 0x6a88b0e2, 0x3ef64b08, 0x80010000}};
  s21_decimal b = {{0x5fa73c7d, 0x81ed660d, 0x8c5b9c04, 0x00010000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x0c01795b, 0x1764b52b, 0x4d6550fc, 0x00010000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v31) {
  s21_decimal a = {{0xe42ec062, 0x12d25821, 0xe34056c2, 0x80010000}};
  s21_decimal b = {{0xdc3d9846, 0x4f5536e0, 0x40cd6eb0, 0x80010000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0xe00ad5aa, 0xa36a5b19, 0x1d3493be, 0x80000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v32) {
  s21_decimal a = {{0x58d1f21d, 0xcafc2b6a, 0x26a401cf, 0x80000000}};
  s21_decimal b = {{0xf706ba3d, 0x59015fe3, 0x1a5aeb4e, 0x80000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x4fd8ac5a, 0x23fd8b4e, 0x40feed1e, 0x80000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v33) {
  s21_decimal a = {{0x45a97d83, 0xb3e8d429, 0x42e0bbd3, 0x80000000}};
  s21_decimal b = {{0xe9520ed9, 0x6cf8d2dc, 0x3d9df925, 0x80000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x2efb8c5c, 0x20e1a706, 0x807eb4f9, 0x80000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v34) {
  s21_decimal a = {{0xee9567e5, 0x024b8221, 0x19ab91d5, 0x00190000}};
  s21_decimal b = {{0xd2f69104, 0xda4c021e, 0x19a80345, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0xd2f55aaf, 0xda4c021e, 0x19a80345, 0x80020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v35) {
  s21_decimal a = {{0xfebb5d52, 0xe6a1269c, 0x0291282e, 0x001c0000}};
  s21_decimal b = {{0xd2f55ae2, 0xda4c021e, 0x19a80345, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0xd2f55ada, 0xda4c021e, 0x19a80345, 0x80020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v36) {
  s21_decimal a = {{0xeea186ec, 0x024b8221, 0x19ab91d5, 0x001b0000}};
  s21_decimal b = {{0xd2f55df4, 0xda4c021e, 0x19a80345, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0xd2f55ada, 0xda4c021e, 0x19a80345, 0x80020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v37) {
  s21_decimal a = {{0x18105f3c, 0x0365c14e, 0x19ab91d5, 0x00180000}};
  s21_decimal b = {{0xd3017882, 0xda4c021e, 0x19a80345, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0xd2f5592c, 0xda4c021e, 0x19a80345, 0x80020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v38) {
  s21_decimal a = {{0xee969df3, 0x024b8221, 0x19ab91d5, 0x00070000}};
  s21_decimal b = {{0x1f0f2056, 0x43fd1acf, 0x19a81416, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x453a96a7, 0x858d8618, 0x19a80343, 0x80020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v39) {
  s21_decimal a = {{0x96ef3247, 0x026a8e33, 0x19ab91d5, 0x000d0000}};
  s21_decimal b = {{0x47a9af99, 0xdb661a2f, 0x19a80345, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x1ea69bf1, 0xda4bdb03, 0x19a80345, 0x80020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v40) {
  s21_decimal a = {{0x88a6d682, 0x0d51f9db, 0x19ab91d5, 0x000e0000}};
  s21_decimal b = {{0x11e02baa, 0xda6837ba, 0x19a80345, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0xa753dfb3, 0xda4bfe35, 0x19a80345, 0x80020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v41) {
  s21_decimal a = {{0xeb4fbc41, 0xf1a7e697, 0x0291282e, 0x001c0000}};
  s21_decimal b = {{0xd2f55ae2, 0xda4c021e, 0x19a80345, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0xd2f55ada, 0xda4c021e, 0x19a80345, 0x80020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v42) {
  s21_decimal a = {{0x7060e207, 0x50d28ee3, 0x19ab91d9, 0x001c0000}};
  s21_decimal b = {{0xd2f55b29, 0xda4c021e, 0x19a80345, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0xd2f55ada, 0xda4c021e, 0x19a80345, 0x80020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v43) {
  s21_decimal a = {{0x0ab383ae, 0xc92457c9, 0x6e693f8d, 0x00000000}};
  s21_decimal b = {{0x87b4465a, 0x9db7e6b2, 0x6e597ef7, 0x80000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x82ff3d54, 0x2b6c7116, 0x000fc096, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v44) {
  s21_decimal a = {{0x0e466d22, 0x4eeacc52, 0x430c1ec1, 0x00000000}};
  s21_decimal b = {{0x05fc5727, 0x1658d098, 0x42fe3b6a, 0x80000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x084a15fb, 0x3891fbba, 0x000de357, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v45) {
  s21_decimal a = {{0x88eaedc6, 0x279e4927, 0x3157b4f6, 0x00000000}};
  s21_decimal b = {{0xc66b9000, 0x036e9594, 0x314a9479, 0x80000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0xc27f5dc6, 0x242fb392, 0x000d207d, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v46) {
  s21_decimal a = {{0xc45a3329, 0xa91277f5, 0xb9847d8d, 0x00010000}};
  s21_decimal b = {{0xa65dbf1a, 0xacd792b8, 0xb90e7564, 0x80010000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x1dfc740f, 0xfc3ae53d, 0x00760828, 0x00010000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v47) {
  s21_decimal a = {{0xbf8fbd1e, 0x5dcbb680, 0x2b97fed9, 0x80020000}};
  s21_decimal b = {{0x9fa8254c, 0xe95b9982, 0x2fe2af4a, 0x00020000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0xe018682e, 0x8b8fe301, 0x044ab071, 0x00020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v48) {
  s21_decimal a = {{0xdc49d807, 0xd128cfbd, 0x1ba2700d, 0x80000000}};
  s21_decimal b = {{0x0009e861, 0x59effbb1, 0x1bac415c, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x23c0105a, 0x88c72bf3, 0x0009d14e, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v49) {
  s21_decimal a = {{0x1b64f887, 0x3f7d00ab, 0x3444676b, 0x80000000}};
  s21_decimal b = {{0x20d35681, 0xa0c69094, 0x344d29a0, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x056e5dfa, 0x61498fe9, 0x0008c235, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v50) {
  s21_decimal a = {{0x4e97f04f, 0xf253172a, 0x4a557fae, 0x80000000}};
  s21_decimal b = {{0xee3273d3, 0x759175f4, 0x4a5d4f08, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x9f9a8384, 0x833e5eca, 0x0007cf59, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v51) {
  s21_decimal a = {{0x4d66c64f, 0x856e0311, 0x6b2d742b, 0x80000000}};
  s21_decimal b = {{0x19e9b153, 0x295a3c79, 0x6b33da0e, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0xcc82eb04, 0xa3ec3967, 0x000665e2, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v52) {
  s21_decimal a = {{0x4c359c4f, 0x1888eef8, 0x8c0568a8, 0x80000000}};
  s21_decimal b = {{0x45a0eed3, 0xdd2302fd, 0x8c0a6513, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0xf96b5284, 0xc49a1404, 0x0004fc6b, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v53) {
  s21_decimal a = {{0xf7ab5547, 0x8b3121dc, 0x9ae74370, 0x80000000}};
  s21_decimal b = {{0x296ff6b1, 0x7299fcf1, 0x9aeb9c12, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x31c4a16a, 0xe768db14, 0x000458a1, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v54) {
  s21_decimal a = {{0x8ee311b7, 0x4bbaccac, 0xb074fbe2, 0x80000000}};
  s21_decimal b = {{0xe620370d, 0x3095bf37, 0xb078674e, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0x573d2556, 0xe4daf28b, 0x00036b6b, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_add_v55) {
  s21_decimal a = {{0xdd78afd7, 0x3a6ac4ce, 0xd7756e36, 0x80000000}};
  s21_decimal b = {{0xda09d015, 0xf6142af4, 0xd7772c64, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_add(a, b, &res);
  s21_decimal expected = {{0xfc91203e, 0xbba96625, 0x0001be2e, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

// === Suite s21_add ===

Suite *s21_add_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("\033[35m====-{s21_add_suite}-====\033[0m");
  tc_core = tcase_create("Add_Core");

  tcase_add_test(tc_core, test_s21_add_v1);
  tcase_add_test(tc_core, test_s21_add_v2);
  tcase_add_test(tc_core, test_s21_add_v3);
  tcase_add_test(tc_core, test_s21_add_v4);
  tcase_add_test(tc_core, test_s21_add_v5);
  tcase_add_test(tc_core, test_s21_add_v6);
  tcase_add_test(tc_core, test_s21_add_v7);
  tcase_add_test(tc_core, test_s21_add_v8);
  tcase_add_test(tc_core, test_s21_add_v9);
  tcase_add_test(tc_core, test_s21_add_v10);
  tcase_add_test(tc_core, test_s21_add_v11);
  tcase_add_test(tc_core, test_s21_add_v12);
  tcase_add_test(tc_core, test_s21_add_v13);
  tcase_add_test(tc_core, test_s21_add_v14);
  tcase_add_test(tc_core, test_s21_add_v15);
  tcase_add_test(tc_core, test_s21_add_v16);
  tcase_add_test(tc_core, test_s21_add_v17);
  tcase_add_test(tc_core, test_s21_add_v18);
  tcase_add_test(tc_core, test_s21_add_v19);
  tcase_add_test(tc_core, test_s21_add_v20);
  tcase_add_test(tc_core, test_s21_add_v21);
  tcase_add_test(tc_core, test_s21_add_v22);
  tcase_add_test(tc_core, test_s21_add_v23);
  tcase_add_test(tc_core, test_s21_add_v24);
  tcase_add_test(tc_core, test_s21_add_v25);
  tcase_add_test(tc_core, test_s21_add_v26);
  tcase_add_test(tc_core, test_s21_add_v27);
  tcase_add_test(tc_core, test_s21_add_v28);
  tcase_add_test(tc_core, test_s21_add_v29);
  tcase_add_test(tc_core, test_s21_add_v30);
  tcase_add_test(tc_core, test_s21_add_v31);
  tcase_add_test(tc_core, test_s21_add_v32);
  tcase_add_test(tc_core, test_s21_add_v33);
  tcase_add_test(tc_core, test_s21_add_v34);
  tcase_add_test(tc_core, test_s21_add_v35);
  tcase_add_test(tc_core, test_s21_add_v36);
  tcase_add_test(tc_core, test_s21_add_v37);
  tcase_add_test(tc_core, test_s21_add_v38);
  tcase_add_test(tc_core, test_s21_add_v39);
  tcase_add_test(tc_core, test_s21_add_v40);
  tcase_add_test(tc_core, test_s21_add_v41);
  tcase_add_test(tc_core, test_s21_add_v42);
  tcase_add_test(tc_core, test_s21_add_v43);
  tcase_add_test(tc_core, test_s21_add_v44);
  tcase_add_test(tc_core, test_s21_add_v45);
  tcase_add_test(tc_core, test_s21_add_v46);
  tcase_add_test(tc_core, test_s21_add_v47);
  tcase_add_test(tc_core, test_s21_add_v48);
  tcase_add_test(tc_core, test_s21_add_v49);
  tcase_add_test(tc_core, test_s21_add_v50);
  tcase_add_test(tc_core, test_s21_add_v51);
  tcase_add_test(tc_core, test_s21_add_v52);
  tcase_add_test(tc_core, test_s21_add_v53);
  tcase_add_test(tc_core, test_s21_add_v54);
  tcase_add_test(tc_core, test_s21_add_v55);

  suite_add_tcase(s, tc_core);

  return s;
}

// ============ Test for s21_sub ===========

START_TEST(test_s21_sub_v1) {
  s21_decimal value_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal res;
  int s21_ret = s21_sub(value_2, value_1, &res);
  s21_decimal expected = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v2) {
  s21_decimal value_1 = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal res;
  int s21_ret = s21_sub(value_1, value_2, &res);
  s21_decimal expected = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v3) {
  s21_decimal value_1 = {{0x7b2b8df7, 0x1924a3e6, 0xfe75e08f, 0x00000000}};
  s21_decimal value_2 = {{0x0c21051d, 0x185152f6, 0xfe762074, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_sub(value_1, value_2, &res);
  s21_decimal expected = {{0x90f57726, 0xff2caf0f, 0x00003fe4, 0x80000000}};
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v4) {
  s21_decimal value_1 = {{0xcd489747, 0x7f3d112a, 0xfd6f20ee, 0x00000000}};
  s21_decimal value_2 = {{0xbee1b331, 0x28878a44, 0xfd6f8b6c, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_sub(value_1, value_2, &res);
  s21_decimal expected = {{0xf1991bea, 0xa94a7919, 0x00006a7d, 0x80000000}};
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v5) {
  s21_decimal value_1 = {{0x4874253f, 0x9861b511, 0xfbe5017d, 0x00000000}};
  s21_decimal value_2 = {{0xcb02b84f, 0x40d8dd3a, 0xfbe5abe0, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_sub(value_1, value_2, &res);
  s21_decimal expected = {{0x828e9310, 0xa8772829, 0x0000aa62, 0x80000000}};
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v6) {
  s21_decimal value_1 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal value_2 = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_sub(value_1, value_2, &res);
  s21_decimal expected = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v7) {
  s21_decimal value_1 = {{0x00000001, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal value_2 = {{0x00000001, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal res;
  int s21_ret = s21_sub(value_1, value_2, &res);
  s21_decimal expected = {{0x00000002, 0x00000000, 0x00000000, 0x00000000}};
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v8) {
  s21_decimal value_1 = {{0x00000001, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal value_2 = {{0x00000001, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal res;
  int s21_ret = s21_sub(value_1, value_2, &res);
  s21_decimal expected = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v9) {
  s21_decimal value_1 = {{0x00000001, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal value_2 = {{0x00000001, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal res;
  int s21_ret = s21_sub(value_1, value_2, &res);
  s21_decimal expected = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v10) {
  s21_decimal value_1 = {{0x397d4ea9, 0x4f12d677, 0x5afd9577, 0x80010000}};
  s21_decimal value_2 = {{0xe35be7eb, 0x9f626ce7, 0x6c2a6080, 0x00010000}};
  s21_decimal res;
  int s21_ret = s21_sub(value_1, value_2, &res);
  s21_decimal expected = {{0x1cd93694, 0xee75435f, 0xc727f5f7, 0x80010000}};
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

// START_TEST(test_s21_sub_v11) {
//   s21_decimal value_1 = {.bits[0] = 0x417ff144,
//                          .bits[1] = 0xcae07d67,
//                          .bits[2] = 0x19a3d9a6,
//                          .bits[3] = 0x800a0000};

//   s21_decimal value_2 = {.bits[0] = 0x3b8bacaf,
//                          .bits[1] = 0x76f6dbf9,
//                          .bits[2] = 0x19b36f16,
//                          .bits[3] = 0x80020000};

//   s21_decimal reference_result = {.bits[0] = 0xcc12e796,
//                                   .bits[1] = 0x29bba3c7,
//                                   .bits[2] = 0x19b36f12,
//                                   .bits[3] = 0x00020000};
//   s21_decimal result = {0};
//   int sub_result = s21_sub(value_1, value_2, &result);
//   printf("%d\n", get_scale(value_1));
//   printf("%d\n", get_scale(value_2));
//   printf("%d\n", get_scale(reference_result));
//   // for (int i = 127; i >= 0; i--) {
//   //   printf("%d", get_bit(value_2, i));
//   // }
//   // printf("\n");
//   ck_assert_int_eq(sub_result, 0);
//   ck_assert_int_eq(result.bits[0], reference_result.bits[0]);
//   ck_assert_int_eq(result.bits[1], reference_result.bits[1]);
//   ck_assert_int_eq(result.bits[2], reference_result.bits[2]);
//   ck_assert_int_eq(result.bits[3], reference_result.bits[3]);
// }
// END_TEST

START_TEST(test_s21_sub_v11) {
  s21_decimal value_1 = {{0x417ff144, 0xcae07d67, 0x19a3d9a6, 0x800a0000}};
  s21_decimal value_2 = {{0x3b8bacaf, 0x76f6dbf9, 0x19b36f16, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_sub(value_1, value_2, &res);
  s21_decimal expected = {{0xcc12e796, 0x29bba3c7, 0x19b36f12, 0x00020000}};
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v12) {
  s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0xffffffff, 0xffffffff, 0xffffffff, 0x00000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v13) {
  s21_decimal a = {{0x01357a33, 0x3e18aaeb, 0xf995d254, 0x00000000}};
  s21_decimal b = {{0xdd343ffc, 0x6552d9ab, 0xf996dc8e, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0xdbfec5c9, 0x273a2ec0, 0x00010a3a, 0x80000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v14) {
  s21_decimal a = {{0xe30553cf, 0x96dbd766, 0xf6c3435a, 0x00000000}};
  s21_decimal b = {{0x48c61eb3, 0x91e7f1c4, 0xf6c4c2b8, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0x65c0cae4, 0xfb0c1a5d, 0x00017f5d, 0x80000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v15) {
  s21_decimal a = {{0x921dc4b3, 0x6edc150d, 0xf15fd54f, 0x00000000}};
  s21_decimal b = {{0x7339b09c, 0xe7049421, 0xf162344e, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0xe11bebe9, 0x78287f13, 0x00025eff, 0x80000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v16) {
  s21_decimal a = {{0x6a44ba3f, 0xf9e88956, 0xeb790773, 0x00000000}};
  s21_decimal b = {{0xf70d998f, 0x443c5225, 0xeb7c5b61, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0x8cc8df50, 0x4a53c8cf, 0x000353ed, 0x80000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v17) {
  s21_decimal a = {{0x61d15063, 0x6a4a7c0e, 0xe1fa9ae6, 0x00000000}};
  s21_decimal b = {{0xec83e3c8, 0xda31d1bd, 0xe1ff78d7, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0x8ab29365, 0x6fe755af, 0x0004ddf1, 0x80000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v18) {
  s21_decimal a = {{0x304f61df, 0x27a03824, 0xd8ff8e29, 0x00000000}};
  s21_decimal b = {{0x8899d6f7, 0x680c35ae, 0xd905e0d2, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0x584a7518, 0x406bfd8a, 0x000652a9, 0x80000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v19) {
  s21_decimal a = {{0x50ea7cab, 0x4b0e617e, 0xcefdc1cb, 0x00000000}};
  s21_decimal b = {{0xd770783a, 0x061cd0ed, 0xcf05b3c5, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0x8685fb8f, 0xbb0e6f6f, 0x0007f1f9, 0x80000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v20) {
  s21_decimal a = {{0xaf1b5e73, 0xfb0edccb, 0xc436e5b4, 0x00000000}};
  s21_decimal b = {{0x2c579c0c, 0xb05615a8, 0xc44096f1, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0x7d3c3d99, 0xb54738dc, 0x0009b13c, 0x80000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v21) {
  s21_decimal a = {{0xf8c4fde7, 0xd1893cc7, 0xb9b1b986, 0x00000000}};
  s21_decimal b = {{0xd48e9459, 0x5681cc8e, 0xb9bd1f60, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0xdbc99672, 0x84f88fc6, 0x000b65d9, 0x80000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v22) {
  s21_decimal a = {{0x948ba6ab, 0x0e1c0a08, 0xae25cdb8, 0x00000000}};
  s21_decimal b = {{0x2f863aba, 0x0ce3bac4, 0xae3312c7, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0x9afa940f, 0xfec7b0bb, 0x000d450e, 0x80000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v23) {
  s21_decimal a = {{0x78c674af, 0xe3108c5a, 0x9e7ee366, 0x00000000}};
  s21_decimal b = {{0x5580996b, 0x041e8634, 0x9e8eb20e, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0xdcba24bc, 0x210df9d9, 0x000fcea7, 0x80000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v24) {
  s21_decimal a = {{0xd82cd0ab, 0xd129b292, 0x8d4dd9a4, 0x00000000}};
  s21_decimal b = {{0x879bfd3a, 0x13aaa49a, 0x8d6071c9, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0xaf6f2c8f, 0x4280f207, 0x00129824, 0x80000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v25) {
  s21_decimal a = {{0xd48f4f9f, 0x39ee50f6, 0x6a26b668, 0x00000000}};
  s21_decimal b = {{0xf1e34767, 0x3eeb8ae1, 0x6a3f0179, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0x1d53f7c8, 0x04fd39eb, 0x00184b11, 0x80000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v26) {
  s21_decimal a = {{0xcd515ff7, 0xe868ee99, 0x5a3e1c2e, 0x00000000}};
  s21_decimal b = {{0xc48dd19d, 0x3a33e425, 0x5a58fb7e, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0xf73c71a6, 0x51caf58b, 0x001adf4f, 0x80000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v27) {
  s21_decimal a = {{0x2b8241bf, 0x986969e7, 0x4f774018, 0x00000000}};
  s21_decimal b = {{0x1974f56f, 0xe46d28e0, 0x4f93deaa, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0xedf2b3b0, 0x4c03bef8, 0x001c9e92, 0x80000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v28) {
  s21_decimal a = {{0x24445217, 0x46e4078a, 0x3f8ea5df, 0x00000000}};
  s21_decimal b = {{0xec1f7fa5, 0xdfb58223, 0x3fadd8af, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0xc7db2d8e, 0x98d17a99, 0x001f32d0, 0x80000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v29) {
  s21_decimal a = {{0xea4ef9b7, 0x749bb657, 0x2d152c94, 0x00000000}};
  s21_decimal b = {{0x7dabbd0d, 0x038565ac, 0x2d375e21, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0x935cc356, 0x8ee9af54, 0x0022318c, 0x80000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v30) {
  s21_decimal a = {{0x9bd25f03, 0xc8cd49d4, 0x1add6331, 0x00000000}};
  s21_decimal b = {{0x6287cef0, 0x2347bb61, 0x1b0288d4, 0x00000000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0xc6b56fed, 0x5a7a718c, 0x002525a2, 0x80000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v31) {
  s21_decimal a = {{0x63879eb8, 0xaee68155, 0x8216d240, 0x00010000}};
  s21_decimal b = {{0x1ce9e159, 0xed647c4e, 0x83a0c119, 0x00010000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0xb96242a1, 0x3e7dfaf8, 0x0189eed9, 0x80010000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v32) {
  s21_decimal a = {{0x043d14c4, 0xe4a40db1, 0xbb552d20, 0x80020000}};
  s21_decimal b = {{0x67833c4e, 0xe6fde132, 0xab0093f0, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0x9cb9d876, 0xfda62c7e, 0x1054992f, 0x80020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v33) {
  s21_decimal a = {{0xf0ebe1c5, 0x3dfce7c1, 0xecd5c886, 0x80010000}};
  s21_decimal b = {{0x4303076e, 0x6ee5474b, 0xeb105d7b, 0x80010000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0xade8da57, 0xcf17a076, 0x01c56b0a, 0x80010000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v34) {
  s21_decimal a = {{0x4124a476, 0x748497d6, 0x325e70c3, 0x80000000}};
  s21_decimal b = {{0x925505ec, 0x18c882bc, 0x322cc5c1, 0x80000000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0xaecf9e8a, 0x5bbc1519, 0x0031ab02, 0x80000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v35) {
  s21_decimal a = {{0x27c77952, 0xa29bd0d9, 0x4c48d75a, 0x80000000}};
  s21_decimal b = {{0x70d3da73, 0x7f6f8e39, 0x4c12f8c9, 0x80000000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0xb6f39edf, 0x232c429f, 0x0035de91, 0x80000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v36) {
  s21_decimal a = {{0x61bcd1b2, 0x74e4220b, 0x5ec250a5, 0x80000000}};
  s21_decimal b = {{0xdf479d0b, 0x5b9faab0, 0x5e897358, 0x80000000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0x827534a7, 0x1944775a, 0x0038dd4d, 0x80000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v37) {
  s21_decimal a = {{0x485fa68e, 0xa2fb5b0e, 0x78acb73c, 0x80000000}};
  s21_decimal b = {{0xbdc67192, 0xc246b62d, 0x786fa660, 0x80000000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0x8a9934fc, 0xe0b4a4e0, 0x003d10db, 0x80000000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v38) {
  s21_decimal a = {{0xc972c607, 0x31934300, 0x19a3c8d9, 0x800a0000}};
  s21_decimal b = {{0x7c29adc6, 0x76f40890, 0x19b36f16, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0x500ef28d, 0x29bba20f, 0x19b36f12, 0x00020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v39) {
  s21_decimal a = {{0x61053788, 0x008c7575, 0x19e56c23, 0x80170000}};
  s21_decimal b = {{0x475df00e, 0x271b801b, 0x19b36f12, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0x46e3a57e, 0x271b801b, 0x19b36f12, 0x00020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v40) {
  s21_decimal a = {{0x885567e5, 0x26901c0a, 0x19a3c8d9, 0x800b0000}};
  s21_decimal b = {{0xd0015a46, 0x957df426, 0x19b36f12, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0xae17a55f, 0x275eb6b3, 0x19b36f12, 0x00020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v41) {
  s21_decimal a = {{0xc40ae40d, 0x91b3e9a9, 0x19a470e1, 0x80020000}};
  s21_decimal b = {{0xf3b16f92, 0x48891a4f, 0x33678693, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0x2fa68b85, 0xb6d530a6, 0x19c315b1, 0x00020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v42) {
  s21_decimal a = {{0x4962cde9, 0x26901cc3, 0x19a3c8d9, 0x80100000}};
  s21_decimal b = {{0xbca2fd36, 0x271bc872, 0x19b36f12, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0x536704ce, 0x271b8047, 0x19b36f12, 0x00020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v43) {
  s21_decimal a = {{0xdb76789f, 0x73c88289, 0x19a3c8dd, 0x80110000}};
  s21_decimal b = {{0x391154fe, 0x271b8757, 0x19b36f12, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0xae8a1fc9, 0x271b801f, 0x19b36f12, 0x00020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v44) {
  s21_decimal a = {{0x95f78b8c, 0xaa6b520b, 0x1c3429bb, 0x80160000}};
  s21_decimal b = {{0x4c1a6a54, 0x271b801b, 0x19b36f12, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0x46e687c5, 0x271b801b, 0x19b36f12, 0x00020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v45) {
  s21_decimal a = {{0x10aaee2b, 0x4d203815, 0x334791b2, 0x80120000}};
  s21_decimal b = {{0xaa85e857, 0x271b818d, 0x19b36f12, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0x286b1bb1, 0x271b801c, 0x19b36f12, 0x00020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v46) {
  s21_decimal a = {{0x8855679e, 0x26901c0a, 0x19a3c8d9, 0x80180000}};
  s21_decimal b = {{0x46ef7de7, 0x271b801b, 0x19b36f12, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0x46e3623e, 0x271b801b, 0x19b36f12, 0x00020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v47) {
  s21_decimal a = {{0x18b3a49c, 0x008cb66b, 0x19e56c23, 0x800b0000}};
  s21_decimal b = {{0xc494c953, 0x969889ca, 0x19b36f12, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0x90678823, 0x275f62c4, 0x19b36f12, 0x00020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v48) {
  s21_decimal a = {{0xa4ad1ba6, 0x2692edbc, 0x19a3c8d9, 0x800b0000}};
  s21_decimal b = {{0xd00d7d53, 0x957df426, 0x19b36f12, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0xae17acc3, 0x275eb6b3, 0x19b36f12, 0x00020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v49) {
  s21_decimal a = {{0xaa3f1c7d, 0x94af597d, 0x19a3c8d9, 0x80070000}};
  s21_decimal b = {{0xe06c72b2, 0x0cf0cb0e, 0x19b37fea, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0xbe05f09c, 0x68a02186, 0x19b36f1c, 0x00020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v50) {
  s21_decimal a = {{0x8855679e, 0x26901c0a, 0x19a3c8d9, 0x80030000}};
  s21_decimal b = {{0x34607d8a, 0xf7d17351, 0x1c456093, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0x26be5994, 0x73f63d50, 0x19b4ffb1, 0x00020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v51) {
  s21_decimal a = {{0x70cbfce3, 0xcae07d67, 0x19a3d9a6, 0x80190000}};
  s21_decimal b = {{0x46e4918f, 0x271b801b, 0x19b36f12, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0x46e35b97, 0x271b801b, 0x19b36f12, 0x00020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v52) {
  s21_decimal a = {{0xdb76789f, 0x73c88289, 0x19a3c8dd, 0x800c0000}};
  s21_decimal b = {{0xaeb2affb, 0x32255884, 0x19b36f12, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0x1f22dcde, 0x272238c4, 0x19b36f12, 0x00020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v53) {
  s21_decimal a = {{0x01b9238d, 0x509825c7, 0x19a3ca87, 0x80150000}};
  s21_decimal b = {{0x764c47c2, 0x271b801b, 0x19b36f12, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0x47003909, 0x271b801b, 0x19b36f12, 0x00020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v54) {
  s21_decimal a = {{0xb7a17335, 0x26901c0a, 0x19a3c8d9, 0x80110000}};
  s21_decimal b = {{0x39101e4a, 0x271b8757, 0x19b36f12, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0xae8a1f0c, 0x271b801f, 0x19b36f12, 0x00020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_sub_v55) {
  s21_decimal a = {{0x8861833f, 0x26901c0a, 0x19a3c8d9, 0x800e0000}};
  s21_decimal b = {{0x45bec6e2, 0x2737c245, 0x19b36f12, 0x80020000}};
  s21_decimal res;
  int s21_ret = s21_sub(a, b, &res);
  s21_decimal expected = {{0x2a51be41, 0x271b9150, 0x19b36f12, 0x00020000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(expected.bits, res.bits, 4 * sizeof(uint32_t));
}
END_TEST

// === Suite s21_sub ===

Suite *s21_sub_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("\033[35m====-{s21_sub_suite}-====\033[0m");
  tc_core = tcase_create("Sub_Core");

  tcase_add_test(tc_core, test_s21_sub_v1);
  tcase_add_test(tc_core, test_s21_sub_v2);
  tcase_add_test(tc_core, test_s21_sub_v3);
  tcase_add_test(tc_core, test_s21_sub_v4);
  tcase_add_test(tc_core, test_s21_sub_v5);
  tcase_add_test(tc_core, test_s21_sub_v6);
  tcase_add_test(tc_core, test_s21_sub_v7);
  tcase_add_test(tc_core, test_s21_sub_v8);
  tcase_add_test(tc_core, test_s21_sub_v9);
  tcase_add_test(tc_core, test_s21_sub_v10);
  tcase_add_test(tc_core, test_s21_sub_v11);
  tcase_add_test(tc_core, test_s21_sub_v12);
  tcase_add_test(tc_core, test_s21_sub_v13);
  tcase_add_test(tc_core, test_s21_sub_v14);
  tcase_add_test(tc_core, test_s21_sub_v15);
  tcase_add_test(tc_core, test_s21_sub_v16);
  tcase_add_test(tc_core, test_s21_sub_v17);
  tcase_add_test(tc_core, test_s21_sub_v18);
  tcase_add_test(tc_core, test_s21_sub_v19);
  tcase_add_test(tc_core, test_s21_sub_v20);
  tcase_add_test(tc_core, test_s21_sub_v21);
  tcase_add_test(tc_core, test_s21_sub_v22);
  tcase_add_test(tc_core, test_s21_sub_v23);
  tcase_add_test(tc_core, test_s21_sub_v24);
  tcase_add_test(tc_core, test_s21_sub_v25);
  tcase_add_test(tc_core, test_s21_sub_v26);
  tcase_add_test(tc_core, test_s21_sub_v27);
  tcase_add_test(tc_core, test_s21_sub_v28);
  tcase_add_test(tc_core, test_s21_sub_v29);
  tcase_add_test(tc_core, test_s21_sub_v30);
  tcase_add_test(tc_core, test_s21_sub_v31);
  tcase_add_test(tc_core, test_s21_sub_v32);
  tcase_add_test(tc_core, test_s21_sub_v33);
  tcase_add_test(tc_core, test_s21_sub_v34);
  tcase_add_test(tc_core, test_s21_sub_v35);
  tcase_add_test(tc_core, test_s21_sub_v36);
  tcase_add_test(tc_core, test_s21_sub_v37);
  tcase_add_test(tc_core, test_s21_sub_v38);
  tcase_add_test(tc_core, test_s21_sub_v39);
  tcase_add_test(tc_core, test_s21_sub_v40);
  tcase_add_test(tc_core, test_s21_sub_v41);
  tcase_add_test(tc_core, test_s21_sub_v42);
  tcase_add_test(tc_core, test_s21_sub_v43);
  tcase_add_test(tc_core, test_s21_sub_v44);
  tcase_add_test(tc_core, test_s21_sub_v45);
  tcase_add_test(tc_core, test_s21_sub_v46);
  tcase_add_test(tc_core, test_s21_sub_v47);
  tcase_add_test(tc_core, test_s21_sub_v48);
  tcase_add_test(tc_core, test_s21_sub_v49);
  tcase_add_test(tc_core, test_s21_sub_v50);
  tcase_add_test(tc_core, test_s21_sub_v51);
  tcase_add_test(tc_core, test_s21_sub_v52);
  tcase_add_test(tc_core, test_s21_sub_v53);
  tcase_add_test(tc_core, test_s21_sub_v54);
  tcase_add_test(tc_core, test_s21_sub_v55);

  suite_add_tcase(s, tc_core);

  return s;
}

// ============ Test for s21_mul ===========

START_TEST(s21_decimal_mul_0) {
  s21_decimal value_1 = {.bits[0] = 0x00000001,
                         .bits[1] = 0x00000000,
                         .bits[2] = 0x00000000,
                         .bits[3] = 0x80000000};  //-1

  s21_decimal value_2 = {.bits[0] = 0x00000001,
                         .bits[1] = 0x00000000,
                         .bits[2] = 0x00000000,
                         .bits[3] = 0x80000000};  // -1

  s21_decimal reference_result = {.bits[0] = 0x00000001,
                                  .bits[1] = 0x00000000,
                                  .bits[2] = 0x00000000,
                                  .bits[3] = 0x00000000};  // 1
  s21_decimal result = {0};
  int sub_result = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(sub_result, 0);
  ck_assert_int_eq(result.bits[0], reference_result.bits[0]);
  ck_assert_int_eq(result.bits[1], reference_result.bits[1]);
  ck_assert_int_eq(result.bits[2], reference_result.bits[2]);
  ck_assert_int_eq(result.bits[3], reference_result.bits[3]);
}
END_TEST

START_TEST(s21_decimal_mul_1) {
  s21_decimal value_1 = {{0x4111b58d, 0xad5e5818, 0x00000006, 0x00190000}};

  s21_decimal value_2 = {{0xc11cc13d, 0xaee52e86, 0x00000006, 0x00190000}};

  s21_decimal reference_result = {
      {0x5f290773, 0x1512d7eb, 0x00000000, 0x001c0000}};  // 1
  s21_decimal result = {0};
  int sub_result = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(sub_result, 0);
  ck_assert_int_eq(result.bits[0], reference_result.bits[0]);
  ck_assert_int_eq(result.bits[1], reference_result.bits[1]);
  ck_assert_int_eq(result.bits[2], reference_result.bits[2]);
  ck_assert_int_eq(result.bits[3], reference_result.bits[3]);
}
END_TEST

START_TEST(s21_decimal_mul_2) {
  s21_decimal value_1 = {{0x4111bf9a, 0xad5e5818, 0x00000006, 0x00190000}};

  s21_decimal value_2 = {{0x4b34791a, 0x1401a7ac, 0x00000008, 0x00190000}};

  s21_decimal reference_result = {
      {0xe7facd26, 0x1978e58c, 0x00000000, 0x001c0000}};
  s21_decimal result = {0};
  int sub_result = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(sub_result, 0);
  ck_assert_int_eq(result.bits[0], reference_result.bits[0]);
  ck_assert_int_eq(result.bits[1], reference_result.bits[1]);
  ck_assert_int_eq(result.bits[2], reference_result.bits[2]);
  ck_assert_int_eq(result.bits[3], reference_result.bits[3]);
}
END_TEST

START_TEST(s21_decimal_mul_3) {
  s21_decimal value_1 = {{0x4111bdde, 0xad5e5818, 0x00000006, 0x00190000}};

  s21_decimal value_2 = {{0x49769f9e, 0xd66206fa, 0x00000007, 0x00190000}};

  s21_decimal reference_result = {
      {0xb1b9bfd3, 0x18b69564, 0x00000000, 0x001c0000}};
  s21_decimal result = {0};
  int sub_result = s21_mul(value_1, value_2, &result);
  ck_assert_int_eq(sub_result, 0);
  ck_assert_int_eq(result.bits[0], reference_result.bits[0]);
  ck_assert_int_eq(result.bits[1], reference_result.bits[1]);
  ck_assert_int_eq(result.bits[2], reference_result.bits[2]);
  ck_assert_int_eq(result.bits[3], reference_result.bits[3]);
}
END_TEST

START_TEST(s21_decimal_mul_4) {
  s21_decimal a = {{0x4111bd39, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0xc8d0efa9, 0xbf7b7680, 0x00000007, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x96a508b6, 0x186e5f63, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_5) {
  s21_decimal value_1 = {{0, 0, 0, 0b00000000000010100000000000000000}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {0};

  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));

  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(s21_decimal_mul_6) {
  s21_decimal a = {{0x4111bffa, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x4b94df7a, 0x215499fc, 0x00000008, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x38e645a6, 0x19a2e90b, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_7) {
  s21_decimal a = {{0x4111bff7, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0xcb91dc47, 0x20ea0269, 0x00000008, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x465ee9e2, 0x19a198ef, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_8) {
  s21_decimal a = {{0x4111bff4, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x4b8ed914, 0x207f6ad7, 0x00000008, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x53d78e1e, 0x19a048d3, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_9) {
  s21_decimal a = {{0x4111bff0, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x4b8ad4d0, 0x1ff14b69, 0x00000008, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x10786919, 0x199e88ae, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_10) {
  s21_decimal a = {{0x4111bfed, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0xcb87d19d, 0x1f86b3d6, 0x00000008, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x1df10d55, 0x199d3892, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_11) {
  s21_decimal a = {{0x4111bfe9, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0xcb83cd59, 0x1ef89468, 0x00000008, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0xda91e84f, 0x199b786c, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_12) {
  s21_decimal a = {{0x4111bfe5, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0xcb7fc915, 0x1e6a74fa, 0x00000008, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x9732c34a, 0x1999b847, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_13) {
  s21_decimal a = {{0x4111bfe1, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0xcb7bc4d1, 0x1ddc558c, 0x00000008, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x53d39e45, 0x1997f822, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_14) {
  s21_decimal a = {{0x4111bfde, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x4b78c19e, 0x1d71bdfa, 0x00000008, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x614c4281, 0x1996a806, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_15) {
  s21_decimal a = {{0x4111bfdb, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0xcb75be6b, 0x1d072667, 0x00000008, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x6ec4e6bd, 0x199557ea, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_16) {
  s21_decimal a = {{0x4111bfd2, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x4b6cb4d2, 0x1bc75fb0, 0x00000008, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x972ed371, 0x19916796, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_17) {
  s21_decimal a = {{0x4111bfce, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x4b68b08e, 0x1b394042, 0x00000008, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x53cfae6b, 0x198fa771, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_18) {
  s21_decimal a = {{0x4111bfca, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x4b64ac4a, 0x1aab20d4, 0x00000008, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x10708966, 0x198de74c, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_19) {
  s21_decimal a = {{0x4111bf67, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0xcb0142b7, 0x0ced96f1, 0x00000008, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0xccfdb521, 0x196293b1, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_20) {
  s21_decimal a = {{0x4111bf01, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0xca9ad5f1, 0xfec5757c, 0x00000007, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x97038518, 0x1935effb, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_21) {
  s21_decimal a = {{0x4111be6a, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x4a0334ea, 0xe9d05304, 0x00000007, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0xe7bbcf8e, 0x18f3da7c, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_22) {
  s21_decimal a = {{0x4111be03, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0xc99bc713, 0xdb84a9b3, 0x00000007, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x60e9d644, 0x18c6c6bd, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_23) {
  s21_decimal a = {{0x4111be00, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x4998c3e0, 0xdb1a1221, 0x00000007, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x6e627a80, 0x18c576a1, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_24) {
  s21_decimal a = {{0x4111bdf0, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x4988b2d0, 0xd8e19469, 0x00000007, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x60e5e66b, 0x18be760c, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_25) {
  s21_decimal a = {{0x4111bd8f, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0xc9274b5f, 0xcb6b1a3d, 0x00000007, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0xbf22a4a9, 0x18940284, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_26) {
  s21_decimal a = {{0x4111bd34, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x48cbea54, 0xbec9cf37, 0x00000007, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x026e1a6f, 0x186c2f35, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_27) {
  s21_decimal a = {{0x4111bcb4, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x484b61d4, 0xad05e177, 0x00000007, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x968979c3, 0x18342a8c, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_28) {
  s21_decimal a = {{0x4111bc5a, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x47f101da, 0xa0881e4c, 0x00000007, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x2aacb8cb, 0x180cc746, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_29) {
  s21_decimal a = {{0x4111bbf2, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x478892f2, 0x9218ed20, 0x00000007, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x5302f640, 0x17df437d, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_30) {
  s21_decimal a = {{0x4111bb80, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x47161960, 0x82466d61, 0x00000007, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x52eb5727, 0x17ad5f57, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_31) {
  s21_decimal a = {{0x4111bb19, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0xc6aeab89, 0x73fac410, 0x00000007, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0xcc195ddd, 0x17804b97, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_32) {
  s21_decimal a = {{0x4111bac1, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0xc6564db1, 0x67c4109c, 0x00000007, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x01ec2f68, 0x1759c864, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_33) {
  s21_decimal a = {{0x4111ba91, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0xc6261a81, 0x611a9774, 0x00000007, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0xd9767327, 0x1744c6a4, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_34) {
  s21_decimal a = {{0x4111ba70, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x4604f750, 0x5c861429, 0x00000007, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x6da581bb, 0x17365571, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_35) {
  s21_decimal a = {{0x4111ba1a, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x45ae9b9a, 0x5096706c, 0x00000007, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x4527e5c8, 0x1710b250, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_36) {
  s21_decimal a = {{0x4111b9c0, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x45543ba0, 0x4418ad41, 0x00000007, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0xd94b24d0, 0x16e94f09, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_37) {
  s21_decimal a = {{0x4111b950, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x44e3c430, 0x348d3d39, 0x00000007, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x7ae3183a, 0x16b84af6, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_38) {
  s21_decimal a = {{0x4111b8d0, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x44633bb0, 0x22c94f79, 0x00000007, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x0efe778f, 0x1680464e, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_39) {
  s21_decimal a = {{0x4111b85f, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0xc3f1c32f, 0x131a5795, 0x00000007, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x5fbea1b8, 0x164ed231, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_40) {
  s21_decimal a = {{0x4111b7f0, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x43824cd0, 0x03b26f69, 0x00000007, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x522e5e63, 0x161e3e27, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_41) {
  s21_decimal a = {{0x4111b797, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0xc328ede7, 0xf7583419, 0x00000006, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x372966ac, 0x15f74aea, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_42) {
  s21_decimal a = {{0x4111b72d, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0xc2be7cdd, 0xe8a1f336, 0x00000006, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0xbdd0119f, 0x15c8e70e, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_43) {
  s21_decimal a = {{0x4111b6dc, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x426d267c, 0xdd63f6c3, 0x00000006, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x298963f3, 0x15a5741c, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_44) {
  s21_decimal a = {{0x4111b699, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0xc229df09, 0xd4176850, 0x00000006, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x010fb7d9, 0x158821ac, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_45) {
  s21_decimal a = {{0x4111b65a, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x41ea9bda, 0xcb58f94c, 0x00000006, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x1bf530c5, 0x156c8f61, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_46) {
  s21_decimal a = {{0x4111b624, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x41b46244, 0xc3da50ff, 0x00000006, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x0e70bcfd, 0x1554ed6a, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_47) {
  s21_decimal a = {{0x4111b5e7, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0xc1772137, 0xbb62f1b1, 0x00000006, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0xcb05c86b, 0x153a3b31, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_48) {
  s21_decimal a = {{0x4111b5a9, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0xc138df19, 0xb2c80a88, 0x00000006, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x36c30a99, 0x151f18f0, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_49) {
  s21_decimal a = {{0x4111b583, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0xc112b693, 0xad81dff3, 0x00000006, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x36bb2ae6, 0x150e778e, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_50) {
  s21_decimal a = {{0x4111b591, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0xc120c581, 0xaf734df4, 0x00000006, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0xa2882c79, 0x15149810, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_51) {
  s21_decimal a = {{0x4111b5ab, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0xc13ae13b, 0xb30f1a3f, 0x00000006, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0xd8729d1b, 0x151ff902, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_52) {
  s21_decimal a = {{0x4111be38, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x49d0ff98, 0xe2dfca25, 0x00000007, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x1d9680cb, 0x18ddf8ab, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_53) {
  s21_decimal a = {{0x4111be45, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0xc9de0d75, 0xe4adb04a, 0x00000007, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x388bb91d, 0x18e3a924, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_decimal_mul_54) {
  s21_decimal a = {{0x4111be6e, 0xad5e5818, 0x00000006, 0x00190000}};
  s21_decimal b = {{0x4a07392e, 0xea5e7272, 0x00000007, 0x00190000}};
  s21_decimal res;
  int s21_ret = s21_mul(a, b, &res);
  s21_decimal expected = {{0x2b1af493, 0x18f59aa2, 0x00000000, 0x001c0000}};
  int expected_ret = 0;
  // int mem_cmp = memcmp(res.bits,expected.bits,4*sizeof(uint32_t));
  // printf("%s",(mem_cmp)?"Different\n":"Same\n");
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

Suite *s21_mul_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("\033[35m====-{s21_mul}-====\033[0m");
  tc_core = tcase_create("s21_mul_Core");

  tcase_add_test(tc_core, s21_decimal_mul_0);
  tcase_add_test(tc_core, s21_decimal_mul_1);
  tcase_add_test(tc_core, s21_decimal_mul_2);
  tcase_add_test(tc_core, s21_decimal_mul_3);
  tcase_add_test(tc_core, s21_decimal_mul_4);
  tcase_add_test(tc_core, s21_decimal_mul_5);
  tcase_add_test(tc_core, s21_decimal_mul_6);
  tcase_add_test(tc_core, s21_decimal_mul_7);
  tcase_add_test(tc_core, s21_decimal_mul_8);
  tcase_add_test(tc_core, s21_decimal_mul_9);
  tcase_add_test(tc_core, s21_decimal_mul_10);
  tcase_add_test(tc_core, s21_decimal_mul_11);
  tcase_add_test(tc_core, s21_decimal_mul_12);
  tcase_add_test(tc_core, s21_decimal_mul_13);
  tcase_add_test(tc_core, s21_decimal_mul_14);
  tcase_add_test(tc_core, s21_decimal_mul_15);
  tcase_add_test(tc_core, s21_decimal_mul_16);
  tcase_add_test(tc_core, s21_decimal_mul_17);
  tcase_add_test(tc_core, s21_decimal_mul_18);
  tcase_add_test(tc_core, s21_decimal_mul_19);
  tcase_add_test(tc_core, s21_decimal_mul_20);
  tcase_add_test(tc_core, s21_decimal_mul_21);
  tcase_add_test(tc_core, s21_decimal_mul_22);
  tcase_add_test(tc_core, s21_decimal_mul_23);
  tcase_add_test(tc_core, s21_decimal_mul_24);
  tcase_add_test(tc_core, s21_decimal_mul_25);
  tcase_add_test(tc_core, s21_decimal_mul_26);
  tcase_add_test(tc_core, s21_decimal_mul_27);
  tcase_add_test(tc_core, s21_decimal_mul_28);
  tcase_add_test(tc_core, s21_decimal_mul_29);
  tcase_add_test(tc_core, s21_decimal_mul_30);
  tcase_add_test(tc_core, s21_decimal_mul_31);
  tcase_add_test(tc_core, s21_decimal_mul_32);
  tcase_add_test(tc_core, s21_decimal_mul_33);
  tcase_add_test(tc_core, s21_decimal_mul_34);
  tcase_add_test(tc_core, s21_decimal_mul_35);
  tcase_add_test(tc_core, s21_decimal_mul_36);
  tcase_add_test(tc_core, s21_decimal_mul_37);
  tcase_add_test(tc_core, s21_decimal_mul_38);
  tcase_add_test(tc_core, s21_decimal_mul_39);
  tcase_add_test(tc_core, s21_decimal_mul_40);
  tcase_add_test(tc_core, s21_decimal_mul_41);
  tcase_add_test(tc_core, s21_decimal_mul_42);
  tcase_add_test(tc_core, s21_decimal_mul_43);
  tcase_add_test(tc_core, s21_decimal_mul_44);
  tcase_add_test(tc_core, s21_decimal_mul_45);
  tcase_add_test(tc_core, s21_decimal_mul_46);
  tcase_add_test(tc_core, s21_decimal_mul_47);
  tcase_add_test(tc_core, s21_decimal_mul_48);
  tcase_add_test(tc_core, s21_decimal_mul_49);
  tcase_add_test(tc_core, s21_decimal_mul_50);
  tcase_add_test(tc_core, s21_decimal_mul_51);
  tcase_add_test(tc_core, s21_decimal_mul_52);
  tcase_add_test(tc_core, s21_decimal_mul_53);
  tcase_add_test(tc_core, s21_decimal_mul_54);
  suite_add_tcase(s, tc_core);

  return s;
}

START_TEST(s21_div_normal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {{1535}};
  value_1.bits[0] = 150;
  value_2.bits[0] = 35;
  set_scale(&value_2, 1);
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 1);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(s21_div_both_neg) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {{1535}};
  value_1.bits[0] = 150;
  value_2.bits[0] = 35;
  set_sign(&value_1, 1);
  set_sign(&value_2, 1);
  set_scale(&value_2, 1);
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 1);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(s21_div_error) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 35;
  int res = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(res, 1);
  set_sign(&value_2, 1);
  set_sign(&value_1, 1);
  memset(&result, 0, sizeof(s21_decimal));
  res = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(s21_div_normal2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {{1535}};
  value_1.bits[0] = 150;
  value_2.bits[0] = 35;
  set_scale(&value_2, 1);
  int res = s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 1);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_div_both_neg2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_decimal test = {{1535}};
  value_1.bits[0] = 150;
  value_2.bits[0] = 35;
  set_sign(&value_2, 1);
  set_sign(&value_1, 1);
  set_scale(&value_2, 1);
  int res = s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 1);
  ck_assert_int_eq(get_sign(result), 1);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_div_error2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 4294967295;
  value_1.bits[1] = 4294967295;
  value_1.bits[2] = 4294967295;
  value_2.bits[0] = 35;
  int res = s21_div(value_1, value_2, &result);
  ck_assert_int_eq(res, 1);
  set_sign(&value_2, 1);
  set_sign(&value_1, 1);

  memset(&result, 0, sizeof(s21_decimal));
  res = s21_add(value_1, value_2, &result);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(part1_div_one_greater) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 540;
  value_2.bits[0] = 560;
  s21_decimal test = {{20}};
  set_sign(&value_2, 1);
  s21_div(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(part1_div_one_greater2) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 540;
  value_2.bits[0] = 560;
  s21_decimal test = {{20}};
  set_sign(&value_1, 1);
  s21_div(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

START_TEST(part1_div_one_sign) {
  s21_decimal value_1 = {{150}};
  s21_decimal value_2 = {{50}};
  s21_decimal result = {0};
  s21_decimal test = {{100}};
  set_sign(&value_1, 1);
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 1);
  set_sign(&value_1, 0);
  set_sign(&value_2, 1);
  memset(&result, 0, sizeof(s21_decimal));
  int res = s21_add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_div_sign) {
  s21_decimal value_1 = {{150}};
  s21_decimal value_2 = {{50}};
  s21_decimal result = {0};
  s21_decimal test = {{100}};
  set_sign(&value_1, 1);
  s21_div(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 1);
  set_sign(&value_1, 0);
  set_sign(&value_2, 1);
  memset(&result, 0, sizeof(s21_decimal));
  s21_add(value_1, value_2, &result);
  ck_assert_uint_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_scale(result), 0);
  ck_assert_int_eq(get_sign(result), 0);
}
END_TEST

Suite *s21_div_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("\033[35m====-{s21_div}-====\033[0m");
  tc_core = tcase_create("s21_div_Core");

  tcase_add_test(tc_core, s21_div_normal);
  tcase_add_test(tc_core, s21_div_both_neg);
  tcase_add_test(tc_core, s21_div_error);
  tcase_add_test(tc_core, s21_div_normal2);
  tcase_add_test(tc_core, s21_div_both_neg2);
  tcase_add_test(tc_core, s21_div_error2);
  tcase_add_test(tc_core, part1_div_one_greater);
  tcase_add_test(tc_core, part1_div_one_greater2);
  tcase_add_test(tc_core, part1_div_one_sign);
  tcase_add_test(tc_core, s21_div_sign);
  suite_add_tcase(s, tc_core);

  return s;
}

// ============ Test for s21_floor ============

START_TEST(s21_floor_1) {
  s21_decimal a = {{0xff57162f, 0x174ff0e4, 0x3e2129cb, 0x001b0000}};
  s21_decimal res;
  s21_decimal expected = {{0x00000013, 0x00000000, 0x00000000, 0x00000000}};
  int s21_ret = s21_floor(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_floor_2) {
  s21_decimal a = {{0xb8bdf40f, 0x911be896, 0x3e2129d0, 0x00110000}};
  s21_decimal res;
  s21_decimal expected = {{0xc4e0c68d, 0x0000002c, 0x00000000, 0x00000000}};
  int s21_ret = s21_floor(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_floor_3) {
  s21_decimal a = {{0xd6c3369f, 0x35a5e618, 0x3e2129d2, 0x800e0000}};
  s21_decimal res;
  s21_decimal expected = {{0x0e0c3971, 0x0000aee1, 0x00000000, 0x80000000}};
  int s21_ret = s21_floor(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_floor_4) {
  s21_decimal a = {{0x44ff0000, 0x67732363, 0x5ea68b9c, 0x000f0000}};
  s21_decimal res;
  s21_decimal expected = {{0x4accef76, 0x00001aa4, 0x00000000, 0x00000000}};
  int s21_ret = s21_floor(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_floor_5) {
  s21_decimal a = {{0x57e3f000, 0x3a7b1eb0, 0x000100ad, 0x801c0000}};
  s21_decimal res;
  s21_decimal expected = {{0x00000001, 0x00000000, 0x00000000, 0x80000000}};
  int s21_ret = s21_floor(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_floor_6) {
  s21_decimal a = {{0xc21f0000, 0x84e3bbf7, 0x723bc2fa, 0x00090000}};
  s21_decimal res;
  s21_decimal expected = {{0x2d459980, 0xeaa0fff5, 0x00000001, 0x00000000}};
  int s21_ret = s21_floor(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_floor_7) {
  s21_decimal a = {{0x967f0000, 0x395e997e, 0x78c2d56f, 0x00070000}};
  s21_decimal res;
  s21_decimal expected = {{0x6173b600, 0x9a7bfb83, 0x000000ca, 0x00000000}};
  int s21_ret = s21_floor(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_floor_8) {
  s21_decimal a = {{0xd1281800, 0x588f9004, 0x00001787, 0x001c0000}};
  s21_decimal res;
  s21_decimal expected = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  int s21_ret = s21_floor(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

Suite *s21_floor_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("\033[35m====-{s21_floor}-====\033[0m");
  tc_core = tcase_create("s21_floor_Core");
  tcase_add_test(tc_core, s21_floor_1);
  tcase_add_test(tc_core, s21_floor_2);
  tcase_add_test(tc_core, s21_floor_3);
  tcase_add_test(tc_core, s21_floor_4);
  tcase_add_test(tc_core, s21_floor_5);
  tcase_add_test(tc_core, s21_floor_6);
  tcase_add_test(tc_core, s21_floor_7);
  tcase_add_test(tc_core, s21_floor_8);
  suite_add_tcase(s, tc_core);
  return s;
}

// ============ Tests for s21_round ============

START_TEST(s21_round_0) {
  s21_decimal a = {{0x9ab8b17f, 0xec91eb14, 0x3e2129ce, 0x80140000}};
  s21_decimal res;
  s21_decimal expected = {{0x0b75fc1a, 0x00000000, 0x00000000, 0x80000000}};
  int s21_ret = s21_round(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_round_1) {
  s21_decimal a = {{0x30d2fe4f, 0x2343de9f, 0x3e2129d7, 0x00050000}};
  s21_decimal res;
  s21_decimal expected = {{0x6a7e7215, 0x9ba0147d, 0x000028b7, 0x00000000}};
  int s21_ret = s21_round(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_round_2) {
  s21_decimal a = {{0xc7df0000, 0x4a028ace, 0x4b11543e, 0x00150000}};
  s21_decimal res;
  s21_decimal expected = {{0x01627f45, 0x00000000, 0x00000000, 0x00000000}};
  int s21_ret = s21_round(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_round_3) {
  s21_decimal a = {{0x57ef0000, 0x2aa64d34, 0x6ef839c0, 0x800a0000}};
  s21_decimal res;
  s21_decimal expected = {{0x974109c0, 0x2fa93d6f, 0x00000000, 0x80000000}};
  int s21_ret = s21_round(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_round_4) {
  s21_decimal a = {{0xc21f0000, 0x84e3bbf7, 0x723bc2fa, 0x00090000}};
  s21_decimal res;
  s21_decimal expected = {{0x2d459980, 0xeaa0fff5, 0x00000001, 0x00000000}};
  int s21_ret = s21_round(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_round_5) {
  s21_decimal a = {{0x2c4f0000, 0xdf212abb, 0x757f4c34, 0x80080000}};
  s21_decimal res;
  s21_decimal expected = {{0x74082f00, 0xb677ff90, 0x00000013, 0x80000000}};
  int s21_ret = s21_round(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_round_6) {
  s21_decimal a = {{0x967f0000, 0x395e997e, 0x78c2d56f, 0x00070000}};
  s21_decimal res;
  s21_decimal expected = {{0x6173b600, 0x9a7bfb83, 0x000000ca, 0x00000000}};
  int s21_ret = s21_round(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_round_7) {
  s21_decimal a = {{0x57e3f000, 0x3a7b1eb0, 0x000100ad, 0x801c0000}};
  s21_decimal res;
  s21_decimal expected = {{0x00000000, 0x00000000, 0x00000000, 0x80000000}};
  int s21_ret = s21_round(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_round_8) {
  s21_decimal a = {{0xf535e9f0, 0x000e5ab9, 0x00000000, 0x801c0000}};
  s21_decimal res;
  s21_decimal expected = {{0x00000000, 0x00000000, 0x00000000, 0x80000000}};
  int s21_ret = s21_round(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

Suite *s21_round_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("\033[35m====-{s21_round}-====\033[0m");
  tc_core = tcase_create("s21_round_Core");
  tcase_add_test(tc_core, s21_round_0);
  tcase_add_test(tc_core, s21_round_1);
  tcase_add_test(tc_core, s21_round_2);
  tcase_add_test(tc_core, s21_round_3);
  tcase_add_test(tc_core, s21_round_4);
  tcase_add_test(tc_core, s21_round_5);
  tcase_add_test(tc_core, s21_round_6);
  tcase_add_test(tc_core, s21_round_7);
  tcase_add_test(tc_core, s21_round_8);
  suite_add_tcase(s, tc_core);
  return s;
}

START_TEST(test_s21_negate_0) {
  s21_decimal a = {{0x23559a40, 0x00000002, 0x00000000, 0x800a0000}};
  s21_decimal res;
  s21_decimal expected = {{0x23559a40, 0x00000002, 0x00000000, 0x000a0000}};
  int s21_ret = s21_negate(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_negate_1) {
  s21_decimal a = {{0xd6b52360, 0x00000001, 0x00000000, 0x800a0000}};
  s21_decimal res;
  s21_decimal expected = {{0xd6b52360, 0x00000001, 0x00000000, 0x000a0000}};
  int s21_ret = s21_negate(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(test_s21_negate_2) {
  s21_decimal a = {{0x23559a40, 0x00000002, 0x00000000, 0x000a0000}};
  s21_decimal res;
  s21_decimal expected = {{0x23559a40, 0x00000002, 0x00000000, 0x800a0000}};
  int s21_ret = s21_negate(a, &res);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

Suite *s21_negate_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("\033[35m====-{s21_negate}-====\033[0m");
  tc_core = tcase_create("s21negate_Core");
  tcase_add_test(tc_core, test_s21_negate_0);
  tcase_add_test(tc_core, test_s21_negate_1);
  tcase_add_test(tc_core, test_s21_negate_2);
  suite_add_tcase(s, tc_core);
  return s;
}

// ============ Test for s21_truncate ============

static s21_decimal arr[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  // -1
    {{0xCF5C048C, 0x004D2BEF, 0x00000000, 0x00070000}},  // 2172188218.2812812
    {{0xFEADBDA2, 0x000001FB, 0x00000000, 0x80060000}},  // -2181821.218210
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950335
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  // -79228162514264337593543950335
    {{0x00000000, 0x00000000, 0x00000000, 0x00020000}},  // 0.00
    {{0x000F4240, 0x00000000, 0x00000000, 0x00020000}},  // 10000.00
    {{0x000F4240, 0x00000000, 0x00000000, 0x80020000}},  // -10000.00
    {{0x00000467, 0x0000007A, 0x00000000, 0x00040000}},  // 52398601.1239
    {{0x00000467, 0x0000007A, 0x00000000, 0x80000000}},  // -523986011239
    {{0x00000467, 0x0000007A, 0x00003215,
      0x00010000}},  // 23650570576955414727997.5
    {{0x00000467, 0x0000007A, 0x00205FF0,
      0x80020000}},  // -391386782621189641642978.31
    {{0x000F4240, 0x00002710, 0x00002710,
      0x80050000}},  // -1844674407800451901.20000
    {{0x0000000E, 0x00000000, 0x00000000, 0x00000000}},  // 14
    {{0x0000000F, 0x00000000, 0x00000000, 0x80000000}},  // -15
    {{0x000186A0, 0x00000000, 0x00000000, 0x00000000}},  // 100000
    {{0x0000000B, 0x00000000, 0x00000000, 0x00010000}},  // 1.1
    {{0x0000000B, 0x00000000, 0x00000000, 0x80010000}},  // -1.1
    {{0x0000000F, 0x00000000, 0x00000000, 0x80010000}},  // -1.5
    {{0x0000000F, 0x00000000, 0x00000000, 0x00010000}},  // 1.5
    {{0x00000086, 0x00000000, 0x00000000, 0x80020000}},  // -1.34
    {{0x00000086, 0x00000000, 0x00000000, 0x00020000}},  // 1.34
    {{0x000006E5, 0x00000000, 0x00000000, 0x00030000}},  // 1.765
    {{0x000006E5, 0x00000000, 0x00000000, 0x80030000}},  // -1.765
    {{0x00000019, 0x00000000, 0x00000000, 0x00010000}},  // 2.5
    {{0x00000019, 0x00000000, 0x00000000, 0x80010000}},  // -2.5
    {{0x1FC40A5F, 0xA98FD4BE, 0x00000000,
      0x00020000}},  // 122182182271212611.51
    {{0x1FC40A5D, 0xA98FD4BE, 0x00000000,
      0x00020000}},  // 122182182271212611.49
    {{0x1FC40A5F, 0xA98FD4BE, 0x00000000,
      0x80020000}},  // -122182182271212611.51
    {{0x1FC40A5D, 0xA98FD4BE, 0x00000000,
      0x80020000}},  // -122182182271212611.49
    {{0x075BCD15, 0x00000000, 0x00000000, 0x00030000}},  // 123456.789
    {{0x075BCD15, 0x00000000, 0x00000000, 0x00090000}},  // 0.123456789
    {{0x075BCD15, 0x00000000, 0x00000000, 0x00120000}},  // 0.000000000123456789
    {{0x075BCD15, 0x00000000, 0x00000000,
      0x001B0000}},  // 0.000000000000000000123456789
    {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x00060000}},  // 4294.967295
    {{0xFFFFFFFF, 0xFFFFFFFF, 0x00000000,
      0x00050000}},  // 184467440737095.51615
    {{0xFFFFFFFF, 0x00000000, 0x00000000, 0x80060000}},  // -4294.967295
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x001C0000}},  // 7.9228162514264337593543950335
    {{0xFFFFFFFF, 0xFFFFFFFF, 0x00000000,
      0x80050000}},  // -184467440737095.51615
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x801C0000}},  // -7.9228162514264337593543950335
};

static s21_decimal result[] = {
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  //-1
    {{0x8178F63A, 0x00000000, 0x00000000, 0x00000000}},  // 2172188218
    {{0x00214ABD, 0x00000000, 0x00000000, 0x80000000}},  //-2181821
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x00000000}},  // 79228162514264337593543950335
    {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
      0x80000000}},  //-79228162514264337593543950335
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
    {{0x00002710, 0x00000000, 0x00000000, 0x00000000}},  // 10000
    {{0x00002710, 0x00000000, 0x00000000, 0x80000000}},  //-10000
    {{0x031F8A09, 0x00000000, 0x00000000, 0x00000000}},  // 52398601
    {{0x00000467, 0x0000007A, 0x00000000, 0x80000000}},  //-523986011239
    {{0xCCCCCD3D, 0x199999A5, 0x00000502,
      0x00000000}},  // 23650570576955414727997
    {{0xBD70A3E2, 0x1EB851EC, 0x000052E1,
      0x80000000}},  //-391386782621189641642978
    {{0xB333333D, 0x19999999, 0x00000000, 0x80000000}},
    //-1844674407800451901
    {{0x0000000E, 0x00000000, 0x00000000, 0x00000000}},  // 14
    {{0x0000000F, 0x00000000, 0x00000000, 0x80000000}},  //-15
    {{0x000186A0, 0x00000000, 0x00000000, 0x00000000}},  // 100000
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  //-1
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  //-1
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  //-1
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
    {{0x00000001, 0x00000000, 0x00000000, 0x00000000}},  // 1
    {{0x00000001, 0x00000000, 0x00000000, 0x80000000}},  //-1
    {{0x00000002, 0x00000000, 0x00000000, 0x00000000}},  // 2
    {{0x00000002, 0x00000000, 0x00000000, 0x80000000}},  //-2
    {{0x24285C43, 0x01B2140C, 0x00000000, 0x00000000}},  // 122182182271212611
    {{0x24285C43, 0x01B2140C, 0x00000000, 0x00000000}},  // 122182182271212611
    {{0x24285C43, 0x01B2140C, 0x00000000, 0x80000000}},  //-122182182271212611
    {{0x24285C43, 0x01B2140C, 0x00000000, 0x80000000}},  //-122182182271212611
    {{0x0001E240, 0x00000000, 0x00000000, 0x00000000}},  // 123456
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
    {{0x00000000, 0x00000000, 0x00000000, 0x00000000}},  // 0
    {{0x000010C6, 0x00000000, 0x00000000, 0x00000000}},  // 4294
    {{0xAC471B47, 0x0000A7C5, 0x00000000, 0x00000000}},  // 184467440737095
    {{0x000010C6, 0x00000000, 0x00000000, 0x80000000}},  //-4294
    {{0x00000007, 0x00000000, 0x00000000, 0x00000000}},  // 7
    {{0xAC471B47, 0x0000A7C5, 0x00000000, 0x80000000}},  //-184467440737095
    {{0x00000007, 0x00000000, 0x00000000, 0x80000000}},  //-7
};

START_TEST(test_s21_truncate) {
  for (size_t i = 0; i < sizeof(arr) / sizeof(s21_decimal); ++i) {
    s21_decimal tmp;
    int ret = s21_truncate(arr[i], &tmp);
    ck_assert_int_eq(tmp.bits[0], result[i].bits[0]);
    ck_assert_int_eq(tmp.bits[1], result[i].bits[1]);
    ck_assert_int_eq(tmp.bits[2], result[i].bits[2]);
    ck_assert_int_eq(tmp.bits[3], result[i].bits[3]);
    ck_assert_int_eq(ret, 0);
  }
}
END_TEST

Suite *s21_truncate_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("\033[35m====-{s21_truncate}-====\033[0m");
  tc_core = tcase_create("s21_truncate_Core");
  tcase_add_test(tc_core, test_s21_truncate);
  suite_add_tcase(s, tc_core);

  return s;
}

// ============ Test for s21_from_int_to_decimal ============

START_TEST(s21_from_int_to_decimal_0) {
  s21_decimal res;
  int fromInt = 2147483647;
  int s21_ret = s21_from_int_to_decimal(fromInt, &res);
  s21_decimal expected = {{0x7fffffff, 0x00000000, 0x00000000, 0x00000000}};
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_from_int_to_decimal_1) {
  s21_decimal res;
  int fromInt = -489;
  int s21_ret = s21_from_int_to_decimal(fromInt, &res);
  s21_decimal expected = {{0x000001e9, 0x00000000, 0x00000000, 0x80000000}};
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

START_TEST(s21_from_int_to_decimal_2) {
  s21_decimal res;
  int fromInt = -419;
  int s21_ret = s21_from_int_to_decimal(fromInt, &res);
  s21_decimal expected = {{0x000001a3, 0x00000000, 0x00000000, 0x80000000}};
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_mem_eq(&expected, &res, 4 * sizeof(uint32_t));
}
END_TEST

Suite *s21_from_int_to_decimal_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("\033[35m====-{s21_from_int_to_decimal}-====\033[0m");
  tc_core = tcase_create("s21_from_int_to_decimal_Core");
  tcase_add_test(tc_core, s21_from_int_to_decimal_0);
  tcase_add_test(tc_core, s21_from_int_to_decimal_1);
  tcase_add_test(tc_core, s21_from_int_to_decimal_2);
  suite_add_tcase(s, tc_core);

  return s;
}

// ============ Test for s21_from_decimal_to_int ============

START_TEST(s21_from_decimal_to_int_0) {
  s21_decimal a = {{0xba1eccc0, 0xc20df37b, 0x3ec10d97, 0x80130000}};
  int toInt = 0;
  int s21_ret = s21_from_decimal_to_int(a, &toInt);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_int_eq(toInt, -1942145748);
}
END_TEST

START_TEST(s21_from_decimal_to_int_1) {
  s21_decimal a = {{0xad95c559, 0xb3d99c8e, 0x24372227, 0x00130000}};
  int toInt = 0;
  int s21_ret = s21_from_decimal_to_int(a, &toInt);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_int_eq(toInt, 1120811256);
}
END_TEST

START_TEST(s21_from_decimal_to_int_2) {
  s21_decimal a = {{0x65ea2349, 0x429f839f, 0x2d9d5d09, 0x00130000}};
  int toInt = 0;
  int s21_ret = s21_from_decimal_to_int(a, &toInt);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_int_eq(toInt, 1411706614);
}
END_TEST

START_TEST(s21_from_decimal_to_int_3) {
  s21_decimal a = {{0x00000000, 0x00000001, 0x00000001, 0x00000000}};
  int toInt = 0;
  int s21_ret = s21_from_decimal_to_int(a, &toInt);
  int expected_ret = 1;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_int_eq(toInt, 0);
}
END_TEST

Suite *s21_from_decimal_to_int_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("\033[35m====-{s21_from_decimal_to_int}-====\033[0m");
  tc_core = tcase_create("s21_from_decimal_to_int_Core");
  tcase_add_test(tc_core, s21_from_decimal_to_int_0);
  tcase_add_test(tc_core, s21_from_decimal_to_int_1);
  tcase_add_test(tc_core, s21_from_decimal_to_int_2);
  tcase_add_test(tc_core, s21_from_decimal_to_int_3);
  suite_add_tcase(s, tc_core);
  return s;
}

// ============ Test for s21_from_decimal_to_float ============

START_TEST(s21_from_decimal_to_float_0) {
  s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 0x80000000}};
  uint32_t u_fl = 0xEF800000;
  float toFloat = 0.0;
  float expectedFloat = 0.0;
  memcpy(&expectedFloat, &u_fl, sizeof(uint32_t));
  int s21_ret = s21_from_decimal_to_float(a, &toFloat);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_float_eq(expectedFloat, toFloat);
}
END_TEST

START_TEST(s21_from_decimal_to_float_1) {
  s21_decimal a = {{0x270ae101, 0x070acf57, 0xc4a2bb63, 0x80190000}};
  uint32_t u_fl = 0xC5BE2CA2;
  float toFloat = 0.0;
  float expectedFloat = 0.0;
  memcpy(&expectedFloat, &u_fl, sizeof(uint32_t));
  int s21_ret = s21_from_decimal_to_float(a, &toFloat);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_float_eq(expectedFloat, toFloat);
}
END_TEST

START_TEST(s21_from_decimal_to_float_2) {
  s21_decimal a = {{0x29b6f8a3, 0xff6dd0e9, 0x0effcd58, 0x80190000}};
  uint32_t u_fl = 0xC3E81A0F;
  float toFloat = 0.0;
  float expectedFloat = 0.0;
  memcpy(&expectedFloat, &u_fl, sizeof(uint32_t));
  int s21_ret = s21_from_decimal_to_float(a, &toFloat);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_float_eq(expectedFloat, toFloat);
}
END_TEST

START_TEST(s21_from_decimal_to_float_3) {
  s21_decimal a = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  uint32_t u_fl = 0x00000000;
  float toFloat = 0.0;
  float expectedFloat = 0.0;
  memcpy(&expectedFloat, &u_fl, sizeof(uint32_t));
  int s21_ret = s21_from_decimal_to_float(a, &toFloat);
  int expected_ret = 0;
  ck_assert_int_eq(s21_ret, expected_ret);
  ck_assert_float_eq(expectedFloat, toFloat);
}
END_TEST

Suite *s21_from_decimal_to_float_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("\033[35m====-{s21_from_decimal_to_float}-====\033[0m");
  tc_core = tcase_create("s21_from_decimal_to_float_Core");
  tcase_add_test(tc_core, s21_from_decimal_to_float_0);
  tcase_add_test(tc_core, s21_from_decimal_to_float_1);
  tcase_add_test(tc_core, s21_from_decimal_to_float_2);
  tcase_add_test(tc_core, s21_from_decimal_to_float_3);
  suite_add_tcase(s, tc_core);
  return s;
}

/* ----------------------------------------------------------------
 * s21_from_float_to_decimal
 * ---------------------------------------------------------------- */

START_TEST(from_float_to_decimal_1) {
  float src = 56.986;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "56986 0 0 196608";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(from_float_to_decimal_2) {
  float src = 1.0 / 0.0;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "0 0 0 0";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 1);
}
END_TEST

START_TEST(from_float_to_decimal_3) {
  float src = -1.596;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "1596 0 0 2147680256";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(from_float_to_decimal_4) {
  float src = 46237.42332 / 12712.37834;
  s21_decimal z = {{0, 0, 0, 0}};
  int n1 = s21_from_float_to_decimal(src, &z);
  char res1[1000], res2[1000] = "3637197 0 0 393216";
  snprintf(res1, sizeof(char) * 1000, "%u %u %u %u", z.bits[0], z.bits[1],
           z.bits[2], z.bits[3]);
  ck_assert_str_eq(res1, res2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

Suite *s21_from_float_to_decimal_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("\033[35m====-{s21_from_float_to_decimal}-====\033[0m");
  tc_core = tcase_create("s21_from_float_to_decimal_Core");
  tcase_add_test(tc_core, from_float_to_decimal_1);
  tcase_add_test(tc_core, from_float_to_decimal_2);
  tcase_add_test(tc_core, from_float_to_decimal_3);
  tcase_add_test(tc_core, from_float_to_decimal_4);
  suite_add_tcase(s, tc_core);
  return s;
}

START_TEST(s21_is_less_normal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  for (int i = 1, j = 2; i < 50 || j < 51; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(s21_is_less(value_1, value_2), 1);
    ck_assert_int_eq(s21_is_less(value_2, value_1), 0);
  }
}
END_TEST

START_TEST(s21_is_less_negative) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 20;
  value_2.bits[0] = 5;
  set_sign(&value_1, 1);
  ck_assert_int_eq(s21_is_less(value_1, value_2), 1);
  set_sign(&value_1, 0);
  set_sign(&value_2, 1);
  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
}
END_TEST

START_TEST(s21_is_less_pow) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 50;
  value_2.bits[0] = 30;
  set_scale(&value_1, 8);
  set_scale(&value_2, 8);
  ck_assert_int_eq(s21_is_less(value_1, value_2), 0);
  set_scale(&value_2, 0);
  ck_assert_int_eq(s21_is_less(value_1, value_2), 1);
}
END_TEST

START_TEST(s21_is_less_or_equal_normal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  for (int i = 0, j = 1; i < 51 || j < 52; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 1);
  }
  for (int i = 0, j = 0; i < 52 || j < 52; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 1);
  }
}
END_TEST

START_TEST(s21_is_less_or_equal_with_sign) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 123450;
  value_2.bits[0] = 123450;
  set_sign(&value_2, 1);
  ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 0);
  set_sign(&value_1, 1);
  ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 1);
  set_sign(&value_1, 0);
  ck_assert_int_eq(s21_is_less_or_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(s21_is_greater_null) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 0;
  value_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_greater(value_1, value_2), 0);
  set_sign(&value_2, 1);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), 0);
}
END_TEST

START_TEST(s21_is_greater_normal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  for (int i = 1, j = 2; i < 50 || j < 51; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(s21_is_greater(value_1, value_2), 0);
    ck_assert_int_eq(s21_is_greater(value_2, value_1), 1);
  }
}
END_TEST

START_TEST(s21_is_greater_negative) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 20;
  value_2.bits[0] = 5;
  set_sign(&value_1, 1);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), 0);
  set_sign(&value_1, 0);
  set_sign(&value_2, 1);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), 1);
}
END_TEST

START_TEST(s21_is_greater_two_negative) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 20;
  value_2.bits[0] = 5;
  set_sign(&value_1, 1);
  set_sign(&value_2, 1);
  ck_assert_int_eq(s21_is_greater(value_1, value_2), 0);
}
END_TEST

START_TEST(s21_is_greater_or_equal_normal) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  for (int i = 0, j = 1; i < 51 || j < 52; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), 0);
  }
  for (int i = 0, j = 0; i < 52 || j < 52; i++, j++) {
    value_1.bits[0] = i;
    value_2.bits[0] = j;
    ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), 1);
  }
}
END_TEST

START_TEST(s21_is_greater_or_equal_with_sign) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  value_1.bits[0] = 123450;
  value_2.bits[0] = 123450;
  set_sign(&value_2, 1);
  ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), 1);
  set_sign(&value_1, 1);
  ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), 1);
  set_sign(&value_2, 0);
  ck_assert_int_eq(s21_is_greater_or_equal(value_1, value_2), 0);
}
END_TEST

START_TEST(s21_one_greater) {
  s21_decimal value_1 = {0};
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  value_1.bits[0] = 540;
  value_2.bits[0] = 560;
  s21_decimal test = {{20}};
  set_sign(&value_2, 1);
  s21_add(value_1, value_2, &result);
  ck_assert_int_eq(result.bits[0], test.bits[0]);
  ck_assert_int_eq(get_sign(result), 1);
}
END_TEST

START_TEST(isEqual_1) {
  s21_decimal a = {{48, 0}}, b = {{48, 0}};
  ck_assert_uint_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(isEqual_2) {
  s21_decimal a = {{1, 1, 0, 0}}, b = {{1, 1, 1, 0}};
  ck_assert_uint_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(s21_not_equal_null) {
  s21_decimal value = {0};
  s21_decimal test = {0};
  int res = s21_is_not_equal(value, test);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(s21_not_equal_normal) {
  s21_decimal value = {{5}};
  s21_decimal test = {{6}};
  int res = s21_is_not_equal(value, test);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(s21_not_equal_negative) {
  s21_decimal value = {{5}};
  s21_decimal test = {{5}};
  set_sign(&value, 1);
  int res = s21_is_not_equal(value, test);
  ck_assert_int_eq(res, 1);
}
END_TEST

Suite *s21_compare_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("\033[35m====-{s21_compare_suite}-====\033[0m");
  tc_core = tcase_create("Compare_Core");

  tcase_add_test(tc_core, s21_is_less_normal);
  tcase_add_test(tc_core, s21_is_less_negative);
  tcase_add_test(tc_core, s21_is_less_pow);

  tcase_add_test(tc_core, s21_is_less_or_equal_normal);
  tcase_add_test(tc_core, s21_is_less_or_equal_with_sign);

  tcase_add_test(tc_core, s21_is_greater_null);
  tcase_add_test(tc_core, s21_is_greater_normal);
  tcase_add_test(tc_core, s21_is_greater_negative);
  tcase_add_test(tc_core, s21_is_greater_two_negative);
  tcase_add_test(tc_core, s21_is_greater_or_equal_normal);
  tcase_add_test(tc_core, s21_is_greater_or_equal_with_sign);
  tcase_add_test(tc_core, s21_one_greater);

  tcase_add_test(tc_core, isEqual_1);
  tcase_add_test(tc_core, isEqual_2);
  tcase_add_test(tc_core, s21_not_equal_null);
  tcase_add_test(tc_core, s21_not_equal_normal);
  tcase_add_test(tc_core, s21_not_equal_negative);

  suite_add_tcase(s, tc_core);

  return s;
}

int main() {
  int number_failed = 0;
  Suite *decimal_tests[] = {s21_add_suite(),
                            s21_sub_suite(),
                            s21_mul_suite(),
                            s21_div_suite(),
                            s21_floor_suite(),
                            s21_round_suite(),
                            s21_negate_suite(),
                            s21_truncate_suite(),
                            s21_from_int_to_decimal_suite(),
                            s21_from_decimal_to_int_suite(),
                            s21_from_decimal_to_float_suite(),
                            s21_from_float_to_decimal_suite(),
                            s21_compare_suite(),
                            NULL};
  for (int i = 0; decimal_tests[i] != NULL; i++) {
    SRunner *srunner;
    srunner = srunner_create(decimal_tests[i]);
    srunner_set_fork_status(srunner, CK_NOFORK);
    srunner_run_all(srunner, CK_NORMAL);
    number_failed += srunner_ntests_failed(srunner);
    srunner_free(srunner);
  }
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
