/*
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2018, Andreas ten Pas
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef OPENVINO_CLASSIFIER_H_
#define OPENVINO_CLASSIFIER_H_

// System
#include <string>
#include <vector>

// OpenVINO
#include <inference_engine.hpp>

// OpenCV
#include <opencv2/opencv.hpp>

#include <gpd/net/classifier.h>

#define MODELS_DIR "/home/wuxr/graspping/gpd-master/models/openvino"

namespace gpd {
namespace net {

/**
 *
 * \brief Classify grasp candidates as viable grasps or not with OpenVINO
 *
 * Classifies grasps as viable or not using a convolutional neural network
 * (CNN) with the OpenVINO framework.
 *
 */
class OpenVinoClassifier : public Classifier {
 public:
  /**
   * \brief Constructor.
   * \param model_dir The directory that contains the openvino network model
   * \param device The target device where the computation executes
   */
  OpenVinoClassifier(const std::string& model_file,
                     const std::string& weights_file,
                     Classifier::Device device,
                     int batch_size);

  /**
   * \brief Classify grasp candidates as viable grasps or not.
   * \param image_list the list of grasp images
   * \return the classified grasp candidates
   */
  std::vector<float> classifyImages(
      const std::vector<std::unique_ptr<cv::Mat>>& image_list);

  /**
   * \brief Return the batch size.
   * \return the batch size
   */
  int getBatchSize() const;

 private:
  static std::map<Classifier::Device, InferenceEngine::TargetDevice>
      device_map_;
  std::vector<cv::Mat> batch_image_list_;
  InferenceEngine::Blob::Ptr input_blob_, output_blob_;
  InferenceEngine::CNNNetwork network_;
  InferenceEngine::InferRequest infer_request_;
  InferenceEngine::InferencePlugin plugin_;
};

}  // namespace net
}  // namespace gpd

#endif /* OPENVINO_CLASSIFIER_H_ */
