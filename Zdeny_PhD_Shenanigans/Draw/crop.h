#pragma once
#include "Core/functionsBaseCV.h"

inline Mat roicrop( const Mat &sourceimgIn, int x, int y, int w, int h )
{
	Rect roi = Rect( x - std::floor( ( double )w / 2. ), y - std::floor( ( double )h / 2. ), w, h );
	Mat crop = sourceimgIn( roi );
	return crop.clone();
}

inline Mat kirkl( unsigned size )
{
	Mat kirkl = Mat::zeros( size, size, CV_32F );
	for ( int r = 0; r < size; r++ )
	{
		for ( int c = 0; c < size; c++ )
		{
			if ( ( sqr( ( double )r - floor( size / 2 ) ) + sqr( ( double )c - floor( size / 2 ) ) ) < sqr( ( double )size / 2 + 1 ) )
			{
				kirkl.at<float>( r, c ) = 1.;
			}
			else
			{
				kirkl.at<float>( r, c ) = 0.;
			}
		}
	}
	return kirkl;
}

inline Mat kirkl( int rows, int cols, unsigned radius )
{
	Mat kirkl = Mat::zeros( rows, cols, CV_32F );
	for ( int r = 0; r < rows; r++ )
	{
		for ( int c = 0; c < cols; c++ )
		{
			if ( ( sqr( ( double )r - floor( rows / 2 ) ) + sqr( ( double )c - floor( cols / 2 ) ) ) < sqr( radius ) )
			{
				kirkl.at<float>( r, c ) = 1.;
			}
			else
			{
				kirkl.at<float>( r, c ) = 0.;
			}
		}
	}
	return kirkl;
}

inline Mat kirklcrop( const Mat &sourceimgIn, int x, int y, int diameter )
{
	Mat crop = roicrop( sourceimgIn, x, y, diameter, diameter );
	Mat kirklik = kirkl( diameter );
	return crop.mul( kirklik );
}