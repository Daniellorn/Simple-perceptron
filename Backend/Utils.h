#ifndef UTILS_H
#define UTILS_H

#include <QObject>
#include <random>
#include <QVariantList>

class Utils: public QObject
{
    Q_OBJECT
public:

    static int RandomInt(int max);
    static float RandomFloat(float min, float max);
    static float DotProduct(const std::array<int, 36>& input, const std::array<float, 36>& weights);

    Q_INVOKABLE void saveInput(const QVariantList& gridlist);

private:

    static std::mt19937& Instance()
    {
        static std::mt19937 engine(std::random_device{}());
        return engine;
    }
};


#endif // UTILS_H
