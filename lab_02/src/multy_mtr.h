#ifndef MULTY_MTR_H
#define MULTY_MTR_H

#include <iostream>
#include "matrix_config.h"

matrix_v empty_matrix();

matrix_v standart_multy(const matrix_v &mtr1, const matrix_v &mtr2);
matrix_v vinograd_alg(const matrix_v &mtr1, const matrix_v &mtr2);
matrix_v opt_vinograd_alg(const matrix_v &mtr1, const matrix_v &mtr2);

#endif //MULTY_MTR_H
