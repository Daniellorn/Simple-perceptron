#include "Utils.h"
#include <QDebug>
#include <fstream>
#include <immintrin.h>

int Utils::RandomInt(int max)
{
    std::uniform_int_distribution<int> distribution(0, max);
    return distribution(Instance());
}

float Utils::RandomFloat(float min, float max)
{
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(Instance());
}

float Utils::DotProduct(const std::array<int, 36>& input, const std::array<float, 36>& weights)
{
    __m256 sum = _mm256_setzero_ps();

    constexpr int FLOATS_IN_AVX_REGISTER = 8;
    const int samples = (input.size() / FLOATS_IN_AVX_REGISTER) * FLOATS_IN_AVX_REGISTER;

    for (int i = 0; i < samples; i+=FLOATS_IN_AVX_REGISTER)
    {
        __m256 w = _mm256_loadu_ps(weights.data() + i);

        __m256i inputs = _mm256_loadu_si256((__m256i*)(input.data() + i));

        __m256 inputsFloats = _mm256_cvtepi32_ps(inputs);
        sum = _mm256_add_ps(sum, _mm256_mul_ps(w, inputsFloats));
    }

    __m128 lo = _mm256_castps256_ps128(sum);
    __m128 hi = _mm256_extractf128_ps(sum, 1);
    __m128 s128 = _mm_add_ps(lo, hi);

    s128 = _mm_hadd_ps(s128, s128);
    s128 = _mm_hadd_ps(s128, s128);
    float dotpr = _mm_cvtss_f32(s128);

    for (int i = samples; i < 36; i++)
    {
        dotpr += (float)input[i] * weights[i];
    }

    return dotpr;
}

void Utils::saveInput(const QVariantList& gridlist)
{
    std::ofstream file("Data.txt", std::ios::app);

    if (file)
    {
        for (int i = 0; i < 35; i++)
        {
            file << gridlist[i].toInt() << " ";
        }
        file << "\n";
        file << gridlist[35].toInt() << "\n";
    }
}
