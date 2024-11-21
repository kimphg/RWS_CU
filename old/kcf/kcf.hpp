/*******************************************************************************
* Created by Qiang Wang on 16/7.24
* Copyright 2016 Qiang Wang.  [wangqiang2015-at-ia.ac.cn]
* Licensed under the Simplified BSD License
*******************************************************************************/

#ifndef SRC_KCF_HPP_
#define SRC_KCF_HPP_

#define PI 3.141592653589793

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <string>
#include <cmath>
#include "fhog.hpp"
#include <QQueue>
#include <qvector.h>
#define TRACK_MEM_SIZE 100
using namespace cv;
using namespace std;

class KCF
{
public:
  KCF(std::string kernel_type = "gaussian", std::string feature_type = "hog");
  bool Init(cv::Mat image, cv::Rect rect_init);
  cv::Rect Update(cv::Mat image);
  void setInterp_factor(float interp_factor);

  void setLearning_rate(float value);
  QVector<double> trackmax;
  double trackmean=0;
  QVector<double> timeline;
  int frameW,frameH;
  double trackLostSens = 2.5;
  cv::Rect getsearchingRect();
protected:
  void Learn(cv::Mat &patch, float lr);

  cv::Mat CreateGaussian1D(int n, float sigma);

  cv::Mat CreateGaussian2D(cv::Size sz, float sigma);

  cv::Mat GaussianShapedLabels(float sigma, cv::Size sz);

  cv::Mat CalculateHann(cv::Size sz);

  cv::Mat GetSubwindow(const cv::Mat &frame, cv::Point centraCoor, cv::Size sz);

  std::vector<cv::Mat> GetFeatures(cv::Mat patch);

  cv::Mat GaussianCorrelation(std::vector<cv::Mat> xf, std::vector<cv::Mat> yf);

  cv::Mat PolynomialCorrelation(std::vector<cv::Mat> xf, std::vector<cv::Mat> yf);

  cv::Mat LinearCorrelation(std::vector<cv::Mat> xf, std::vector<cv::Mat> yf);

  cv::Mat ComplexMul(const cv::Mat &x1, const cv::Mat &x2);

  cv::Mat ComplexDiv(const cv::Mat &x1, const cv::Mat &x2);

  inline cv::Size FloorSizeScale(cv::Size sz, double scale_factor) {
            if (scale_factor > 0.9999 && scale_factor < 1.0001)
              return sz;
           return cv::Size(cvFloor(sz.width * scale_factor), 
                           cvFloor(sz.height * scale_factor));
         }

  inline cv::Point FloorPointScale(cv::Point p, double scale_factor) {
           if (scale_factor > 0.9999 && scale_factor < 1.0001)
              return p; 
           return cv::Point(cvFloor(p.x * scale_factor), 
                            cvFloor(p.y * scale_factor));
	 }

private:
  int trackerMode = 0;
  float padding_ = 1.5;
  float lambda_ = 1e-4;
  float output_sigma_factor_ = 0.1;
  bool features_hog_ = false;
  int features_hog_orientations_ = 9;
  bool features_gray_ = false;
  float kernel_sigma_ = 0.2;
  int kernel_poly_a_ = 1;
  int kernel_poly_b_ = 7;
  std::string kernel_type_;
  int cell_size_ = 1;
  float learning_rate = 0.075;
  cv::Rect result_rect_;
  cv::Point pos_;
  cv::Size target_sz_;
  bool resize_image_ = false;
  cv::Size window_sz_;
  cv::Mat yf_;
  cv::Mat cos_window_;
  std::vector<cv::Mat> model_xf_;
  cv::Mat model_alphaf_;
  FHoG f_hog_;
  bool isLost = false;
  bool detectTrackLost(double matchingScore);
};

#endif /* SRC_KCF_HPP_ */
