;; Auto-generated. Do not edit!


(when (boundp 'perception::Landmark)
  (if (not (find-package "PERCEPTION"))
    (make-package "PERCEPTION"))
  (shadow 'Landmark (find-package "PERCEPTION")))
(unless (find-package "PERCEPTION::LANDMARK")
  (make-package "PERCEPTION::LANDMARK"))

(in-package "ROS")
;;//! \htmlinclude Landmark.msg.html


(defclass perception::Landmark
  :super ros::object
  :slots (_x _y _signature ))

(defmethod perception::Landmark
  (:init
   (&key
    ((:x __x) 0.0)
    ((:y __y) 0.0)
    ((:signature __signature) 0)
    )
   (send-super :init)
   (setq _x (float __x))
   (setq _y (float __y))
   (setq _signature (round __signature))
   self)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:signature
   (&optional __signature)
   (if __signature (setq _signature __signature)) _signature)
  (:serialization-length
   ()
   (+
    ;; float32 _x
    4
    ;; float32 _y
    4
    ;; int32 _signature
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _x
       (sys::poke _x (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _y
       (sys::poke _y (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; int32 _signature
       (write-long _signature s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _x
     (setq _x (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _y
     (setq _y (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; int32 _signature
     (setq _signature (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get perception::Landmark :md5sum-) "2e3688e586de9cd73537826cf84070c3")
(setf (get perception::Landmark :datatype-) "perception/Landmark")
(setf (get perception::Landmark :definition-)
      "float32 x
float32 y
int32 signature

")



(provide :perception/Landmark "2e3688e586de9cd73537826cf84070c3")


