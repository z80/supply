
import cv2
import numpy as np
import glob

import yaml

with open('./cam.yml', 'r' ) as f:
    data = yaml.load_all( f )
    print data 
    for doc in data:
        mtx   = doc[ "mtx" ]
        dist  = doc[ "dist" ]
        rvecs = doc[ "rvecs" ]
        tvecs = doc[ "tvecs" ]
#        for k,v in doc.items():
#            print k, "->", v
#            print "\n"
    

def draw(img, corners, imgpts):
    corner = tuple(corners[0].ravel())
    img = cv2.line(img, corner, tuple(imgpts[0].ravel()), (255,0,0), 5)
    img = cv2.line(img, corner, tuple(imgpts[1].ravel()), (0,255,0), 5)
    img = cv2.line(img, corner, tuple(imgpts[2].ravel()), (0,0,255), 5)
    return img
    
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)
objp = np.zeros((3*4,3), np.float32)
objp[:,:2] = np.mgrid[0:4,0:3].T.reshape(-1,2)

axis = np.float32([[3,0,0], [0,3,0], [0,0,-3]]).reshape(-1,3)

cap = cv2.VideoCapture(0)

try:
    while True:
        #img = cv2.imread(fname)
        ret, img = cap.read()
        if ( not ret ):
            break
    
        gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
        ret, corners = cv2.findChessboardCorners(gray, (4,3),None)
    
        if ret == True:
            #corners2 = cv2.cornerSubPix(gray,corners,(11,11),(-1,-1),criteria)
    
            # Find the rotation and translation vectors.
            #rvecs, tvecs, inliers = cv2.solvePnPRansac(objp, corners2, None, None)
            rvecs, tvecs, inliers = cv2.solvePnPRansac(objp, corners, None, None)
    
            # project 3D points to image plane
            imgpts, jac = cv2.projectPoints(axis, rvecs, tvecs, mtx, dist)
    
            img = draw(img,corners2,imgpts)
        cv2.imshow('img',img)
        cv2.waitKey(10)
        #k = cv2.waitKey(0) & 0xff
        #if k == 's':
        #    cv2.imwrite(fname[:6]+'.png', img)
finally:
    cap.release()
cv2.destroyAllWindows()

