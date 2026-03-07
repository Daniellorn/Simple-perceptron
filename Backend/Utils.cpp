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
    __m128 sum = _mm_setzero_ps();

    for (int i = 0; i < 32; i+=4)
    {
        __m128 w = _mm_loadu_ps(&weights[i]);
        __m128i inputs = _mm_loadu_si128((__m128i*)&input[i]);
        __m128 inputsFloats = _mm_cvtepi32_ps(inputs);

        sum = _mm_add_ps(sum, _mm_mul_ps(w, inputsFloats));
    }

    alignas(16) float temp[4];
    _mm_store_ps(temp, sum);
    float dotpr = temp[0] + temp[1] + temp[2] + temp[3];

    for (int i = 32; i < 36; i++)
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
