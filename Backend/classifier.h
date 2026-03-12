#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <QObject>

#include "perceptron.h"

class Classifier : public QObject
{
    Q_OBJECT
public:
    explicit Classifier(const std::array<Perceptron, 10>& net, QObject *parent = nullptr):
        QObject(parent), m_Net(net){}

    Q_INVOKABLE int check(const QVariantList& pixels);
    Q_INVOKABLE int getError();

private:
    std::array<Perceptron, 10> m_Net;

signals:
};

#endif // CLASSIFIER_H
