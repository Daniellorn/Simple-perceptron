#include "classifier.h"
#include <QVariant>

int Classifier::check(const QVariantList &pixels)
{
    std::array<int, 36> input;
    input[0] = 1;

    for (int i = 0; i < 35; i++)
    {
        input[i + 1] = pixels[i].toInt();
    }

    return Perceptron::Predict(input, m_Net);
}

int Classifier::getError()
{
    return Perceptron::GetErrors();
}
