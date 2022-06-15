//
// Created by Robbe on 04/05/2022.
//

#include "Routegraph.h"

void drawBackground()  {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), STRAVA_ORANGE);
    DrawRectangle(border_int, 0, GetScreenWidth(), GetScreenHeight()-border_int, LIGHTGRAY);
}

void drawDataset(const DataSet& dataSet) {
    if (!dataSet.filled()) return;
    if (dataSet.x_points.size() != dataSet.y_points.size()) return;

    auto screenheight = (float)GetScreenHeight();

    for (auto index=0; index<dataSet.x_points.size(); ++index) {
        Vector2 dot = {dataSet.x_points.at(index) + border_float, screenheight - dataSet.y_points.at(index) - border_float};

        DrawCircleV(dot, 6, STRAVA_ORANGE);
        DrawCircleV(dot, 3, LIGHTGRAY);
    }
}

void drawDataset(const DataSet &pointDataSet, const DataSet &dataDataSet, const Font& font) {
    if (!pointDataSet.same_size(dataDataSet)) return;
    auto screenheight = (float)GetScreenHeight();

    for (auto index=0; index < pointDataSet.x_points.size(); ++index) {
        Vector2 dotV2 = {pointDataSet.x_points.at(index) + border_float, screenheight - pointDataSet.y_points.at(index) - border_float};
        Vector2 textV2 = {dotV2.x-6, dotV2.y-16};

        DrawCircleV(dotV2, 6, STRAVA_ORANGE);
        DrawCircleV(dotV2, 3, LIGHTGRAY);

        DrawText(TextFormat("%01.1f, %01.02f", dataDataSet.x_points.at(index), dataDataSet.y_points.at(index)), textV2.x, textV2.y, 6, STRAVA_ORANGE);
    }

}
