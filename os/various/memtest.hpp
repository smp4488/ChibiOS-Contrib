/*
    ChibiOS/RT - Copyright (C) 2013-2014 Uladzimir Pylinsky aka barthess

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef MEMTEST_HPP_
#define MEMTEST_HPP_

#define MEMTEST_WALKING_ONE               (1 << 0)
#define MEMTEST_WALKING_ZERO              (1 << 1)
#define MEMTEST_OWN_ADDRESS               (1 << 2)
#define MEMTEST_MOVING_INVERSION_ZERO     (1 << 3)
#define MEMTEST_MOVING_INVERSION_55AA     (1 << 4)
#define MEMTEST_MOVING_INVERSION_RAND     (1 << 5)

#define MEMTEST_RUN_ALL                   (MEMTEST_WALKING_ONE              | \
                                           MEMTEST_WALKING_ZERO             | \
                                           MEMTEST_OWN_ADDRESS              | \
                                           MEMTEST_MOVING_INVERSION_ZERO    | \
                                           MEMTEST_MOVING_INVERSION_55AA    | \
                                           MEMTEST_MOVING_INVERSION_RAND)

typedef struct memtest_t memtest_t;
typedef uint32_t testtype;

/*
 * Error call back.
 */
typedef void (*memtestecb_t)(memtest_t *testp, testtype type, size_t offset,
                           size_t current_width, uint32_t got, uint32_t expect);

/*
 *
 */
typedef enum {
  MEMTEST_WIDTH_8,
  MEMTEST_WIDTH_16,
  MEMTEST_WIDTH_32,
} memtest_bus_width_t;

/*
 *
 */
struct memtest_t {
  /*
   * Pointer to the test area start. Must be word aligned.
   */
  void                *start;
  /*
   * Test area size in bytes.
   */
  size_t              size;
  /*
   * Maximum width of transactions.
   * Note: it implies all narrower tests.
   * Note: width my be wider then your memory interface because AHB is
   *       smart enough to split big transactions to smaller ones.
   */
  memtest_bus_width_t width;
  /*
   * Error callback pointer. Set to NULL if unused.
   */
  memtestecb_t        errcb;
};

/*
 *
 */
#ifdef __cplusplus
extern "C" {
#endif
  void memtest_run(memtest_t *testp, uint32_t testmask);
#ifdef __cplusplus
}
#endif

#endif /* MEMTEST_HPP_ */
