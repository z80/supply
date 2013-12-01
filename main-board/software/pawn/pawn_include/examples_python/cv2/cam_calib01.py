
import numpy as np
import cv2
import glob
import yaml

# termination criteria
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)

# prepare object points, like (0,0,0), (1,0,0), (2,0,0) ....,(6,5,0)
objp = np.zeros((3*4,3), np.float32)
objp[:,:2] = np.mgrid[0:4,0:3].T.reshape(-1,2)

# Arrays to store object points and image points from all the images.
objpoints = [] # 3d point in real world space
imgpoints = [] # 2d points in image plane.


def callback():
    doExit = True

#cv2.createButton( "btn", callback, None, None )

#images = glob.glob('*.jpg')
cap = cv2.VideoCapture(0)

ptsCnt = 20

while ptsCnt > 0:
    #img = cv2.imread(fname)
    #gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    ret, img = cap.read()
    if ( not ret ):
        break

    #w, h = img2.shape[:2]
    #img2 = cv2.resize( img2, (h/2, w/2), interpolation = cv2.INTER_CUBIC )
    # Our operations on the frame come here
    gray = cv2.cvtColor( img, cv2.COLOR_BGR2GRAY )

    # Find the chess board corners
    ret, corners = cv2.findChessboardCorners(gray, (4,3),None)

    # If found, add object points, image points (after refining them)
    if ret == True:
        print "Found!!!"
        print corners
        ptsCnt -= 1
        
        objpoints.append( objp )

        corners2 = cv2.cornerSubPix(gray,corners,(11,11),(-1,-1),criteria)
        print "corners2: "
        print corners2
        #imgpoints.append(corners2)
        imgpoints.append(corners)

        # Draw and display the corners
        #img = cv2.drawChessboardCorners(img, (4,3), corners2,ret)
    cv2.imshow('img',img)
    cv2.waitKey(250)

cap.release()
cv2.destroyAllWindows()

print "objpoints: "
print objpoints
print "imgpoints: "
print imgpoints
ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1],None,None)

data = {}
data[ "mtx" ]   = mtx
data[ "dist" ]  = dist
data[ "rvecs" ] = rvecs
data[ "tvecs" ] = tvecs
with open('./cam.yml', 'w') as outfile:
    outfile.write( yaml.dump(data, default_flow_style=True) )

