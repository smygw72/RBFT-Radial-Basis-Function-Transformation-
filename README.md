# RBFT-Radial-Basis-Funcion-Transformation

Implement of "Image warping" using RBFT(Radial Basis Function Transformation).
Detail is at https://qiita.com/smygw72/items/ccccfea5a0de5cf3e568 (in Japanese).

# System
You can control the deformation of the image by moving the anchor.


The program was made using GLFW, OpenCV and Eigen.
OpenCV was used for reading texture images.


## How to use
- Setting (in stdafx.h)
  - Texture image
  - Parameters that allow affine transformation.
- Mouse
  - Left: Control of the anchor.
  - Right: Add or remove an anchor.
- Key
  - "S": Initialize the setting
  - "T": Visualize the texture
  - "P": Visualize anchor points and points cloud.
  - "esc": Quit the program.


## Enviroment
C++, Visual Studio 2015 (Release x64 mode)

Because it is written in relative path, you can execute it as it is




## Reference
["Image Warping by Radial Basis
Functions: Application to Facial
Expressions" Nur Arad, Nira Dyn, Daniel Reisfeld
, Yehezkel Yeshurun
](https://www.researchgate.net/profile/Daniel_Reisfeld/publication/2255034_Image_Warping_by_Radial_Basis_Functions_Application_to_Facial_Expressions/links/02e7e51f7943d959ec000000.pdf)
