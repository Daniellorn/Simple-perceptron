#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "Backend/Utils.h"
#include "Backend/perceptron.h"
#include "Backend/classifier.h"

#include <fstream>
#include <string>
#include <sstream>

std::vector<Input> LoadData(std::ifstream& file)
{
    std::vector<Input> inputs;
    Input current;
    current.pixels[0] = 1;

    std::string line;
    int numline = 0;

    while(std::getline(file, line))
    {
        std::istringstream iss(line);
        numline++;

        if ((numline % 2) == 0)
        {
            iss >> current.number;
            inputs.push_back(current);
        }
        else
        {
            for (int i = 1; i < 36; i++)
            {
                iss >> current.pixels[i];
            }
        }
    }

    return inputs;
}


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    Utils utils;

    std::array<Perceptron, 10> net
    {
        Perceptron(0), Perceptron(1), Perceptron(2), Perceptron(3), Perceptron(4),
        Perceptron(5), Perceptron(6), Perceptron(7), Perceptron(8), Perceptron(9)
    };

    std::ifstream inputFile("Data.txt");

    if (inputFile)
    {
        auto inputs = LoadData(inputFile);

        for (int i = 0; i < 10; i++)
        {
            net[i].Train(inputs, 1000);
        }
    }

    Classifier classifier(net);

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("utils", &utils);
    engine.rootContext()->setContextProperty("backend", &classifier);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("NumbersPerceptron", "Main");

    return app.exec();
}
