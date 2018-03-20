from PIL import Image
import pytesseract
import pyttsx3
import argparse
import numpy as np
import cv2
import os
import sys
import pyttsx3

imgname = "C:\\Users\\sneha\\Desktop\\test.png"
img = cv2.imread(imgname)
gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

mser = cv2.MSER_create()
mser.setMinArea(50)
mser.setMaxArea(800)

coordinates, bboxes = mser.detectRegions(gray)

vis = img.copy()
coords = []

i, a2, b2, a3, b3 = 0, 0, 0, 0, 0
for coord in coordinates:

    bbox = cv2.boundingRect(coord)
    x, y, w, h = bbox
    if w < 5 or h < 5 or w / h > 6 or h / w > 6:
        continue
    vis = cv2.rectangle(vis, (x, y), (x + w + 4, y + h + 4), (0, 255, 0), 1)

    if i is 0:
        a1, b1 = x, y
    else:
        a2, b2 = x, y
        if i == 1:
            a3, b3 = x, y
        elif a3 <= a2:
            a3 = a2 + w
        elif b3 <= b2:
            b3 = b2 + h
        elif a1 >= a2:
            a1 = a2
        elif b1 >= b2:
            b1 = b2
    i += 1
    coords.append(coord)

img = cv2.rectangle(img, (a1 - w, b1 - h), (a3, b3), (255, 0, 0), 1)

colors = [[43, 43, 200], [43, 75, 200], [43, 106, 200], [43, 137, 200], [43, 169, 200], [43, 200, 195], [43, 200, 163],
          [43, 200, 132], [43, 200, 101], [43, 200, 69], [54, 200, 43], [85, 200, 43], [116, 200, 43], [148, 200, 43],
          [179, 200, 43], [200, 184, 43], [200, 153, 43], [200, 122, 43], [200, 90, 43], [200, 59, 43], [200, 43, 64],
          [200, 43, 95], [200, 43, 127], [200, 43, 158], [200, 43, 190], [174, 43, 200], [142, 43, 200], [111, 43, 200],
          [80, 43, 200], [43, 43, 200]]
np.random.seed(0)
canvas1 = img.copy()
canvas2 = cv2.cvtColor(gray, cv2.COLOR_GRAY2BGR)
img1 = np.zeros_like(img)

for cnt in coords:
    xx = cnt[:, 0]
    yy = cnt[:, 1]
    color = colors[np.random.choice(len(colors))]
    canvas1[yy, xx] = color
    canvas2[yy, xx] = color
    img1[yy, xx] = color

# canvas3 = cv2.cvtColor(canvas3, cv2.COLOR_BGR2GRAY)
# ret, canvas3 = cv2.threshold(canvas3,25,255,cv2.THRESH_BINARY_INV | cv2.THRESH_OTSU)
# cv2.imwrite("result1.png", canvas1)
# cv2.imwrite("result2.png", canvas2)
cv2.imwrite("result3.png", img1)
crop_img = img[b1:b3, a1:a3]
cv2.imshow("original image", img)
cv2.imshow("bbox image", vis)
# gray = cv2.threshold(canvas3, 0, 255,cv2.THRESH_BINARY | cv2.THRESH_OTSU)[1]
filename = "{}.png".format(os.getpid())
cv2.imwrite(filename, crop_img)

text = pytesseract.image_to_string(Image.open(filename), lang="eng+eng1+eng2")
os.remove(filename)
print(text)
fo = open("output.txt", 'w+', 3)
fo.write(text)
print(fo.read())
# with open("output.txt",'w',3, encoding = 'utf-8') as f:
#       print(text,file=f)

# cv2.imshow("original image", img)
# cv2.waitKey(0)

engine = pyttsx3.init()
rate = engine.getProperty('rate')
engine.setProperty('rate', 115)
with open('output.txt', 'r', 3, encoding='utf-8') as f:
    for word in f:
        print(word)
        engine.say(word)
        engine.runAndWait()

