
import numpy as np
import cv2
from matplotlib import pyplot as plt
import time


MIN_MATCH_COUNT = 120

FEATURE_FILE = './board_big.png'

img1 = cv2.imread( FEATURE_FILE, cv2.COLOR_BGR2GRAY ) # queryImage

#print img1
orb = cv2.ORB()

# find the keypoints and descriptors with SIFT
kp1, des1 = orb.detectAndCompute( img1, None )
print "kp size: ", len( kp1 )
#assert( False )
for i in range( len(kp1) ):
    pt = kp1[ i ]
    x, y = pt.pt
    x = int( x )
    y = int( y )
    cv2.circle( img1, (x, y), 5, (200, 0, 0), -1 )
cv2.imshow( 'base', img1 )


# create BFMatcher object
bf = cv2.BFMatcher( cv2.NORM_HAMMING, crossCheck=True )




cap = cv2.VideoCapture(0)

while(True):
    # Capture frame-by-frame
    ret, img2 = cap.read()
    if ( not ret ):
        break

    w, h = img2.shape[:2]
    img2 = cv2.resize( img2, (h/2, w/2), interpolation = cv2.INTER_CUBIC )
    
    # Our operations on the frame come here
    gray = cv2.cvtColor( img2, cv2.COLOR_BGR2GRAY )

    kp2, des2 = orb.detectAndCompute( gray, None )
    
    # Match descriptors.
    matches = bf.match( des1, des2 )
    
    # Sort them in the order of their distance.
    matches = sorted(matches, key = lambda x:x.distance)
    
    n = len( matches )
    print "matches: ", n
    
    #if len(good)>MIN_MATCH_COUNT:
    if n > MIN_MATCH_COUNT:
        src_pts = np.float32([ kp1[m.queryIdx].pt for m in matches ]).reshape(-1,1,2)
        dst_pts = np.float32([ kp2[m.trainIdx].pt for m in matches ]).reshape(-1,1,2)
    
        M, mask = cv2.findHomography(src_pts, dst_pts, cv2.RANSAC,5.0)
        matchesMask = mask.ravel().tolist()
    
        h,w = img1.shape[:2]
        pts = np.float32([ [0,0],[0,h-1],[w-1,h-1],[w-1,0] ]).reshape(-1,1,2)
        dst = cv2.perspectiveTransform(pts,M)
    
        cv2.polylines(img2,[np.int32(dst)],True,255,3 ) #, cv2.LINE_AA)
    
    else:
        print "Not enough matches are found - %d/%d" % (n,MIN_MATCH_COUNT)
        matchesMask = None    
    
    
    for i in range( n ):
        m = matches[i]
        pt = kp2[ m.trainIdx ]
        x, y = pt.pt
        x = int( x )
        y = int( y )
        cv2.circle( img2, (x, y), 5, (200, 0, 0), -1 )
    
    cv2.imshow( 'a', img2 )


    #plt.show()
    time.sleep( 0.5 )

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()

print "Executrion finished"

