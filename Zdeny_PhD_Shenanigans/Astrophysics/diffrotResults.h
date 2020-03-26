#pragma once
#include "stdafx.h"
#include "Core/functionsBaseCV.h"
#include "Plot/Plot1D.h"
#include "Plot/Plot2D.h"

class DiffrotResults
{
public:
	void ShowResults( int medianSize, double sigma, double quanBot = 0, double quanTop = 1 )
	{
		// reset
		FlowX = SourceFlowX.clone();

		if ( medianSize )
		{
			for ( int med = 3; med <= min( medianSize, 7 ); med += 2 )
			{
				medianBlur( FlowX, FlowX, med );
			}
		}

		// diffrot profile
		Plot1D::plot( SourceThetas, std::vector<std::vector<double>> {SourceOmegasXavg, SourceOmegasXavgpolyfit, SourceOmegasXavgsin2sin4fit, SourcePredicX1, SourcePredicX2}, "diffrot profile X", "solar latitude [deg]", "horizontal plasma flow speed [deg/day]", std::vector<std::string> {"omegasXavg", "omegasXavgpolyfit", "omegasXavgsin2sin4fit", "predicX1", "predicX2"}, saveDir + "diffrotprofileXs" + to_string( SourceStride ) + ".png" );

		// shifts profile
		Plot1D::plot( SourceThetas, SourceShiftsX, "shifts profile X", "solar latitude [deg]", "horizontal px shift [px]", saveDir + "shiftsprofileXs" + to_string( SourceStride ) + ".png" );

		// flow X jet
		Plot2D::plot( applyQuantile( FlowX, quanBot, quanTop ), "diffrot flow X", "time [hours]", "solar latitude [deg]", "horizontal plasma flow speed [deg/day]", 0, ( double )( SourcePics - 1 ) * SourceStride * 45 / 60 / 60, SourceThetas.front(), SourceThetas.back(), colRowRatio, saveDir + to_string( medianSize ) + "_diffrotflowXs" + to_string( SourceStride ) + ".png" );

		// relative flow X jet
		Plot2D::plot( applyQuantile( FlowX - SourcePredicX, quanBot, quanTop ), "diffrot relative flow X", "time [hours]", "solar latitude [deg]", "relative horizontal plasma flow speed [deg/day]", 0, ( double )( SourcePics - 1 ) * SourceStride * 45 / 60 / 60, SourceThetas.front(), SourceThetas.back(), colRowRatio, saveDir + to_string( medianSize ) + "_diffrotrelativeflowXs" + to_string( SourceStride ) + ".png" );

		// source img
		showimg( SourceImage, "diffrot source" );

		// relative flow X binary
		showimg( combineTwoPics( FlowX - SourcePredicX, SourceImage, bluered, sigma ), "diffrot relative flow X binary", false, quanBot, quanTop );

		// relative magnitude & absolute phase

	}

	void SetData2D( const std::vector<std::vector<double>> &image, const std::vector<std::vector<double>> &flowX, const std::vector<std::vector<double>> &predicX )
	{
		flip( matFromVector( image, true ), SourceImage, 1 );
		flip( matFromVector( flowX, true ), SourceFlowX, 1 );
		flip( matFromVector( predicX, true ), SourcePredicX, 1 );
	}

	void SetData1D( const std::vector<double> &thetas, const std::vector<double> &omegasXavg, const std::vector<double> &omegasXavgpolyfit, const std::vector<double> &omegasXavgsin2sin4fit, const std::vector<double> &predicX1, const std::vector<double> &predicX2, const std::vector<double> &shiftsX )
	{
		SourceThetas = ( 360. / Constants::TwoPi ) * thetas;
		SourceOmegasXavg = omegasXavg;
		SourceOmegasXavgpolyfit = omegasXavgpolyfit;
		SourceOmegasXavgsin2sin4fit = omegasXavgsin2sin4fit;
		SourcePredicX1 = predicX1;
		SourcePredicX2 = predicX2;
		SourceShiftsX = shiftsX;
	}

	void SetParams( int pics, int stride )
	{
		SourcePics = pics;
		SourceStride = stride;
	}

private:

	// source data
	Mat SourceImage;
	Mat SourceFlowX;
	Mat SourcePredicX;
	int SourcePics;
	int SourceStride;
	std::vector<double> SourceThetas;
	std::vector<double> SourceOmegasXavg;
	std::vector<double> SourceOmegasXavgpolyfit;
	std::vector<double> SourceOmegasXavgsin2sin4fit;
	std::vector<double> SourcePredicX1;
	std::vector<double> SourcePredicX2;
	std::vector<double> SourceShiftsX;

	// internal data
	Mat FlowX;
	std::string saveDir = "C:\\Users\\Zdeny\\Desktop\\PhD_things\\diffrot\\plotsave\\";
	static constexpr double colRowRatio = 2;
};