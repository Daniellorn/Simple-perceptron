#include "perceptron.h"
#include <random>
#include <algorithm>

#include "Utils.h"

Perceptron::Perceptron(int target)
{
    std::generate(m_Weights.begin(), m_Weights.end(), []()
                  { return Utils::RandomFloat(0.0f, 0.3);});

    m_Target = target;
}

void Perceptron::Train(const std::vector<Input>& input, int iterations)
{
    int currentLifeTime = 0;
    int pocketLifeTime = 0;
    m_Pocket = m_Weights;
    float learningRate = 0.1f;

    int maxIndex = input.size();

    for (int i = 0; i < iterations; i++)
    {
        auto sample = input[Utils::RandomInt(maxIndex - 1)];

        int predicted = Utils::DotProduct(sample.pixels, m_Weights) >= 0.0f ? 1: -1;
        int expected = (m_Target == sample.number) ? 1: -1;
        int error = expected - predicted;

        if (error == 0)
        {
            currentLifeTime++;

            if (currentLifeTime > pocketLifeTime)
            {
                pocketLifeTime = currentLifeTime;
                m_Pocket = m_Weights;
            }
        }
        else
        {
            for (int j = 0; j < 36; j++)
            {
                m_Weights[j] += learningRate * error * sample.pixels[j];
            }
            currentLifeTime = 0;
        }
    }

    m_Weights = m_Pocket;
}

int Perceptron::Predict(const std::array<int, 36> &pixels, const std::array<Perceptron, 10>& net)
{
    int bestDigit = 0;
    float bestScore = -std::numeric_limits<float>::max();

    for (int i = 0; i < 10; i++)
    {
        float score = Utils::DotProduct(pixels, net[i].GetWeights());

        if (score > bestScore)
        {
            bestScore = score;
            bestDigit = i;
        }
    }
    return bestDigit;
}

