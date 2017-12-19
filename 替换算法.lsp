(defun fifo (lst num)
	   (let ((Queue nil))
	     (dolist (ele lst)
	       (if (position ele Queue :test #'equal)
		   (format t "~A Hit!!!~%" Queue)
		   (if (>= (length Queue) num)
		       (progn
			 (setf Queue (remove (nth (- num 1) Queue) Queue))
			 (push ele Queue)
			 (format t "~A~%" Queue))
		       (progn
			 (push ele Queue)
			 (format t "~A~%" Queue)))))))
			 
(defun lru (lst num)
	   (let ((Queue nil) (pos nil) (sum 0))
	     (dolist (ele lst)
	       (setf pos (position ele Queue :test #'equal))
	       (if pos
		   (progn
		     (setf Queue (cons ele (remove ele Queue)))
		     (setf sum (+ sum 1))
		     (format t "~A Hit!!!~%" Queue))
		   (if (>= (length Queue) num)
		       (progn
			 (setf Queue (remove (nth (- num 1) Queue) Queue))
			 (push ele Queue)
			 (format t "~A~%" Queue))
		       (progn
			 (push ele Queue)
			 (format t "~A~%" Queue)))))
	     (format t "hit :~Atimes~%hit rate:~A~%" sum (/ sum (length lst)))))