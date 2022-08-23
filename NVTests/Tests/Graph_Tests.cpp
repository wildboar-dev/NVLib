//--------------------------------------------------
// Unit Tests for class Graph
//
// @author: Wild Boar
//
// @date: 2022-02-07
//--------------------------------------------------

#include <gtest/gtest.h>

#include <NVLib/Graphics/Graph.h>
using namespace NVLib;

//--------------------------------------------------
// Test Methods
//--------------------------------------------------

/**
 * @brief Confirm that we are able to render the graph
 */
TEST(Graph_Test, render_test)
{
	// Setup
	auto graphic = Graph("Sine", "Amplitude", "Angle");

	auto values_1 = vector<Point2d>(); auto values_2 = vector<Point2d>();
	for (auto i=0; i <= 180; i++) 
	{
		auto radians = (i / 180.0) * M_PI;
		auto value = sin(radians);
		values_1.push_back(Point2d(i, value));
		values_2.push_back(Point2d(i, cos(radians)));
	}
	auto series_1 = GraphSeries("wave_1", Vec3i(0,0,255), values_1); graphic.AddSeries(series_1);
	auto series_2 = GraphSeries("cos test", Vec3i(255, 0, 0), values_2); graphic.AddSeries(series_2);

	// Execute
	Mat graphImage = graphic.Render(Size(1000, 500));
	imwrite("graph.png", graphImage);

	// Check out the image as the test.. oh and the system did not crash (haha)
}
