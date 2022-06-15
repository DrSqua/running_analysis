//
// Created by Robbe on 04/05/2022.
//

#ifndef CSV_PARSER_ROUTEGRAPH_H
#define CSV_PARSER_ROUTEGRAPH_H

#include "algorithm"

#include "raylib.h"
#include "../data_processing/data_processer.h"
#include "../data_processing/DataSet.h"

#define STRAVA_ORANGE CLITERAL(Color){252, 76, 2, 255}

const float border_float = 10;
const int border_int = 10;

void drawBackground();
void drawDataset(const DataSet& dataSet);
void drawDataset(const DataSet& pointDataSet, const DataSet& dataDataSet, const Font& font);

#endif //CSV_PARSER_ROUTEGRAPH_H
