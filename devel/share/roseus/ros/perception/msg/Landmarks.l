;; Auto-generated. Do not edit!


(when (boundp 'perception::Landmarks)
  (if (not (find-package "PERCEPTION"))
    (make-package "PERCEPTION"))
  (shadow 'Landmarks (find-package "PERCEPTION")))
(unless (find-package "PERCEPTION::LANDMARKS")
  (make-package "PERCEPTION::LANDMARKS"))

(in-package "ROS")
;;//! \htmlinclude Landmarks.msg.html


(defclass perception::Landmarks
  :super ros::object
  :slots (_landmarks ))

(defmethod perception::Landmarks
  (:init
   (&key
    ((:landmarks __landmarks) ())
    )
   (send-super :init)
   (setq _landmarks __landmarks)
   self)
  (:landmarks
   (&rest __landmarks)
   (if (keywordp (car __landmarks))
       (send* _landmarks __landmarks)
     (progn
       (if __landmarks (setq _landmarks (car __landmarks)))
       _landmarks)))
  (:serialization-length
   ()
   (+
    ;; perception/Landmark[] _landmarks
    (apply #'+ (send-all _landmarks :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; perception/Landmark[] _landmarks
     (write-long (length _landmarks) s)
     (dolist (elem _landmarks)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; perception/Landmark[] _landmarks
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _landmarks (let (r) (dotimes (i n) (push (instance perception::Landmark :init) r)) r))
     (dolist (elem- _landmarks)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get perception::Landmarks :md5sum-) "49e711d7c1f85a6a1a9bc1177447407c")
(setf (get perception::Landmarks :datatype-) "perception/Landmarks")
(setf (get perception::Landmarks :definition-)
      "Landmark[] landmarks

================================================================================
MSG: perception/Landmark
float32 x
float32 y
int32 signature

")



(provide :perception/Landmarks "49e711d7c1f85a6a1a9bc1177447407c")


