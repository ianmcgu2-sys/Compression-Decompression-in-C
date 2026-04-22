#lang racket

(define (compress)
  (define (ch i lst)
    (define pc (peek-char))
    (cond
      [(eof-object? pc) (void)]
      [(char-whitespace? pc) (display (read-char)) (ch i lst)]
      [(char-alphabetic? pc) (define rw (list->string (read-word)))
                             (define inlist (assoc rw lst))
                             (cond
                               [(not (equal? inlist false))
                                (display (second inlist)) (ch i lst)]
                               [else (display rw) (ch (add1 i) (cons (list rw i) lst))])]))
  (ch 0 '()))

(define (read-word)
  (define pc (peek-char))
  (if (char-alphabetic? pc)
      (cons (read-char) (read-word))
      '()))

(compress)