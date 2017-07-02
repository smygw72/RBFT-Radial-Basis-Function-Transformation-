#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <iterator>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <glfw3.h>
#include <Eigen/Dense>
#include "RBFT.h"


#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"GLFW3.lib")
#pragma warning(disable:4996)


/* 設定 */
const int Width = 540; // ウィンドウの幅
const int Height = 540; // ウィンドウの高さ

const int TEXWIDTH = 500; /* テクスチャの幅 */
const int TEXHEIGHT = 500; /* テクスチャの高さ */
const std::string TexturePath = "texture.jpg"; // 読み込むテクスチャのパス

const double lamda = 0; // アフィン変換の程度

