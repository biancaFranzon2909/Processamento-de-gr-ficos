import numpy as np
import cv2 as cv

imgColor = cv.imread('./baboon.png')

print(imgColor.shape[2])

if imgColor is not None:
  imghsv =cv.cvtColor(imgColor, cv.COLOR_BGR2HSV)
  # print(imgGray.shape[2])
  h, s, v = cv.split(imghsv)
  s_modificado = cv.multiply(s, 1.5)
  imgSaturada = cv.merge([h, s_modificado, v])
  imgSaturada = cv.cvtColor(imgSaturada, cv.COLOR_HSV2BGR)
  v_escurecido = cv.multiply(v, 0.5)
  imgEscurecida = cv.merge([h, s, v_escurecido])
  imgEscurecida = cv.cvtColor(imgEscurecida, cv.COLOR_HSV2BGR)
  h_modificado = cv.add(-h, 359)
  imgSepia = cv.merge([h_modificado, s, v])
  imgSepia = cv.cvtColor(imgSepia, cv.COLOR_HSV2BGR)

cv.imshow("Imagem original", imgColor)
cv.imshow("Imagem saturada", imgSaturada)
cv.imshow("Imagem ESCURECIDA", imgEscurecida)
cv.imshow("Imagem Sépia", imgSepia)

cv.waitKey(0)