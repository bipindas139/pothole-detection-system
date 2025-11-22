import cv2
from ultralytics import YOLO


from firebase import Firebase
config = {
  "apiKey": "AIzaSyCXhrQpv4OPlqyRcddnk9C7YUf_vziwxQg",
  "authDomain": "potholedetection-7278d.firebaseapp.com",
  "databaseURL": "https://potholedetection-7278d-default-rtdb.firebaseio.com",
  "storageBucket": "potholedetection-7278d.appspot.com"
}
firebase = Firebase(config)
db = firebase.database()
childName = 'Pothole2k24'


# Load the YOLOv8 model
model = YOLO('last.pt')
#model = YOLO('best.pt')

# Open camera
cap = cv2.VideoCapture(0)
cap = cv2.VideoCapture('http://172.16.13.61:8080/video')


# Loop through the video frames
while cap.isOpened():
    # Read a frame from the video
    success, frame = cap.read()

    if success:
        # Run YOLOv8 inference on the frame
        results = model(frame)
        #print(results)
        # Visualize the results on the frame
        annotated_frame = results[0].plot()

        # Display the annotated frame
        cv2.imshow("YOLOv8 Inference", annotated_frame)
        
        #results = self.model.predict(img, stream=True)
        Marine_Object_list=[]
        
        for result in results:                                         # iterate results
            boxes = result.boxes.cpu().numpy()                         # get boxes on cpu in numpy
            for box in boxes:                                          # iterate boxes
                r = box.xyxy[0].astype(int)                            # get corner points as int
                area = (r[2]-r[0])*(r[3]-r[1])
                print(f'area:{area}')
                Object_name = result.names[int(box.cls[0])]
                print(Object_name)

                db.child(childName).child('yolo_message').set({'msg' : str(area)})
                db.child(childName).child('yolo_msgFlag').set('1')

    

        # Break the loop if 'q' is pressed
        if cv2.waitKey(1) & 0xFF == ord("q"):
            break
    else:
        # Break the loop if the end of the video is reached
        break

# Release the video capture object and close the display window
cap.release()
cv2.destroyAllWindows()
