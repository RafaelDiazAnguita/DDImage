import os
import sys
import cv2 as cv

auto = False
#check arguments
if(len(sys.argv) < 2):
    print("Se debe introducir la ruta del directorio a explorar como mínimo.")
if(len(sys.argv) == 3):
	auto = True
	
#image path array
images = []
    
#add paths from a folder
for root, dirs, files in os.walk(sys.argv[1]):
	for name in files:
		if name.endswith((".jpg", ".png")):
			images.append(root+"/"+name)
		
#image path array to delete
to_delete = []
for i in images:
	img1 = cv.imread(i)
	for j in images:
		img2 = cv.imread(j)
		if img1.shape == img2.shape and i!=j and j>i and not(cv.bitwise_xor(img1,img2).any()):
			if(auto==False):
				cv.imshow("image1",img1)
				cv.imshow("image2",img2)
				k = cv.waitKey(0)
				if(k==27):
					to_delete.append(j)	
			else:
				to_delete.append(j)	
		
#delete		
for x in to_delete:
	os.remove(x)
		
		
  
