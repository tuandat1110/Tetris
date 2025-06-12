#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

Model::Model() : modelListener(0)
{

}

void Model::tick()
{

}

void Model::setFinalScore(int s) { finalScore = s; }
int Model::getFinalScore() const { return finalScore; }
