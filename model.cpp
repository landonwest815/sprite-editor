#include "model.h"
#include "Tool.h"

Model::Model()
{
    draw = *new Tool("draw", false);
    erase = *new Tool("erase", false);
    mirror = *new Tool("mirror", true);
}
