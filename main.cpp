/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-09-20
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "EWLIB/stdEWLIB.h"
#include <fftw3.h>

int main() {
    const int N = 2048;  // 샘플 개수
    double in[N];     // 입력 데이터
    fftw_complex out[N/2 + 1];  // 복소 출력 데이터

    // 예제 입력 (사인파)
    for (int i = 0; i < N; ++i)
        in[i] = sin(2 * M_PI * i / N);

    // FFT 계획(plan) 생성
    fftw_plan plan = fftw_plan_dft_r2c_1d(N, in, out, FFTW_ESTIMATE);

    // FFT 실행
    fftw_execute(plan);

    // 결과 출력
    std::cout << "FFT 결과:\n";
    for (int i = 0; i < N/2 + 1; ++i)
        std::cout << i << ": " << out[i][0] << " + " << out[i][1] << "i\n";

    // 계획 해제
    fftw_destroy_plan(plan);
    fftw_cleanup();

    return 0;
}
