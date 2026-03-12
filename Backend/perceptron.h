#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <array>
#include <vector>

struct Input
{
    std::array<int, 36> pixels;
    int number;
};

class Perceptron
{
public:

    Perceptron(int target);

    void Train(const std::vector<Input>& input, int iterations);

    static int Predict(const std::array<int, 36>& pixels, const std::array<Perceptron, 10>& net);

    const std::array<float, 36>& GetWeights() const { return m_Weights; }
    static int GetErrors() { return m_ErrorsNumber; }

private:
    std::array<float, 36> m_Weights;
    std::array<float, 36> m_Pocket;
    int m_Target;
    static inline int m_ErrorsNumber = 0;
};



#endif // PERCEPTRON_H
