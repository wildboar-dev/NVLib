//--------------------------------------------------
// Implementation code for RandomUtils
//
// @author: Wild Boar
//--------------------------------------------------

#include "RandomUtils.h"
using namespace NVLib;

//--------------------------------------------------
// GetKMatrix
//--------------------------------------------------

/**
 * Generate a random K Matrix
 * @param focal Range for the focal length generation
 * @param imageSize The size of the image we are generating for
 * @param centerOffset The range of center ofsets to chose from
 * @param sameFocal Indicate if we want the focals to be the same or different
 * @return Return a Mat
 */
cv::Mat RandomUtils::GetKMatrix(const Range<double> & focal, const cv::Size & imageSize, const Range<double>& centerOffset, bool sameFocal)
{
	auto fx = GetValue(focal);
	auto fy = (sameFocal) ? fx : GetValue(focal);
	auto cx = (imageSize.width * 0.5) + GetValue(centerOffset);
	auto cy = (imageSize.width * 0.5) + GetValue(centerOffset);
	return (cv::Mat_<double>(3,3) << fx, cx, 0, 0, fy, cy, 0, 0, 1);
}

//--------------------------------------------------
// GetPoseMatrix
//--------------------------------------------------

/**
 * Generate a random pose
 * @param rx A range for the rotation in x (degrees)
 * @param ry A range for the rotation in y (degrees)
 * @param rz A range for the rotation in z (degrees)
 * @param tx A translation in the x-direction
 * @param ty A range for the translation in the y-direction
 * @param tz A range for the translation in the z-direction
 * @return Return a Mat
 */
cv::Mat RandomUtils::GetPoseMatrix(const Range<double>&  rx, const Range<double>& ry, const Range<double>& rz, const Range<double>& tx, const Range<double> ty, const Range<double>& tz)
{
	auto rotationX = GetValue(rx);
	auto rotationY = GetValue(ry);
	auto rotationZ = GetValue(rz);

	auto translationX = GetValue(tx);
	auto translationY = GetValue(ty);
	auto translationZ = GetValue(tz);

	auto rvec = Vec3d(rotationX, rotationY, rotationZ);
	auto tvec = Vec3d(translationX, translationY, translationZ);

	Mat rotation = PoseUtils::Euler2Matrix(rvec);

	return PoseUtils::GetPose(rotation, tvec);
}

//--------------------------------------------------
// GetDistortionMatrix
//--------------------------------------------------

/**
 * Generate a random distortion matrix
 * @param k1 Defines a range for k1
 * @param k2 A range for the k2 variable
 * @param p1 A range for tangential parameter p1
 * @param p2 A tangential parameter for p2
 * @return Return a Mat
 */
cv::Mat RandomUtils::GetDistortionMatrix(const Range<double> & k1, const Range<double> & k2, const Range<double> & p1, const Range<double>& p2)
{
	auto k1Distortion = GetValue(k1);
	auto k2Distortion = GetValue(k2);
	auto p1Distortion = GetValue(p1);
	auto p2Distortion = GetValue(p2);

	return (cv::Mat_<double>(4, 1) << k1Distortion, k2Distortion, p1Distortion, p2Distortion);
}

//--------------------------------------------------
// GetValue
//--------------------------------------------------

/**
 * Retrieve a random variable
 * @param range The value that we want the random variable in
 * @return Return a double
 */
double RandomUtils::GetValue(const Range<double>& range)
{
	if (range.GetMax() == range.GetMin()) return range.GetMax();
	random_device device;
	auto generator = default_random_engine(device());
	auto distribution = uniform_real_distribution<double>(range.GetMin(), range.GetMax());
	return distribution(generator);
}

//--------------------------------------------------
// GetRandomPoint
//--------------------------------------------------

/**
 * @brief Generate a random point
 * @param region The region from which to select the random point
 * @return Point The point that we found
 */
Point RandomUtils::GetRandomPoint(const Rect region) 
{
	auto x = rand() % region.width + region.x;
	auto y = rand() % region.height + region.y; 
	return Point(x, y);
}
