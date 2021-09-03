#!/bin/bash

echo "Installing OpenCV 4.1.0 to /usr/local ..."

if [ $PWD != '/home/student' ]
then echo -e "\e[31mYou are in the wrong path. Move to '/home/student'.\e[39m"
     return -1;
fi

echo "** Remove OpenCV3.3 first"
sudo apt-get purge *libopencv*

echo "** Install requirements"
sudo apt-get update
sudo apt-get install -y build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
sudo apt-get install -y libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev
sudo apt-get install -y python2.7-dev python3.6-dev python-dev python-numpy python3-numpy
sudo apt-get install -y libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev
sudo apt-get install -y libv4l-dev v4l-utils qv4l2 v4l2ucp
sudo apt-get install -y curl
sudo apt-get update

if [ -f "./opencv-4.1.0.tar.gz" ];
then echo -e "\e[92mArchive 'opencv-4.1.0.tar.gz' found \e[39m",
     tar -xzvf opencv-4.1.0.tar.gz -C /home/student/
     cd $HOME/opencv/
     curl -L https://github.com/opencv/opencv_contrib/archive/4.1.0.zip -o opencv_contrib-4.1.0.zip
     unzip opencv_contrib-4.1.0.zip &&
     echo "Unpacking done..."
     cd /home/student/opencv/opencv-4.1.0/release/ &&
     sudo make install
     echo -e "\e[93mRemoving zip-Folder..."
     cd /home/student/opencv/
     rm opencv_contrib-4.1.0.zip
     echo -e "\e[93mWe're done..."
else echo -e "\e[31mArchive 'opencv-4.1.0.tar.gz' not found!";
fi
