/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2017, Cyrille Morin
 *  Copyright (c) 2011, Willow Garage, Inc.
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
 *   * Neither the name of Willow Garage nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
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
 *********************************************************************/

/* Author: Jon Binney, Ioan Sucan, Cyrille Morin */

// #ifndef MOVEIT_PERCEPTION_POINTCLOUD_OCTOMAP_UPDATER_
// #define MOVEIT_PERCEPTION_POINTCLOUD_OCTOMAP_UPDATER_

#include <ros/ros.h>
#include <tf/tf.h>
#include <tf/message_filter.h>
#include <message_filters/subscriber.h>
#include <octomap_msgs/conversions.h>
#include <moveit/occupancy_map_monitor/occupancy_map_updater.h>
#include <moveit/point_containment_filter/shape_mask.h>

namespace occupancy_map_monitor
{
class ExternalOctomapUpdater : public OccupancyMapUpdater
{
public:
  ExternalOctomapUpdater();
  virtual ~ExternalOctomapUpdater();

  virtual bool setParams(XmlRpc::XmlRpcValue& params);

  virtual bool initialize();
  virtual void start();
  virtual void stop();
  virtual ShapeHandle excludeShape(const shapes::ShapeConstPtr& shape);
  virtual void forgetShape(ShapeHandle handle);



private:

  void octoMsgCallback(const octomap_msgs::Octomap::ConstPtr& octo_msg);
  void stopHelper();

  ros::NodeHandle root_nh_;
  ros::NodeHandle private_nh_;
  boost::shared_ptr<tf::Transformer> tf_;

  /* params */
  std::string octomap_topic;

  message_filters::Subscriber<octomap_msgs::Octomap>* octomap_subscriber_;
};
}

// #endif
