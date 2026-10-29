import numpy as np
import cv2 as cv

imgColor = cv.imread('./baboon.png')

print(imgColor.shape[2])

if imgColor is not None:
  imgGray =cv.cvtColor(imgColor, cv.COLOR_BGR2GRAY)
  # print(imgGray.shape[2])

cv.imshow("Imagem original", imgColor)
cv.imshow("Imagem grayscale", imgGray)

cv.waitKey(0)